#pragma once

#include <QObject>
#include <QSystemTrayIcon>

#include "../base/store.h"
#include "../network/networkactiontypes.h"

class ServerNotificationStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showNotifications READ getShowNotifications NOTIFY showNotificationsChanged)
    Q_PROPERTY(bool closableWindow READ getClosableWindow NOTIFY closableWindowChanged)
public:
    ~ServerNotificationStore();
    ServerNotificationStore(const ServerNotificationStore&) = delete;
    ServerNotificationStore& operator=(const ServerNotificationStore&) = delete;

    static ServerNotificationStore& get() {
        static ServerNotificationStore instance;
        return instance;
    }

    void process(const QSharedPointer<Action>& action);

    void createTray();
    bool getShowNotifications();
    bool getClosableWindow();
signals:
    void showNotificationsChanged();
    void closableWindowChanged();
    void showWindow();
    void closeWindow();
private:
    ServerNotificationStore();
    void processReceiveMessage(networkMessage_t&& message);
    void processReceiveSync(networkMessage_t&& message);
    void processSaveSettings(QPair<bool, bool> msg);
private:
    QSystemTrayIcon *m_TrayIcon;
    QMenu *m_TrayMenu;
    bool m_HasNotifications;
    bool m_IsWindowClosable = true;
};

