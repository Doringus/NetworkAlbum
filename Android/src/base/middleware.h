#pragma once

#include <QSharedPointer>

class Action;

/*!
 *      \brief The Middleware class is abstract interface for flux middlewares
 */
class Middleware {
public:
    virtual ~Middleware() = default;

    /*!
     * Processes action and returns it
     */
    virtual QSharedPointer<Action> process(const QSharedPointer<Action>& action) = 0;
protected:
    Middleware() = default;
};

