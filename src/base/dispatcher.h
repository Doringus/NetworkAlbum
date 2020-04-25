#pragma once

#include <QObject>
#include <QQueue>
#include <QSharedPointer>
#include <QHash>

#include "action.h"

class Store;
class Middleware;

class Dispatcher : public QObject {
    Q_OBJECT
public:

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    static Dispatcher& get() {
        static Dispatcher instance;
        return instance;
    }

    int addStore(const QSharedPointer<Store>& store);
    int addMiddleware(const QSharedPointer<Middleware>& middleware);
    void removeMiddleware(const QSharedPointer<Middleware>& middleware);
    void removeStore(const QSharedPointer<Store>& store);

    template<class... Args>
    void dispatch(Args&&... args) {
        m_Actions.enqueue(QSharedPointer<Action>(std::forward<Args>(args)...));
        emit newAction();
    }

signals:
    void newAction();

private:
    Dispatcher();
    ~Dispatcher() = default;
    void handleAction();
private:
    QQueue<QSharedPointer<Action>> m_Actions;
    QVector<QSharedPointer<Middleware>> m_Middlewares;
    QVector<QSharedPointer<Store>> m_Stores;
};

