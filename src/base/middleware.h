#pragma once

#include <QSharedPointer>

class Action;

class Middleware {
public:
    virtual ~Middleware() = default;
    virtual QSharedPointer<Action> process(const QSharedPointer<Action>& action) = 0;
protected:
    Middleware() = default;
};

