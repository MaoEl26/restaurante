#ifndef FLOYD_H
#define FLOYD_H

#include "Matriz.h"

#include <iostream>
#include <stdlib.h>

using namespace std;

class Floyd
{
    public:
        Floyd();
        virtual ~Floyd();

    protected:
        void creaMatriz();
        void algoritmoFloyd();
        void print(Matriz< ArrayList<int>*,int> *matriz);

        Matriz< ArrayList<int>*,int> *matrizD0;
        Matriz< ArrayList<int>*,int> *matrizDn;

        int nodos;
    private:
};

#endif // FLOYD_H
