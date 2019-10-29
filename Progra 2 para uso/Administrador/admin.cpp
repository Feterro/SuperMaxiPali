#include "admin.h"

Admin::Admin(QObject *parent):QThread(parent)
{

}

void Admin::SocketConnection()
{
    socketCli=new QTcpSocket(this);

    socketCli->connectToHost("LocalHost",1234);

    if(socketCli->waitForConnected(5000))
    {
        connect(this->socketCli,SIGNAL(connected()),this,SLOT(connected()));
        connect(this->socketCli,SIGNAL(disconnected()),this,SLOT(disconnected()));
        connect(this->socketCli,SIGNAL(readyRead()),this,SLOT(readyRead()));


        qDebug()<< "Administrador conectado!";
    }
    else
    {
        qDebug()<<"Imposible conectarse";
    }
}
void Admin:: connected()
{

}
void Admin::disconnected()
{
    qDebug()<<"Cliente desconectado";
}
void Admin::readyRead()
{

}
void Admin::escribirServidor(QByteArray info)
{
    this->socketCli->write(info);
}
void Admin::verificarBloqueo(string vali)
{
  if(vali=="BK")
    this->bloqueo=true;
  else
    this->bloqueo=false;
}

