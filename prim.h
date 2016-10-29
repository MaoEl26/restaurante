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
        Prim();
        virtual ~Prim();
        void cantidadNodos();
        void algoritmo();
        void busquedaNodoMenor();
    protected:
        int nodos;
        Matriz< ArrayList<int>*,int> *matrizPesos;
        Matriz< ArrayList<bool>*,bool> *matrizValoresUsados;
        ArrayList<bool> *nodosVisitados;
        ArrayList<int> *nodosInicial;
        ArrayList<int> *nodosDestinos;
        int filaMenor;
        int columnaMenor;
        int pesoMayor;
        int cantidadNodosVisitados;
};

#endif // PRIM_H
