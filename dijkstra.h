#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include "Matriz.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class Dijkstra
{
    public:
        Dijkstra(int nodos, int nodoBusqueda , int nodoDestino, Matriz< ArrayList<int>*,int> *matrizPeso);
        virtual ~Dijkstra();
        void algoritmo();
        void cantidadNodos();
        void ruta();
        ArrayList<int>getRutaPesos();
        ArrayList<int>getRutaNodo();

    protected:
        Matriz< ArrayList<int>*,int> *matrizPesos;
        Matriz< ArrayList<int>*, int> *matrizPesosDijkstra;
        ArrayList<bool> *nodosVisitados;
        ArrayList<int>* pesosMenores;
        ArrayList<int>* posicionMenores;
        ArrayList<int>* rutaNodo;
        int nodos;
        int ultimaFilaCompletada;
        int busquedaNodoMenor(int fila);
        int nodoMayorDistancia;
        int nodoBusqueda;
        int nodoDestino;

    private:
};

#endif // DIJKSTRA_H

