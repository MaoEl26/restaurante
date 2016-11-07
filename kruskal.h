#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Matriz.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

class Kruskal
{
    public:
        Kruskal(Matriz<ArrayList<int> *, int>* matriz, int cantidadNodos);
        virtual ~Kruskal();

        Matriz<ArrayList<int> *, int> algoritmoKruskal();

        ArrayList<int> getPesoRuta();
        ArrayList<int> getRutaInicial();
        ArrayList<int> getRutaDestino();

    protected:

        int nodos;
        Matriz<ArrayList<int>*,int> *matrizKruskalInicial;
        Matriz<ArrayList<int>*,int> *matrizKruskalResultado;
        ArrayList<int> *pesoRuta;
        ArrayList<int> *nodosInicio;
        ArrayList<int> *nodosDestino;
        ArrayList<int> *nodosUsados;

    private:
};

#endif // KRUSKAL_H
