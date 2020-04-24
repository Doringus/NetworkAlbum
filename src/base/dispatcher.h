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

    int addStore(const QString& storeName, const QSharedPointer<Store>& store);
    int addMiddleware(const QString& middlewareName, const QSharedPointer<Middleware>& middleware);
    void removeMiddleware(const QString& middlewareName);
    void removeStore(const QString& storeName);

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
    QHash<QString, QSharedPointer<Middleware>> m_Middlewares;
    QHash<QString, QSharedPointer<Store>> m_Stores;
};

