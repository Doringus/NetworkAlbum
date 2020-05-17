#pragma once

#include <QSharedPointer>

class Action;

/*!
 *      \brief The Store class is abstract interface for flux stores
 *      Store is last stage for data stream in application
 */
class Store {
public:
    virtual ~Store() = default;
    /*!
     * Processes action
     */
    virtual void process(const QSharedPointer<Action>& action) = 0;
protected:
    Store() = default;
};

