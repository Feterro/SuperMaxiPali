#include <QCoreApplication>
#include "cliente.h"
#include "threadcli.h"

Cliente socketCli;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    socketCli.SocketConnection();

    ThreadCli proceso;
    proceso.start();

    return a.exec();
}
