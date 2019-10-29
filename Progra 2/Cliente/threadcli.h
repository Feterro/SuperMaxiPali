#ifndef THREADCLI_H
#define THREADCLI_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <iostream>
#include "cliente.h"
#include "globalizarSocket.h"

using namespace std;

class ThreadCli: public QThread
{
    Q_OBJECT
public:
    explicit ThreadCli(QObject *parent=nullptr);
    void menuReg();
    void comprar(string ced,bool repe);
    void consPre();
    void consImp();
    void consCan();
    void reportes();


signals:
    void escribirServidor(QByteArray info);

public slots:

protected:
    void run() override;


};

#endif // THREADCLI_H
