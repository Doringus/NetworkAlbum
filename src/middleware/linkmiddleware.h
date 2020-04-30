#pragma once

#include <QObject>

#include "../base/middleware.h"
#include "../session.h"

/*!
 *      \brief The LinkMiddleware class provides interface for link creation
 *      Link contains ip and session id. Session id is simple number in base64
 */
class LinkMiddleware : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit LinkMiddleware(QObject *parent);
    QSharedPointer<Action> process(const QSharedPointer<Action>& action);
private:
    /*!
     * Creates link
     */
    void processCreateLink(Session& session);
private:
    QString m_PublicIp, m_LocalIp;
    int m_Counter = INT_MIN;
};

