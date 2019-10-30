#ifndef PROGRAPRINCIPAL_H
#define PROGRAPRINCIPAL_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "headers/rojinegro.h"
#include "headers/lista.h"
#include "headers/ciudades.h"
#include "headers/avlProducto.h"
#include "headers/arbolPas.h"
#include "headers/arbolInventario.h"
#include "headers/arbolb.h"
#include "Principal.h"
#include "globalHeaders.h"

using namespace std;
/*
Metodos simples de insertar, mostrar ect
*/
//Ciudad:
void Ciudad::Mostrar()
{
    /*
    Muestra contenido de la lista de ciudades
    */


    nodoCiudad *aux;
    if (primero== NULL)
        cout << "No hay elementos";
    else
    {
        aux = primero;
        while(aux)
        {
            cout << aux->codigo<<" || "<<aux->nombre<< "-> ";
            aux = aux->siguiente;
        }
        cout << endl;
   }
}
int Ciudad::largoCiudad(){
    /*
    Dice el !argo de la lista de ciudad
    */

    int cont=0;
    pnodoCiudad aux;
    aux = primero;
    if(listaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }

}
void Ciudad::InsertarFinal(int cod, string nom)
{
    if (listaVacia())
        primero = new nodoCiudad(cod, nom);
    else
        { pnodoCiudad aux = primero;
            while ( aux->siguiente != NULL)
                aux= aux->siguiente;
                aux->siguiente=new nodoCiudad(cod, nom);
        }
}
bool Ciudad::agregarCiudad(Ciudad lista, int cod){
    /*
  Agrega ciudades a la lista
  */

    pnodoCiudad aux=lista.primero;
    while (aux!=NULL){
        if(aux->codigo==cod)
            return false;
        aux=aux->siguiente;
    }
    return true;
}
//Marcas
pnodoMarca RN::insertarNodo(pnodoMarca raiz, pnodoMarca pt){
    /*
    Inserta marcas a! Árbol
    */

    if (raiz == NULL)
        return pt;
    int codRaiz;
    stringstream codtrans(raiz->codMarca);
    codtrans>>codRaiz;
    int codIns;
    stringstream codtrans2(pt->codMarca);
    codtrans2>>codIns;
    if (codIns<codRaiz)
    {
        raiz->hIzq = insertarNodo(raiz->hIzq, pt);
        raiz->hIzq->padre = raiz;
    }
    else if (codIns > codRaiz)
    {
        raiz->hDer = insertarNodo(raiz->hDer, pt);
        raiz->hDer->padre = raiz;
    }
    else {
        return pt;
    }
    return raiz;
}
void RN::rotarIzquierda(nodoMarca *&raiz, nodoMarca *&pt)
{
    /*
    Rotación del árbol EN
    */

    pnodoMarca pt_hDer = pt->hDer;

    pt->hDer = pt_hDer->hIzq;

    if (pt->hDer != NULL)
        pt->hDer->padre = pt;

    pt_hDer->padre = pt->padre;

    if (pt->padre == NULL)
        raiz = pt_hDer;

    else if (pt == pt->padre->hIzq)
        pt->padre->hIzq = pt_hDer;

    else
        pt->padre->hDer = pt_hDer;

    pt_hDer->hIzq = pt;
    pt->padre = pt_hDer;
}
void RN::rotarDerecha(nodoMarca *&raiz, nodoMarca *&pt)
/*
Rotación del árbol RN
*/

{
    pnodoMarca pt_hIzq = pt->hIzq;

    pt->hIzq = pt_hIzq->hDer;

    if (pt->hIzq != NULL)
        pt->hIzq->padre = pt;

    pt_hIzq->padre = pt->padre;

    if (pt->padre == NULL)
        raiz = pt_hIzq;

    else if (pt == pt->padre->hIzq)
        pt->padre->hIzq = pt_hIzq;

    else
        pt->padre->hDer = pt_hIzq;

    pt_hIzq->hDer = pt;
    pt->padre = pt_hIzq;
}
void RN::balancearArbol(nodoMarca *&raiz, nodoMarca *&pt)
{
    /*
    Balancea el árbol
    */

    pnodoMarca padre_pt = NULL;
    pnodoMarca abuelo_pt = NULL;

    while ((pt != raiz) && (pt->color != NEGRO) &&
        (pt->padre->color == ROJO))
    {

        padre_pt = pt->padre;
        abuelo_pt = pt->padre->padre;
        if (padre_pt == abuelo_pt->hIzq)
        {
            pnodoMarca tio_pt = abuelo_pt->hDer;
            if (tio_pt != NULL && tio_pt->color == ROJO)
            {
                abuelo_pt->color = ROJO;
                padre_pt->color = NEGRO;
                tio_pt->color = NEGRO;
                pt = abuelo_pt;
            }
            else
            {
                if (pt == padre_pt->hDer)
                {
                    rotarIzquierda(raiz, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->padre;
                }
                rotarDerecha(raiz, abuelo_pt);
                swap(padre_pt->color, abuelo_pt->color);
                pt = padre_pt;
            }
        }
        else
        {
            pnodoMarca tio_pt = abuelo_pt->hIzq;
            if ((tio_pt != NULL) && (tio_pt->color == ROJO))
            {
                abuelo_pt->color = ROJO;
                padre_pt->color = NEGRO;
                tio_pt->color = NEGRO;
                pt = abuelo_pt;
            }
            else
            {
                if (pt == padre_pt->hIzq)
                {
                    rotarDerecha(raiz, padre_pt);
                    pt = padre_pt;
                    padre_pt = pt->padre;
                }
                rotarIzquierda(raiz, abuelo_pt);
                swap(padre_pt->color, abuelo_pt->color);
                pt = padre_pt;
            }
        }
    }

    raiz->color = NEGRO;
}
void RN::insert(const string &codPasilo,const string &nombre,const string &codProducto,const string &codMar,const int &gon, const float &val)
{
    pnodoMarca pt = new nodoMarca(codPasilo,nombre,codProducto,codMar,gon,val);
    raiz = insertarNodo(raiz, pt);
    balancearArbol(raiz, pt);
}
void RN::InordenMar(pnodoMarca R){
    /*
    Muestra el contenido del árbol
    */

 if(R==NULL){
        return;
    }else{
        InordenMar(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->codProducto<<"~"<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<<"/";
        InordenMar(R->hDer);
    }
}
string RN::InordenMarServ(pnodoMarca R){
    /*
    Muestra el contenido del árbol para server
    */

 if(R==NULL){
        return"";
    }else{
        string dev=R->codMarca+" "+ R->nombre+"\n";
        dev+=InordenMarServ(R->hIzq);
        dev+=InordenMarServ(R->hDer);
        return dev;
    }
}
//Listas para codigos repetidos
int lista::largoLista(){
    int cont=0;

    pnodoProd aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }

}
int lista::largoListaMar(){
    int cont=0;

    pnodoMarca aux;
    aux = primeroMar;
    if(ListaVaciaMar()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
}
void lista::InsertarFinal(string codPas, string codPro, string nom)
{
    /*
    Inserta al final de la lista
    */

   if (ListaVacia())
     primero = new nodoProducto(codPas,codPro,nom);
   else
     { pnodoProd aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoProducto(codPas,codPro,nom);
      }
}
void lista::InsertarFinalMar(string codPas, string nom, string codPro, string codMar,int cantGon,float precio)
{
    /*
    Inserta al final de la lista
    */

   if (ListaVaciaMar())
     primeroMar = new nodoMarca(codPas, nom, codPro, codMar, cantGon, precio);
   else
     { pnodoMarca aux = primeroMar;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoMarca(codPas, nom, codPro, codMar, cantGon, precio);
      }
}
void lista::Mostrar()
{
   nodoProducto *aux;
   if (primero== NULL)
       cout << "No hay elementos";
   else
   {


        aux = primero;
        while(aux)
        {
            cout <<aux->codPasillo<<"~"<<aux->codProducto<<"~"<<aux->nombre<< "-> ";
            aux = aux->siguiente;
        }
        cout << endl;
   }
}
void lista::MostrarMar()
{
    /*
    Muestra las marcas
    */

   nodoMarca *R;
   if (primeroMar== NULL)
       cout << "No hay elementos";
   else
   {
        R = primeroMar;
        while(R)
        {
            cout<<R->codPasillo<<"~"<<R->codProducto<<"~"<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<< "-> ";
            R = R->siguiente;
        }
        cout << endl;
   }
}
//Pasillos
void arbolPas::InordenI(pnodoPas R){
    /*
    Muestra los pasillos
    */

    if(R==NULL){
        return;
    }else{
        InordenI(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->nombre<<"||";
        InordenI(R->hDer);
    }
}
string arbolPas::InordenServ(pnodoPas R){
    /*
    Muestra los pasillos
    */

    if(R==NULL){
        return "";
    }else{
        string conc=R->codPasillo+ " " + R->nombre +"\n";
        conc+=InordenServ(R->hIzq);
        conc+=InordenServ(R->hDer);
        return conc;
    }
}
void arbolPas::InsertaBinario(pnodoPas aux,string cod, string nombre)
{
    /*
    Inserta al árbol binario
    */

    stringstream codi(cod);
    int valor;
    codi>>valor;
    if (arbolVacio()){
        raiz=new nodoPasillo(cod, nombre);
    }
    else{
        stringstream codRa(aux->codPasillo);
        int valRa;
        codRa>>valRa;
        if(valor<valRa){
            if(aux->hIzq==NULL){
                aux-> hIzq = new nodoPasillo(cod, nombre);
            }else{
                InsertaBinario(aux->hIzq,cod, nombre);
            }
        }else if(valor>valRa){
            if(aux->hDer==NULL){
                aux->hDer = new nodoPasillo(cod,nombre);
            }else{
                InsertaBinario(aux->hDer,cod, nombre);
            }
        }
    }
}
arbolPas arbolPas::ListaBase()
{
/*
Metodo que crea la lista de pasillos a
partir de archivos
*/

    arbolPas pasillos;
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
        bool rep=false;
        pasillos.InsertaBinario(pasillos.raiz,cod, nom);
    }
    archivo.close();
    return pasillos;
}
void arbolPas::InordenTriple(pnodoPas R){
    /*
    Muestra todas las estructuras
    */


    if(R==NULL){
        return;
    }else{
        InordenTriple(R->hIzq);
        cout<<"||"<<R->codPasillo<<"~"<<R->nombre;
        AVLProducto pro;
        pro.raiz=R->subsiguiente;
        pro.InordenPro(R->subsiguiente);
        InordenTriple(R->hDer);
    }
}
//Productos
void AVLProducto::InsertarBalanceado(nodoProducto *aux, nodoProducto *ra, bool Hh, string codPas, string codProd, string nomProd){
    /*
    Inserta en el AVL
    */

    pnodoProd n1;
    stringstream cp(codProd);
    int codProdu;
    cp>>codProdu;
    int codProduAux;
    if(aux!=NULL){
        stringstream cpa(aux->codProducto);
        cpa>>codProduAux;
    }
    else{
        stringstream cpa(ra->codProducto);
        cpa>>codProduAux;
    }
    if(raiz==NULL){
        raiz=new nodoProducto(codPas,codProd,nomProd);
        Hh = true;
        return;
    }
    else if(aux==NULL&&raiz!=NULL){
        if(codProdu<codProduAux)
            ra->hIzq=new nodoProducto(codPas,codProd,nomProd);
        else if(codProdu>codProduAux)
            ra->hDer=new nodoProducto(codPas,codProd,nomProd);
        //cout<<raiz->hDer->hDer<<endl;
        //cout<<"Otros: "<<->valor<<endl;
        Hh = true;
    }else{
        //cout<<"q as2"<<endl;
        if(codProdu<codProduAux){
            InsertarBalanceado(aux->hIzq,aux, Hh,codPas,codProd,nomProd);

        if(Hh){
            switch(aux->FB){
                case 1: aux->FB=0;
                Hh = false;
                break;
                case 0: aux->FB  = -1;
                break;
                case -1: n1=aux->hIzq;
                if(n1->FB==-1){
                    RotacionSimpleIzquierda(aux, n1);
                    if(aux->codProducto==raiz->codProducto)
                        raiz=n1;
                }else{
                    RotacionDobleIzquierda(aux,n1);
                    if(aux->codProducto==raiz->codProducto)
                        raiz=n1;
                }
                Hh = false;
                break;
            }
        }
        }else{
            if(codProdu>codProduAux){
            InsertarBalanceado(aux->hDer,aux, Hh,codPas,codProd,nomProd);
                if(Hh){
                    switch(aux->FB){
                        case -1: aux->FB=0;
                        Hh = false;
                        break;
                        case 0: aux->FB=1;
                        break;
                        case 1:n1=aux->hDer;
                        if(n1->FB==1){
                            RotacionSimpleDerecha(aux, n1);
                            if(aux->codProducto==raiz->codProducto)
                                raiz=n1;
                        }else{
                            RotacionDobleDerecha(aux, n1);
                            if(aux->codProducto==raiz->codProducto)
                                raiz=n1;
                        }
                        Hh=false;
                        break;
                    }
                }
            }
        }
    }
}
void AVLProducto::RotacionDobleIzquierda(nodoProducto* n, nodoProducto* n1){
    /*
   Rotación del AVL
   */

    nodoProducto *n2;
    n2=n1->hDer;
    n->hIzq = n2->hDer;
    n2->hDer=n;
    n1->hDer=n2->hIzq;
    n2->hIzq=n1;

    if(n2->FB==1){
        n1->FB=-1;
    }else{
        n1->FB=0;
    }
    if(n2->FB==-1){
        n->FB=1;
    }else{
        n->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void AVLProducto::RotacionDobleDerecha(nodoProducto* n, nodoProducto* n1){
    /*
  Rotación del VAL
  */

    nodoProducto *n2;
    n2=n1->hIzq;
    n->hDer = n2->hIzq;
    n2->hIzq=n;
    n1->hIzq=n2->hDer;
    n2->hDer=n1;

    if(n2->FB==1){
        n->FB=-1;
    }else{
        n->FB=0;
    }
    if(n2->FB==-1){
        n1->FB=1;
    }else{
        n1->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void AVLProducto::RotacionSimpleDerecha(nodoProducto* n, nodoProducto* n1){
    /*
  Rotación del VAL
  */

    n->hDer=n1->hIzq;
    n1->hIzq=n;

    if(n1->FB==1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=1;
        n1->FB=-1;
    }
    n=n1;
}
void AVLProducto::RotacionSimpleIzquierda(nodoProducto* n, nodoProducto* n1){
    /*
  Rotación del VAL
  */

    n->hIzq=n1->hDer;
    n1->hDer=n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=-1;
    }
    n=n1;
}
void AVLProducto::InordenPro(pnodoProd R){
    /*
   Muestra información del AVL
   */

    if(R==NULL){
        return;
    }else{
        InordenPro(R->hIzq);
        cout<<"|||"<<R->codPasillo<<"~"<<R->codProducto<<R->nombre<<"||||";
        RN mar;
        mar.raiz=R->subsiguiente;
        mar.InordenMar(R->subsiguiente);
        InordenPro(R->hDer);
    }
}
string AVLProducto::InordenProServ(pnodoProd R){
    /*
   Muestra información del AVL
   */

    if(R==NULL){
        return "";
    }else{
        string conc=R->codProducto+" "+R->nombre+"\n";
        conc+=InordenProServ(R->hIzq);
        conc+=InordenProServ(R->hDer);
        return conc;
    }
}
//Inventario
pnodoInventario ArbolInventario::insertar(int conca, string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta, pnodoInventario aux)
{
    /*
    Inserta información al inventario
    */

    if (aux==NULL){
        aux=new nodoInventario(codPas, nom, codPro, codMar, cantStk, canasta);
    }
    else if (conca<aux->codArbol){
        aux->hIzq=insertar(conca,codPas, nom, codPro, codMar, cantStk, canasta, aux->hIzq);
    }
    else if (conca>aux->codArbol){
        aux->hDer=insertar(conca,codPas, nom, codPro, codMar, cantStk, canasta, aux->hDer);
    }
    else {
        cout<<"Repetido"<<endl;
        return aux;
    }
    aux=giro(aux);
    aux=reparto(aux);
    return aux;
}
pnodoInventario ArbolInventario::giro( pnodoInventario aux )
{
    /*
    Giro del AA
    */

    if (aux->hIzq==NULL){
        return aux;
    }
    if(aux->hIzq->nivel == aux->nivel ){
        aux= rotarIzquierda( aux );
    }
    return aux;
}
pnodoInventario ArbolInventario::reparto(pnodoInventario aux)
{
    if (aux->hDer==NULL){
        return aux;
    }
    if( aux->hDer->nivel == aux->nivel && aux->hDer->hDer!=NULL && aux->hDer->hDer->nivel==aux->nivel)
    {
        aux= rotarDerecha(aux);
        aux->nivel++;
    }
    return aux;
}
pnodoInventario ArbolInventario::rotarIzquierda(pnodoInventario aux)
{
    pnodoInventario otro=aux->hIzq;
    aux->hIzq = otro->hDer;
    otro->hDer= aux;
    return otro;
}
/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
*/
pnodoInventario ArbolInventario::rotarDerecha(pnodoInventario aux)
{
    pnodoInventario otro = aux->hDer;
    aux->hDer= otro->hIzq;
    otro->hIzq=aux;
    return otro;
}
//Cola de clientes
void colaCliente::BorrarInicio()
{
    /*
    Borra el inicio de la cola de clientes.
    */
    if (ListaVacia()){
     cout << "No hay elementos en la lista:" << endl;

   }else{
        if (primero->siguiente == NULL) {
                primero= NULL;
            } else {

                pnodoCola aux = primero;
                primero=primero->siguiente;
                delete aux;
            }
        }
}
void colaCliente::InsertarFinal(int ced, string nom,string ciudad, string tel, string correo,qintptr descriptor)
{
/*
Metodo de la clase lista clientes. Su funcion es insertar un nodo
con la informacion al final de la lista. No retorna nada. Recibe los valores
que se van a insertar en el nodo.
*/
    if (ListaVacia())
    {
        primero = new nodoCola(ced, nom, ciudad, tel, correo, descriptor);
    }
    else
    {
        pnodoCola aux = primero;
        while ( aux->siguiente != NULL)
            aux= aux->siguiente;
        aux->siguiente=new nodoCola(ced, nom, ciudad, tel, correo, descriptor);
    }
}
void colaCliente::Mostrar()
{
    /*
    Muestra la cola de clientes
    */
   pnodoCola aux;
   if (primero== NULL)
       cout << "No hay elementos";
   else
   {
           aux = primero;
        while(aux!=NULL)
        {
            cout << "Ced: "<<aux->cedula<<" Nombre: "<<aux->nombre<<" Tel: "<<aux->telefono<<" Correo: "<<aux->correoC<< "-> ";
            aux = aux->siguiente;
        }
        cout << endl;
   }
}
int colaCliente::largoLista(){
    /*
    Retorna el largo de la cola de clientes.
    */
    int cont=0;
    pnodoCola aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
}
bool colaCliente::agregarCliente(colaCliente cola, int ced){
    /*
    Agrega cliente a la cola
    */

    pnodoCola aux=cola.primero;
    while (aux!=NULL){
        if(aux->cedula==ced)
            return false;
        aux=aux->siguiente;
    }
    return true;
}
//Crear Estructuras
lista lista::enlistarCodigos(){
    /*
    Genera lista de códigos de archivo
    */

    lista listaAlm;
    ifstream archivo;
    string texto;
    archivo.open("ProductosPasillos.txt",ios::in);
    while(!archivo.eof())
    {
        //cout<<"ciclo"<<endl;
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
        bool rep=false;
        if(!listaAlm.ListaVacia())
        {
           //cout<<"siay nada"<<endl;
            pnodoProd aux=listaAlm.primero;
            for(int i=0; i<listaAlm.largoLista(); i++)
            {
                //cout<<"vuelto loko prro"<<codPro<<" "<<aux->codProducto<<endl;
                if(aux->codProducto==codPro){
                    rep=true;
                    //cout<<"cmamo"<<endl;
                }
                aux=aux->siguiente;
            }
            if(rep==false)
                listaAlm.InsertarFinal(codPas,codPro,nom);
        }
        else{
          //cout<<"nuai nada"<<endl;
          listaAlm.InsertarFinal(codPas,codPro,nom);
        }
    }
    //listaAlm.Mostrar();
    return listaAlm;
}
void AVLProducto::EnlaceAvl(nodoPasillo *nodoPas,nodoProducto *nodoPro){
    /*
    Enlaza nodos de lista con árbol
    */

    if(nodoPas==NULL){
        return;
    }else{
        EnlaceAvl(nodoPas->hIzq, nodoPro);
        if(nodoPas->codPasillo==nodoPro->codPasillo)
        {
            if(nodoPas->subsiguiente==NULL){
                nodoPas->subsiguiente=nodoPro;
            }
            else{
                AVLProducto ArbolEnla;
                ArbolEnla.raiz=nodoPas->subsiguiente;
                ArbolEnla.InsertarBalanceado(ArbolEnla.raiz, ArbolEnla.raiz, false,nodoPro->codPasillo,nodoPro->codProducto,nodoPro->nombre);
            }
        }
        EnlaceAvl(nodoPas->hDer, nodoPro);
    }
}
string AVLProducto::EnlaceRNServ(nodoProducto *nodoPro, string codi){
    /*
    Genera lista de marcas para el servidor
    */

    if(nodoPro==NULL){
        return"";
    }else{
        string dev;
        cout<<codi<<endl;
        if(nodoPro->codProducto==codi)
        {
            RN arb;
            dev=arb.InordenMarServ(nodoPro->subsiguiente);
        }
        dev+=EnlaceRNServ(nodoPro->hIzq, codi);
        dev+=EnlaceRNServ(nodoPro->hDer, codi);
        return dev;
    }
}
string AVLProducto::EnlaceAvlServ(nodoPasillo *nodoPas,string req){
    /*
    Genera lista de productos para el sevidor
    */

    if(nodoPas==NULL){
        return"";
    }else{
        string dev;
        if(nodoPas->codPasillo==req)
        {
            dev=InordenProServ(nodoPas->subsiguiente);
        }
        dev+=EnlaceAvlServ(nodoPas->hIzq, req);
        dev+=EnlaceAvlServ(nodoPas->hDer, req);
        return dev;
    }
}
string AVLProducto::EnlaceAvlServPro(nodoPasillo *nodoPas,string req){
    if(nodoPas==NULL){
        return"";
    }else{
        string dev;
        char cstr[req.size() + 1];
        strcpy(cstr, req.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        token = strtok(NULL,var);
        string comp=token;
        token = strtok(NULL,var);
        if(nodoPas->codPasillo==comp)
        {
            cout<<"encont"<<token<<endl;
            dev=EnlaceRNServ(nodoPas->subsiguiente,token);
        }
        dev+=EnlaceAvlServPro(nodoPas->hIzq, req);
        dev+=EnlaceAvlServPro(nodoPas->hDer, req);
        return dev;
    }
}
arbolPas arbolPas::arbolProductos(){
    /*
    Genera árbol de productos
    */

    AVLProducto arbolProd;
    lista listaCod;
    listaCod=listaCod.enlistarCodigos();
    arbolPas arbolPasillo;
    arbolPasillo=arbolPasillo.ListaBase();
    pnodoProd aux=listaCod.primero;
    for(int i=0; i<listaCod.largoLista();i++)
    {
        arbolProd.EnlaceAvl(arbolPasillo.raiz, aux);
        aux=aux->siguiente;
    }
    return arbolPasillo;
}
lista lista::enlistarCodigosMar(){
    /*
    Generar lista de códigos de archivo
    */

    lista listaAlm;
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
        bool rep=false;
        if(!listaAlm.ListaVacia())
        {
           //cout<<"siay nada"<<endl;
            pnodoMarca aux=listaAlm.primeroMar;
            for(int i=0; i<listaAlm.largoListaMar(); i++)
            {
                //cout<<"vuelto loko prro"<<codPro<<" "<<aux->codProducto<<endl;
                if(aux->codMarca==codMar){
                    rep=true;
                    //cout<<"cmamo"<<endl;
                }
                aux=aux->siguiente;
            }
            if(rep==false)
                listaAlm.InsertarFinalMar(codPas,nom,codPro,codMar,cantGond,precio);
        }
        else{
          //cout<<"nuai nada"<<endl;
          listaAlm.InsertarFinalMar(codPas,nom,codPro,codMar,cantGond,precio);
        }
    }
    //listaAlm.MostrarMar();
    return listaAlm;
}
void AVLProducto::EnlaceRN(nodoProducto *nodoPro, nodoMarca *nodoMar){
    if(nodoPro==NULL){
        return;
    }else{
        EnlaceRN(nodoPro->hIzq, nodoMar);
        if(nodoPro->codProducto==nodoMar->codProducto)
        {
            //cout<<nodoPro->codProducto<<nodoMar->codProducto<<endl;
            if(nodoPro->subsiguiente==NULL){
                RN ArbolEnla;
                ArbolEnla.raiz=nodoPro->subsiguiente;
                ArbolEnla.insert(nodoMar->codPasillo,nodoMar->nombre,nodoMar->codProducto,nodoMar->codMarca,nodoMar->cantGondola,nodoMar->precio);
                nodoPro->subsiguiente=ArbolEnla.raiz;

            }
            else{
                RN ArbolEnla;
                ArbolEnla.raiz=nodoPro->subsiguiente;
                ArbolEnla.insert(nodoMar->codPasillo,nodoMar->nombre,nodoMar->codProducto,nodoMar->codMarca,nodoMar->cantGondola,nodoMar->precio);
                nodoPro->subsiguiente=ArbolEnla.raiz;
            }
        }
        EnlaceRN(nodoPro->hDer, nodoMar);
    }
}
nodoProducto* arbolPas::busquedaPro(nodoPasillo *nodoPas,nodoMarca* nodoMar){
    /*
    Busca un nodo de producto
    */

    if(nodoPas==NULL){
    }else{
        busquedaPro(nodoPas->hIzq, nodoMar);
        if(nodoPas->codPasillo==nodoMar->codPasillo)
        {
            if(nodoPas->subsiguiente==NULL){
            }
            else{
                AVLProducto arbol;
                arbol.raiz=nodoPas->subsiguiente;
                arbol.EnlaceRN(nodoPas->subsiguiente,nodoMar);
            }
        }
        busquedaPro(nodoPas->hDer, nodoMar);
    }
}
arbolPas arbolPas::arbolMarcas(){
    lista listaCod;
    listaCod=listaCod.enlistarCodigosMar();
    arbolPas arbolPasillo;
    arbolPasillo=arbolPasillo.arbolProductos();
    pnodoMarca aux=listaCod.primeroMar;
    for(int i=0; i<listaCod.largoListaMar();i++)
    {
       pnodoProd encont=arbolPasillo.busquedaPro(arbolPasillo.raiz, aux);
       aux=aux->siguiente;
    }
    //arbolPasillo.InordenTriple(arbolPasillo.raiz);
    return arbolPasillo;
}
Ciudad Ciudad::agregarCiudades(){
    /*
    Agrega ciudades a la lista
    */

    Ciudad listaCiudades;
    ifstream archivo;
    string ciudad;
    archivo.open("Ciudades.txt", ios::in);
    if (archivo.fail()){
        cout<<"Error al leer el archivo"<<endl;
    }
    else{
        while(!archivo.eof())
        {
            getline(archivo, ciudad);
            char cstr[ciudad.size()+1];
            strcpy(cstr, ciudad.c_str());
            char *frase=cstr;
            char *aux;
            aux=strtok(frase,";");
            string cod;
            stringstream codStr;
            codStr<<aux;
            codStr>>cod;
            stringstream stringInt(cod);
            int codI;
            stringInt>>codI;
            aux=strtok(NULL, ";");
            string nom=aux;
            if (listaCiudades.listaVacia()){
                listaCiudades.InsertarFinal(codI, nom);
            }
            bool agregar=agregarCiudad(listaCiudades, codI);
            if(agregar){
                listaCiudades.InsertarFinal(codI, nom);
            }
        }
    }
    //listaCiudades.Mostrar();
    return listaCiudades;
}
void ArbolInventario::Inorden(pnodoInventario R){

 if(R==NULL){
        return;
    }else{
        Inorden(R->hIzq);
        cout<<R->codArbol<<" ** "<<R->nivel<<"->";
        Inorden(R->hDer);
    }
}
ArbolInventario ArbolInventario::agregarInventario(){
    /*
    Agrega productos al inventario
    */

    ArbolInventario inventario;
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
        string conc=codPas+codPro+codMar;
        stringstream codTrans(conc);
        int codArbol;
        codTrans>>codArbol;
        inventario.raiz=insertar(codArbol,codPas, nom, codPro, codMar, cantStk, canasta, inventario.raiz);
    }
    archivo.close();
    //cout<<"Inorden: "<<endl;
    //inventario.Inorden(inventario.raiz);
    return inventario;
}
void ArbolB::insertar(tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo)
{
    /*
    Inserta el árbol B
    */

    raiz = insertar(raiz, cl, nombre, telefono, codigoCiudad, correo);
}
Pagina* ArbolB::insertar(Pagina *r, tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo)
{
    bool subeArriba;
    int mediana;
    Pagina *nd;
    subeArriba = empujar(r, cl,  mediana, nd, nombre, telefono, codigoCiudad, correo);
    // El arbol crece de nivel y se inserta la clave mediana
    if(subeArriba)
    {
        Pagina *p;
        p = new Pagina(orden);
        p->cambiarCuenta(1);
        p->cambiarClave(1, mediana);
        p->cambiarDato(1,0,nombre);
        p->cambiarDato(1,1,telefono);
        p->cambiarDato(1,2,codigoCiudad);
        p->cambiarDato(1,3,correo);
        // Claves menores
        p->cambiarRamas(0, r);
        // Claves mayores
        p->cambiarRamas(1, nd);
        r = p;
    }
    return r;
}
bool ArbolB::empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo, string &nombre, string &telefono, string &codigoCiudad, string &correo)
{
    /*
    Método de empuje del árbol B
    */

    int k;
    bool subeArriba = false;
    // Llego a una pagina nula
    if(actual == NULL)
    {
        // Se devuelve hacia la pagina padre
        subeArriba = true;
        mediana = cl;
        nuevo = NULL;
    }
    else
    {
        bool esta;
        esta = buscarNodo(actual, cl, k);
        if (esta) {
            throw "\nClave duplicada";
        }
        subeArriba = empujar(actual->obtenerRama(k), cl, mediana, nuevo, nombre, telefono, codigoCiudad, correo);
        if (subeArriba) {
            if (!actual->nodoLleno()) {
                subeArriba = false;
                meterPagina(actual, mediana, nuevo, k, nombre, telefono, codigoCiudad, correo);
            } else {
                subeArriba = true;
                dividirNodo(actual, mediana, nuevo, k, nombre, telefono, codigoCiudad, correo);
            }
        }
    }
    return subeArriba;
}
/**
 * Revisa si la clave se encuentra en el arbol
 * @param actual La pagina actual
 * @param cl La clave que se busca
 * @param k La posicion de la pagina
 * @return verdadero si se encuentra la clave
 */
bool ArbolB::buscarNodo(Pagina *actual, tipoClave cl, int &k)
{
    int index;
    bool encontrado;
    // Revisar si la clave esta en la pagina
    if(cl < actual->obtenerClave(1))
    {
        encontrado = false;
        index = 0;
    }
    else
    {
        // Llegar a la posicion que debe tener la clave
        index = actual->obtenerCuenta();
        while(cl < actual->obtenerClave(index) && index > 1)
        {
            index--;
        }
        // Revisar si la clave existe
        encontrado = cl == actual->obtenerClave(index);
    }
    k = index;
    return encontrado;
}
/**
 * Baja por las ramas del arbol hasta encontrar la clave
 * @param cl La clave que se desea buscar
 * @param n
 * @return La referencia al nodo donde se encuentra la clave
 */
Pagina* ArbolB::buscar(tipoClave cl, int &n)
{
    /*
    Busca nodo del árbol B
    */

    return buscar(this->raiz, cl, n);
}

/**
 * Recorre todos los nodos en busca de las claves
 * @param actual
 * @param cl
 * @param n
 * @return
 */
Pagina* ArbolB::buscar(Pagina *actual, tipoClave cl, int &n)
{
    /*
    Busca nodo del árbol B
    */

    // Parada de la funcion recursiva
    if(actual == nullptr)
    {
        return nullptr;
    }
    else
    {
        // Verificar si existe dentro del nodo
        bool esta = buscarNodo(actual, cl, n);
        if (esta)
            return actual;
        else
            return buscar(actual->obtenerRama(n), cl, n);
    }
}
void ArbolB::meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k, string nombre, string telefono, string codigoCiudad, string correo)
{
    /*
    Inserta página al árbol B
    */

    // Desplazar elementos a la derecha
    for(int i = actual->obtenerCuenta(); i >= k + 1; i--)
    {
        actual->cambiarClave(i + 1, actual->obtenerClave(i));
        actual->cambiarDato(i+1 , 0 , actual->obtenerDato(i,0));
        actual->cambiarDato(i+1 , 1 , actual->obtenerDato(i,1));
        actual->cambiarDato(i+1 , 2 , actual->obtenerDato(i,2));
        actual->cambiarDato(i+1 , 3 , actual->obtenerDato(i,3));
        actual->cambiarRamas(i + 1, actual->obtenerRama(i));
    }
    // Pone la clave y la rama derecha en la posicion k + 1
    actual->cambiarClave(k + 1, cl);
    actual->cambiarDato(k+1,0,nombre);
    actual->cambiarDato(k+1,1,telefono);
    actual->cambiarDato(k+1,2,codigoCiudad);
    actual->cambiarDato(k+1,3,correo);
    actual->cambiarRamas(k + 1, ramaDr);
    // Incrementa el numero de claves
    actual->cambiarCuenta(actual->obtenerCuenta() + 1);
}
void ArbolB::dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos, string &nombre, string &telefono, string &codigoCiudad, string &correo)
{
    int i, posMdna, k;
    Pagina *nuevaPag;
    k = pos;
    // Posicion de la clave mediana
    posMdna = (k <= orden / 2) ? orden / 2 : orden / 2 + 1;
    nuevaPag = new Pagina(orden);
    for(i = posMdna + 1; i < orden; i++)
    {
        nuevaPag->cambiarClave(i - posMdna, actual->obtenerClave(i));
        nuevaPag->cambiarRamas(i - posMdna, actual->obtenerRama(i));
        nuevaPag->cambiarDato(i - posMdna , 0 , actual->obtenerDato(i,0));
        nuevaPag->cambiarDato(i - posMdna , 1 , actual->obtenerDato(i,1));
        nuevaPag->cambiarDato(i - posMdna , 2 , actual->obtenerDato(i,2));
        nuevaPag->cambiarDato(i - posMdna , 3 , actual->obtenerDato(i,3));
    }
    nuevaPag->cambiarCuenta((orden - 1) - posMdna);
    actual->cambiarCuenta(posMdna);
    if (k <= orden / 2)
        meterPagina(actual, mediana, nuevo, pos, nombre, telefono, codigoCiudad, correo);
    else
    {
        pos = k - posMdna;
        meterPagina(nuevaPag, mediana, nuevo, pos, nombre, telefono, codigoCiudad, correo);
    }
    mediana = actual->obtenerClave(actual->obtenerCuenta());
    nombre = actual->obtenerDato(actual->obtenerCuenta(),0);
    telefono = actual->obtenerDato(actual->obtenerCuenta(),1);
    codigoCiudad = actual->obtenerDato(actual->obtenerCuenta(),2);
    correo = actual->obtenerDato(actual->obtenerCuenta(),3);
    nuevaPag->cambiarRamas(0, actual->obtenerRama(actual->obtenerCuenta()));
    actual->cambiarCuenta(actual->obtenerCuenta() - 1);
    nuevo = nuevaPag;
}
void ArbolB::escribir()
{
    /*
    Método de muestra del árbol B
    */

    escribir(raiz, 1);
}
void ArbolB::escribir(Pagina *r, int h)
{
    /*
    Método de muestra del árbol B
    */

    int i;
    if (r != NULL)
    {
        escribir(r->obtenerRama(0), h + 5);
        for(int i = 1; i <= r->obtenerCuenta() / 2; i++){
            escribir(r->obtenerRama(i), h + 5);
            cout << endl;
        }
        for(i = 1; i <= r->obtenerCuenta(); i++)
        {
            for(int j = 0; j <= h; j++)
            {
                cout << " ";
            }
            cout << r->obtenerClave(i) <<","<< r->obtenerDato(i,0) << endl;
        }
        for(i = r->obtenerCuenta() / 2 + 1; i <= r->obtenerCuenta(); i++)
        {
            this->escribir(r->obtenerRama(i), h + 5);
        }
        cout << endl;
    }
}
void ArbolB::listaCreciente()
{
    /*
    Método de muestra del árbol B
    */

    inOrden(raiz);
}
void ArbolB::inOrden(Pagina *r)
{
    /*
    Método de muestra del árbol B
    */

    if(r)
    {
        inOrden(r->obtenerRama(0));
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            cout << r->obtenerClave(k) <<","<< r->obtenerDato(k,0) << endl;" - ";
            inOrden(r->obtenerRama(k));
        }
    }
}
void ArbolB::cargarClientes(string pNombreArchivo){
    /*
    Genera árbol de clientes
    */

    //ArbolB cliente;
    int n;
    bool repetido;
    int cedula;
    string codigoCiudad;
    string linea;
    string cedulaS;
    string nombre;
    string telefono;
    string correo;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,cedulaS,';');
        getline(lineaActual,nombre,';');
        getline(lineaActual,codigoCiudad,';');
        getline(lineaActual,telefono,';');
        getline(lineaActual,correo,';');
        cedula = stoi (cedulaS);
        Pagina* aux = buscar(cedula,n);
        if (aux == NULL){
            insertar(cedula,nombre,telefono,codigoCiudad,correo);
            princi.cliente.InsertarFinalCliente(cedula,nombre,codigoCiudad,telefono,correo);
        }
    }
    archivo.close();
    //return cliente;
}
void ArbolB::cargarAdmins(string pNombreArchivo){
    /*
    Genera árbol de administradores
    */

    int n;
    bool repetido;
    int cedula;
    string linea;
    string cedulaS;
    string nombre;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,cedulaS,';');
        getline(lineaActual,nombre,';');
        cedula = stoi (cedulaS);
        Pagina* aux = buscar(cedula,n);
        if (aux == NULL){
            insertar(cedula,nombre,"","","");
        }
    }
    archivo.close();
}

//Funcionalidad
//Comprar
void arbolPas::MostrarProductos(pnodoPas R, string codPas){
    /*
    Muestra los productos del árbol
    */

    if(R==NULL){
        return;
    }else{
        MostrarProductos(R->hIzq, codPas);
        if (R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            pro.MostrarProductos(R->subsiguiente);
        }
        MostrarProductos(R->hDer, codPas);
    }
}
void AVLProducto::MostrarProductos(pnodoProd R){
    /*
    Muestra los productos del árbol
    */

    if(R==NULL){
        return;
    }else{
        MostrarProductos(R->hIzq);

        cout<<R->nombre<<" "<<R->codProducto<<endl;
        MostrarProductos(R->hDer);
    }
}
void arbolPas::MostrarPasillos(pnodoPas ra){
    /*
    Muestra los pasillos del árbol
    */

    if (ra==NULL){
        return;
    }
    else{
        MostrarPasillos(ra->hIzq);
        cout<<ra->nombre<<" "<<ra->codPasillo<<endl;
        MostrarPasillos(ra->hDer);
    }
}
bool arbolPas::encontrarPasillo(bool encontrado, pnodoPas ra, string codPas){
    /*
    Búsqueda de pasillo en el árbol
    */

    if (ra==NULL){
    }
    else{
        encontrado=encontrarPasillo(encontrado, ra->hIzq, codPas);
        if (codPas==ra->codPasillo){
            encontrado=true;
        }
        encontrado=encontrarPasillo(encontrado, ra->hDer, codPas);
    }
    return encontrado;

}
bool arbolPas::ValidarProducto1(pnodoPas R, string codPas,string codProd ,bool valido){
    /*
    Validación de la existencia del producto
    */

    if(R==NULL){
    }else{
        valido=ValidarProducto1(R->hIzq, codPas, codProd, valido);
        if (R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            valido=pro.validarProducto2(R->subsiguiente,codPas, codProd, valido);

        }
        valido=ValidarProducto1(R->hDer, codPas, codProd, valido);
    }
    return valido;
}
bool AVLProducto::validarProducto2(pnodoProd ra,string codPas, string codProd, bool valido){
    /*
    Validación de la existencia del producto
    */

    if(ra==NULL){
    }else{
        valido=validarProducto2(ra->hIzq, codPas, codProd, valido);
        if (codProd==ra->codProducto){
            valido=true;
        }
        valido=validarProducto2(ra->hDer, codPas, codProd, valido);

    }
    return valido;
}
void arbolPas::MostrarMarcas(pnodoPas R, string codPas, string codProd){
    if(R==NULL){
        return;
    }else{
        MostrarMarcas(R->hIzq, codPas, codProd);
        if (R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            pro.MostrarMarcas2(R->subsiguiente, codProd);
        }
        MostrarMarcas(R->hDer, codPas, codProd);
    }
}
void AVLProducto::MostrarMarcas2(pnodoProd R, string codProd){
    /*
    Muestra las marcas del árbol
    */

    if(R==NULL){
    }else{
        MostrarMarcas2(R->hIzq, codProd);
        if (codProd==R->subsiguiente->codProducto){
            RN mar;
            mar.MostrarMarcas3(R->subsiguiente);
        }
        MostrarMarcas2(R->hDer, codProd);
    }
}
void RN::MostrarMarcas3(pnodoMarca R){
    /*
    Valida existencia de marca
    */

 if(R==NULL){
    }else{
        MostrarMarcas3(R->hIzq);
        cout<<R->nombre<<" "<<R->codMarca<<" // "<<R->cantGondola<<" "<<R->precio<<endl;
        MostrarMarcas3(R->hDer);
    }
}
bool arbolPas::validarMarca(pnodoPas ra, string codPas, string codProd, string codMar, bool valido){
    if(ra==NULL){
    }else{
        valido=validarMarca(ra->hIzq, codPas, codProd,codMar, valido);
        if (ra->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=ra->subsiguiente;
            valido=pro.validarMarcas2(ra->subsiguiente, codProd,codMar, valido);

        }
        valido=validarMarca(ra->hDer, codPas, codProd, codMar, valido);
    }
    return valido;
}
bool AVLProducto::validarMarcas2(pnodoProd ra, string codProd, string codMar, bool found){
    if(ra==NULL){
    }else{
        found=validarMarcas2(ra->hIzq, codProd, codMar, found);
        if (codProd==ra->subsiguiente->codProducto){
            RN marcas;
            found=marcas.validarMarcas3(ra->subsiguiente,codMar, found);
        }
        found=validarMarcas2(ra->hDer,codProd, codMar, found);

    }
    return found;
}
bool RN::validarMarcas3(pnodoMarca ra, string codMar,bool encontrado){
    pnodoMarca marca;
    if(ra==NULL){
    }else{
        encontrado=validarMarcas3(ra->hIzq,codMar,encontrado);
        if (codMar==ra->codMarca){
            encontrado=true;
            marca=ra;
        }
        encontrado=validarMarcas3(ra->hDer,codMar, encontrado);

    }
    return encontrado;
}
pnodoMarca arbolPas::encontrarNodo1(pnodoPas ra, string codPas, string codProd, string codMar, pnodoMarca marca){
    /*
    Encuentra nodo de pasillo
    */

    bool var=false;
    if(ra==NULL){
    }else{
        marca=encontrarNodo1(ra->hIzq, codPas, codProd,codMar, marca);
        if (ra->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=ra->subsiguiente;
            marca=pro.encontrarNodo2(ra->subsiguiente, codProd,codMar, marca);
        }
        marca=encontrarNodo1(ra->hDer, codPas, codProd, codMar, marca);
    }
    return marca;

}
pnodoMarca AVLProducto::encontrarNodo2(pnodoProd ra, string codProd, string codMar, pnodoMarca marca){
    /*
    Encuentra nodo de pasillo
    */

    if(ra==NULL){
    }else{
        marca=encontrarNodo2(ra->hIzq,codProd,codMar, marca);
        if (ra->codProducto==codProd){
            RN marcas;
            marcas.raiz=ra->subsiguiente;
            marca=marcas.encontrarNodo3(ra->subsiguiente,codMar, marca);
        }
        marca=encontrarNodo2(ra->hDer, codProd, codMar, marca);
    }
    return marca;
}
pnodoMarca RN::encontrarNodo3(pnodoMarca ra, string codMar, pnodoMarca marca){
    /*
    Encuentra nodo de pasillo
    */

    bool var=false;
    if(ra==NULL){
    }else{
        marca=encontrarNodo3(ra->hIzq, codMar, marca);
        if (ra->codMarca==codMar){
            marca=ra;
        }
        marca=encontrarNodo3(ra->hDer,codMar, marca);
    }
    return marca;
}
void Principal::escogerPasillo(int cant1,string codPas,string codPro,string codMar){
    /*
    Encuentra nodo de pasillo
    */

    escogerProducto(cant1,codPas,codPro,codMar);
}
void Principal::escogerProducto(int cant1,string codPas,string codPro,string codMar){

    /*
    Método para escoger pasillo
    */

    escogerMarca(cant1,codPas,codPro,codMar);
}
void Principal::escogerMarca(int cant1,string codPas,string codProd,string codMar)
{
    /*
    Método para escoger pasillo
    */

    pnodoCola auxC=cola.primero;
    if (cola.largoLista()!=1){
        while(auxC->siguiente!=NULL){
            auxC=auxC->siguiente;
        }
    }
    pnodoMarca mar;
    mar=arbolPasillos.encontrarNodo1(arbolPasillos.raiz, codPas, codProd, codMar, mar);
    if (mar->cantGondola>=cant1){
        if(auxC->pila==NULL){
            auxC->pila=new nodoPila(codPas, codProd, codMar,mar->precio, cant1);
            //arbolPasillos.ventaPasillo(arbolPasillos.raiz, codPas);
        }
        else
        {
            pnodoPila pil=auxC->pila;
            while (pil!=NULL)
            {
                if (pil->codMarc==codMar&&pil->codProd==codProd&&pil->codPas==codPas){
                    pil->cant=((pil->cant)+cant1);
                   // arbolPasillos.ventaPasillo(arbolPasillos.raiz, codPas);

                    break;
                }
                else{
                    pnodoPila pil2=auxC->pila;
                    while(pil2->siguiente!=NULL){
                        pil2=pil2->siguiente;
                    }
                    pil2->siguiente=new nodoPila(codPas, codProd, codMar, mar->precio, cant1);
                   // arbolPasillos.ventaPasillo(arbolPasillos.raiz, codPas);
                    break;
                }
                pil=pil->siguiente;
            }
            mar->cantGondola=((mar->cantGondola)-cant1);
        }
    }
    else if(mar->cantGondola<cant1)
    {

        if(auxC->pila==NULL){
            auxC->pila=new nodoPila(codPas, codProd, codMar,mar->precio, mar->cantGondola);
            //arbolPasillos.ventaPasillo(arbolPasillos.raiz, codPas);

        }
        else
        {
            pnodoPila pil=auxC->pila;
            while (pil!=NULL)
            {
                if (pil->codMarc==codMar&&pil->codProd==codProd&&pil->codPas==codPas){
                    pil->cant=((pil->cant)+mar->cantGondola);
                    //arbolPasillos.ventaPasillo(arbolPasillos.raiz, codPas);
                    break;
                }
                else{
                    pnodoPila pil2=auxC->pila;
                    while(pil2->siguiente!=NULL){
                        pil2=pil2->siguiente;
                    }
                    pil2->siguiente=new nodoPila(codPas, codProd, codMar, mar->precio, mar->cantGondola);
                    //arbolPasillos.ventaPasillo(arbolPasillos.raiz, codPas);
                    break;
                }
                pil=pil->siguiente;
            }
        }
        mar->cantGondola=0;
    }
}
void Principal::comprar(int cant1,string codPas,string codPro,string codMar){
    /*
    Método de inicio de la compra
    */

    escogerPasillo(cant1,codPas,codPro,codMar);
}
//Ingresar
//Cola de clientes, log in
bool Principal::validarCliente(ArbolB cliente, int ced){
    int k;
    Pagina *pag=cliente.buscar(ced, k);
    if (pag!=NULL){
        return true;
    }
    else{
        return false;
    }
}
bool Principal::validarAdministrador(ArbolB administrador, int cod){
    /*
  Valida existencia de código de administrador
  */

    int k;
    Pagina *pag=administrador.buscar(cod, k);
    if (pag!=NULL){
        return true;
    }
    else{
        return false;
    }
}

bool Principal::agregarCola(ArbolB cliente, int cedulaa, qintptr descriptor){ //Listo
    /*
    Agrega la cola de clientes
    */

    int k;
    Pagina *pag=cliente.buscar(cedulaa, k);
    if (pag!=NULL){
        cola.InsertarFinal(cedulaa, pag->obtenerDato(k, 0), pag->obtenerDato(k, 2), pag->obtenerDato(k, 1), pag->obtenerDato(k, 3),descriptor);
        }
}
string Principal::consultarUnPrecio(string codPas, string codProd, string codMar){
    /*
    Muestra precio de producto seleccionado
    */

    bool vali=false;
    vali=arbolPasillos.encontrarPasillo(vali,arbolPasillos.raiz, codPas);
    if (vali){
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if (val2){
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoMarca mar=arbolPasillos.encontrarNodo1(arbolPasillos.raiz, codPas, codProd, codMar, mar);
                string precio=to_string(mar->precio);
                return "El precio de "+mar->nombre+" es de: "+precio;
            }
            else{
            return"Codigos invalidos,trate de nuevo";
            }
        }
        else{
        return"Codigos invalidos,trate de nuevo";
        }
    }
    else{
        return"Codigos invalidos,trate de nuevo";
    }
}
//Funcionalidades de administrador:
int arbolPas::largoArbol(pnodoPas R, int cont){
    if(R==NULL){
        return cont;
    }else{
        cont=largoArbol(R->hIzq, cont);
        cont++;
        cont=largoArbol(R->hDer, cont);
    }
}
string Principal::consultarUnPrecioAdm(){
    /*
    Muestra precio de producto seleccionado
    */

    bool vali=false;
    cout<<"Opciones de pasillos: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escriba el codigo del pasillo que desea:"<<endl;
    string codPas;
    cin>>codPas;
    vali=arbolPasillos.encontrarPasillo(vali,arbolPasillos.raiz, codPas);
    if (vali){
        cout<<"Opciones de productos: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        cout<<"Escriba el codigo del producto que desea: "<<endl;
        string codProd;
        cin>>codProd;
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if (val2){
            cout<<"Opciones de marcas: "<<endl;
            arbolPasillos.MostrarMarcas(arbolPasillos.raiz, codPas, codProd);
            cout<<"Escriba el codigo de la marca que desea: "<<endl;
            string codMar;
            cin>>codMar;
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoMarca mar=arbolPasillos.encontrarNodo1(arbolPasillos.raiz, codPas, codProd, codMar, mar);
                string precio=to_string(mar->precio);
                return "El precio de "+mar->nombre+" es de: "+precio;
            }
            else{
            return"Codigos invalidos,trate de nuevo";
            }
        }
        else{
        return"Codigos invalidos,trate de nuevo";
        }
    }
    else{
        return"Codigos invalidos,trate de nuevo";
    }
}
pnodoProd arbolPas::encontrarNodoProd1(pnodoPas ra, string codPas, string codProd, pnodoProd prod){
    /*
    Encuentra nodo de producto
    */

    bool var=false;
    if(ra==NULL){
    }else{
        prod=encontrarNodoProd1(ra->hIzq, codPas, codProd, prod);
        if (ra->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=ra->subsiguiente;
            prod=pro.encontrarNodoProd2(ra->subsiguiente, codProd, prod);
        }
        prod=encontrarNodoProd1(ra->hDer, codPas, codProd, prod);
    }
    return prod;

}
pnodoProd AVLProducto::encontrarNodoProd2(pnodoProd ra, string codProd, pnodoProd prod){
    /*
    Encuentra nodo de producto
    */

    if(ra==NULL){
    }else{
        prod=encontrarNodoProd2(ra->hIzq,codProd, prod);
        if (ra->codProducto==codProd){
            prod=ra;
        }
        prod=encontrarNodoProd2(ra->hDer, codProd, prod);
    }
    return prod;
}
void Principal::ModificarCanasta(){//Buscar y quitar el cout
    /*
    Método que modifica el código de canasta
    */

    cout<<"Los pasillos a escoger son: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escoja el codigo: "<<endl;
    string codPas;
    cin>>codPas;
    bool vali=false;
    vali=arbolPasillos.encontrarPasillo(vali, arbolPasillos.raiz, codPas);
    if(vali){
        cout<<"Los productos a escoger son: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        cout<<"Escoja el codigo del producto: "<<endl;
        string codProd;
        cin>>codProd;
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if(val2){
            cout<<"Estas son las marcas: "<<endl;
            arbolPasillos.MostrarMarcas(arbolPasillos.raiz, codPas, codProd);
            cout<<"Escriba la marca que desea: "<<endl;
            string codMar;
            cin>>codMar;
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoInventario invent=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, invent);
                if (invent->codCanasta==1){
                    invent->codCanasta=false;
                    cout<<"El producto antes pertenecia a la canasta ahora no pertenece"<<endl;
                }
                else{
                    invent->codCanasta=true;
                    cout<<"El producto antes no pertenecia a la canasta ahora pertenece"<<endl;
                }
            }
            else{
                cout<<"Codigo de marca incorrecto, ingrese los datos de nuevo."<<endl;
                ModificarCanasta();
            }
        }
        else{
            cout<<"Codigo de producto incorrecto, ingrese los datos de nuevo."<<endl;
            ModificarCanasta();
        }
    }
    else{
        cout<<"Codigo de pasillo incorrecto, ingrese los datos de nuevo"<<endl;
        ModificarCanasta();
    }
}
void Principal::ModificarPrecio(){
    cout<<"Pasillos disponibles: "<<endl;
    cout<<"Codigo / Nombre "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escoja el codigo del pasillo en el que esta la marca a la que le desea modificar el precio: "<<endl;
    string codPas;
    cin>>codPas;
    bool valido=false;
    valido=arbolPasillos.encontrarPasillo(valido,arbolPasillos.raiz, codPas);
    if (valido){
        cout<<"Productos a escoger en este pasillo: "<<endl;
        cout<<"Codigo / Nombre"<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        cout<<"Escriba el codigo del producto: "<<endl;
        string codProd;
        cin>>codProd;
        bool valid2=false;
        valid2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, valid2);
        if(valid2){
            cout<<"Las marcas a escoger son: "<<endl;
            cout<<"Nombre / Codigo // Cantidad Gondola / Precio"<<endl;
            arbolPasillos.MostrarMarcas(arbolPasillos.raiz, codPas, codProd);
            cout<<"Escoja un codigo de marca: "<<endl;
            string codMar;
            cin>>codMar;
            bool valid3=false;
            valid3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, valid3);
            if (valid3){
                pnodoMarca mar=arbolPasillos.encontrarNodo1(arbolPasillos.raiz, codPas, codProd, codMar, mar);
                cout<<"Ingrese el nuevo precio de "<<" "<<mar->codMarca<<" "<<mar->nombre<<" "<<endl;
                float nuevoPrecio;
                cin>>nuevoPrecio;
                if(!cin){
                    cin.clear();
                    cin.ignore();
                    cout<<"Ingrese solo numeros: "<<endl;
                    cin>>nuevoPrecio;
                }
                mar->precio=nuevoPrecio;
                cout<<"Precio modificado exitosamente"<<endl;
            }
            else{
                cout<<"Codigo de marca invalido, vuelva a ingresar los datos."<<endl;
                ModificarPrecio();
            }
        }
        else{
            cout<<"Codigo de producto invalido, vuelva a ingresar los datos."<<endl;
            ModificarPrecio();
        }

    }
    else{
        cout<<"Codigo de pasillo incorrecto, vuelva a ingresar los datos"<<endl;
        ModificarPrecio();
    }
}
//arbolPas arbolPas::insertarPasillo(string codPas, string nomb){
//    arbolPasillos.InsertaBinario(arbolPasillos.raiz, codPas, nomb);
//    if (largo!=largo2){
//        cout<<"Pasillo creado con exito!"<<endl;
//        cout<<"Codigo de pasillo: "<<codPas<<" Nombre pasillo: "<<nomb<<endl;
//    }
//    else{
//        cout<<"El pasillo no se pudo crear porque el codigo ya existia."<<endl;
//        insertarPasillo();
//    }
//    return arbolPasillos;
//}
//arbolPas arbolPas::insertarProductos(){
//    cout<<"Las opciones de pasillos son: "<<endl;
//    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
//    cout<<"Escriba el codigo de la opcion que desea: "<<endl;
//    string codPas;
//    cin>>codPas;
//    bool valido=false;
//    valido=encontrarPasillo(valido, arbolPasillos.raiz, codPas);
//    if (valido){
//        cout<<"Ingrese el codigo del producto que desea ingresar: "<<endl;
//        string codProd;
//        cin>>codProd;
//        cout<<"Ingrese el nombre del producto que desea ingresar: "<<endl;
//        string nombre;
//        cin>>nombre;
//        bool valid2=false;
//        valid2=ValidarProducto1(arbolPasillos.raiz, codPas, codProd, valid2);
//        if (!valid2){
//            pnodoProd nuevo=new nodoProducto(codPas, codProd, nombre);
//            AVLProducto arbolprod;
//            arbolprod.EnlaceAvl(arbolPasillos.raiz, nuevo);
//            cout<<"Producto agregado con exito!"<<endl;
//            cout<<"Codigo de pasillo: "<<codPas<<" Codigo de producto: "<<codProd<<" Nombre: "<<nombre<<endl;
//        }
//        else{
//            cout<<"Los datos para producto que ingreso ya existen."<<endl;
//            arbolPasillos.insertarProductos();
//        }
//    }
//    else{
//        cout<<"Escoja un codigo de un pasillo valido: "<<endl;
//        string codPas2;
//        cin>>codPas2;
//        arbolPasillos.insertarProductos();
//    }
//    return arbolPasillos;

//}
arbolPas Principal::insertarMarca(){
    cout<<"Estas son las opciones de pasillos que hay: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escriba el numero del codigo en el que quiere insertar la marca nueva: "<<endl;
    string codPas;
    cin>>codPas;
    bool valido=false;
    valido=arbolPasillos.encontrarPasillo( valido, arbolPasillos.raiz, codPas);
    if(valido){
        cout<<"Estas son las opciones de productos: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        cout<<"Escriba el codigo del producto en el que desea agregar la marca nueva: "<<endl;
        string codProd;
        cin>>codProd;
        bool valid2=false;
        valid2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, valid2);
        if (valid2){
            pnodoProd raiz=arbolPasillos.encontrarNodoProd1(arbolPasillos.raiz, codPas, codProd, raiz);
            cout<<"Escriba el codigo de la marca nueva: "<<endl;
            string codMar;
            cin>>codMar;
            bool valid3=false;
            valid3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar,valid3);
            if (!valid3){
                cout<<"Escriba el nombre de la marca nueva: "<<endl;
                string nombre;
                cin>>nombre;
                cout<<"Ingrese la cantidad que existe de esta nueva marca: "<<endl;
                int cant;
                cin>>cant;
                if(!cin){
                    cin.clear();
                    cin.ignore();
                    cout<<"Ingrese solo valores numericos: "<<endl;
                    cin>>cant;
                }
                cout<<"Ingrese el precio de la nueva marca: "<<endl;
                float precio;
                cin>>precio;
                if(!cin){
                    cin.clear();
                    cin.ignore();
                    cout<<"Ingrese solo valores numericos: "<<endl;
                    cin>>precio;
                }
                cout<<"Ingrese 1 si es de canasta basica u otra cosa sino: "<<endl;
                string canasta;
                cin>>canasta;
                bool canasBasic;
                if (canasta=="1"){
                    canasBasic=true;
                }
                else{
                    canasBasic=false;
                }
                pnodoMarca nuevo=new nodoMarca(codPas,nombre, codProd, codMar, cant, precio);
                AVLProducto productos;
                productos.EnlaceRN(raiz, nuevo);
                string conca=codPas+codProd+codMar;
                stringstream conca2(conca);
                int conca3;
                conca2>>conca3;
                arbolInventario.insertar(conca3, codPas, nombre, codProd, codMar, cant, canasBasic, arbolInventario.raiz);
                cout<<"Marca agregada con exito!"<<endl;
                cout<<"Codigo de pasillo: "<<codPas<<" Codigo de producto: "<<codProd<<" Codigo de marca: "<<codMar<<" Nombre: "<<nombre<<" "<<"Cantidad ingresada: "<<cant<<" Precio: "<<precio<<" Canasta: "<<canasBasic<<endl;
            }
            else{
                cout<<"Ese codigo de marca ya existe.Ingrese los datos nuevamente."<<endl;
                arbolPasillos=insertarMarca();
            }
        }
        else{
            cout<<"Ingrese datos correctos,codigo de producto inexistente."<<endl;
            arbolPasillos=insertarMarca();
        }
    }
    else{
        cout<<"Ingrese un codigo de pasillo que exista."<<endl;
        arbolPasillos=insertarMarca();
    }
}
pnodoInventario ArbolInventario::encontrarNodo(pnodoInventario ra, string codPas, string codProd, string codMar, pnodoInventario nodoIn){
    if (ra==NULL){
    }
    else{
        nodoIn=encontrarNodo(ra->hIzq, codPas, codProd, codMar, nodoIn);
        if (codPas==ra->codPasillo && codProd==ra->codProducto && codMar==ra->codMarca){
            nodoIn=ra;
        }
        nodoIn=encontrarNodo(ra->hDer, codPas, codProd, codMar, nodoIn);
    }
    return nodoIn;
}
void Principal::ModificarImpuesto(){
    cout<<"Los pasillos a escoger son: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escoja el codigo: "<<endl;
    string codPas;
    cin>>codPas;
    bool vali=false;
    vali=arbolPasillos.encontrarPasillo(vali, arbolPasillos.raiz, codPas);
    if(vali){
        cout<<"Los productos a escoger son: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        cout<<"Escoja el codigo del producto: "<<endl;
        string codProd;
        cin>>codProd;
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if(val2){
            cout<<"Estas son las marcas: "<<endl;
            arbolPasillos.MostrarMarcas(arbolPasillos.raiz, codPas, codProd);
            cout<<"Escriba la marca que desea: "<<endl;
            string codMar;
            cin>>codMar;
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoInventario invent=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, invent);
                cout<<"El impuesto actual de "<<invent->codMarca<<" "<<invent->nombre<<" es del "<<invent->impuesto<<" %"<<endl;
                cout<<"Ingrese el nuevo impuesto que desea para el producto: "<<endl;
                int imp;
                cin>>imp;
                if(!cin){
                    cin.clear();
                    cin.ignore();
                    cout<<"Ingrese solo valores numericos: "<<endl;
                    cin>>imp;
                }
                //invent->impuesto=imp;
            }
            else{
                cout<<"El codigo de marca es invalido, ingrese los datos de nuevo"<<endl;
                ModificarImpuesto();
            }
        }
        else{
            cout<<"El codigo de producto es incorrecto, ingrese los datos nuevamente."<<endl;
            ModificarImpuesto();
        }
    }
    else{
        cout<<"El codigo de pasillo es incrrecto.Intentelo de nuevo"<<endl;
        ModificarImpuesto();
    }
}
string Principal::ConsultarImpuesto(){
    cout<<"Estas son las opciones de pasillos: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escriba el codigo de pasillo que desea: "<<endl;
    string codPas;
    cin>>codPas;
    bool vali=false;
    vali=arbolPasillos.encontrarPasillo( vali, arbolPasillos.raiz, codPas);
    if (vali){
        cout<<"Estas son las opciones de productos: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        string codProd;
        cout<<"Escoja un codigo de produto: "<<endl;
        cin>>codProd;
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if (val2){
            cout<<"Estas son las marcas:"<<endl;
            arbolPasillos.MostrarMarcas(arbolPasillos.raiz, codPas, codProd);
            string codMar;
            cin>>codMar;
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoInventario invent=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, invent);
                string impuesto=to_string(invent->impuesto);
                return "El impuesto del producto solicitado es de: "+impuesto;
            }
            else{
                return "Codigos invalidos,trate de nuevo";
                ConsultarImpuesto();
            }
        }
        else{
            return "Codigos invalidos,trate de nuevo";
            ConsultarImpuesto();
        }
    }
    else{
        return "Codigos invalidos,trate de nuevo";
        ConsultarImpuesto();
    }
}
string Principal::ConsultarCanasta(){
    cout<<"Estas son las opciones de pasillos: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escriba el codigo de pasillo que desea: "<<endl;
    string codPas;
    cin>>codPas;
    bool vali=false;
    vali=arbolPasillos.encontrarPasillo(vali, arbolPasillos.raiz, codPas);
    if (vali){
        cout<<"Estas son las opciones de productos: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, codPas);
        cout<<"Escriba el codigo de producto que desea: "<<endl;
        string codProd;
        cin>>codProd;
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if (val2){
            cout<<"Estas son las opciones de marcas: "<<endl;
            arbolPasillos.MostrarMarcas(arbolPasillos.raiz, codPas, codProd);
            cout<<"Escriba el codigo de marca que desea: "<<endl;
            string codMar;
            cin>>codMar;
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoInventario invent=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, invent);
                if (invent->codCanasta)
                    return "El producto pertece a la canasta basica";
                else{
                    return "El producto no pertenece a la canasta basica";
                }
            }
            else{
                cout<<"Codigos invalidos,trate de nuevo"<<endl;
                ConsultarCanasta();
            }
        }
        else{
            cout<<"Codigos invalidos,trate de nuevo"<<endl;
            ConsultarCanasta();
        }

    }
    else{
        cout<<"Codigos invalidos,trate de nuevo"<<endl;
        ConsultarCanasta();
    }
}
int listaVentas::largoLista(){
/*
Retorna el largo de la cola de clientes.
*/
    int cont=0;
    pnodoVenta aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
}
void Principal::revisarGondolas()
{
/*
Metodo que revisa gondolas y las rellena de ser necesario
*/
    pnodoVenta prodPila=ventas.primero;
    int larglist=ventas.largoLista();
    cout<<larglist<<endl;
    int cont=0;
    while(cont<larglist)
    {
        cout<<"En el ciclo"<<endl;
        pnodoMarca mar=arbolPasillos.encontrarNodo1(arbolPasillos.raiz, prodPila->codPasillo, prodPila->codProducto, prodPila->codMarca, mar);
        if (mar->cantGondola<=2){
            cout<<"If"<<endl;
            cout<<"Cuanto desea cargar en la gondola de "<<mar->nombre<<" ?: "<<endl;
            int canti;
            cin>>canti;
            if(!cin){
                cin.clear();
                cin.ignore();
                cout<<"Ingrese solo numeros: "<<endl;
                cin>>canti;
            }
            pnodoInventario inven=arbolInventario.encontrarNodo(arbolInventario.raiz, mar->codPasillo, mar->codProducto, mar->codMarca, inven);
            if (inven->cantStock>=canti){
                inven->cantStock=((inven->cantStock)-canti);
                mar->cantGondola=((mar->cantGondola)+canti);
                cout<<"Se relleno la gondola!"<<endl;
            }
            else{
                cout<<"En el inventario no hay suficiente para cargar la gondola, desea cargar lo que hay? Digite 1 para si u otra cosa para no: "<<endl;
                string rep;
                cin>>rep;
                if (rep=="1"){
                    mar->cantGondola=((mar->cantGondola)+inven->cantStock);
                    inven->cantStock=0;
                    cout<<"Se cargo no la gondola!"<<endl;
                }
                else{
                    cout<<"No se cargo la gondola por no haber productos"<<endl;
                }
            }
        }
        prodPila=prodPila->siguiente;
        cont++;
    }
    cout<<"Sale"<<endl;
}
void Principal::cargarInventario(){
    pnodoVenta prodPila=ventas.primero;
    int larglist=ventas.largoLista();
    cout<<larglist<<endl;
    int cont=0;
    while(cont<larglist)
    {
        pnodoInventario inven=arbolInventario.encontrarNodo(arbolInventario.raiz, prodPila->codPasillo, prodPila->codProducto, prodPila->codMarca, inven);
        cout<<inven->codPasillo<<endl;
        cout<<inven->cantStock<<endl;
        if (inven->cantStock<=20){
            cout<<"Cuanto desea cargar en el producto ?: "<<endl;
            int canti;
            cin>>canti;
            if(!cin){
                cin.clear();
                cin.ignore();
                cout<<"Ingrese solo numeros: "<<endl;
                cin>>canti;
            }
            inven->cantStock=((inven->cantStock)+canti);
        }
        prodPila=prodPila->siguiente;
        cont++;
    }
}
//Facturar y pagar ********************************************************************************************************************
void listaVentas::InsertarFinal(string pas, string prod, string mar, int cant)
{
    if (ListaVacia())
        primero = new nodoListaVentas(pas, prod, mar, cant);
    else
        { pnodoVenta aux = primero;
            while ( aux->siguiente != NULL)
                aux= aux->siguiente;
                aux->siguiente=new nodoListaVentas(pas, prod, mar, cant);
        }
}
void Pila::InsertarFinalOrd(string pas, string prod, string mar, int cant, float precio)
{
    if (ListaVacia())
        primero = new nodoPila(pas, prod, mar, precio, cant);
    else
        { pnodoPila aux = primero;
            while ( aux->siguiente != NULL)
                aux= aux->siguiente;
                aux->siguiente=new nodoPila(pas, prod, mar, precio, cant);
        }
}
bool listaVentas::agregarArticulo(listaVentas lista, string codPas, string codProd, string codMar){
    pnodoVenta aux=lista.primero;
    while (aux!=NULL){
        if(aux->codPasillo==codPas && aux->codProducto==codProd && aux->codMarca==codMar)
            return false;
        aux=aux->siguiente;
    }
    return true;
}
void Principal::listaVentas1(string pas, string prod, string mar, int cant)
{
    /*
    Inserta valores en la lista de ventas según una serie de condiciones.
    */
    if(ventas.ListaVacia()){
        ventas.InsertarFinal(pas, prod, mar, cant);
    }
    else{
        bool rep=ventas.agregarArticulo(ventas, pas, prod, mar);
        if (!rep){
           ventas.InsertarFinal(pas, prod, mar, cant);
        }
        else{
            pnodoVenta aux=ventas.primero;
            while (aux!=NULL){
                if(aux->codPasillo==pas && aux->codProducto==prod&& aux->codMarca==mar)
                    aux->cantidad=((aux->cantidad)+cant);
                aux=aux->siguiente;
            }
        }

    }
}
// Quicksort
nodoPila* Pila:: getTail(nodoPila *cur)
{
    /*
    Para realizar el ordenamiento de la lista de la pila del cliente. Retorna el Ãºltimo elemento de la lista, recibe un nodo actual.
    */
    while (cur != NULL && cur->siguiente != NULL)
        cur = cur->siguiente;
    return cur;
}
nodoPila* Pila::partition(nodoPila* head, nodoPila* end, nodoPila **newHead, nodoPila **newEnd)
{
    /*
    Para realizar el ordenamiento de la lista de la pila del cliente. Realiza la particion de la lista en dos sublistas.
    */
    nodoPila* pivot = end;
    nodoPila* prev = NULL, *cur = head, *tail = pivot;
    while (cur != pivot)
    {

        if (cur->cant > pivot->cant)
        {
            if ((*newHead) == NULL)
                (*newHead) = cur;

            prev = cur;
            cur = cur->siguiente;
        }
        else
        {
            if (prev)
                prev->siguiente = cur->siguiente;
            nodoPila* tmp = cur->siguiente;
            cur->siguiente = NULL;
            tail->siguiente = cur;
            tail = cur;
            cur = tmp;
        }
    }
    if ((*newHead) == NULL)
        (*newHead) = pivot;
    (*newEnd) = tail;
    return pivot;
}
nodoPila* Pila::quickSortRecur(nodoPila* head, nodoPila* end)
{
    /*
    Para realizar el ordenamiento de la lista de la pila del cliente.
    */
    if (!head || head == end)
        return head;

    nodoPila *newHead = NULL, *newEnd = NULL;
    nodoPila* pivot = partition(head, end, &newHead, &newEnd);
    if (newHead != pivot)
    {
        nodoPila *tmp = newHead;
        while (tmp->siguiente != pivot)
            tmp = tmp->siguiente;
        tmp->siguiente = NULL;
        newHead = quickSortRecur(newHead, tmp);
        tmp = getTail(newHead);
        tmp->siguiente =  pivot;
    }
    pivot->siguiente = quickSortRecur(pivot->siguiente, newEnd);
    return newHead;
}
void Pila::quickSort(nodoPila **headRef)
{
    /*
    Para realizar el ordenamiento de la lista de la pila del cliente.
    */
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

string Principal::pagar(Pila pila){
    string devolver;
    string nombre;
    string codMarca;
    string cant;
    string precio;
    string imp;
    float precio_Total=0;
    string precio_Totals;
    float precio_total_unidad=0;
    string precio_total_unidads;
    float precio_total_unidades=0;
    string precio_total_unidadesS;
    pnodoPila prim=pila.primero;
    while (prim!=NULL){
        string codPas=prim->codPas;
        string codProd=prim->codProd;
        string codMar=prim->codMarc;
        pnodoMarca marca=arbolPasillos.encontrarNodo1(arbolPasillos.raiz, codPas, codProd, codMar, marca);
        nombre=marca->nombre;
        pnodoInventario inven=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, inven);
        imp=to_string(inven->impuesto);
        float preci=marca->precio;
        precio=to_string(preci);
        precio_total_unidad=(preci+(preci*inven->impuesto/100));
        precio_total_unidades=precio_total_unidad*prim->cant;
        precio_total_unidadesS=to_string(precio_total_unidades);
        precio_Total=precio_Total+precio_total_unidades;
        devolver=devolver+nombre+" "+codMar+" "+imp+"%"+" "+precio+" "+precio_total_unidads+" "+precio_total_unidadesS+"\n";
        prim=prim->siguiente;
    }
    precio_Totals=to_string(precio_Total);
    return devolver+" "+precio_Totals;
}

string Principal::agregarListaOrdenada(){
//Metodo primero
    pnodoCola aux=cola.primero;
    pnodoPila aux2=aux->pila;
    Pila lista1;
    while(aux2!=NULL)
    {
        if (aux2->cant==0)
            break;
        lista1.InsertarFinalOrd(aux2->codPas, aux2->codProd, aux2->codMarc, aux2->cant,  aux2->precioP);
        aux2=aux2->siguiente;
    }
    cola.BorrarInicio();
    //Ordenar la pila
    lista1.quickSort(&(lista1.primero));
    string pas;
    string prod;
    string marca;
    int cant;
    pnodoPila pil=lista1.primero;
    string resp;
    while(pil!=NULL)
    {
        pas=pil->codPas;
        prod=pil->codProd;
        marca=pil->codMarc;
        cant=pil->cant;
        listaVentas1(pas, prod, marca, cant);
        pil=pil->siguiente;
    }
    string devuelto=pagar(lista1);
    return devuelto;
}


string Principal::ConsultarImpuesto(string codPas, string codProd, string codMar){
    bool vali=false;
    vali=arbolPasillos.encontrarPasillo(vali,arbolPasillos.raiz, codPas);
    if (vali){
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if (val2){
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoInventario invent=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, invent);
                string impuesto=to_string(invent->impuesto);
                return "El impuesto del producto solicitado es de: "+impuesto;
            }
            else{
                return"Codigos invalidos,trate de nuevo";
            }
        }
        else{
            return"Codigos invalidos,trate de nuevo";
        }
    }
    else{
        return"Codigos invalidos,trate de nuevo";

    }
}
string Principal::ConsultarCanasta(string codPas, string codProd, string codMar){
    bool vali=false;
    vali=arbolPasillos.encontrarPasillo(vali,arbolPasillos.raiz, codPas);
    if (vali){
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, codPas, codProd, val2);
        if (val2){
            bool vali3=false;
            vali3=arbolPasillos.validarMarca(arbolPasillos.raiz, codPas, codProd, codMar, vali3);
            if(vali3){
                pnodoInventario invent=arbolInventario.encontrarNodo(arbolInventario.raiz, codPas, codProd, codMar, invent);
                if(invent->codCanasta)
                    return"\nEl producto si pertenece a la canasta";
                else
                    return"\nEl producto no pertenece a la canasta";
            }
            else{
                return"\nCodigos invalidos,trate de nuevo";
            }
        }
        else{
            return"\nCodigos invalidos,trate de nuevo";
        }
    }
    else{
        return"\nCodigos invalidos,trate de nuevo";
    }
}
void Principal::generarReporte(){
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    archivo<<"*******************************Reportes administrador*******************************"<<endl;
    archivo<<"Pasillo mas vendido: "<<endl;
    pnodoPas masVendido=arbolPasillos.raiz;
    masVendido=PasillosMasVisitado(arbolPasillos.raiz, masVendido);
    archivo<<"                     "<<masVendido->codPasillo<<" "<<masVendido->nombre<<endl;
    archivo<<"\nPasillo menos vendido: "<<endl;
    pnodoPas menosVendido=arbolPasillos.raiz;
    menosVendido=PasillosMenosVisitado(arbolPasillos.raiz,menosVendido);
    cout<<menosVendido->nombre<<endl;
    archivo<<"                      "<<menosVendido->codPasillo<<" "<<menosVendido->nombre<<endl;
    cout<<"***Producto mas vendido en un pasillo***"<<endl;
    cout<<"Estas son las opciones de pasillos: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Seleccione un codigo de pasillo: "<<endl;
    string codPas;
    cin>>codPas;
    bool valid=false;
    valid=arbolPasillos.encontrarPasillo(valid, arbolPasillos.raiz, codPas);
    if (valid){
        pnodoPas pas=arbolPasillos.nodoPasillos(arbolPasillos.raiz, codPas, arbolPasillos.raiz);
        pnodoProd mas=pas->subsiguiente;
        mas=ProductosMasVendidos(arbolPasillos.raiz, codPas, mas);
        archivo<<"\nProducto mas vendido en un pasillo: "<<endl;
        archivo<<"                                    Pasillo: "<<codPas<<" \n                                                 "<<mas->codProducto<<" "<<mas->nombre<<endl;
    }
    else{
        archivo<<"Se selecciono un codigo de pasillo inexistente"<<endl;
    }
    cout<<"**Marca mas vendida en un pasillo en un producto**"<<endl;
    cout<<"Las opciones de pasillos son: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escoja un codigo de pasillo: "<<endl;
    string pas;
    cin>>pas;
    bool val=false;
    val=arbolPasillos.encontrarPasillo(val, arbolPasillos.raiz, pas);
    if(val){
        cout<<"Las opciones de productos son: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, pas);
        cout<<"Escoja un codigo de producto: "<<endl;
        string prod;
        cin>>prod;
        bool val2=false;
        val2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, pas, prod, val2);
        if(val2){
            pnodoPas pasi=arbolPasillos.nodoPasillos(arbolPasillos.raiz, pas,arbolPasillos.raiz);
            pnodoProd produ=arbolPasillos.encontrarNodoProd1(arbolPasillos.raiz, pas, prod, pasi->subsiguiente);
            pnodoMarca mar=MarcasMasVendidas(arbolPasillos.raiz, pas, prod,produ->subsiguiente);
            archivo<<"La marca mas vendida es: "<<endl;
            archivo<<"                       Pasillo: "<<pas<<" producto: "<<prod<<endl;
            archivo<<"                                                      "<<mar->codMarca<<" "<<mar->nombre<<endl;
        }
        else{
            archivo<<"Se escogio un codigo invalido"<<endl;
        }
    }
    else{
        archivo<<"Se escogio un codigo invalido"<<endl;
    }
    cout<<"**Mostrar las marcas de un pasillo en un producto**"<<endl;
    cout<<"Las opciones de pasillos son: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Escoja el codigo: "<<endl;
    string pas1;
    cin>>pas1;
    bool vali3=false;
    vali3=arbolPasillos.encontrarPasillo(vali3, arbolPasillos.raiz, pas1);
    if (vali3){
        cout<<"Las opciones de productos son: "<<endl;
        arbolPasillos.MostrarProductos(arbolPasillos.raiz, pas1);
        cout<<"Escoja el codigo: "<<endl;
        string prod1;
        cin>>prod1;
        bool vali2=false;
        vali2=arbolPasillos.ValidarProducto1(arbolPasillos.raiz, pas1, prod1, vali2);
        if (vali2){
            archivo<<"Las marcas del producto que escogio son: "<<endl;
            archivo<<"Pasillo: "<<pas1<<" Producto: "<<prod1<<" : "<<endl;
            InordenTripleReporte(arbolPasillos.raiz, pas1, prod1);
        }
        else{
            archivo<<"Se ingreso un codigo invalido"<<endl;
        }
    }
    else{
        archivo<<"Se ingreso un codigo incorrecto"<<endl;
    }
    cout<<"***Productos de un pasillo***"<<endl;
    cout<<"Estas son las opciones de pasillos: "<<endl;
    arbolPasillos.MostrarPasillos(arbolPasillos.raiz);
    cout<<"Seleccione un codigo de pasillo: "<<endl;
    string codPas2;
    cin>>codPas2;
    bool valid2=false;
    valid2=arbolPasillos.encontrarPasillo(valid2, arbolPasillos.raiz, codPas2);
    if (valid2){
        archivo<<"\nProductos de un pasillo: "<<endl;
        archivo<<"Pasillo: "<<codPas2<<endl;
        InordenTripleReporte2_1(arbolPasillos.raiz, codPas2);
    }
    else{
        archivo<<"Se selecciono un codigo de pasillo inexistente"<<endl;
    }
    archivo<<"\nClientes registrados del supermercado: "<<endl;
    arbolClientes.mostrar1();
    archivo<<"\nPasillos que existen en el supermercado: "<<endl;
    arbolPasillos.MostrarPasillosReporte(arbolPasillos.raiz);
    pnodoProd prod=arbolPasillos.raiz->subsiguiente;
    prod=masCargadoGondola(arbolPasillos.raiz, prod);
    archivo<<"\nProducto mas cargado en gondolas: "<<endl;
    archivo<<"                                  "<<prod->codProducto<<" "<<prod->nombre<<endl;
    archivo<<"El iventario del supermecado es: "<<endl;
    arbolInventario.InordenReporte(arbolInventario.raiz);
    clienteMasFacturas();
    archivo.close();
}
pnodoProd Principal::masCargadoGondola(pnodoPas R,  pnodoProd masGon){
    if (R==NULL){
    }
    else{
        masGon=masCargadoGondola(R->hIzq, masGon);
        masGon=masGondola(R->subsiguiente,masGon);
        masGon=masCargadoGondola(R->hDer, masGon);
    }
    return masGon;
}
pnodoProd Principal::masGondola(pnodoProd R, pnodoProd masGon){
    if(R==NULL){

    }
    else{
        masGon=masGondola(R->hIzq, masGon);
        if (R->cargaGondolas>masGon->cargaGondolas)
            masGon=R;
        masGon=masGondola(R->hDer, masGon);
    }
    return masGon;
}
void arbolPas::ventaPasillo(pnodoPas R, string codPas){
    if(R==NULL){
        return;
    }else{
        ventaPasillo(R->hIzq, codPas);
        if (R->codPasillo==codPas)
            R->pasvis++;
        ventaPasillo(R->hDer, codPas);
    }
}
void Principal::ventaProductos(pnodoPas R, string codPas, string codProd){
    if(R==NULL){
        return;
    }else{
        ventaProductos(R->hIzq, codPas, codProd);
        if (R->codPasillo==codPas)
            ventaProductos2(R->subsiguiente, codProd);
        ventaProductos(R->hDer, codPas, codProd);
    }
}
void Principal::ventaProductos2(pnodoProd R, string codProd ){
    if(R==NULL){
        return;
    }else{
        ventaProductos2(R->hIzq, codProd);
        if (R->codProducto==codProd)
            R->masVend++;
        ventaProductos2(R->hDer, codProd);
    }
}
void Principal::cargoEnGondolas(pnodoPas R, string codPas, string codProd){
    if(R==NULL){
        return;
    }else{
        cargoEnGondolas(R->hIzq, codPas, codProd);
        if (R->codPasillo==codPas)
            cargoEnGondolas2(R->subsiguiente, codProd);
        cargoEnGondolas(R->hDer, codPas, codProd);
    }
}
void Principal::cargoEnGondolas2(pnodoProd R, string codProd ){
    if(R==NULL){
        return;
    }else{
        cargoEnGondolas2(R->hIzq, codProd);
        if (R->codProducto==codProd)
            R->cargaGondolas++;
        cargoEnGondolas2(R->hDer, codProd);
    }
}
pnodoPas Principal::PasillosMasVisitado(pnodoPas R, pnodoPas pasMas){
    if(R==NULL){

    }else{
        pasMas=PasillosMasVisitado(R->hIzq, pasMas);
        if (R->pasvis>pasMas->pasvis){
            pasMas=R;
        }
        pasMas=PasillosMasVisitado(R->hDer, pasMas);
    }
    return pasMas;
}
pnodoPas Principal::PasillosMenosVisitado(pnodoPas R,pnodoPas pasmenos){
    if(R==NULL){

    }else{
        pasmenos=PasillosMenosVisitado(R->hIzq,pasmenos);
        if (R->pasvis<pasmenos->pasvis){
            pasmenos=R;
        }
        pasmenos=PasillosMenosVisitado(R->hDer, pasmenos);
    }
    return pasmenos;
}
pnodoProd Principal::ProductosMasVendidos2(pnodoProd R, pnodoProd prodMas){
    if(R==NULL){

    }else{
        prodMas=ProductosMasVendidos2(R->hIzq,prodMas);
        if (R->masVend>prodMas->masVend){
            prodMas=R;
        }
        prodMas=ProductosMasVendidos2(R->hDer, prodMas);
    }
    return prodMas;
}
pnodoProd Principal::ProductosMasCargado(pnodoPas R, string codPas,pnodoProd prodMas){
    if(R==NULL){

    }else{
        prodMas=ProductosMasCargado(R->hIzq,codPas, prodMas);
        if (R->codPasillo==codPas){
            prodMas=ProductosMasCargado2(R->subsiguiente, prodMas);
        }
        prodMas=ProductosMasCargado(R->hIzq,codPas, prodMas);
    }
    return prodMas;
}
pnodoProd Principal::ProductosMasCargado2(pnodoProd R,pnodoProd prodMas){
    if(R==NULL){

    }else{
        prodMas=ProductosMasCargado2(R->hIzq,prodMas);
        if (R->cargaGondolas>prodMas->cargaGondolas){
            prodMas=R;
        }
        prodMas=ProductosMasCargado2(R->hDer, prodMas);
    }
    return prodMas;
}
pnodoProd Principal::ProductosMasVendidos(pnodoPas R, string codPas,pnodoProd prodMas){
    if(R==NULL){

    }else{
        prodMas=ProductosMasVendidos(R->hIzq,codPas,prodMas);
        if (R->codPasillo==codPas){
            prodMas=ProductosMasVendidos2(R->subsiguiente, prodMas);
        }
        prodMas=ProductosMasVendidos(R->hIzq,codPas, prodMas);
    }
    return prodMas;
}
void Principal::ventaMarcas(pnodoPas R, string codPas, string codProd, string codMar){
    if(R==NULL){
        return;
    }else{
        ventaMarcas(R->hIzq, codPas, codProd, codMar);
        if (R->codPasillo==codPas)
            ventaMarcas2(R->subsiguiente, codProd, codMar);
        ventaMarcas(R->hDer, codPas, codProd, codMar);
    }
}
void Principal::ventaMarcas2(pnodoProd R, string codProd, string codMar){
    if(R==NULL){
        return;
    }else{
        ventaMarcas2(R->hIzq, codProd, codMar);
        if (R->codProducto==codProd)
            ventaMarcas3(R->subsiguiente, codMar);
        ventaMarcas2(R->hDer, codProd, codMar);
    }
}
void Principal::ventaMarcas3(pnodoMarca R, string codMar ){
    if(R==NULL){
        return;
    }else{
        ventaMarcas3(R->hIzq, codMar);
        if (R->codMarca==codMar)
            R->cantcomp++;
        ventaMarcas3(R->hDer, codMar);
    }
}
pnodoMarca Principal::MarcasMasVendidas3(pnodoMarca R, pnodoMarca marcMas){
    if(R==NULL){

    }else{
        marcMas=MarcasMasVendidas3(R->hIzq, marcMas);
        if (R->cantcomp>marcMas->cantcomp){
            marcMas=R;
        }
        marcMas=MarcasMasVendidas3(R->hDer, marcMas);
    }
    return marcMas;
}
pnodoMarca Principal::MarcasMasVendidas2(pnodoProd R, string codProd, pnodoMarca marcMas){
    if(R==NULL){

    }else{
        marcMas=MarcasMasVendidas2(R->hIzq,codProd,marcMas);
        if (R->codProducto==codProd){
            marcMas=MarcasMasVendidas3(R->subsiguiente, marcMas);
        }
        marcMas=MarcasMasVendidas2(R->hDer, codProd, marcMas);
    }
    return marcMas;
}
pnodoMarca Principal::MarcasMasVendidas(pnodoPas R, string codPas, string codProd,pnodoMarca MarcMas){
    if(R==NULL){

    }else{
        MarcMas=MarcasMasVendidas(R->hIzq,codPas,codProd,MarcMas);
        if (R->codPasillo==codPas){
            MarcMas=MarcasMasVendidas2(R->subsiguiente,codProd, MarcMas);
        }
        MarcMas=MarcasMasVendidas(R->hIzq,codPas,codProd, MarcMas);
    }
    return MarcMas;
}
pnodoPas arbolPas::nodoPasillos(pnodoPas R, string codPas, pnodoPas pasi){
    if(R==NULL){

    }else{
        pasi=nodoPasillos(R->hIzq,codPas,pasi);
        if (R->codPasillo==codPas){
            pasi=R;
        }
        pasi=nodoPasillos(R->hDer,codPas, pasi);
    }
    return pasi;
}
void Principal::InordenProReporte(pnodoProd R, string codProd){
    if(R==NULL){
        return;
    }else{
        InordenProReporte(R->hIzq, codProd);
        if(R->codProducto==codProd){
            RN mar;
            mar.raiz=R->subsiguiente;
            InordenMarReporte(R->subsiguiente);
        }
        InordenProReporte(R->hDer, codProd);
    }
}
void Principal::InordenTripleReporte(pnodoPas R, string codPas, string codProd){
    if(R==NULL){
        return;
    }else{
        InordenTripleReporte(R->hIzq, codPas, codProd);
        if(R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            InordenProReporte(R->subsiguiente,codProd);
        }
        InordenTripleReporte(R->hDer, codPas, codProd);
    }
}
void Principal::InordenMarReporte(pnodoMarca R){
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    if(archivo.fail())
        archivo.open("Reportes Administrador.txt",ios::out);
    if(R==NULL){
        return;
    }else{
        InordenMarReporte(R->hIzq);
        archivo<<"                       "<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<<endl;
        InordenMarReporte(R->hDer);
    }
    archivo.close();
}
void Principal::InordenProReporte2_2(pnodoProd R){
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    if(archivo.fail())
        archivo.open("Reportes Administrador.txt",ios::out);
    if(R==NULL){
        return;
    }else{
        InordenProReporte2_2(R->hIzq);
            archivo<<"                        "<<R->codProducto<<"~"<<R->nombre<<endl;
        InordenProReporte2_2(R->hDer);
    }
    archivo.close();
}
void Principal::InordenTripleReporte2_1(pnodoPas R, string codPas){
    if(R==NULL){
        return;
    }else{
        InordenTripleReporte2_1(R->hIzq, codPas);
        if(R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            InordenProReporte2_2(R->subsiguiente);
        }
        InordenTripleReporte2_1(R->hDer, codPas);
    }
}
void ArbolB::mostrar1()
{
    mostrar(raiz, 1);
}
void ArbolB::mostrar(Pagina *r, int h)
{
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    if(archivo.fail())
        archivo.open("Reportes Administrador.txt",ios::out);
    int i;
    if (r != NULL)
    {
        mostrar(r->obtenerRama(0), h + 5);
        for(int i = 1; i <= r->obtenerCuenta() / 2; i++){
            mostrar(r->obtenerRama(i), h + 5);
            cout << endl;
        }
        for(i = 1; i <= r->obtenerCuenta(); i++)
        {
            for(int j = 0; j <= h; j++)
            {
                cout << " ";
            }
            archivo<<"\n                                    "<< r->obtenerClave(i) <<","<< r->obtenerDato(i,0) << endl;
        }
        for(i = r->obtenerCuenta() / 2 + 1; i <= r->obtenerCuenta(); i++)
        {
            this->mostrar(r->obtenerRama(i), h + 5);
        }
        cout << endl;
    }
    archivo.close();
}
void arbolPas::MostrarPasillosReporte(pnodoPas ra){
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    if(archivo.fail())
        archivo.open("Reportes Administrador.txt",ios::out);
    if (ra==NULL){
        return;
    }
    else{
        MostrarPasillosReporte(ra->hIzq);
        archivo<<"                                         "<<ra->nombre<<" "<<ra->codPasillo<<endl;
        MostrarPasillosReporte(ra->hDer);
    }
    archivo.close();
}
void ArbolInventario::InordenReporte(pnodoInventario R){
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    if(archivo.fail())
        archivo.open("Reportes Administrador.txt",ios::out);
    if(R==NULL){
        return;
    }else{
        InordenReporte(R->hIzq);
        archivo<<"                                   "<<R->codMarca<<" "<<R->nombre<<"  "<<R->impuesto<<" "<<R->codCanasta<<endl;
        InordenReporte(R->hDer);
    }
    archivo.close();
}
void lista::InsertarFinalCliente(int ced, string nom, string ciu,string tel,string correo)
{
   if (ListaVaciaClie())
     primeroClie = new nodoCola(ced, nom, ciu, tel, correo);
   else
     { pnodoCola aux = primeroClie;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoCola(ced, nom, ciu, tel, correo);
      }
}
void Principal::clienteMasFacturas(){
    ofstream archivo;
    archivo.open("Reportes Administrador.txt",ios::app);
    if(archivo.fail())
        archivo.open("Reportes Administrador.txt",ios::out);
    pnodoCola aux=princi.cliente.primeroClie;
    pnodoCola menor=princi.cliente.primeroClie;
    pnodoCola mayor=princi.cliente.primeroClie;
    pnodoCola masMonto=princi.cliente.primeroClie;
    cout<<"Cola sirve: "<<aux<<endl;
    while(aux!=NULL){
        if (mayor->cantFact<aux->cantFact){
            mayor=aux;
        }
        else if (menor->cantFact>aux->cantFact){
            menor=aux;
        }
        if (masMonto->montoFact<aux->montoFact){
            masMonto=aux;
        }
        aux=aux->siguiente;
    }
    archivo<<"\nCliente con mas facturas: "<<endl;
    archivo<<"                         "<<mayor->cedula<<" "<<mayor->cantFact<<endl;
    archivo<<"\nCliente con menos facturas: "<<endl;
    archivo<<"                         "<<menor->cedula<<" "<<menor->cantFact<<endl;
    archivo<<"\nFactura de mayor monto: "<<endl;
    archivo<<"                          "<<masMonto->cedula<<" "<<masMonto->nombre<<" "<<masMonto->montoFact<<endl;
    archivo.close();
}
#endif // PROGRAPRINCIPAL_H
