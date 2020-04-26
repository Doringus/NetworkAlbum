#pragma once

#include <QObject>

#include "../base/middleware.h"

class Session;

class SessionFactory : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit SessionFactory(QObject *parent = nullptr);
    ~SessionFactory();
    QSharedPointer<Action> process(const QSharedPointer<Action>& action);
private:
    Session processCreateSession(QList<QVariant> data);
    QString validateUrl(QUrl url);
    bool copyFolder(const QString& from, const QString& to);
private:
    QList<QUrl> m_SessionsUrlCache;
signals:

};

