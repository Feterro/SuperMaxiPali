#include "socketServer.h"

serverSocket::serverSocket(QObject *parent) : QTcpSocket(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}

void serverSocket::setSocket(qintptr handle)
{
    socket=new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    socket->setSocketDescriptor(handle);
}
void serverSocket:: connected()
{

}
void serverSocket::disconnected()
{
    qDebug()<<"Conexion desestablecida";
}

void serverSocket::readyRead()
{
    QByteArray info=socket->readAll();
    //qDebug()<<info<<endl;
    string infoConv=info.toStdString();
    if(infoConv.substr(0,2)=="IN"||infoConv.substr(0,2)=="RE"||infoConv.substr(0,2)=="CO"||infoConv.substr(0,2)=="CA"||infoConv.substr(0,2)=="CB"||infoConv.substr(0,2)=="CF"||infoConv.substr(0,2)=="ZP"||infoConv.substr(0,2)=="ZC"||infoConv.substr(0,2)=="ZR")
          this->funcionesCliente(infoConv);
    else if(infoConv.substr(0,2)=="XB"||infoConv.substr(0,2)=="XB"||infoConv.substr(0,2)=="XV"||infoConv.substr(0,2)=="XP"||infoConv.substr(0,2)=="XR")
        this->funcionesAdministrador(infoConv);
}
void serverSocket::funcionesAdministrador(string infoConv)
{
    if(infoConv.substr(0,2)=="XB")
    {
        arbolPasillos.bloqueo=true;
    }
    else if(infoConv.substr(0,2)=="XD")
    {
        arbolPasillos.bloqueo=false;
    }
    else if(infoConv.substr(0,2)=="XV")
    {
        string codVal=infoConv;
        char cstr[codVal.size() + 1];
        strcpy(cstr, codVal.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        string iden=token;
        stringstream cb(iden);
        int identi;
        cb>>identi;
        if(princi.validarAdministrador(arbolAdmin,identi))
            this->socket->write("AV");
        else
            this->socket->write("AN");
    }
    else if(infoConv.substr(0,2)=="XP")
    {
        string codVal=infoConv;
        cout<<codVal<<endl;
        char cstr[codVal.size() + 1];
        strcpy(cstr, codVal.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        string codigo=token;
        token = strtok(NULL,var);
        string nombre=token;
        int largoIni=0;
        int largoCambio=0;
        largoIni=arbolPasillos.largoArbol(arbolPasillos.raiz, largoIni);
        arbolPasillos.InsertaBinario(arbolPasillos.raiz,codigo,nombre);
        largoCambio=arbolPasillos.largoArbol(arbolPasillos.raiz, largoCambio);
        if (largoIni!=largoCambio)
            socket->write("LE;Pasillo Agregado con exito");
        else
            socket->write("LE;El codigo deseado ya existe");
    }
    else if(infoConv.substr(0,2)=="XR")
    {
        string codVal=infoConv;
        //cout<<codVal<<endl;
        char cstr[codVal.size() + 1];
        strcpy(cstr, codVal.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        string codPasi=token;
        token = strtok(NULL,var);
        string codigo=token;
        token = strtok(NULL,var);
        string nombre=token;
        bool valido=false;
        valido=arbolPasillos.encontrarPasillo(valido, arbolPasillos.raiz, codPasi);
        if(valido)
        {
            bool valid=false;
            valid=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPasi, codigo, valid);
            if(!valid)
            {
                cout<<"valido"<<endl;
                pnodoProd nuevo=new nodoProducto(codPasi, codigo, nombre);
                AVLProducto arbolprod;
                arbolprod.EnlaceAvl(arbolPasillos.raiz, nuevo);
                this->socket->write("LE;Producto agregado con exito");
                arbolPasillos.InordenTriple(arbolPasillos.raiz);
            }
            else
                this->socket->write("VF");
        }
        else
            this->socket->write("VF");
    }
}
void serverSocket::funcionesCliente(string infoConv)
{
    if(infoConv.substr(0,2)=="IN")
    {
        if(arbolPasillos.bloqueo==false)
        {
            this->verificarCed(infoConv);
        }
        else
            this->socket->write("BK");
    }
    else if(infoConv.substr(0,2)=="RE")
    {
        if(arbolPasillos.bloqueo==false)
        {
            this->agregar(infoConv);
        }
            else
                this->socket->write("BK");

    }
    else if(infoConv.substr(0,2)=="CO")
    {
        if(arbolPasillos.bloqueo==false)
        {
            string devolver=arbolPasillos.InordenServ(arbolPasillos.raiz);
            QByteArray listaPa(devolver.c_str(), devolver.length());
            this->socket->write("MA;"+listaPa);
        }
        else
            this->socket->write("BK");
    }
    else if(infoConv.substr(0,2)=="CA")
    {
        if(arbolPasillos.bloqueo==false)
        {
      //  bool val=false;
      //  val=arbolPasillos.encontrarPasillo(val,arbolPasillos.raiz,infoConv.substr(2,4));
      //  if(val)
       // {
         AVLProducto arb;
         string devolver=arb.EnlaceAvlServ(arbolPasillos.raiz,infoConv.substr(2,4));
         QByteArray listaPro(devolver.c_str(), devolver.length());
         this->socket->write("MB;"+listaPro);
        }
        else
            this->socket->write("BK");
        //}
        //else
          //  this->socket->write("VF");
    }
    else if(infoConv.substr(0,2)=="CB")
    {
        if(arbolPasillos.bloqueo==false)
        {
            string codVal=infoConv;
            char cstr[codVal.size() + 1];
            strcpy(cstr, codVal.c_str());
            char var[]=";";
            char *token = strtok(cstr,var);
            token = strtok(NULL,var);
            string codiPas=token;
            token = strtok(NULL,var);
            string codiPro=token;
           // bool val=false;
           // val=arbolPasillos.ValidarProducto1(arbolPasillos.raiz,codiPas,codiPro,val);

                AVLProducto arb;
                string devolv=arb.EnlaceAvlServPro(arbolPasillos.raiz,infoConv);
                QByteArray listaPro(devolv.c_str(), devolv.length());
                this->socket->write("MC;"+listaPro);
        }
        else
            this->socket->write("BK");
            //else
            //    this->socket->write("VF");
    }
    else if(infoConv.substr(0,2)=="CF")
    {
        if(arbolPasillos.bloqueo==false)
        {
            char cstr[infoConv.size() + 1];
            strcpy(cstr, infoConv.c_str());
            char var[]=";";
            char *token = strtok(cstr,var);
            string codi=token;
            token = strtok(NULL,var);
            string codPas=token;
            token = strtok(NULL,var);
            string codPro=token;
            token = strtok(NULL,var);
            string codMar=token;
            token = strtok(NULL,var);
            string canti=token;
            stringstream camb(canti);
            int cantidad;
            camb>>cantidad;
            token = strtok(NULL,var);
            string cedula=token;
            stringstream camb2(cedula);
            int ced;
            camb2>>ced;
    //        bool val=false;
    //        val=arbolPasillos.validarMarca(arbolPasillos.raiz,codPas,codPro,codMar,val);
    //        if(val)
    //        {
                //***********************************
                bool rep=true;
                if(codi!="CFD")
                {
                    rep=princi.cola.agregarCliente(princi.cola,ced);
                    princi.agregarCola(arbolClientes,ced,this->socket->socketDescriptor());
                }
                if(rep==true)
                {
                    pnodoCola aux=princi.cola.primero;
                    princi.comprar(cantidad,codPas,codPro,codMar);
                   // for(int i=0;i<princi.cola.largoLista();i++)
                  //  {
                  //      cout<<"cedCli "<<aux->cedula<<"->";
                  //      pnodoPila auxi=aux->pila;
                  //      while(auxi!=NULL)
                  //     {
                   //         cout<<"peticion "<<auxi->codMarc<<" "<<auxi->cant<<endl;
                   //         auxi=auxi->siguiente;
                    //    }
                     //   aux=aux->siguiente;
                    //}
                    //this->socket->write("MC; ");
                }
                else
                    this->socket->write("MC;Usted ya se encuentra en la lista de facturacion");
    //        }
    //        else
    //            this->socket->write("VF");
        }
        else
            this->socket->write("BK");
    }
    else if(infoConv.substr(0,2)=="ZP")
    {
        if(arbolPasillos.bloqueo==false)
        {
            char cstr[infoConv.size() + 1];
            strcpy(cstr, infoConv.c_str());
            char var[]=";";
            char *token = strtok(cstr,var);
            string codi=token;
            token = strtok(NULL,var);
            string codPas=token;
            token = strtok(NULL,var);
            string codPro=token;
            token = strtok(NULL,var);
            string codMar=token;
            string dev=princi.consultarUnPrecio(codPas,codPro,codMar);
            QByteArray listaPro(dev.c_str(), dev.length());
            this->socket->write("MB;"+listaPro);
        }
        else
            this->socket->write("BK");
    }
    else if(infoConv.substr(0,2)=="ZR")
    {
        if(arbolPasillos.bloqueo==false)
        {
            char cstr[infoConv.size() + 1];
            strcpy(cstr, infoConv.c_str());
            char var[]=";";
            char *token = strtok(cstr,var);
            string codi=token;
            token = strtok(NULL,var);
            string codPas=token;
            token = strtok(NULL,var);
            string codPro=token;
            token = strtok(NULL,var);
            string codMar=token;
            string dev=princi.ConsultarImpuesto(codPas,codPro,codMar);
            QByteArray listaPro(dev.c_str(), dev.length());
            this->socket->write("MB;"+listaPro);
       }
        else
            this->socket->write("BK");
    }
    else if(infoConv.substr(0,2)=="ZC")
    {
        if(arbolPasillos.bloqueo==false)
        {
            char cstr[infoConv.size() + 1];
            strcpy(cstr, infoConv.c_str());
            char var[]=";";
            char *token = strtok(cstr,var);
            string codi=token;
            token = strtok(NULL,var);
            string codPas=token;
            token = strtok(NULL,var);
            string codPro=token;
            token = strtok(NULL,var);
            string codMar=token;
            string dev=princi.ConsultarCanasta(codPas,codPro,codMar);
            QByteArray listaPro(dev.c_str(), dev.length());
            this->socket->write("MB;"+listaPro);
        }
        else
            this->socket->write("BK");
    }

}

void serverSocket::verificarCed(string info)
{
    Principal prin;
    string infobusc=info.substr(2,7);
    stringstream ss(infobusc);
    int infoConv;
    ss>>infoConv;
    if(arbolPasillos.bloqueo==false)
    {
        if(prin.validarCliente(arbolClientes,infoConv))
        {
            this->socket->write("EXI");//flush
        }
        else if(!prin.validarCliente(arbolClientes,infoConv))
        {
            this->socket->write("FALL");//flush
        }
    }
    else
        this->socket->write("BK");

}

void serverSocket::agregar(string infoConv)
{
    if(arbolPasillos.bloqueo==false)
    {
        char cstr[infoConv.size() + 1];
        strcpy(cstr, infoConv.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        string cedu=token;
        token = strtok(NULL,var);
        string nomb=token;
        token = strtok(NULL,var);
        string ciud=token;
        token = strtok(NULL,var);
        string tele=token;
        token = strtok(NULL,var);
        string corr=token;
        stringstream conv(cedu);
        int ceduTrans;
        conv>>ceduTrans;
        arbolClientes.insertar(ceduTrans,nomb,tele,ciud,corr);
        arbolClientes.listaCreciente();
    }
    else
        this->socket->write("BK");
}
