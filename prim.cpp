#include "Prim.h"
#define infinito -1
#define vacio -300

Prim::Prim(int nodos, Matriz<ArrayList<int> *, int> *matrizPesos)
{
   //Inicializa los arreglos y matrices
    this->matrizPesos= matrizPesos;  //Matriz de pesos de grafo original
    this->nodos= nodos;   //Cantidad de nodos totales
    matrizValoresUsados = new Matriz< ArrayList<bool>*,bool>(nodos); //Marcara en true las aristas por las cuales ya
                                                                        // se recorrio
    nodosVisitados = new ArrayList<bool>(nodos); //Indicara cuales nodos ya fueron visitados
    nodosInicial = new ArrayList<int>(nodos);
    nodosDestinos = new ArrayList<int>(nodos);
    cantidadNodosVisitados=1; //ira aumentando de acuerdo a los nodos q ya se visitaron
    cantidadNodos();
}

void Prim::cantidadNodos(){

    //Pone todos los elementos de la matriz en 0 y false
    for(int i=0; i<nodos;i++){
        matrizValoresUsados->returnPos(i)->allEqual(false);
    }
    pesoMayor=0;
    nodosVisitados->allEqual(false);
    nodosVisitados->setValue(0,true);
    nodosInicial->allEqual(infinito);
    nodosDestinos->allEqual(infinito);

    for(int i=0; i<nodos; i++){
        //Pone en true la diagonal
        matrizValoresUsados->returnPos(i)->setValue(i,true);
        for(int j=0; j<nodos;j++){
            //Busca el nodo con mayor peso
            if(matrizPesos->returnPos(i)->returnPos(j) > pesoMayor){
                pesoMayor=matrizPesos->returnPos(i)->returnPos(j);
            }
        }
    }

    algoritmo();
}

void Prim::algoritmo(){

    int contador= 0;
    while(cantidadNodosVisitados!= nodos){
        busquedaNodoMenor();
        matrizValoresUsados->returnPos(filaMenor)->setValue(columnaMenor,true);
        matrizValoresUsados->returnPos(columnaMenor)->setValue(filaMenor,true);
        nodosVisitados->setValue(columnaMenor,true);
        nodosInicial->setValue(contador,filaMenor);
        nodosDestinos->setValue(contador,columnaMenor);
        contador++;
    }
}

void Prim::busquedaNodoMenor(){
    //i fila
    //j columna
    int pesoMenor= pesoMayor;
    for(int i=0; i < nodosVisitados->getSize(); i++){
        if(nodosVisitados->returnPos(i)){
            for(int j=0; j<nodos; j++){
                if(nodosVisitados->returnPos(j)!= true &&
                   matrizValoresUsados->returnPos(i)->returnPos(j)!= true &&
                   pesoMenor >= matrizPesos->returnPos(i)->returnPos(j)&&
                   matrizPesos->returnPos(i)->returnPos(j)!= infinito){
                   pesoMenor = matrizPesos->returnPos(i)->returnPos(j);
                   filaMenor= i;
                   columnaMenor=j;
               }
            }
        }
    }
    cantidadNodosVisitados+=1;
}

ArrayList<int> Prim::getRutaInicial(){
    return *nodosInicial;
}

ArrayList<int> Prim::getRutaDestino(){
    return *nodosDestinos;
}

Prim::~Prim()
{
    //dtor
}
