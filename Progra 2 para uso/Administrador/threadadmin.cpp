#include "threadadmin.h"

ThreadAdmin::ThreadAdmin(QObject *parent):QThread(parent)
{
    connect(this, SIGNAL(escribirServidor(QByteArray)),&socketAdmin,SLOT(escribirServidor(QByteArray)));
}

void ThreadAdmin::run()
{
    bool fin=true;
    while(fin)
    {
        emit escribirServidor(QString::fromStdString("XD").toUtf8());
        string identificacion;
        cout<<"Digite su codigo de administrador: ";
        cin>>identificacion;
        cout<<"\n";
        emit escribirServidor(QString::fromStdString("XV;"+identificacion).toUtf8());
        this->sleep(1);
        if(socketAdmin.registro==true)
        {
            emit escribirServidor(QString::fromStdString("XB").toUtf8());
            fin=false;
            bool menu=true;
            while(menu){
                cout<<"Bienvenido!"<<endl;
                cout<<"Usted tiene las opciones de: "<<endl;
                cout<<"1.Insertar Pasillo"<<endl;
                cout<<"2.Insertar Producto"<<endl;
                cout<<"3.Insertar Marca"<<endl;
                cout<<"4.Consultar el % impuesto de un producto"<<endl;
                cout<<"5.Modificar el Precio"<<endl;
                cout<<"6.Modificar el % de impuesto"<<endl;
                cout<<"7.Modificar si el producto pertenece a la canasta basica"<<endl;
                cout<<"8.Consultar un precio"<<endl;
                cout<<"9.Consultar si un producto es de la canasta"<<endl;
                cout<<"10.Facturar"<<endl;
                cout<<"11.Verificar inventario"<<endl;
                cout<<"12.Verificar gondolas"<<endl;
                cout<<"13.Reportes"<<endl;
                cout<<"14.Salir"<<endl;
                cout<<"\nEscriba el numero de la opcion que desea: "<<endl;
                string resp;
                cin>>resp;
                if (resp=="1"){
                    insertarPas();
                }
                else if (resp=="2"){
                    insertarPro();
                }
                else if (resp=="3"){
                    //arbolPasillos=princi.insertarMarca();
                }
                else if (resp=="4"){
                    //string impu=princi.ConsultarImpuesto();
                    //cout<<impu<<endl;
                }
                else if (resp=="5"){
                    //princi.ModificarPrecio();
                }
                else if (resp=="6"){
                    //princi.ModificarImpuesto();
                }
                else if (resp=="7"){
                    //princi.ModificarCanasta();
                }
                else if (resp=="8"){
                    //string precio=princi.consultarUnPrecioAdm();
                    //cout<<precio<<endl;
                }
                else if (resp=="9"){
                    //string canasta=princi.ConsultarCanasta();
                    //cout<<canasta<<endl;
                }
                else if (resp=="10"){
                    //if(!princi.cola.ListaVacia())
                    //                    {
                    //                        //qintptr descrip=princi.cola.primero->descriptor;
                    //                        //string factura=princi.agregarListaOrdenada();
                    //                        //emit enviarFactura(descrip, QByteArray::fromStdString(factura));
                    //                    }
                    //                    else
                    //                        cout<<"No se han realizado compras aun"<<endl;
                }
                else if (resp=="11"){
                    //princi.revisarGondolas();
                }
                else if (resp=="12"){
                    //princi.cargarInventario();
                }
                else if(resp=="13"){
                    //princi.generarReporte();
                    cout<<"reporte generado!"<<endl;
                }
                else if (resp=="14"){
                    cout<<"Gracias por usar el sistema"<<endl;
                    menu=false;
                    fin=true;
                }
            }

        }
        else
            cout<<"Codigo invalido"<<endl;
    }
}

void ThreadAdmin::insertarPas()
{
    string cod;
    string nom;
    cout<<"Digite El codigo del nuevo Pasillo: ";
    cin>>cod;
    cout<<"\nDigite el nombre del nuevo Pasillo: ";
    cin>>nom;
    string codnom=cod+";"+nom;
    emit escribirServidor(QString::fromStdString("XP;"+codnom).toUtf8());
    this->sleep(1);
}

void ThreadAdmin::insertarPro()
{
    while(socketAdmin.correcto)
    {
        cout<<"\n";
        emit escribirServidor(QString::fromStdString("CO").toUtf8());
        this->sleep(1);
        string env;
        cout<<"\nDigite el codigo de Pasillo que desea: "<<endl;
        cin>>env;
        cout<<"\n";
        string cod;
        string nom;
        cout<<"Digite El codigo del nuevo Producto: ";
        cin>>cod;
        cout<<"\nDigite el nombre del nuevo Producto: ";
        cin>>nom;
        string codnom=cod+";"+nom;
        emit escribirServidor(QString::fromStdString("XR;"+env+";"+codnom).toUtf8());
        this->sleep(1);
        if(!socketAdmin.correcto)
            cout<<"Codigos incorrectos, intente de nuevo\n"<<endl;
        else
            break;
    }
}
