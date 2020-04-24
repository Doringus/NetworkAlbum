#include "dispatcher.h"

#include "store.h"
#include "middleware.h"


int Dispatcher::addStore(const QString& storeName, const QSharedPointer<Store>& store) {
    m_Stores.insert(storeName, store);
    return m_Stores.size() - 1;
}

int Dispatcher::addMiddleware(const QString& middlewareName, const QSharedPointer<Middleware>& middleware) {
    m_Middlewares.insert(middlewareName, middleware);
    return m_Middlewares.size() - 1;
}

void Dispatcher::removeMiddleware(const QString& middlewareName) {
    m_Middlewares.remove(middlewareName);
}

void Dispatcher::removeStore(const QString& storeName) {
    m_Stores.remove(storeName);
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
