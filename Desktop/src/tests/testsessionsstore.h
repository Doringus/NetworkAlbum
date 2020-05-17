#pragma once

#include <QObject>
#include <QtTest>

class TestSessionsStore : public QObject {
    Q_OBJECT
public:
    explicit TestSessionsStore(QObject *parent = nullptr);
private slots:
    void testOpenAlbum();
    void testCreateAlbum();
    void testGetSessionIndex();
};

