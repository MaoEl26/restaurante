#ifndef PRIM_H
#define PRIM_H
#include "Matriz.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

class Prim
{
    public:
        Prim(int nodos, Matriz<ArrayList<int> *, int> *matriz);
        virtual ~Prim();
        void cantidadNodos();
        void algoritmo();
        void busquedaNodoMenor();
        ArrayList<int> getRutaInicial();
        ArrayList<int> getRutaDestino();
        ArrayList<int> getPesos();

    protected:
        int nodos;
        Matriz< ArrayList<int>*,int> *matrizPesos;
        Matriz< ArrayList<bool>*,bool> *matrizValoresUsados;
        ArrayList<bool> *nodosVisitados;
        ArrayList<int> *nodosInicial;
        ArrayList<int> *nodosDestinos;
        ArrayList<int> *arrayPesos;
        int filaMenor;
        int columnaMenor;
        int pesoMayor;
        int cantidadNodosVisitados;
};

#endif // PRIM_H
