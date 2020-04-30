#pragma once

#include <QObject>
#include <QQueue>
#include <QSharedPointer>
#include <QHash>

#include "action.h"

class Store;
class Middleware;


/*!
 *      \brief The Dispatcher class is a common flux dispatcher
 *      Dispatcher manages all actions: it provides actions to all registered stores and middlewares
 *      \warning Dispatcher is a singleton
 */
class Dispatcher : public QObject {
    Q_OBJECT
public:

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

    /*!
     * Return Dispatcher instance
     */
    static Dispatcher& get() {
        static Dispatcher instance;
        return instance;
    }

    /*!
     * Registers store in dispathcer
     * \deprecated Returns int as store index in vector
     */
    int addStore(const QSharedPointer<Store>& store);

    /*!
     * Registers middleware in dispathcer
     * \deprecated Returns int as middleware index in vector
     */
    int addMiddleware(const QSharedPointer<Middleware>& middleware);

    /*!
     * Removes middleware from dispatcher
     */
    void removeMiddleware(const QSharedPointer<Middleware>& middleware);
    /*!
     * Removes store from dispatcher
     */
    void removeStore(const QSharedPointer<Store>& store);

    /*!
     * Adds Actions to queue and emits a newAction signal
     */
    template<class... Args>
    void dispatch(Args&&... args) {
        m_Actions.enqueue(QSharedPointer<Action>(std::forward<Args>(args)...));
        emit newAction();
    }

signals:
    /*!
     * Signal emited when new actions were added
     */
    void newAction();

private:
    Dispatcher();
    ~Dispatcher() = default;
    /*!
     *  Handles all added action
     */
    void handleAction();
private:
    QQueue<QSharedPointer<Action>> m_Actions;
    QVector<QSharedPointer<Middleware>> m_Middlewares;
    QVector<QSharedPointer<Store>> m_Stores;
};

