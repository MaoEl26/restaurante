#ifndef FLOYD_H
#define FLOYD_H

#include "Matriz.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

class Floyd
{
    public:
        Floyd(int nodos, int nodoInicio, int nodoDestino, Matriz<ArrayList<int> *, int> *matrizPesos);
        void algoritmoFloyd();
        Matriz<ArrayList<int> *, int> getMatrizRutas();
        Matriz<ArrayList<int> *, int> getMatrizPesos();
        ArrayList<int> getRuta();
        virtual ~Floyd();

    protected:

        Matriz< ArrayList<int>*,int> *matrizRutas;
        Matriz< ArrayList<int>*,int> *matrizDn;
        ArrayList<int> *ruta;

        int nodos;
        int nodoInicio;
        int nodoDestino;
    private:
};

#endif // FLOYD_H
