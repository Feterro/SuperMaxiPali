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
    QByteArray info=socketCli->readAll();
    string infoConv=info.toStdString();
    //cout<<infoConv<<endl;
    if(infoConv.substr(0,2)=="AV"||infoConv.substr(0,2)=="AN")
    {
        cambiarRegistro(infoConv);
    }
    else if(infoConv.substr(0,2)=="LE")
    {
        string codVal=infoConv;
        char cstr[codVal.size() + 1];
        strcpy(cstr, codVal.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        string lectura=token;
        cout<<lectura<<endl;
    }
    else if(infoConv.substr(0,2)=="VF")
    {
        correccion(infoConv);
    }
}
void Admin::escribirServidor(QByteArray info)
{
    this->socketCli->write(info);
}
void Admin::cambiarRegistro(string infoConv)
{
    if(infoConv=="AV")
    {
        this->registro=true;
    }
    else if(infoConv=="AN")
    {
        this->registro=false;
    }
}

void Admin::correccion(string vali)
{
    cout<<"VALI="<<vali<<endl;
    if(vali=="VF")
        this->correcto=false;
    else
        this->correcto=true;
}
