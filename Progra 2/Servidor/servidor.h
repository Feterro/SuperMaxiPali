#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "socketServer.h"


class Servidor : public QTcpServer
{
    Q_OBJECT
public:
    explicit Servidor(QObject *parent = nullptr);
    void inicioServidor();
    QList<serverSocket *> lisSockets;
protected:
    void incomingConnection(qintptr handle);  //posible error= poner override despues de()

signals:

private:
QThreadPool *pool;

public slots:
    void enviarFactura(qintptr desc, QByteArray info);
};

#endif // SERVIDOR_H

