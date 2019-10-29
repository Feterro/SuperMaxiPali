#include "servidor.h"
#include <iostream>

Servidor::Servidor(QObject *parent) : QTcpServer(parent)
{

}

void Servidor:: inicioServidor()
{
    if(!listen(QHostAddress::LocalHost,1234))
    {
        qDebug() <<"error de coneccion";
    }
    else
    {
        qDebug() <<"conexion exitosa!";
    }
}

void Servidor::incomingConnection(qintptr handle)
{
    cout<<"cliente conectado"<<endl;
    serverSocket *socketNuevo=new serverSocket(this);
    socketNuevo->setSocket(handle);
    this->lisSockets.append(socketNuevo);
}
