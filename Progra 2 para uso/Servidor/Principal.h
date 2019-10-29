#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include "headers/nodos.h"
#include "headers/ciudades.h"
#include "headers/avlProducto.h"
#include "headers/arbolPas.h"
#include "headers/arbolInventario.h"
#include "headers/arbolb.h"
#include "headers/rojinegro.h"
#include "headers/lista.h"

using namespace std;
class colaCliente {
   public:
    colaCliente() { primero = actual = NULL; }
    void InsertarFinal(int ced, string nom, string codCiudad, string tel, string correo,qintptr descriptor); //Inserta cada cliente en la cola
    bool ListaVacia() { return primero == NULL; }
    void Mostrar();
    bool agregarCliente(colaCliente cola, int cedula);
    void BorrarInicio();
    int largoLista();
    pnodoPila pila;
    pnodoCola primero;
   private:
    pnodoCola actual;
  friend class Principal;
};

class Pila {
   public:
    Pila() { primero = actual = NULL; }
    void InsertarFinal(int pas, int prod, int codMarc, int cant, float precio); //Para la pila de cada cliente y para la lista de ventas
    bool ListaVacia() { return primero == NULL; }
    void Mostrar();
    void BorrarInicio();
    int largoLista();
    void quickSort(nodoPila **prim);
    void InsertarFinalMay(float precio);
    nodoPila* quickSortRecur(nodoPila* head, nodoPila* tail);
    nodoPila* partition(nodoPila* head,nodoPila* tail,nodoPila **nhead,nodoPila **ntail);
    nodoPila *getTail(nodoPila *head);
    void eliminarTodo();
    void InsertarFinalOrd(string pas, string prod, string mar, int cant, float precio);

   private:
    pnodoPila primero;
    pnodoPila actual;
friend class Principal;
};

class listaVentas
{
   public:
    listaVentas() { primero = actual = NULL; }
    void InsertarFinal(string codPas, string codProd, string codMar, int cant);
    bool ListaVacia() { return primero == NULL; }
    void Mostrar();
    bool agregarArticulo(listaVentas lista, string pas, string prod, string mar);
    void BorrarInicio();
    int largoLista();
   private:
    pnodoVenta primero;
    pnodoVenta actual;
   friend class Principal;
};
class Principal
{
    public:
        Principal(){
        }
        bool validarCliente(ArbolB cliente, int ced);
        void escogerPasillo(int cant1,string codPas,string codPro,string codMar);
        void escogerProducto(int cant1,string codPas,string codPro,string codMar);
        void escogerMarca(int cant1,string codPas,string codPro,string codMar);
        void comprar(int cant1,string codPas,string codPro,string codMar);
        bool validarAdministrador(ArbolB administrador, int cod);
        bool agregarCola(ArbolB cliente, int cedula,qintptr descriptor);
        void login(arbolPas pas, AVLProducto prod, RN mar, ArbolInventario inv, ArbolB administradores, ArbolB clientes);
        //void menuCliente(arbolPas pasi, AVLProducto prod, RN mar, ArbolInventario inve, ArbolB cli, int ced);
        void listaVentas1(string pas, string prod, string mar, int cant);
        //Clientes
        string consultarUnPrecio(string codPas, string codProd, string codMar);
        string ConsultarImpuesto(string codPas, string codProd, string codMar);
        string ConsultarCanasta(string codPas, string codProd, string codMar);
        //Administrador
        string consultarUnPrecioAdm();
        arbolPas insertarMarca();
        void ModificarImpuesto();
        string ConsultarImpuesto();
        void ModificarPrecio();
        void ModificarCanasta();
        string ConsultarCanasta();
        void revisarGondolas();
        void encontrarPasSumar(pnodoPas R, string codPas, pnodoPas pasillo);
        void cargarInventario();
        string agregarListaOrdenada();
        string pagar(Pila pila);
        void PasillosMasMenosVisitado(pnodoPas R, string codPas, pnodoPas pasillo);
        pnodoPas PasillosMasVisitado(pnodoPas R,pnodoPas nodo1);
        pnodoPas PasillosMenosVisitado(pnodoPas R, pnodoPas nodo1);
        void generarReporte();
        pnodoProd ProductosMasVendidos2(pnodoProd R,pnodoProd prodMas);
        pnodoProd ProductosMasVendidos(pnodoPas R, string codPas,pnodoProd prodMas);
        void ventaProductos2(pnodoProd R, string codProd);
        void ventaProductos(pnodoPas R,string codPas, string codProd);
        pnodoMarca MarcasMasVendidas(pnodoPas R,string codPas,  string codProd, pnodoMarca marcMas);
        pnodoMarca MarcasMasVendidas2(pnodoProd R, string codProd, pnodoMarca marcMas);
        pnodoMarca MarcasMasVendidas3(pnodoMarca R, pnodoMarca marcMas);
        void ventaMarcas(pnodoPas R, string codPas, string codProd, string codMar);
        void ventaMarcas2(pnodoProd R, string codProd, string codMar);
        void ventaMarcas3(pnodoMarca R, string codMar );
        void InordenProReporte(pnodoProd R, string codProd);
        void InordenTripleReporte(pnodoPas R, string codPas, string codProd);
        void InordenMarReporte(pnodoMarca R);
        void InordenProReporte2_2(pnodoProd R);
        void InordenTripleReporte2_1(pnodoPas R, string codPas);
        void cargoEnGondolas(pnodoPas R, string codPas, string codProd);
        void cargoEnGondolas2(pnodoProd R, string codProd );
        pnodoProd ProductosMasCargado2(pnodoProd R,pnodoProd prodMas);
        pnodoProd ProductosMasCargado(pnodoPas R, string codPas,pnodoProd prodMas);
        pnodoProd masCargadoGondola(pnodoPas R, pnodoProd nodo2);
        pnodoProd masGondola(pnodoProd R, pnodoProd nodo2);
        void clienteMasFacturas();
        colaCliente cola;
        lista cliente;
    private:
        listaVentas ventas;
        //colaCliente cola;
};
#endif // PRINCIPAL_H
