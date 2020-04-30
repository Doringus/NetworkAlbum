#pragma once

#include <QObject>

#include "../base/store.h"

class EasterEggStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(bool showEasterEgg READ getShowEasterEgg NOTIFY showEasterEggChanged)
public:
    EasterEggStore(const EasterEggStore&) = delete;
    EasterEggStore& operator=(const EasterEggStore&) = delete;

    static EasterEggStore& get() {
        static EasterEggStore instance;
        return instance;
    }

    void process(const QSharedPointer<Action>& action);

    bool getShowEasterEgg();
signals:
    void showEasterEggChanged();
private:
    EasterEggStore() = default;
    void processSendMessage(const QString& message);
private:
    bool m_ShowEasterEgg;
};

