#pragma once

#include <QObject>
#include <QQueue>

#include "action.h"

class Store;
class Middleware;

class Dispatcher : public QObject {
    Q_OBJECT
public:

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    static Dispatcher& get() {
        return m_Instance;
    }

    void addStore();
    void addMiddleware();

    template<class... Args>
    void dispatch(Args&&... args) {
        m_Actions.enqueue(std::make_shared<Action>(std::forward<Args>(args)...));
    }

signals:
    void newAction();

private:
    Dispatcher();
    void handleAction();
private:
    static Dispatcher m_Instance;
    QQueue<std::shared_ptr<Action>> m_Actions;
    QVector<std::shared_ptr<Store>> m_Stores;
    QVector<std::shared_ptr<Middleware>> m_Middlewares;
};

