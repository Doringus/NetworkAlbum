#include "sessionsstore.h"

#include <QDir>
#include <QFuture>
#include <QFutureWatcher>
#include <QJsonArray>
#include <QDebug>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"
#include "../imageconverter.h"

SessionsStore::SessionsStore() {
    m_ImageMover = new ImageMover(this);
}


void SessionsStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            if(action->getErrorString() == "") {
                processCreateSession(action->getData<Session>());
            }
            break;
        }
        case ActionType::OPEN_ALBUM: {
            m_CurrentAlbumIndex = action->getData<int>();
            break;
        }
        case ActionType::CLIENT_CONNECTED: {
            processSendImages(action->getData<networkMessage_t>());
            break;
        }
        case ActionType::RECEIVE_SYNC_DATA: {
            processReceiveSync(action->getData<networkMessage_t>());
            break;
        }
        case ActionType::BEGIN_SEND_MESSAGE: {
            processSendMessage(action->getData<QString>());
            break;
        }
        case ActionType::RECEIVE_MESSAGE: {
            processReceiveMessage(action->getData<networkMessage_t>());
            break;
        }
    }
}

const Session& SessionsStore::getCurrentSession() {
    return m_Sessions.at(m_CurrentAlbumIndex);
}

const Session &SessionsStore::getSession(int index) {
    return m_Sessions.at(index);
}

void SessionsStore::processCreateSession(const Session& session) {
    qDebug() << "Sessions store" << session.getConversation();
    if(m_Sessions.contains(session)) {
        return;
    }
    m_Sessions.append(session);
    Dispatcher::get().dispatch(new Action(ActionType::REGISTER_LINK, QVariant::fromValue(session.getSessionId())));
}

void SessionsStore::processSendImages(networkMessage_t&& message) {
    qDebug() << "Starting image sending process" << message.clientLink;
    auto it = std::find_if(m_Sessions.begin(), m_Sessions.end(), [=](Session session){
        return session.getSessionId() == message.clientLink;
    });
    if(it != m_Sessions.end()) {
        qDebug() << "Session found";
        qDebug() << it->getAlbumPath().path();
        QDir albumDir(it->getAlbumPath().toLocalFile());
        QFileInfoList paths = albumDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
        ImageConventer scaler;
        QFuture<QList<QJsonObject>> future;
        QFutureWatcher<QList<QJsonObject>> *watcher = new QFutureWatcher<QList<QJsonObject>>();
        if(message.data.toBool()) {
            future = scaler.scaleAndConvertImages(paths, it->getCompression());
        } else {
            future = scaler.convertImages(paths);
        }
        connect(watcher, &QFutureWatcher<QList<QJsonValue>>::finished, [message, future, watcher]() mutable {
            QList<QJsonObject> images = future.result();
            message.data = QVariant::fromValue<QList<QJsonObject>>(images);
            Dispatcher::get().dispatch(new Action(ActionType::SEND_IMAGES, QVariant::fromValue(message)));
            watcher->deleteLater();
        });
        watcher->setFuture(future);
    }
}

void SessionsStore::processReceiveSync(const networkMessage_t &&message) {
    auto it = std::find_if(m_Sessions.begin(), m_Sessions.end(), [=](Session session) {
        return session.getSessionId() == message.clientLink;
    });
    if(it != m_Sessions.end()) {
        QJsonArray arr = message.data.toJsonArray();
        QList<QPair<QString, QString>> changes;
        for(int i = 0; i < arr.size(); ++i) {
            QJsonObject changeObject = arr.at(i).toObject();
            changes.append({changeObject.value("NewPath").toString(), changeObject.value("OldPath").toString()});
        }
        m_ImageMover->moveImageAsynch(changes, it->getAlbumPath().toLocalFile());
    }
}

void SessionsStore::processSendMessage(const QString &message) {
    m_Sessions.at(m_CurrentAlbumIndex).getConversation()->add(message, true);
    networkMessage_t networkMessage;
    networkMessage.clientLink = SessionsStore::get().getCurrentSession().getSessionId();
    networkMessage.data = message.trimmed();
    Dispatcher::get().dispatch(new Action(ActionType::SEND_MESSAGE, QVariant::fromValue(networkMessage)));
}

void SessionsStore::processReceiveMessage(const networkMessage_t &&message) {
    auto it = std::find_if(m_Sessions.begin(), m_Sessions.end(), [=](Session session) {
        return session.getSessionId() == message.clientLink;
    });
    if(it != m_Sessions.end()){
        it->getConversation()->add(message.data.toString(), false);
    }
}
