#pragma once

#include <QSharedPointer>

class Action;

class Store {
public:
    virtual ~Store() = default;
    virtual void process(const QSharedPointer<Action>& action) = 0;
protected:
    Store() = default;
};

