#include "linkstore.h"

#include <QDebug>

LinkStore::LinkStore(QObject *parent) : QObject(parent) {
    qDebug() << "Created";
}

LinkStore::~LinkStore() {
    qDebug() << "Destroyed";
}

void LinkStore::process(const QSharedPointer<Action> &action) {

}

QString LinkStore::getLink() const {
    return "TEST";
}
