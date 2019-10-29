#ifndef ADMIN_H
#define ADMIN_H

#include <QObject>
#include <QThread>
#include <iostream>
#include <QTcpSocket>
#include "socketServer.h"
#include "globalServer.h"

using namespace std;


class Admin : public QThread
{  
    Q_OBJECT
public:
    explicit Admin(QObject *parent = nullptr);
    void run() override;

signals:
    void enviarFactura(qintptr desc, QByteArray info);

};

#endif // ADMIN_H
