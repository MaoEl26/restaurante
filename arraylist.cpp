#include "ArrayList.h"
#define default_max_size 1024
#include <stdexcept>
#include <iostream>
using namespace std;


template <class E>
ArrayList<E>::ArrayList(int pMax)
{
    //Crea el nuevo array
    max = pMax;
    size = 0;
    pos = 0;
    elements = new E [pMax];
}


template <class E>
int ArrayList<E>::getPos (){
    return pos;
}

template <class E>
int ArrayList<E>::getMax (){
    return max;
}

template <class E>
void ArrayList<E>::goToStart(){
    pos = 0;
}

template <class E>
void ArrayList<E>::next(){
    if (pos < size){
        pos++;
    }
}

template <class E>
void ArrayList<E>::goToEnd(){
    pos = size;
}


template <class E>
void ArrayList<E>::previous(){
    // Validaciones
    pos--;
}


template <class E>
int ArrayList<E>::getSize(){
    //Retorna el tamaño del arreglo
    return size;
}

template <class E>
void ArrayList<E>::goToPos(int pos){
    //Establece una nueva posición
    this->pos = pos;
}

template <class E>
void ArrayList<E>::setValue(int pos,E value){
    elements[pos]= value;
}

template <class E>
void ArrayList<E>::append(E pElement){
    //Agrega al final de la lista un nuevo elemento
    elements [size] = pElement;
    size++;
}

template <class E>
void ArrayList<E>::insert(E pElement){
    //Inserta en un posición establecida previamente un elemento
    for (int i= size; i> pos; i--){
        elements [i] = elements[i-1];
    }
    elements[pos]= pElement;
    size++;
}

template <class E>
E ArrayList<E>::remove(int pos){
    //Remueve y retorna un elemento de una posición específica
    goToPos(pos);
    E deletedElement = elements [pos];
    for (int i = pos; i < size; i++){
        elements[i]= elements [i+1];
    }
    size --;
    return deletedElement;
}

template <class E>
E ArrayList<E>::returnPos(int pos){
    //Retorna el elemento de la posicion seleccionada
    return elements[pos];
}

template <class E>
void ArrayList<E>::clear(){
    //Limpia los valores de la lista
    int largoLista = size;
    for (int i= largoLista;i>0;i--){
        remove(i);
    }
}

template <class E>
//Precondicion: Pos debe apuntar al elemento que se quiere procesar
E ArrayList<E>::getValue(){
    if (pos < 0 || pos > size){
        throw runtime_error ("Index out of bound");
    }else{
        return elements [pos];
    }
}



template <class E>
void ArrayList<E>::print(){
    for (int i =0; i< size; i++){
        cout <<"Elemento sub "<<i<<" : "<<elements[i]<<"\n";
    }
}

template <class E>
void ArrayList<E>::allEqual(E pElement){
    size= max;
    for(int i=0; i< max; i++){
        elements[i]= pElement;
    }
}

template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<bool>;

