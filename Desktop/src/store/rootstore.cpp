#include "rootstore.h"

#include "../base/action.h"
#include "../action/actiontypes.h"
#include "../base/dispatcher.h"

void RootStore::process(const QSharedPointer<Action> &action) {
    switch (action->getType<ActionType>()) {
        case ActionType::CREATE_SESSION: {
            if(action->getErrorString() == "") {
                setCreatePopupVisibility(false);
                if(!m_SessionCreated) {
                    Dispatcher::get().dispatch(new Action(ActionType::START_SERVER));
                    m_SessionCreated = true;
                    emit sessionCreated();
                }
            }
            processShowError(action->getErrorString());
            break;
        }
        case ActionType::CLIENT_CONNECTED: {
            if(action->getErrorString() != "") {
                processShowError(action->getErrorString());
            } else {
                setOpenPopupVisibility(false);
                m_ShowGetImagesPopup = true;
                emit showGetImagesPopupChanged();
            }
            break;
        }
        case ActionType::IMAGES_RECEIVED: {
            m_ShowGetImagesPopup = false;
            emit showGetImagesPopupChanged();
            break;
        }
        case ActionType::OPEN_CREATION_POPUP: {
            setCreatePopupVisibility(true);
            break;
        }
        case ActionType::HIDE_CREATION_POPUP: {
            setCreatePopupVisibility(false);
            processShowError("");
            break;
        }
        case ActionType::OPEN_CONNECT_POPUP: {
            setOpenPopupVisibility(true);
            break;
        }
        case ActionType::HIDE_CONNECT_POPUP: {
            setOpenPopupVisibility(false);
            processShowError("");
            break;
        }
        case ActionType::SHOW_HELP_POPUP: {
            setHelpPopupVisibility(true);
            break;
        }
        case ActionType::HIDE_HELP_POPUP: {
            setHelpPopupVisibility(false);
            break;
        }
        case ActionType::HIDE_GET_IMAGES_POPUP: {
            m_ShowGetImagesPopup = false;
            emit getShowGetImagesPopup();
            break;
        }
    }
}

bool RootStore::getShowCreatePopup() {
    return m_ShowCreatePopup;
}

bool RootStore::getShowOpenPopup() {
    return m_ShowOpenPopup;
}

bool RootStore::getShowHelpPopup() {
    return m_ShowHelpPopup;
}

bool RootStore::getShowGetImagesPopup() {
    return m_ShowGetImagesPopup;
}

QString RootStore::getErrorString() {
    return m_ErrorString;
}

void RootStore::processShowError(const QString &errorString) {
    m_ErrorString = errorString;
    emit errorStringChanged();
}

void RootStore::setCreatePopupVisibility(bool visible) {
    m_ShowCreatePopup = visible;
    emit showCreatePopupChanged();
}

void RootStore::setOpenPopupVisibility(bool visible) {
    m_ShowOpenPopup = visible;
    emit showOpenPopupChanged();
}

void RootStore::setHelpPopupVisibility(bool visible) {
    m_ShowHelpPopup = visible;
    emit showHelpPopupChanged();
}
