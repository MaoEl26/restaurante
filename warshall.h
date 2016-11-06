#ifndef WARSHALL_H
#define WARSHALL_H
#include "Matriz.h"
#include <iostream>
using namespace std;

class Warshall
{
    public:
        Warshall(int nodos,Matriz<ArrayList<int> *, int> *matriz);
        void convertirMatriz();
        void algoritmo ();
        Matriz<ArrayList<int>*,int> getMatriz();
        virtual ~Warshall();

    protected:
        Matriz< ArrayList<int>*,int> *matrizAdyacencia;
        int nodos;



};

#endif // WARSHALL_H
