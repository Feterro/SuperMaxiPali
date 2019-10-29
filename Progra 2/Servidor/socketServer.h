#ifndef SOCKETSERVER_H
#define SOCKETSERVER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "Principal.h"
#include "globalHeaders.h"
#include "headers/avlProducto.h"
#include <sstream>
//#include "Progra2principal.h"

using namespace std;

class serverSocket : public QTcpSocket
{
    Q_OBJECT
public:
    explicit serverSocket(QObject *parent = nullptr);
    void setSocket(qintptr);
    void verificarCed(string info);
    void agregar(string cantConv);
    QTcpSocket *socket;

signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();

private:


};


#endif // SOCKETSERVER_H
