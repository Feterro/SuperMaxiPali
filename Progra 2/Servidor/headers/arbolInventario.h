#ifndef ARBOLINVENTARIO_H
#define ARBOLINVENTARIO_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"

using namespace std;

class ArbolInventario{
public:
    nodoInventario *raiz;
	ArbolInventario() { raiz = NULL; }
    void InordenR(pnodoInventario ra);
    pnodoInventario insertar(int codArb,string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta, pnodoInventario aux);
    pnodoInventario giro(pnodoInventario aux);
    pnodoInventario reparto(pnodoInventario aux);
    pnodoInventario rotarDerecha(pnodoInventario aux);
    pnodoInventario rotarIzquierda(pnodoInventario aux);
    void Inorden(pnodoInventario ra);
    ArbolInventario agregarInventario();
    pnodoInventario encontrarNodo(pnodoInventario ra, string codPas, string codProd, string codMar, pnodoInventario nodoIn);
    void setImpuesto(int num, pnodoInventario inv);
    void InordenReporte(pnodoInventario R);

friend class Principal;

};
#endif // ARBOLINVENTARIO_H
