#pragma once

#include <QObject>
#include <QtTest>

class TestSessionFactory : public QObject {
    Q_OBJECT
public:
    explicit TestSessionFactory(QObject *parent = nullptr);
private slots:
    void testCreateSession();
    void testCreateDublicateSession();
    void testCreateEmptySession();
};

