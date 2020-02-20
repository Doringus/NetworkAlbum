#include "dispatcher.h"

#include "store.h"
#include "middleware.h"


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
