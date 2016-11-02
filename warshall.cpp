#include "Warshall.h"
#define infinito -1
#define uno 1
#define cero 0
Warshall::Warshall(int nodos, Matriz<ArrayList<int> *, int> *matriz)
{
    this->nodos= nodos;
    matrizAdyacencia = matriz;
    convertirMatriz();
    algoritmo();
}

void Warshall::convertirMatriz(){

    int numero;
    for(int i= cero; i<nodos; i++){
        for(int j= cero ; j<nodos; j++){
            numero = matrizAdyacencia->returnPos(i)->returnPos(j);
            if(numero!= infinito && j != i){
                matrizAdyacencia->returnPos(i)->setValue(j,uno);
            }
            else{
                matrizAdyacencia->returnPos(i)->setValue(j,cero);
            }
        }
    }
}

void Warshall::algoritmo(){

        for(int k = 0; k < nodos; k++){
                cout<<endl;
            for(int i = 0; i < nodos; i++){
                for(int j = 0; j < nodos; j++){
                    if(matrizAdyacencia->returnPos(i)->returnPos(j) == 1 ||
                       (matrizAdyacencia->returnPos(i)->returnPos(k)== 1 &&
                        matrizAdyacencia->returnPos(k)->returnPos(j))){
                            matrizAdyacencia->returnPos(i)->setValue(j,uno);
                    }
                }
            }
        }
}

Warshall::~Warshall()
{
    //dtor
}
