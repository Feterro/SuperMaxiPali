#ifndef THREADADMIN_H
#define THREADADMIN_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <iostream>
#include "admin.h"
#include "globalizarSocketAd.h"

using namespace std;

class ThreadAdmin: public QThread
{
    Q_OBJECT
public:
    explicit ThreadAdmin(QObject *parent=nullptr);
    void reportes();
    void insertarPas();
    void insertarPro();

signals:
    void escribirServidor(QByteArray info);

public slots:

protected:
    void run() override;


};

#endif // THREADADMIN_H
