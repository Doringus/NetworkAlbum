#pragma once

#include <QObject>

#include "../base/store.h"

class LinkStore : public QObject, public Store {
    Q_OBJECT
public:
    Q_PROPERTY(QString link READ getLink NOTIFY linkChanged)

    LinkStore(QObject *parent = nullptr);
    ~LinkStore();
    void process(const QSharedPointer<Action>& action) override;
    QString getLink() const;

signals:
    void linkChanged();
private:

};

