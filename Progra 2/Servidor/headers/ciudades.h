#ifndef CIUDADES_H
#define CIUDADES_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include "nodos.h"
using namespace std;
class Ciudad {
   public:
    Ciudad() { primero = actual = NULL; }

    void InsertarFinal(int cod, string nom);
    bool listaVacia() { return primero == NULL; }
    void Mostrar();
    int largoCiudad();
    Ciudad agregarCiudades();
    bool agregarCiudad(Ciudad lista, int cod);

   private:
    pnodoCiudad primero;
    pnodoCiudad actual;
};
#endif // CIUDADES_H
