#pragma once

#include <QObject>

#include "../base/store.h"

/*!
 *      \brief The RootStore class is store for main application page.
 *      RootStore is like main domain of application
 */
class RootStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showCreatePopup READ getShowCreatePopup NOTIFY showCreatePopupChanged)
    Q_PROPERTY(bool showOpenPopup READ getShowOpenPopup NOTIFY showOpenPopupChanged)
    Q_PROPERTY(QString errorString READ getErrorString NOTIFY errorStringChanged)
    Q_PROPERTY(bool showHelpPopup READ getShowHelpPopup NOTIFY showHelpPopupChanged)
    Q_PROPERTY(bool showGetImagesPopup READ getShowGetImagesPopup NOTIFY showGetImagesPopupChanged)
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
    bool getShowHelpPopup();
    bool getShowGetImagesPopup();
    QString getErrorString();
signals:
    void showCreatePopupChanged();
    void showOpenPopupChanged();
    void errorStringChanged();
    void showHelpPopupChanged();
    void showGetImagesPopupChanged();

    void sessionCreated();
private:
    RootStore() = default;
    void processShowError(const QString& errorString);
    void setCreatePopupVisibility(bool visible);
    void setOpenPopupVisibility(bool visible);
    void setHelpPopupVisibility(bool visible);
private:
    bool m_ShowCreatePopup;
    bool m_ShowOpenPopup;
    QString m_ErrorString;
    bool m_SessionCreated = false;
    bool m_ShowHelpPopup;
    bool m_ShowGetImagesPopup;
};

