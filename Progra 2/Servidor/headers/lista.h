#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"
using namespace std;
class lista {
   public:
    lista() { primero = actual = NULL; primeroMar = actualMar= NULL; primeroClie=actualClie=NULL;}

    void InsertarFinal(string codPas, string codPro, string nom);
    void InsertarFinalMar(string codPas, string nom, string codPro, string codMar,int cantGon,float precio);
    bool ListaVacia() { return primero == NULL; }
    bool ListaVaciaMar() { return primeroMar == NULL; }
    int largoLista();
    int largoListaMar();
    void Mostrar();
    void MostrarMar();
    lista enlistarCodigos();
    lista enlistarCodigosMar();
    bool verificarCedula();
    void InsertarFinalCliente(int ced, string nom, string ciudad, string tel,string correo);
    bool ListaVaciaClie() { return primeroClie == NULL; }



    pnodoCola primeroClie;
    pnodoCola actualClie;
   private:
    pnodoProd primero;
    pnodoMarca primeroMar;
    pnodoProd actual;
    pnodoMarca actualMar;

    friend class arbolPas;
    friend class RN;
    friend class AVLProducto;
};
#endif // LISTA_H
