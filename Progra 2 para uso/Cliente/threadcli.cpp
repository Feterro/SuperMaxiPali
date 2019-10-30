#include "threadcli.h"

ThreadCli::ThreadCli(QObject *parent):QThread(parent)
{
    connect(this, SIGNAL(escribirServidor(QByteArray)),&socketCli,SLOT(escribirServidor(QByteArray)));
}
void ThreadCli::run()
{
    emit escribirServidor(QString::fromStdString("IN").toUtf8());
    this->sleep(1);
    string cedDig;
    bool prinRegi=true;
    while(prinRegi==true)
    {
        while(true)
        {
            cout<<"Digite su numero de cedula: ";
            cin>>cedDig;
            if(cedDig.length()==7)
                break;
            else
                cout<<"Longitud de cedula incorrecto"<<endl;
        }
        emit escribirServidor(QString::fromStdString("IN"+cedDig).toUtf8());
        this->sleep(2);
        if(socketCli.registro==true)
        {
            string decis;
            while(true)
            {
               this->sleep(1);
               cout<<"Menu\n"<<endl;
               cout<<"\n 1)Consultar Precio";
               cout<<"\n 2)Consultar si un producto es de la canasta";
               cout<<"\n 3)Consultar el % impuesto de un producto";
               cout<<"\n 4)Comprar";
               cout<<"\n 5)Reportes";
               cout<<"\n 6)Salir";
               cout<<"\n Digite el numero de la opcion deseada: "<<endl;
               cin>>decis;
               emit escribirServidor(QString::fromStdString("IN"+cedDig).toUtf8());
               this->sleep(1);
               if(socketCli.bloqueo==false)
                {
                    if(decis=="1")
                    {
                       consPre();
                    }
                    else if(decis=="2")
                    {
                        consCan();
                    }
                    else if(decis=="3")
                    {
                        consImp();
                    }
                    else if(decis=="4")
                    {
                        comprar(cedDig,false);
                    }
                    else if(decis=="5")
                    {
                        reportes();
                    }
                    else if(decis=="6")
                    {
                        cout<<"Gracias por usar nuestro servicio!"<<endl;
                        break;
                    }
                    else
                        cout<<"opcion invalida"<<endl;
                   }
                   else
                      cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
                }
                prinRegi=false;
            }
            else if(socketCli.registro==false)
            {
                string elecc;
                bool fin=true;
                while(fin)
                {
                    cout<<"Usted no esta registrado, desea hacerlo ahora? S/N: ";
                    cin>>elecc;
                    emit escribirServidor(QString::fromStdString("IN"+cedDig).toUtf8());
                    this->sleep(1);
                    if(socketCli.bloqueo==false)
                    {
                        if(elecc=="S"||elecc=="s")
                        {
                            string nuevReg;
                            string digCin;
                            while(true)
                            {
                                cout<<"Digite su numero de cedula: ";
                                cin>>digCin;
                                if(digCin.length()==7)
                                    break;
                                else
                                    cout<<"Longitud de cedula incorrecto"<<endl;
                            }
                            nuevReg=+";"+digCin;
                            cout<<"Digite su nombre: "<<endl;
                            cin>>digCin;
                            nuevReg=nuevReg+";"+digCin;
                            cout<<"Digite su codigo de ciudad: "<<endl;//validacion de que ciudad exista
                            cin>>digCin;
                            nuevReg=nuevReg+";"+digCin;
                            cout<<"Digite su numero de telefono: "<<endl;
                            cin>>digCin;
                            nuevReg=nuevReg+";"+digCin;
                            cout<<"Digite su correo electronico: "<<endl;
                            cin>>digCin;
                            nuevReg=nuevReg+";"+digCin;
                            emit escribirServidor(QString::fromStdString("RE"+nuevReg).toUtf8());
                            this->sleep(1);
                            if(socketCli.bloqueo==false)
                            {
                                cout<<"Ha sido registrado!"<<endl;
                                break;
                            }
                            else
                                cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;

                        }
                        else if(elecc=="N"||elecc=="n")
                        {
                            cout<<"Menu:\n"<<endl;
                            cout<<"\n 1)Consultar Precio";
                            cout<<"\n 2)Consultar si un producto es de la canasta";
                            cout<<"\n 3)Consultar el % impuesto de un producto";
                            cout<<"\n 4)Reportes";
                            cout<<"\n 5)Salir";
                            string deci;
                            while(true)
                            {
                                cout<<"\n Digite el numero de la opcion deseada: "<<endl;
                                cin>>deci;
                                emit escribirServidor(QString::fromStdString("IN").toUtf8());
                                this->sleep(1);
                                if(socketCli.bloqueo==false)
                                {
                                    if(deci=="1")
                                    {
                                        consPre();
                                    }
                                    else if(deci=="2")
                                    {
                                        consCan();
                                    }
                                    else if(deci=="3")
                                    {
                                        consImp();
                                    }
                                    else if(deci=="4")
                                    {

                                    }
                                    else if(deci=="5")
                                    {
                                        cout<<"Gracias por usar nuestro servivio!"<<endl;
                                        break;
                                    }
                                    else
                                        cout<<"opcion invalida"<<endl;
                                }
                                else
                                    cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
                            }
                            fin=false;
                            prinRegi=false;
                        }
                        else
                            cout<<"Digite Unicamente S o N"<<endl;
                    }
                    else
                         cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
                }
            }
    }
}

void ThreadCli::reportes()
{
    cout<<"\n";
    emit escribirServidor(QString::fromStdString("CO").toUtf8());
    this->sleep(1);
    string env;
    string codComp;
    cout<<"\nDigite el codigo de Pasillo que desea: "<<endl;
    cin>>env;
    cout<<"\n";
    codComp=env;
    emit escribirServidor(QString::fromStdString("CA"+codComp).toUtf8());
    this->sleep(1);
    if(socketCli.bloqueo==false)
    {
        cout<<"Digite el codigo de Producto que desea: "<<endl;
        cin>>env;
        cout<<"\n";
        codComp=codComp+";"+env;
        emit escribirServidor(QString::fromStdString("CB;"+codComp).toUtf8());
        this->sleep(1);
    }
    else
        cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
}

void ThreadCli::consCan()
{
    cout<<"\n";
    emit escribirServidor(QString::fromStdString("CO").toUtf8());
    this->sleep(1);
    string env;
    string codComp;
    cout<<"\nDigite el codigo de Pasillo que desea: "<<endl;
    cin>>env;
    cout<<"\n";
    codComp=env;
    emit escribirServidor(QString::fromStdString("CA"+codComp).toUtf8());
    this->sleep(1);
    if(socketCli.bloqueo==false)
    {
        cout<<"Digite el codigo de Producto que desea: "<<endl;
        cin>>env;
        cout<<"\n";
        codComp=codComp+";"+env;
        emit escribirServidor(QString::fromStdString("CB;"+codComp).toUtf8());
        this->sleep(1);
        if(socketCli.bloqueo==false)
        {
            cout<<"Digite el codigo de Marca que desea: "<<endl;
            cin>>env;
            codComp=codComp+";"+env;
            emit escribirServidor(QString::fromStdString("ZC;"+codComp).toUtf8());
            if(socketCli.bloqueo==true)
            {
                cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
            }
        }
        else
            cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
    }
    else
        cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
}

void ThreadCli::consImp()
{
    cout<<"\n";

    emit escribirServidor(QString::fromStdString("CO").toUtf8());
    this->sleep(1);
    string env;
    string codComp;
    cout<<"\nDigite el codigo de Pasillo que desea: "<<endl;
    cin>>env;
    cout<<"\n";
    codComp=env;
    emit escribirServidor(QString::fromStdString("CA"+codComp).toUtf8());
    this->sleep(1);
    if(socketCli.bloqueo==false)
    {
        cout<<"Digite el codigo de Producto que desea: "<<endl;
        cin>>env;
        cout<<"\n";
        codComp=codComp+";"+env;
        emit escribirServidor(QString::fromStdString("CB;"+codComp).toUtf8());
        this->sleep(1);
        if(socketCli.bloqueo==false)
        {
            cout<<"Digite el codigo de Marca que desea: "<<endl;
            cin>>env;
            codComp=codComp+";"+env;
            emit escribirServidor(QString::fromStdString("ZR;"+codComp).toUtf8());
            if(socketCli.bloqueo==true)
            {
                cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
            }
        }
        else
            cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
    }
    else
        cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
}
void ThreadCli::consPre()
{
    cout<<"\n";
    emit escribirServidor(QString::fromStdString("CO").toUtf8());
    this->sleep(1);
    string env;
    string codComp;
    cout<<"\nDigite el codigo de Pasillo que desea: "<<endl;
    cin>>env;
    cout<<"\n";
    codComp=env;
    emit escribirServidor(QString::fromStdString("CA"+codComp).toUtf8());
    this->sleep(1);
    if(socketCli.bloqueo==false)
    {
        cout<<"Digite el codigo de Producto que desea: "<<endl;
        cin>>env;
        cout<<"\n";
        codComp=codComp+";"+env;
        emit escribirServidor(QString::fromStdString("CB;"+codComp).toUtf8());
        this->sleep(1);
        if(socketCli.bloqueo==false)
        {
            cout<<"Digite el codigo de Marca que desea: "<<endl;
            cin>>env;
            codComp=codComp+";"+env;
            emit escribirServidor(QString::fromStdString("ZP;"+codComp).toUtf8());
            if(socketCli.bloqueo==true)
            {
                cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
            }
        }
        else
            cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
    }
    else
        cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
}
void ThreadCli::comprar(string ced, bool repe)
{
    while(true)
    {

        cout<<"\n";
        emit escribirServidor(QString::fromStdString("CO").toUtf8());
        this->sleep(1);
        string env;
        string codComp;
        cout<<"\nDigite el codigo de Pasillo que desea: "<<endl;
        cin>>env;
        cout<<"\n";
        codComp=env;
        emit escribirServidor(QString::fromStdString("CA"+codComp).toUtf8());
        this->sleep(1);
        if(socketCli.bloqueo==false)
        {
            cout<<"Digite el codigo de Producto que desea: "<<endl;
            cin>>env;
            cout<<"\n";
            codComp=codComp+";"+env;
            emit escribirServidor(QString::fromStdString("CB;"+codComp).toUtf8());
            this->sleep(1);
            if(socketCli.bloqueo==false)
            {
                cout<<"Digite el codigo de Marca que desea: "<<endl;
                cin>>env;
                codComp=codComp+";"+env;
                cout<<"Digite la cantidad que desea: "<<endl;
                cin>>env;
                codComp=codComp+";"+env;
                if(repe==false)
                    emit escribirServidor(QString::fromStdString("CF;"+codComp+";"+ced).toUtf8());
                else
                    emit escribirServidor(QString::fromStdString("CFD;"+codComp+";"+ced).toUtf8());
                this->sleep(1);
                if(socketCli.bloqueo==false)
                {
                    cout<<"\nCompra relizada!\nDesea comprar mas? Presione s para si o cualquier otra tecla para no"<<endl;
                    string resp;
                    cin>>resp;
                    if(resp=="S"||resp=="s")
                    {
                        comprar(ced,true);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                    cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
            }
            else
                cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
        }
        else
            cout<<"Se esta actualizando el servidor, intente mas tarde"<<endl;
            //break;
    }
                //else if(socketCli.correcto==false){
                //    cout<<"Codigo de marca inexistente, intente de nuevo\n"<<endl;
                    //break;
               // }
           // }
           // else if(socketCli.correcto==false){
           //     cout<<"Codigo de producto inexistente, intente de nuevo\n"<<endl;
                //break;
          //  }
      //  }
      //  else if(socketCli.correcto==false){
     //       cout<<"Codigo de pasillo inexistente, intente de nuevo\n"<<endl;
            //break;
       // }
   // }
}

