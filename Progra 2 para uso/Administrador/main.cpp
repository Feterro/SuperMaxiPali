#include <QCoreApplication>
#include "admin.h"
#include "threadadmin.h"

Admin socketAdmin;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    socketAdmin.SocketConnection();

    ThreadAdmin proceso;
    proceso.start();

    return a.exec();
}
