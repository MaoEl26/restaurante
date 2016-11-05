#include "Matriz.h"
#include <stdexcept>
#include <iostream>
using namespace std;
template<class E,class V>
Matriz<E,V>::Matriz(int pMax)
{
    //Crea el nuevo array
    max = pMax;
    size = 0;
    pos = 0;
    elements = new E[pMax];
    insertArray(max);
}

template<class E,class V>
Matriz<E,V>::Matriz(int maxMatriz, int maxArray)
{
    //Crea el nuevo array
    max = maxMatriz;
    size = 0;
    pos = 0;
    elements = new E[max];
    insertArray(maxArray);
}


template <class E,class V>
void Matriz<E,V>::cambiarFila (int pos){
    //Establece una nueva posición
    this->pos = pos;
}

template <class E,class V>
E Matriz<E,V>::returnPos(int position){
    //Establece una nueva posición
    return elements[position];
}


template <class E,class V>
void Matriz<E,V>::insertArray(int maxArray){
        for (int i=0; i<max; i++){
        elements[i]= new ArrayList<V>(maxArray);
    }
}

template <class E,class V>
void Matriz<E,V>::insert(int fila,int columna,V valor){
    elements[fila]->goToPos(columna);
    elements[fila]->insert(valor);
}



template<class E,class V>
Matriz<E,V>::~Matriz()
{
    //dtor
}


template class Matriz< ArrayList<int>*,int >;
template class Matriz< ArrayList<bool>*,bool>;
template class Matriz< ArrayList<string>*,string>;
