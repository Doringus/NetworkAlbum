#include "servernotificationstore.h"

#include <QMenu>
#include <QAction>

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "sessionsstore.h"

ServerNotificationStore::ServerNotificationStore() {

}

ServerNotificationStore::~ServerNotificationStore() {
    if(m_TrayIcon != nullptr) {
        m_TrayIcon->hide();
    }
    m_TrayMenu->deleteLater();
}

void ServerNotificationStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::RECEIVE_MESSAGE: {
            processReceiveMessage(action->getData<networkMessage_t>());
            break;
        }
        case ActionType::RECEIVE_SYNC_DATA: {
            processReceiveSync(action->getData<networkMessage_t>());
            break;
        }
        case ActionType::SAVE_SETTINGS: {
            processSaveSettings(action->getData<QPair<bool, bool>>());
            break;
        }
        case ActionType::CLOSE_WINDOW: {
            processCloseWindow();
            break;
        }
    }
}

void ServerNotificationStore::createTray() {
    m_TrayMenu = new QMenu();
    QAction *openAction = new QAction(tr("Открыть"), m_TrayMenu);
    QAction *closeAction = new QAction(tr("Выйти"), m_TrayMenu);
    connect(openAction, &QAction::triggered, this, &ServerNotificationStore::showWindow);
    connect(closeAction, &QAction::triggered, this, &ServerNotificationStore::closeWindow);
    m_TrayMenu->addAction(openAction);
    m_TrayMenu->addAction(closeAction);
    m_TrayIcon = new QSystemTrayIcon(this);
    m_TrayIcon->setContextMenu(m_TrayMenu);
    m_TrayIcon->setIcon(QIcon(":/res/albumIcon.jpg"));
    m_TrayIcon->show();
}

bool ServerNotificationStore::getShowNotifications() {
    return m_HasNotifications;
}

bool ServerNotificationStore::getClosableWindow() {
    return m_IsWindowClosable;
}

void ServerNotificationStore::processReceiveMessage(networkMessage_t &&message) {
    if(Qt::WindowMinimized && m_HasNotifications) {
        m_TrayIcon->showMessage("Новое сообщение", "Вам пришло новое сообщение от клиента",
                                QSystemTrayIcon::MessageIcon(QSystemTrayIcon::MessageIcon::Information));
    }
}

void ServerNotificationStore::processReceiveSync(networkMessage_t &&message) {
    if(Qt::WindowMinimized && m_HasNotifications) {
        m_TrayIcon->showMessage("Синхронизация", "Клиент синхронизировал данные",
                                QSystemTrayIcon::MessageIcon(QSystemTrayIcon::MessageIcon::Information));
    }
}

void ServerNotificationStore::processSaveSettings(QPair<bool, bool> msg) {
    if(m_HasNotifications != msg.first) {
        m_HasNotifications = msg.first;
        emit showNotificationsChanged();
    }
    if(m_IsWindowClosable != msg.second) {
        m_IsWindowClosable = msg.second;
        emit closableWindowChanged();
    }
}

void ServerNotificationStore::processCloseWindow() {
    m_TrayIcon->showMessage("Фоновый режим", "Программа будет работать в фоновом режиме. Для отключения этой опции зайдите в настройки",
                            QSystemTrayIcon::MessageIcon(QSystemTrayIcon::MessageIcon::Information));

}


