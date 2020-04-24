#pragma once

#include <QObject>

#include "../base/store.h"

class RootStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showCreatePopup READ getShowCreatePopup NOTIFY showCreatePopupChanged)
    Q_PROPERTY(bool showOpenPopup READ getShowOpenPopup NOTIFY showOpenPopupChanged)
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
public:
    RootStore(const RootStore&) = delete;
    RootStore& operator=(const RootStore&) = delete;

    static RootStore& get() {
        static RootStore instance;
        return instance;
    }
    void process(const QSharedPointer<Action>& action);
    bool getShowCreatePopup();
    bool getShowOpenPopup();
    QString getErrorString();
signals:
    void showCreatePopupChanged();
    void showOpenPopupChanged();
    void errorStringChanged();

    void sessionCreated();
private:
    RootStore() = default;
    void processShowError(const QString& errorString);
    void setCreatePopupVisibility(bool visible);
    void setOpenPopupVisibility(bool visible);
private:
    bool m_ShowCreatePopup;
    bool m_ShowOpenPopup;
    QString m_ErrorString;
    bool m_SessionCreated = false;
};

