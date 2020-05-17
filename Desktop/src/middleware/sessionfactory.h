#pragma once

#include <QObject>

#include "../base/middleware.h"

class Session;

/*!
 *      \brief The SessionFactory class provides interface for creating and validating session data
 */
class SessionFactory : public QObject, public Middleware {
    Q_OBJECT
public:
    explicit SessionFactory(QObject *parent = nullptr);
    ~SessionFactory();
    QSharedPointer<Action> process(const QSharedPointer<Action>& action);
private:
    /*!
     *  Creates session. Data - list with album url, reserve folder and image compression
     *  Invokes copy folder if option is on
     */
    Session processCreateSession(QList<QVariant> data);
    /*!
     * Validates provided url, and returns error string
     */
    QString validateUrl(QUrl url);
    /*!
     * Creates reserve folder and copies images from original album into it
     */
    bool copyFolder(const QString& from, const QString& to);
private:
    QList<QUrl> m_SessionsUrlCache;
signals:

};

