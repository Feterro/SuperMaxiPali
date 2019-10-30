#include <QCoreApplication>
#include "globalServer.h"
#include "admin.h"
#include "socketServer.h"
#include "globalHeaders.h"
#include "Prograprincipal.h"

ArbolB arbolClientes=ArbolB(5);
ArbolB arbolAdmin=ArbolB(5);
arbolPas arbolPasillos;
ArbolInventario arbolInventario;
Ciudad listaCiudades;
Principal princi;
Servidor servGlo;

int main(int argc, char *argv[])
{
    qRegisterMetaType<qintptr>("qintptr");
    arbolClientes.cargarClientes("Clientes.txt");
    //arbolClientes.listaCreciente();
    cout<<endl;

    arbolAdmin.cargarAdmins("Administradores.txt");
    //arbolAdmin.listaCreciente();
    cout<<endl;

    arbolPasillos=arbolPasillos.arbolMarcas();
    //arbolPasillos.InordenTriple(arbolPasillos.raiz);
    cout<<"\n"<<endl;

    arbolInventario=arbolInventario.agregarInventario();
    cout<<"\n"<<endl;

    listaCiudades=listaCiudades.agregarCiudades();
    cout<<"\n"<<endl;

    QCoreApplication a(argc, argv);
    servGlo.inicioServidor();

    Admin administrador;
    administrador.start();

    return a.exec();
}
