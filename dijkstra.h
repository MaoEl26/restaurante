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
        Dijkstra();
        virtual ~Dijkstra();

        void algoritmo();

        void cantidadNodos();
        void ruta(int nodoBusqueda);



    protected:
        Matriz< ArrayList<int>*,int> *matrizPesos;
        Matriz< ArrayList<int>*, int> *matrizPesosDijkstra;
        ArrayList<bool> *nodosVisitados;
        ArrayList<int>* pesosMenores;
        ArrayList<int>* posicionMenores;
        int nodos;
        int ultimaFilaCompletada;
        int busquedaNodoMenor(int fila);

    private:
};

#endif // DIJKSTRA_H

