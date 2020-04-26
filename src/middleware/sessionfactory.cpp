#include "sessionfactory.h"

#include <QDir>

#include "../action/actiontypes.h"
#include "../session.h"
#include "../base/action.h"

SessionFactory::SessionFactory(QObject *parent) : QObject(parent) {

}

SessionFactory::~SessionFactory() {

}

QSharedPointer<Action> SessionFactory::process(const QSharedPointer<Action>& action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            QString errorString = validateUrl(action->getData<QList<QVariant>>().at(0).toUrl());
            Session session = processCreateSession(action->getData<QList<QVariant>>());
            QVariant sessionData = QVariant::fromValue(session);
            action->setData(sessionData);
            action->setErrorString(errorString);
            break;
        }
        case ActionType::CLOSE_SESSION: {
            m_SessionsUrlCache.removeAt(action->getData<int>());
            break;
        }
    }
    return action;
}

Session SessionFactory::processCreateSession(QList<QVariant> data) {
    Session session(data.at(0).toUrl(), data.at(1).toBool(), data.at(2).toDouble());
    if(session.hasCopy() && !copyFolder(session.getAlbumPath().toLocalFile(), session.getAlbumReservePath().toLocalFile())) {
        session.setHasCopy(false);
    }
    return session;
}

QString SessionFactory::validateUrl(QUrl url) {
    if(url.isEmpty()) {
        return "Не указана папка альбома!";
    } else if(m_SessionsUrlCache.contains(url)) {
        return "Папка уже используется!";
    } else {
        m_SessionsUrlCache.append(url);
        return QString();
    }
}

bool SessionFactory::copyFolder(const QString &from, const QString &to) {
    bool success = false;
    QDir sourceDir(from);
    if(!sourceDir.exists()) {
        return false;
    }
    QDir destDir(to);
    if(destDir.exists()) {
        destDir.removeRecursively();
    }
    destDir.mkdir(to);
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++) {
        QString srcName = from + "/" + files[i];
        QString destName = to + "/" + files[i];
        success = QFile::copy(srcName, destName);
        if(!success) {
            return false;
        }

    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++) {
        QString srcName = from + "/" + files[i];
        QString destName = to + "/" + files[i];
        success = copyFolder(srcName, destName);
        if(!success) {
            return false;
        }
    }
    return true;
}

