#include "dispatcher.h"

#include "store.h"
#include "middleware.h"


int Dispatcher::addStore(const QSharedPointer<Store>& store) {
    m_Stores.append(store);
    return m_Stores.size() - 1;
}

int Dispatcher::addMiddleware(const QSharedPointer<Middleware>& middleware) {
    m_Middlewares.append(middleware);
    return m_Middlewares.size() - 1;
}

void Dispatcher::removeMiddleware(const QSharedPointer<Middleware>& middleware) {
    m_Middlewares.removeOne(middleware);
}

void Dispatcher::removeStore(const QSharedPointer<Store>& store) {
    m_Stores.removeOne(store);
}

Dispatcher::Dispatcher() {
    QObject::connect(this, &Dispatcher::newAction, this, [=](){
        this->handleAction();
    }, Qt::QueuedConnection);
}

void Dispatcher::handleAction() {
    while (!m_Actions.isEmpty()) {
        auto action = m_Actions.dequeue();
        for(auto& middleware : m_Middlewares) {
            action = middleware->process(action);
        }
        for(auto& store : m_Stores) {
            store->process(action);
        }
    }
}
