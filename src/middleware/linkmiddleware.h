#pragma once

#include <QObject>

#include "../base/middleware.h"
#include "../session.h"

class LinkMiddleware : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit LinkMiddleware(QObject *parent);
    QSharedPointer<Action> process(const QSharedPointer<Action>& action);
private:
    void processCreateLink(Session& session);
private:
    QString m_PublicIp, m_LocalIp;
    int m_Counter = INT_MIN;
};

