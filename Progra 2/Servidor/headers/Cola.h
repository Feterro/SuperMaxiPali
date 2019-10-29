#ifndef COLA_H
#define COLA_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"

using namespace std;
class colaCliente {
   public:
    colaCliente() { primero = actual = NULL; }
    void InsertarFinal(int ced, string nom, int tel, string correo); //Inserta cada cliente en la cola
    bool ListaVacia() { return primero == NULL; }
    void Mostrar();
    void Siguiente();
    void Primero();
    void Ultimo();
    void BorrarInicio();
    int largoLista();

   private:
    pnodoCola primero;
    pnodoCola actual;
  friend class Principal;
};
#endif // COLA_H
