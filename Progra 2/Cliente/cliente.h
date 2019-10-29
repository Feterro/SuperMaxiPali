#ifndef CLIENTE_H
#define CLIENTE_H
#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThread>
#include <QThreadPool>
#include <iostream>

using namespace std;

class Cliente : public QThread
{
Q_OBJECT
public:
    Cliente(QObject *parent = nullptr);
    void SocketConnection();
    void cambiarRegistro();
    void correccion(string vali);
    void verificarBloqueo();
    bool registro;
    bool bloqueo=false;
    bool correcto;

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void escribirServidor(QByteArray info);
    void cambiarRegistro(string info);
    void verificarBloqueo(string vali);

private:
    QTcpSocket *socketCli;

};

#endif // CLIENTE_H
