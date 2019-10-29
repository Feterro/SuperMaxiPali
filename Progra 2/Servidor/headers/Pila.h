#ifndef PILA_H
#define PILA_H

#include "globalizarCola.h"

class Pila {
   public:
    Pila() { primero = actual = NULL; }
    void InsertarFinal(int pas, int prod, int codMarc, int cant, float precio); //Para la pila de cada cliente y para la lista de ventas
    void InsertarFinalOrd(string codPas, string codProd, string codMar, int cant, float precio);
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
   private:
    pnodoPila primero;
    pnodoPila actual;
friend class Principal;
};
#endif // PILA_H
