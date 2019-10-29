#ifndef NODOS_H
#define NODOS_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <QtGlobal>
#include <bits/stdc++.h>
using namespace std;

enum Color {
    ROJO,
    NEGRO
};
class nodoMarca {
/*
Clase que construye los objetos de tipo nodo donde se
gurdan los datos de las marcas de los productos.
Clase amiga de lista marcas y la clase principal.
*/

   public:
    nodoMarca(string codPas, string nom, string codPro, string codMar, int cantGon, float val)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantGondola=cantGon;
        precio=val;
        cantcomp=0;
        hIzq = NULL;
        hDer = NULL;
        padre=NULL;
        siguiente=NULL;
        color=ROJO;
    }
   private:
    string codPasillo;
    string nombre;
    string codProducto;
    string codMarca;
    int cantGondola;
    float precio;
    int cantcomp;
    nodoMarca *hIzq;
    nodoMarca *hDer;
    nodoMarca *padre;
    nodoMarca *siguiente;
    Color color;

   friend class AVLProducto;
   friend class arbolPas;
   friend class RN;
   friend class lista;
   friend class Principal;
};
typedef nodoMarca*pnodoMarca;
class nodoProducto {
/*
Clase creadora de nodos de productos para ser
enlazado a los nodos de pasillo . Clase amiga
 de listaDCpas,listaSimple.
*/
public:
    nodoProducto(string codPas,string codPro, string nom)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        hIzq=NULL;
        hDer=NULL;
        siguiente=NULL;
        subsiguiente=NULL;
        cargaGondolas=0;
        masVend=0;
    }

    nodoMarca *subsiguiente;
    string codProducto;
    nodoProducto *hIzq;
    nodoProducto *hDer;
    int masVend;
    string nombre;
    int cargaGondolas;
private:
    int FB;
    string codPasillo;
    nodoProducto *siguiente;



   friend class arbolPas;
   friend class RN;
   friend class lista;
   friend class AVLProducto;
};
typedef nodoProducto *pnodoProd;
class nodoPasillo {
/*
Clase creadora de nodos de pasillo para ser
usados en listas. Clase amiga de listaDCpas,
listaSimple y nodoCarrito
*/
   public:
    nodoPasillo(string codPas, string nom)
    {
        codPasillo=codPas;
        nombre=nom;
        pasvis=0;
        hIzq=NULL;
        hDer=NULL;
        subsiguiente=NULL;
    }
   private:
    string codPasillo;
    string nombre;
    int pasvis;
    nodoPasillo *hIzq;
    nodoPasillo *hDer;
    nodoProducto *subsiguiente;
   friend class arbolPas;
   friend class AVLProducto;
   friend class RN;
   friend class Principal;
};
typedef nodoPasillo *pnodoPas;
class nodoCiudad{
   public:
    nodoCiudad(int cod, string nom)
    {
       codigo= cod;
       siguiente = NULL;
       nombre=nom;
    }

nodoCiudad(int cod, string nom, nodoCiudad * signodo)
    {
       codigo =cod;
       nombre=nom;
       siguiente = signodo;
    }

   private:
    int codigo;
    string nombre;
    nodoCiudad *siguiente;
   friend class Ciudad;
};
typedef nodoCiudad *pnodoCiudad;
class nodoInventario {
/*
Clase creadora de nodos de inventario para ser
usados en listas. Clase amiga de listaDCpas,
listaSimple y listaDCInv
*/

   public:
    nodoInventario(string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantStock=cantStk;
        codCanasta=canasta;
        string codi=codPas+codPro+codMar;
        stringstream codTrans(codi);
        int codigo;
        codTrans>>codigo;
        codArbol=codigo;
        hIzq = NULL;
        hDer = NULL;
        nivel=1;
        if (codCanasta){
            impuesto=1;
        }
        else{
            impuesto=13;
        }
    }
    string codMarca;
    string nombre;
    int impuesto;
   private:
    string codPasillo;
    bool codCanasta;
    string codProducto;
    int cantStock;
    int codArbol;
    nodoInventario *hIzq;
    nodoInventario *hDer;
    int nivel;

   friend class Principal;
   friend class ArbolInventario;
};
typedef nodoInventario *pnodoInventario;
using datosCliente=string[4];
typedef int tipoClave;
class Pagina;
typedef Pagina *pPagina;
class Pagina
{
protected:
    tipoClave *claves;
    pPagina *ramas;
    int cuenta;
    datosCliente *clientes;
private:
    int max;
public:
    Pagina(int orden)
    {
        this->max = orden;
        this->claves = new tipoClave[orden];
        this->clientes = new datosCliente[orden];
        this->ramas = new pPagina[orden];
        for(int i = 0; i <= orden; i++)
        {
            this->ramas[i] = nullptr;
        }
    }
    string obtenerDato (int y,int dato) {return this->clientes[y][dato];}
    void cambiarDato (int numCliente, int numDato , string dato) {this->clientes[numCliente][numDato] = dato;}
    bool nodoLleno() { return (this->cuenta == this->max - 1); }
    bool nodoSemiVacio() { return (this->cuenta < this->max / 2); }
    tipoClave obtenerClave(int i) { return this->claves[i]; }
    void cambiarClave(int i, tipoClave clave) { this->claves[i] = clave; }
    Pagina *obtenerRama(int i) { return this->ramas[i]; }
    void cambiarRamas(int i, Pagina *p) { this->ramas[i] = p; }
    int obtenerCuenta(){ return this->cuenta; }
    void cambiarCuenta(int valor) { this->cuenta = valor; }
};
class nodoPila {
   public:
    nodoPila(string pas, string prod, string codMarc1,float precio, int cant1)
    {
        codPas=pas;
        codProd=prod;
        codMarc=codMarc1;
        cant=cant1;
        precioP=precio;
        siguiente = NULL;
    }

    nodoPila(string pas, string prod, string codMarc1,float precio,int cant1, nodoPila * signodo)
    {
        codPas=pas;
        codProd=prod;
        codMarc=codMarc1;
        cant=cant1;
        precioP=precio;
        siguiente = signodo;
    }
    string codMarc;
    int cant;
    nodoPila *siguiente;
   private:
    string codPas;
    string codProd;
    //string codMarc;
    //int cant;
    float precioP;
    //nodoPila *siguiente;
   friend class Principal;
   friend class nodoCola;
   friend class Pila;
};
typedef nodoPila *pnodoPila;
class nodoCola {
   public:
    nodoCola(int ced, string nom, string ciudad,  string tel, string correo)
    {
       cedula=ced;
       nombre=nom;
       telefono=tel;
       correoC=correo;
       codCiudad=ciudad;
       siguiente = NULL;
       pila=NULL;
       descriptor=0;
    }
    nodoCola(int ced, string nom, string ciudad,  string tel, string correo,qintptr descri)
    {
       cedula=ced;
       nombre=nom;
       telefono=tel;
       correoC=correo;
       codCiudad=ciudad;
       siguiente = NULL;
       pila=NULL;
       descriptor=descri;
    }

nodoCola(int ced, string nom, string ciudad, string tel, string correo,qintptr descri, nodoCola * signodo)
    {
       cedula=ced;
       nombre=nom;
       telefono=tel;
       correoC=correo;
       codCiudad=ciudad;
       pila=NULL;
       siguiente = signodo;
       descriptor= descri;
       cantFact=0;
       montoFact=0;
    }
    nodoPila *pila;
    int cedula;
    nodoCola *siguiente;
    qintptr descriptor;
    int cantFact;
    float montoFact;
   private:
    string telefono;
    string correoC;
    string nombre;
    string codCiudad;

   friend class colaCliente;
   friend class Principal;
};
typedef nodoCola *pnodoCola;

class nodoListaVentas {
   public:
    nodoListaVentas(string codPas, string codProd, string codMar, int cant)
    {
        codPasillo=codPas;
        codProducto=codProd;
        codMarca=codMar;
        cantidad=cant;
        siguiente=NULL;
    }
    nodoListaVentas(string codPas, string codProd, string codMar, int cant, nodoListaVentas *signodo)
    {
        codPasillo=codPas;
        codProducto=codProd;
        codMarca=codMar;
        cantidad=cant;
        siguiente=signodo;
    }
   private:
    int cantidad;
    string codPasillo;
    string codProducto;
    string codMarca;
    string codCiudad;
    nodoListaVentas *siguiente;

   friend class listaVentas;
   friend class Principal;
};
typedef nodoListaVentas*pnodoVenta;

#endif // NODOS_H
