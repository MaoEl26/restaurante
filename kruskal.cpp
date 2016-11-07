#include "kruskal.h"

#define infinito 999999999  

Kruskal::Kruskal(Matriz<ArrayList<int>*,int>* matriz, int cantidadNodos){

    matrizKruskalInicial = new Matriz< ArrayList<int>*,int>(cantidadNodos);

    this->nodos=cantidadNodos;

    for(int i =0; i<nodos;i++){
        for(int j=0;j<nodos;j++){
            matrizKruskalInicial->insert(i,j,matriz->returnPos(i)->returnPos(j));
        }
    }

    matrizKruskalResultado = new Matriz< ArrayList<int>*,int>(nodos);
    nodosUsados = new ArrayList<int>(nodos);
    nodosInicio = new ArrayList<int>(nodos);
    nodosDestino = new ArrayList<int>(nodos);
    pesoRuta = new ArrayList<int>(nodos);
    nodosDestino->allEqual(-1);
    nodosInicio->allEqual(-1);
    pesoRuta->allEqual(-1);
    for (int i=0;i<nodos;i++){
        matrizKruskalResultado->returnPos(i)->allEqual(0);
        nodosUsados->insert(i);
    }
    algoritmoKruskal();
}

Matriz<ArrayList<int>*,int> Kruskal::algoritmoKruskal(){
    int nodoTempA;
    int nodoTempB;
    int conexiones = 1;

    while(conexiones<nodos){
        int min=infinito;
        for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                if ((min > matrizKruskalInicial->returnPos(i)->returnPos(j) &&
                     matrizKruskalInicial->returnPos(i)->returnPos(j)!=-1)
                    && (matrizKruskalInicial->returnPos(i)->returnPos(j)!=0) &&
                nodosUsados->returnPos(i)!= nodosUsados->returnPos(j)){
                    min=matrizKruskalInicial->returnPos(i)->returnPos(j);
                    nodoTempA=i;
                    nodoTempB=j;
                }
            }
        }
        if(nodosUsados->returnPos(nodoTempA)!=nodosUsados->returnPos(nodoTempB)){

            pesoRuta->setValue(conexiones-1,min);
            nodosInicio->setValue(conexiones-1,nodoTempA);
            nodosDestino->setValue(conexiones-1,nodoTempB);

            matrizKruskalResultado->returnPos(nodoTempA)->setValue(nodoTempB,min);
            matrizKruskalResultado->returnPos(nodoTempB)->setValue(nodoTempA,min);

            int valorTemporal = nodosUsados->returnPos(nodoTempB);

            nodosUsados->setValue(nodoTempB,nodosUsados->returnPos(nodoTempA));
            for(int k=0; k<nodos;k++){
                if (nodosUsados->returnPos(k)== valorTemporal){
                    nodosUsados->setValue(k,nodosUsados->returnPos(nodoTempA));
                }
            }

            conexiones++;
        }
    }

    return *matrizKruskalResultado;
}

ArrayList<int> Kruskal::getRutaInicial(){
    return *nodosInicio;
}

ArrayList<int> Kruskal::getRutaDestino(){
    return *nodosDestino;
}

ArrayList<int> Kruskal::getPesoRuta(){
    return *pesoRuta;
}

Kruskal::~Kruskal(){
    //dtor
}
