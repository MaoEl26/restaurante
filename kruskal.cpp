#include "kruskal.h"

#define infinito 999999999

Kruskal::Kruskal(Matriz<ArrayList<int>*,int>* matriz, int cantidadNodos){
    matrizKruskalInicial = matriz;
    this->nodos=cantidadNodos;
    matrizKruskalResultado = new Matriz< ArrayList<int>*,int>(nodos);
    nodosUsados = new ArrayList<int>(nodos);

    for (int i=0;i<nodos;i++){
        matrizKruskalResultado->returnPos(i)->allEqual(0);
        nodosUsados->insert(i);
    }
}

Matriz<ArrayList<int>*,int>* Kruskal::algoritmoKruskal(){
    int nodoTempA;
    int nodoTempB;
    int conexiones = 1;

    while(conexiones<nodos){
        int min=infinito;
        for(int i=0;i<nodos;i++){
            for(int j=0;j<nodos;j++){
                if ((min > matrizKruskalInicial->returnPos(i)->returnPos(j))
                    && (matrizKruskalInicial->returnPos(i)->returnPos(j)!=0) &&
                nodosUsados->returnPos(i)!= nodosUsados->returnPos(j)){
                    min=matrizKruskalInicial->returnPos(i)->returnPos(j);
                    nodoTempA=i;
                    nodoTempB=j;
                }
            }
        }
        if(nodosUsados->returnPos(nodoTempA)!=nodosUsados->returnPos(nodoTempB)){
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
    for(int i=0;i<nodos;i++){
           for(int j=0;j<nodos;j++){
               cout<<matrizKruskalResultado->returnPos(i)->returnPos(j);
           }
           cout<<endl;
       }
    return matrizKruskalResultado;
}

Kruskal::~Kruskal(){
    //dtor
}
