#ifndef FLOYD_H
#define FLOYD_H

#include "Matriz.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

class Floyd
{
    public:
        Floyd(int nodos,  Matriz<ArrayList<int> *, int> *matrizPesos);
        Matriz<ArrayList<int> *, int> algoritmoFloyd();
        Matriz<ArrayList<int> *, int> getMatrizRutas();
        virtual ~Floyd();

    protected:

        Matriz< ArrayList<int>*,int> *matrizRutas;
        Matriz< ArrayList<int>*,int> *matrizDn;

        int nodos;
    private:
};

#endif // FLOYD_H
