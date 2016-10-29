#ifndef MATRIZ_H
#define MATRIZ_H
#include "ArrayList.h"

template<class E,class V>
class Matriz
{
    public:
        Matriz(int pMax);
        void cambiarFila(int pos);
        E returnPos(int position);
        void insert(int fila,int columna,V valor);
        virtual ~Matriz();

    protected:

    private:
        void insertArray();
        int size;
        int max;
        int pos;
        E* elements;
};

#endif // MATRIZ_H
