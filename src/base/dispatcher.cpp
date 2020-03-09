#include "dispatcher.h"

#include "store.h"
#include "middleware.h"


void Dispatcher::addStore(QSharedPointer<Store> store) {
    m_Stores.append(store);
}

void Dispatcher::addMiddleware(QSharedPointer<Middleware> middleware) {
    m_Middlewares.append(middleware);
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
