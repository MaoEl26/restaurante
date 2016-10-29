#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Matriz.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

class Kruskal
{
    public:
        Kruskal();
        virtual ~Kruskal();

    protected:
        void print();
        void ingresoDatos();
        void algoritmoKruskal();

        int nodos;
        Matriz<ArrayList<int>*,int> *matrizKruskalInicial;
        Matriz<ArrayList<int>*,int> *matrizKruskalResultado;
        ArrayList<int> *nodosUsados;

    private:
};

#endif // KRUSKAL_H
