#pragma once

#include <QObject>
#include <QtTest>

class TestAlbumsStore : public QObject {
    Q_OBJECT
public:
    explicit TestAlbumsStore(QObject *parent = nullptr);
private slots:
    void testCreateSession();
    void testOpenAlbum();
    void testReceiveMessage();
};

