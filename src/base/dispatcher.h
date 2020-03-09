#pragma once

#include <QObject>
#include <QQueue>
#include <QSharedPointer>

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

    void addStore(QSharedPointer<Store> store);
    void addMiddleware(QSharedPointer<Middleware> middleware);

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
    QVector<QSharedPointer<Store>> m_Stores;
    QVector<QSharedPointer<Middleware>> m_Middlewares;
};

