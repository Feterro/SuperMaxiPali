#include "cliente.h"

Cliente::Cliente(QObject *parent):QThread(parent)
{

}
void Cliente::SocketConnection()
{
    socketCli=new QTcpSocket(this);

    socketCli->connectToHost("LocalHost",1234);

    if(socketCli->waitForConnected(5000))
    {
        connect(this->socketCli,SIGNAL(connected()),this,SLOT(connected()));
        connect(this->socketCli,SIGNAL(disconnected()),this,SLOT(disconnected()));
        connect(this->socketCli,SIGNAL(readyRead()),this,SLOT(readyRead()));


        qDebug()<< "Cliente conectado!";
    }
    else
    {
        qDebug()<<"Imposible conectarse";
    }
}
void Cliente:: connected()
{

}
void Cliente::disconnected()
{
    qDebug()<<"Cliente desconectado";
}
void Cliente::readyRead()
{
    QByteArray info=socketCli->readAll();
    string infoConv=info.toStdString();
    //cout<<infoConv<<endl;
    if(infoConv=="BK")
    {
        verificarBloqueo(infoConv);
    }
    else if(infoConv=="EXI" || infoConv=="FALL")
    {
        cambiarRegistro(infoConv);
        verificarBloqueo(infoConv);
    }
    else if(infoConv.substr(0,2)=="MA")
    {
        char cstr[infoConv.size() + 1];
        strcpy(cstr, infoConv.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        cout<<token<<endl;
        verificarBloqueo(infoConv);
    }
    else if(infoConv.substr(0,2)=="MB"||infoConv.substr(0,2)=="MC")
    {
        char cstr[infoConv.size() + 1];
        strcpy(cstr, infoConv.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        cout<<token<<endl;
        verificarBloqueo(infoConv);
        //correccion(infoConv.substr(0,2));
    }
    else if(infoConv.substr(0,2)=="FK")
    {
        char cstr[infoConv.size() + 1];
        strcpy(cstr, infoConv.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        cout<<token<<endl;
    }
}
void Cliente::escribirServidor(QByteArray info)
{
    this->socketCli->write(info);
}
void Cliente::cambiarRegistro(string infoConv)
{
    if(infoConv=="EXI")
    {
        this->registro=true;//cambiar al global
    }
    else if(infoConv=="FALL")
    {
        this->registro=false;
    }
}
void Cliente::correccion(string vali)
{
    cout<<"VALI="<<vali<<endl;
    if(vali=="MB"||vali=="MC")
        this->correcto=true;
    else if(vali=="VF")
        this->correcto=false;
}
void Cliente::verificarBloqueo(string vali)
{
  if(vali=="BK")
    this->bloqueo=true;
  else
    this->bloqueo=false;
}

