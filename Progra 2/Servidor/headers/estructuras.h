#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream> //De la progra vieja
using namespace std;

class nodoInventario {
   public:
    nodoInventario(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantStock=cantStk;
        codCanasta=canasta;
        siguiente = NULL;
        anterior=NULL;
    }
    nodoInventario(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta, nodoInventario * signodo)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantStock=cantStk;
        codCanasta=canasta;
        siguiente = signodo;
    }
   private:
    string codPasillo;
    string nombre;
    string codProducto;
    string codMarca;
    int cantStock;
    bool codCanasta;
    nodoInventario *siguiente;
    nodoInventario *anterior;

   friend class listaDCpas;
   friend class listaDCInv;
   friend class listaSimple;
};
class nodoMarca {
   public:
    nodoMarca(string codPas, string nom, string codPro, string codMar, int cantGon, float val)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantGondola=cantGon;
        precio=val;
        siguiente = NULL;
        anterior=NULL;
    }
    nodoMarca(string codPas, string nom, string codPro, string codMar, int cantGon, float val, nodoMarca * signodo)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantGondola=cantGon;
        precio=val;
        siguiente = signodo;
    }
   private:
    string codPasillo;
    string nombre;
    string codProducto;
    string codMarca;
    int cantGondola;
    float precio;
    nodoMarca *siguiente;
    nodoMarca *anterior;

   friend class listaDCpas;
   friend class listaSimple;
};
class nodoProducto {
   public:
    nodoProducto(string codPas, string nom, string codPro)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        siguiente = NULL;
        anterior=NULL;
        subsiguiente=NULL;;
    }
    nodoProducto(string codPas, string nom, string codPro, nodoProducto * signodo)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        siguiente = signodo;
    }
   private:
    string codPasillo;
    string nombre;
    string codProducto;
    nodoProducto *siguiente;
    nodoProducto *anterior;
    nodoMarca *subsiguiente;

   friend class listaDCpas;
   friend class listaSimple;
};
class nodoPasillo {
   public:
    nodoPasillo(string codPas, string nom)
    {
        codPasillo=codPas;
        nombre=nom;
        siguiente = NULL;
        anterior=NULL;
        subsiguiente=NULL;
    }
    nodoPasillo(string codPas, string nom, nodoPasillo * signodo)
    {
        codPasillo=codPas;
        nombre=nom;
        siguiente = signodo;
    }
   private:
    string codPasillo;
    string nombre;
    nodoPasillo *siguiente;
    nodoPasillo *anterior;
    nodoProducto *subsiguiente;
   friend class listaDCpas;
   friend class listaSimple;
   friend class nodoCarrito;
};
class nodoCarrito {
   public:
    nodoCarrito(string codigoPas, string codigoPro, string codigoMar, int cant)
    {
        codPas=codigoPas;
        codPro=codigoPro;
        codMar=codigoMar;
        cantidad=cant;
        cantrecar=0;
        siguiente = NULL;
        anterior=NULL;
    }
    nodoCarrito(string codigoPas, string codigoPro, string codigoMar, int cant, nodoCarrito *signodo)
    {
        codPas=codigoPas;
        codPro=codigoPro;
        codMar=codigoMar;
        cantrecar=0;
        cantidad=cant;
        siguiente = signodo;
    }
    int cantidad;
    nodoCarrito *siguiente;
    nodoCarrito *anterior;
   private:
    int cantrecar;
    string codPas;
    string codPro;
    string codMar;

    friend class listaSimple;
    friend class nodoCliente;
};

class nodoCliente {
   public:
    nodoCliente(string ced, string nom, string cor, string tel)
    {
        cedula=ced;
        nombre=nom;
        telefono=tel;
        correo=cor;
        cantFacturas=0;
        carrito=NULL;
        mont=0;
        fact="";
        siguiente = NULL;
        anterior=NULL;
    }
    nodoCliente(string ced, string nom, string cor, string tel, nodoCliente * signodo)
    {
        cedula=ced;
        nombre=nom;
        telefono=tel;
        correo=cor;
        cantFacturas=0;
        mont=0;
        fact="";
        siguiente = signodo;
    }
   private:
    string cedula;
    string nombre;
    string telefono;
    string correo;
    string fact="f";
    int mont=0;
    int cantFacturas;
    nodoCliente *siguiente;
    nodoCliente *anterior;
    nodoCarrito *carrito;

    friend class listaSimple;
    friend class listaDCCli;
};

typedef nodoPasillo *pnodo;
typedef nodoProducto *pnodo2;
typedef nodoMarca *pnodo3;
typedef nodoInventario *pnodo4;
typedef nodoCliente *pnodo5;
typedef nodoCarrito *pnodo6;

class listaDCpas {
   public:
    listaDCpas() { primeroPas = actual = NULL; }

    void InsertarInicio(string codPas, string nom);
    void InsertarFinal(string codPas, string nom);
    bool ListaVacia() { return primeroPas == NULL; }
    void Imprimir();
    void Mostrar();
    void MostrarSeg();
    void MostrarTerc();
    void Siguiente();
    void Primero();
    void BorrarFinal();
    void BorrarInicio();
    int largoLista();
    listaDCpas ListaBase();
    listaDCpas SublistaPro();
    listaDCpas SublistaMar();

   private:
    pnodo primeroPas;
    pnodo actual;
   friend class listaDCPro;
   friend class listaSimple;
   friend class nodoCarrito;
};
int listaDCpas::largoLista()
{
    int cont=0;

    pnodo aux = primeroPas->siguiente;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primeroPas)
        {
          aux=aux->siguiente;
          cont++;
        }
    cont=cont+1;
    return cont;
    }

}
void listaDCpas::InsertarInicio(string codPas, string nom)
{
   if (ListaVacia())
   {
     pnodo primeroPas = new nodoPasillo(codPas,nom);
     primeroPas->anterior=primeroPas;
     primeroPas->siguiente=primeroPas;
   }
   else
   {
     pnodo nuevo=new nodoPasillo (codPas,nom);
     nuevo->siguiente=primeroPas;
     nuevo->anterior= primeroPas->anterior;
     primeroPas->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primeroPas= nuevo;
   }
}
void listaDCpas::InsertarFinal(string codPas, string nom)
{
   if (ListaVacia())
     {
     primeroPas = new nodoPasillo(codPas, nom);
     primeroPas->anterior=primeroPas;
     primeroPas->siguiente=primeroPas;
   }
   else
   {
     pnodo nuevo = new nodoPasillo(codPas, nom);
     nuevo->anterior = primeroPas->anterior;
     nuevo->siguiente=primeroPas->anterior->siguiente;
     primeroPas->anterior->siguiente=nuevo;
     primeroPas->anterior=nuevo;
    }
}
void listaDCpas::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primeroPas->siguiente == primeroPas)
      {
        pnodo temp= primeroPas;
        primeroPas= NULL;
        delete temp;
      }
      else
      {
         pnodo aux = primeroPas;
         while (aux->siguiente->siguiente != primeroPas)
              aux = aux->siguiente;
         pnodo temp = aux->siguiente;
         aux->siguiente= primeroPas;
         primeroPas->anterior=aux;
         delete temp;
      }
    }
}

void listaDCpas::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primeroPas->siguiente == primeroPas)
     {
        pnodo temp= primeroPas;
        primeroPas= NULL;
        delete temp;
     }
     else
     {
        pnodo aux = primeroPas->anterior;
        pnodo temp= primeroPas;
        aux->siguiente=primeroPas->siguiente;
        primeroPas=primeroPas->siguiente;
        primeroPas->anterior=aux;
        delete temp;
      }
    }
}
void listaDCpas::Mostrar()
{
   pnodo aux=primeroPas;
   while(aux->siguiente!=primeroPas)
     {
      cout << aux->codPasillo<< "~";
      cout << aux->nombre<< "-> ";
      aux = aux->siguiente;
     }
     cout<<aux->codPasillo<< "~";
     cout<<aux->nombre<<"->";
     cout<<endl;
}
void listaDCpas::MostrarSeg()
{
    if(ListaVacia())
        cout<<"La lista esta vacia"<<endl;
    else{
        pnodo aux=primeroPas;
        while(aux->siguiente!=primeroPas)
        {
            pnodo2 aux2=aux->subsiguiente;
            cout << aux->codPasillo<< "~";
            cout << aux->nombre<< "->> ";
            if(aux2!=NULL)
            {
                if(aux2->siguiente==aux2){
                cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->";}
            else{
            while(aux2->siguiente!=aux->subsiguiente)
	      	{
	      		cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->";
	      		aux2=aux2->siguiente;
			}
			cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->";
		  	}
            }
            else
                cout<<"No tiene productos";
            aux = aux->siguiente;
	    }
        pnodo2 aux2=aux->subsiguiente;
        cout<<aux->codPasillo<< "~";
        cout<<aux->nombre<<"->>";
        if(aux->subsiguiente!=NULL)
            cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->";
	    else
	    	cout<<"No tiene productos";
        cout<<endl;
		}
}

void listaDCpas::MostrarTerc()
{
    if(ListaVacia())
        cout<<"No se han creado pasillos"<<endl;
    else{
        pnodo aux=primeroPas;
        while(aux->siguiente!=primeroPas)
        {
            pnodo2 aux2=aux->subsiguiente;
            cout << aux->codPasillo<< "~";
            cout << aux->nombre<< "->> ";
            if(aux2!=NULL)
            {
                pnodo3 aux3=aux2->subsiguiente;
                if(aux2->siguiente==aux2)
                {
                    cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->>>";
                    if (aux2->subsiguiente!=NULL)
                    {
                        if(aux3->siguiente==aux3)
                            cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                        else
                        {
                            while(aux3->siguiente!=aux2->subsiguiente)
                            {
                                cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                                aux3=aux3->siguiente;
                            }
                            cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                        }
                    }
                    else
                        cout<< "No hay marcas de este producto ->";
                }
                else
                {
                    while(aux2->siguiente!=aux->subsiguiente)
                    {
                        aux3=aux2->subsiguiente;
                        cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->>>";
                        if (aux2->subsiguiente!=NULL)
                        {
                            if(aux3->siguiente==aux3)
                                cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                            else
                            {
                                while(aux3->siguiente!=aux2->subsiguiente)
                                {
                                    cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                                    aux3=aux3->siguiente;
                                }
                                cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                            }
                        }
                        else
                            cout<< "No hay marcas de este producto ->";
                        aux2=aux2->siguiente;
                    }
                    aux3=aux2->subsiguiente;
                    cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->>>";
                    if (aux2->subsiguiente!=NULL)
                    {
                        if(aux3->siguiente==aux3)
                            cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                        else
                        {
                            while(aux3->siguiente!=aux2->subsiguiente)
                            {
                                cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                                aux3=aux3->siguiente;
                            }
                            cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                        }
                    }
                    else
                        cout<< "No hay marcas de este producto ->";
                }
            }
            else
                cout<<"No tiene productos->";
            aux = aux->siguiente;
	    }
        pnodo2 aux2=aux->subsiguiente;
        cout<<aux->codPasillo<< "~";
        cout<<aux->nombre<<"->>";
        if(aux->subsiguiente!=NULL)
        {
            cout<<aux2->codPasillo<<"~"<<aux2->codProducto<<"~"<<aux2->nombre<<"->>";
            if (aux2->subsiguiente!=NULL)
            {
                pnodo3 aux3=aux2->subsiguiente;
                if(aux3->siguiente==aux3)
                    cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                else
                    {
                        while(aux3->siguiente!=aux2->subsiguiente)
                        {
                            cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                            aux3=aux3->siguiente;
                        }
                        cout<<aux3->codPasillo<<"~"<<aux3->codProducto<<"~"<<aux3->codMarca<<"~"<<aux3->nombre<<"~"<<aux3->cantGondola<<"~"<<aux3->precio<<"->";
                    }
            }
            else
            cout<< "No hay marcas de este producto ->";
        }
	    else
	    	cout<<"No tiene productos->";
        cout<<endl;
		}
}
class listaDCCli {
   public:
    listaDCCli() { primeroCli = actual = NULL; }

    void InsertarInicio(string ced, string nom, string cor, string tel);
    void InsertarFinal(string ced, string nom, string cor, string tel);
    void EliminarInicio();
    void EliminarFinal();
    bool ListaVacia() { return primeroCli == NULL; }
    void BorrarFinal();
    void BorrarInicio();;
    int largoLista();
    listaDCCli ListaClientes();
    void Mostrar();

   private:
    pnodo5 primeroCli;
    pnodo5 actual;
   friend class listaSimple;
};
int listaDCCli::largoLista()
{
    int cont=0;

    pnodo5 aux = primeroCli;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primeroCli)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }

}
void listaDCCli::InsertarInicio(string ced, string nom, string cor, string tel)
{

   if (ListaVacia())
   {
     primeroCli = new nodoCliente(ced, nom, cor, tel);
     primeroCli->anterior=primeroCli;
     primeroCli->siguiente=primeroCli;
   }
   else
   {
     pnodo5 nuevo=new nodoCliente (ced, nom, cor, tel);
     nuevo->siguiente=primeroCli;
     nuevo->anterior= primeroCli->anterior;
     primeroCli->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primeroCli= nuevo;
   }
}

void listaDCCli::InsertarFinal(string ced, string nom, string cor, string tel)
{
   if (ListaVacia())
     {
     primeroCli = new nodoCliente(ced, nom, cor, tel);
     primeroCli->anterior=primeroCli;
     primeroCli->siguiente=primeroCli;
   }
   else
   {
     pnodo5 nuevo = new nodoCliente(ced, nom, cor, tel);
     nuevo->anterior = primeroCli->anterior;
     nuevo->siguiente=primeroCli->anterior->siguiente;
     primeroCli->anterior->siguiente=nuevo;
     primeroCli->anterior=nuevo;
    }
}

void listaDCCli::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primeroCli->siguiente == primeroCli)
      {
        pnodo5 temp= primeroCli;
        primeroCli= NULL;
        delete temp;
      }
      else
      {
         pnodo5 aux = primeroCli;
         while (aux->siguiente->siguiente != primeroCli)
              aux = aux->siguiente;
         pnodo5 temp = aux->siguiente;
         aux->siguiente= primeroCli;
         primeroCli->anterior=aux;
         delete temp;
      }
    }
}

void listaDCCli::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primeroCli->siguiente == primeroCli)
     {
        pnodo5 temp= primeroCli;
        primeroCli= NULL;
        delete temp;
     }
     else
     {
        pnodo5 aux = primeroCli->anterior;
        pnodo5 temp= primeroCli;
        aux->siguiente=primeroCli->siguiente;
        primeroCli=primeroCli->siguiente;
        primeroCli->anterior=aux;
        delete temp;
      }
    }
}
void listaDCCli ::Mostrar()
{
   pnodo5 aux=primeroCli;
   while(aux->siguiente!=primeroCli)
     {

        cout<< aux->cedula<< "~"<< aux->nombre<< "~"<< aux->telefono<< "~"<< aux->correo<< "-> ";
        aux = aux->siguiente;
     }
     cout<< aux->cedula<< "~"<< aux->nombre<< "~"<< aux->telefono<< "~"<< aux->correo<< "-> ";
     cout<<endl;
}

class listaDCInv {
   public:
    listaDCInv() { primeroInv = actual = NULL; }

    void InsertarInicio(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta);
    void InsertarFinal(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta);
    void EliminarInicio();
    void EliminarFinal();
    bool ListaVacia() { return primeroInv == NULL; }
    void BorrarFinal();
    void BorrarInicio();;
    int largoLista();
    listaDCInv CrearInventario();
    void Mostrar();

   private:
    pnodo4 primeroInv;
    pnodo4 actual;
   friend class listaSimple;
};
int listaDCInv::largoLista()
{
    int cont=0;

    pnodo4 aux = primeroInv;
    if(ListaVacia())
    {
        return cont;
    }
    else
    {
        while(aux!=primeroInv)
        {
          aux=aux->siguiente;
          cont++;
        }
    return cont;
    }

}
void listaDCInv::InsertarInicio(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta)
{

   if (ListaVacia())
   {
     primeroInv = new nodoInventario(codPas, nom, codPro, codMar, cantStk, canasta);
     primeroInv->anterior=primeroInv;
     primeroInv->siguiente=primeroInv;
   }
   else
   {
     pnodo4 nuevo=new nodoInventario (codPas, nom, codPro, codMar, cantStk, canasta);
     nuevo->siguiente=primeroInv;
     nuevo->anterior= primeroInv->anterior;
     primeroInv->anterior->siguiente=nuevo;
     nuevo->siguiente->anterior=nuevo;
     primeroInv= nuevo;
   }
}

void listaDCInv::InsertarFinal(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta)
{
   if (ListaVacia())
     {
     primeroInv = new nodoInventario(codPas, nom, codPro, codMar, cantStk, canasta);
     primeroInv->anterior=primeroInv;
     primeroInv->siguiente=primeroInv;
   }
   else
   {
     pnodo4 nuevo = new nodoInventario(codPas, nom, codPro, codMar, cantStk, canasta);
     nuevo->anterior = primeroInv->anterior;
     nuevo->siguiente=primeroInv->anterior->siguiente;
     primeroInv->anterior->siguiente=nuevo;
     primeroInv->anterior=nuevo;
    }
}

void listaDCInv::BorrarFinal()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
      if (primeroInv->siguiente == primeroInv)
      {
        pnodo4 temp= primeroInv;
        primeroInv= NULL;
        delete temp;
      }
      else
      {
         pnodo4 aux = primeroInv;
         while (aux->siguiente->siguiente != primeroInv)
              aux = aux->siguiente;
         pnodo4 temp = aux->siguiente;
         aux->siguiente= primeroInv;
         primeroInv->anterior=aux;
         delete temp;
      }
    }
}

void listaDCInv::BorrarInicio()
{
    if (ListaVacia())
      cout << "No hay elementos en la lista:" << endl;
    else
    {
     if (primeroInv->siguiente == primeroInv)
     {
        pnodo4 temp= primeroInv;
        primeroInv= NULL;
        delete temp;
     }
     else
     {
        pnodo4 aux = primeroInv->anterior;
        pnodo4 temp= primeroInv;
        aux->siguiente=primeroInv->siguiente;
        primeroInv=primeroInv->siguiente;
        primeroInv->anterior=aux;
        delete temp;
      }
    }
}
void listaDCInv ::Mostrar()
{
   pnodo4 aux=primeroInv;
   while(aux->siguiente!=primeroInv)
     {
        cout<<aux->codPasillo<<"~"<<aux->codProducto<<"~"<<aux->codMarca<<"~"<<aux->nombre<<"~"<<aux->cantStock<<"~"<<aux->codCanasta<<"->";
        aux=aux->siguiente;
     }
     cout<<aux->codPasillo<<"~"<<aux->codProducto<<"~"<<aux->codMarca<<"~"<<aux->nombre<<"~"<<aux->cantStock<<"~"<<aux->codCanasta<<"->";
     cout<<endl;
}

listaDCpas listaDCpas::ListaBase()
{
    listaDCpas lista;
    ifstream archivo;
    string texto;
    archivo.open("Pasillos.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string cod=token;
        token = strtok(NULL,var);
        string nom=token;
        pnodo aux=lista.primeroPas;
        bool rep=false;
        if(!lista.ListaVacia())
        {
            while(aux->siguiente!=lista.primeroPas)
            {   if(aux->codPasillo==cod){
                    rep=true;
                }
                aux=aux->siguiente;
            }
            if(lista.primeroPas->siguiente==lista.primeroPas)
            {
                if(aux->codPasillo==cod)
                    rep=true;
        	}
            if(rep==true)
                cout<<"El pasillo con codigo " <<cod << " ya existe."<<endl;
            if (rep==false)
                lista.InsertarFinal(cod,nom);
        }
        else
           lista.InsertarFinal(cod,nom);
    }
    //lista.Mostrar();
    archivo.close();
    return lista;
}




listaDCpas listaDCpas::SublistaPro()
{
    listaDCpas lista;
    listaDCpas listabas=lista.ListaBase();
    ifstream archivo;
    string texto;
    archivo.open("ProductosPasillos.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string codPas=token;
        token = strtok(NULL,var);
        string codPro=token;
        token = strtok(NULL,var);
        string nom=token;
        pnodo aux=listabas.primeroPas;
        int cont=1;
        while(aux->siguiente!=listabas.primeroPas||cont==listabas.largoLista())
        {
            if(aux->codPasillo==codPas)
            {
                if(aux->subsiguiente!=NULL)
                {
                    bool rep=false;
                    pnodo2 aux2=aux->subsiguiente;
                    while(aux2->siguiente!=aux->subsiguiente)
                    {
                        if(aux2->siguiente->codProducto==codPro){
                            rep=true;
                            break;}
					 	if(aux2->codProducto==codPro){
                            rep=true;
                            break;
                        }
                    aux2=aux2->siguiente;
                    }
                    if(aux->subsiguiente->siguiente==aux->subsiguiente)
                    {
                        if(aux2->codProducto==codPro)
                            rep=true;
                	}
                    if(rep==true)
                    {
                        cout<< "Ya existe un producto con el codigo "<< codPro<<endl;
                        aux=listabas.primeroPas;
                        break;
                	}
                    if (rep==false)
                    {
                        pnodo2 nuevo = new nodoProducto(codPas, nom, codPro);
                        nuevo->anterior = aux->subsiguiente->anterior;
                        nuevo->siguiente=aux->subsiguiente;
                        aux->subsiguiente->anterior->siguiente=nuevo;
                        aux->subsiguiente->anterior=nuevo;
                        break;
                    }
                }
                else
                {
                   aux->subsiguiente= new nodoProducto(codPas, nom, codPro);
                   aux->subsiguiente->anterior=aux->subsiguiente;
                   aux->subsiguiente->siguiente=aux->subsiguiente;
                   break;
            	}
            }
            cont++;
            aux=aux->siguiente;
        }
    }
archivo.close();
//listabas.MostrarTerc();
return listabas;
}

listaDCpas listaDCpas::SublistaMar()
{
    listaDCpas lista;
    listaDCpas listabas=lista.SublistaPro();
    ifstream archivo;
    string texto;
    archivo.open("MarcasProductos.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string codPas=token;
        token = strtok(NULL,var);
        string codPro=token;
        token = strtok(NULL,var);
        string codMar=token;
        token = strtok(NULL,var);
        string nom=token;
        token = strtok(NULL,var);
        string cantGondIni=token;
        stringstream cantconv(cantGondIni);
        int cantGond;
        cantconv>>cantGond;
        token = strtok(NULL,var);
        string precioIni=token;
        stringstream preconv(precioIni);
        int precio;
        preconv>>precio;
        pnodo aux=listabas.primeroPas;
        int cont=1;
        while(aux->siguiente!=listabas.primeroPas||cont==listabas.largoLista())
        {
            //cout<<aux->nombre<<endl;
            //cout<<nom<<codMar<<endl;
            //cout<< "se fija en el pasillo"<<endl;
            pnodo2 aux2=aux->subsiguiente;
            int temp=0;
            if(aux2!=NULL)
            {

                while(aux2->siguiente!=aux->subsiguiente||temp<1)
                {
                    bool deci=false;
                    if(aux2->codProducto==codPro){
                       //cout<<aux2->nombre<< " "<<aux2->codProducto<< " "<<codPro<<endl;
                        deci=true;}
                    if (deci==false)
                    {
                        //cout<<aux2->siguiente->nombre<< " "<<aux2->siguiente->codProducto<< " "<<codPro<<endl;
                        if(aux2->siguiente->codProducto==codPro)
                        {
                            aux2=aux2->siguiente;
                            deci=true;
                        }
                    }
                   //cout<<deci<<endl;
                    if(deci==true)
                    {
                        //cout<<"encuentra codigo"<<endl;
                        if(aux2->subsiguiente!=NULL)
                        {
                            //cout<< "ya existe una marca"<<endl;
                            bool rep=false;
                            pnodo3 aux3=aux2->subsiguiente;
                            while(aux3->siguiente!=aux2->subsiguiente)
                            {
                                //cout<< "entra a revisar repeticion por haber otra marca"<<endl;
                                //cout<< aux3->nombre<< " "<<aux3->codMarca<<" " << nom<<" "<<codMar<<endl;
                                if(aux3->codMarca==codMar){
                                    rep=true;
                                    break;
                                }
                                if(aux3->siguiente->codMarca==codMar){
                                    rep=true;
                                    break;
                                }
                                aux3=aux3->siguiente;
                            }
                            if(aux2->subsiguiente->siguiente==aux2->subsiguiente)
                            {
                                //cout<<"Es segunda marca entonces entra a if"<<endl;
                                if(aux3->codMarca==codMar)
                                    rep=true;
                            }
                            if(rep==true)
                            {
                                cout<< "Ya existe una Marca con el codigo "<< codMar<<endl;
                                aux=listabas.primeroPas;
                                break;
                            }
                            if (rep==false)
                            {
                                //cout<<"segunda marca entra bien"<<endl;
                                pnodo3 nuevo = new nodoMarca(codPas, nom, codPro,codMar,cantGond,precio);
                                nuevo->anterior = aux2->subsiguiente->anterior;
                                nuevo->siguiente=aux2->subsiguiente;
                                aux2->subsiguiente->anterior->siguiente=nuevo;
                                aux2->subsiguiente->anterior=nuevo;
                                break;
                            }
                        }
                        else
                        {
                            //cout<<"entra porque no hay ninguna otra marca"<<endl;
                            aux2->subsiguiente= new nodoMarca(codPas, nom, codPro,codMar,cantGond,precio);
                            aux2->subsiguiente->anterior=aux2->subsiguiente;
                            aux2->subsiguiente->siguiente=aux2->subsiguiente;
                            break;
                        }
                        break;
                    }
                    temp++;
                    aux2=aux2->siguiente;
                }
            }
            cont++;
            aux=aux->siguiente;
            if (cont>listabas.largoLista())
                break;
        }
        //listabas.MostrarTerc();
    }
archivo.close();
listabas.MostrarTerc();
return listabas;
}

listaDCCli  listaDCCli ::ListaClientes()
{
    listaDCCli lista;
    ifstream archivo;
    string texto;
    archivo.open("Clientes.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string ced=token;
        token = strtok(NULL,var);
        string nom=token;
        token = strtok(NULL,var);
        string cor=token;
        token = strtok(NULL,var);
        string tel=token;
        pnodo5 aux=lista.primeroCli;
        bool rep=false;
        if(!lista.ListaVacia())
        {
            while(aux->siguiente!=lista.primeroCli)
            {   if(aux->cedula==ced){
                    rep=true;
                }
                aux=aux->siguiente;
            }
            if(lista.primeroCli->siguiente==lista.primeroCli)
            {
                if(aux->cedula==ced)
                    rep=true;
        	}
            if(rep==true)
                cout<<"El cliente con cedula " <<ced << " ya existe."<<endl;
            if (rep==false)
                lista.InsertarFinal(ced,nom,tel,cor);
        }
        else
           lista.InsertarFinal(ced,nom,tel,cor);
    }
    lista.Mostrar();
    archivo.close();
    return lista;
}

listaDCInv listaDCInv::CrearInventario()
{
    listaDCInv lista;
    ifstream archivo;
    string texto;
    archivo.open("Inventario.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string codPas=token;
        token = strtok(NULL,var);
        string codPro=token;
        token = strtok(NULL,var);
        string codMar=token;
        token = strtok(NULL,var);
        string nom=token;
        token = strtok(NULL,var);
        string cantStkIni=token;
        stringstream cantconv(cantStkIni);
        int cantStk;
        cantconv>>cantStk;
        token = strtok(NULL,var);
        string decbool=token;
        bool canasta;
        if(decbool=="1")
            canasta=true;
        else
            canasta=false;
        pnodo4 aux=lista.primeroInv;
        bool rep=false;
        if(!lista.ListaVacia())
        {
            while(aux->siguiente!=lista.primeroInv)
            {
                if(aux->codPasillo==codPas&&aux->codProducto==codPro&&aux->codMarca==codMar)
                    rep=true;
                if(aux->siguiente->siguiente==lista.primeroInv)
                    if(aux->siguiente->codPasillo==codPas&&aux->siguiente->codProducto==codPro&&aux->siguiente->codMarca==codMar)
                        rep=true;
                aux=aux->siguiente;
            }
            if(aux->siguiente==lista.primeroInv)
                if(aux->siguiente->codPasillo==codPas&&aux->siguiente->codProducto==codPro&&aux->siguiente->codMarca==codMar)
                        rep=true;
            if(rep==false)
                lista.InsertarFinal(codPas, nom, codPro, codMar, cantStk, canasta);
            else
                cout<<"marca con codigo"<< codMar<<"esta repetido"<<endl;
        }
        else
            lista.InsertarFinal(codPas, nom, codPro, codMar, cantStk, canasta);
    }
archivo.close();
lista.Mostrar();
return lista;
}
//int main()
//{
//    listaDCpas Lista;
//    listaDCCli lista;
//    //Lista.ListaBase();
//    //Lista.SublistaPro();
//    Lista.SublistaMar();
//    cout<<"\n";
//    lista.ListaClientes();
//    cout<<"\n";
//    Lista.CrearInventario();
//    cin.get();
//    return 0;
//}

