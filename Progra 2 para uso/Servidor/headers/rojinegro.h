#ifndef ROJINEGRO_H
#define ROJINEGRO_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"
#include "arbolPas.h"
using namespace std;

class RN{
public:
    nodoMarca *raiz;
	RN() { raiz = NULL; }
	void rotarIzquierda(nodoMarca *&, nodoMarca *&);
	void rotarDerecha(nodoMarca *&, nodoMarca *&);
	void balancearArbol(nodoMarca *&, nodoMarca *&);
	void insert(const string &codPasilo,const string &nombre,const string &codProducto,const string &codMar,const int &gon, const float &val);
	void levelOrder();
	pnodoMarca insertarNodo(pnodoMarca raiz, pnodoMarca pt);
	void InordenMar(pnodoMarca R);
    string InordenMarServ(pnodoMarca R);
	void MostrarMarcas3(pnodoMarca ra);
	bool validarMarcas3(pnodoMarca ra, string codMar,bool encontrado);
	pnodoMarca encontrarNodo3(pnodoMarca ra, string codMar, pnodoMarca marca);
};
#endif // ROJINEGRO_H
