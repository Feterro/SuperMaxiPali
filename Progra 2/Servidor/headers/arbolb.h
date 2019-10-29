#ifndef ARBOLB_H
#define ARBOLB_H
#include <string>
#include <fstream>
#include <sstream>
#include "nodos.h"

using namespace std;
class ArbolB
{
protected:
    int orden;
    Pagina *raiz;

private:
    Pagina *insertar(Pagina *raiz, tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo);
    bool empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo, string &nombre, string &telefono, string &codigoCiudad, string &correo);
    void meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k, string nombre, string telefono, string codigoCiudad, string correo);

public:
    ArbolB()
    {
        this->orden = 0;
        this->raiz = NULL;
    }

    explicit ArbolB(int m)
    {
        this->orden = m;
        this->raiz = NULL;
    }
    bool arbolVacio() { return this->raiz == NULL; }
    Pagina *obtenerRaiz() { return raiz; }
    void cambiarRaiz(Pagina *r) { raiz = r; }
    int obtenerOrden() { return orden; }
    void cambiarOrden(int ord) { orden = ord; }

    Pagina *buscar(tipoClave cl, int &n);
    Pagina *buscar(Pagina *actual, tipoClave cl, int &n);

    bool buscarNodo(Pagina *actual, tipoClave cl, int &k);
    void dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos, string &nombre, string &telefono, string &codigoCiudad, string &correo);

    void escribir();
    void escribir(Pagina *r, int h);

    void listaCreciente();
    void inOrden(Pagina *r);
    void cargarClientes (string pNombreArchivo);
    void cargarAdmins(string pNombreArchivo);

    void insertar(tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo);
    void agregarClienteNoRegistrado(int cedula, ArbolB arbol);
    void mostrar1();
    void mostrar(Pagina *r, int h);

    friend class Principal;
};
#endif // ARBOLB_H
