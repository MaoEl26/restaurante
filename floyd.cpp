#include "Floyd.h"
#define infinito -1

Floyd::Floyd(int nodos, Matriz<ArrayList<int> *, int> *matrizPesos){
    this->nodos=nodos;
    matrizDn = matrizPesos;
    matrizRutas = new Matriz<ArrayList<int>*,int>(nodos);
    for(int i=0;i<nodos;i++){
        matrizRutas->returnPos(i)->allEqual(0);
    }
}

Matriz<ArrayList<int> *, int> Floyd::algoritmoFloyd(){
    int valorActual;
    int valorFila;
    int valorColumna;
     for(int k = 0; k < nodos; k++){
        for(int i = 0; i < nodos; i++){
          for(int j = 0; j < nodos; j++){
                if(i!=j){
                    valorFila = matrizDn->returnPos(i)->returnPos(k);
                    if (valorFila!=infinito){
                        valorColumna = matrizDn->returnPos(k)->returnPos(j);
                        if (valorColumna != infinito){
                            valorActual = matrizDn->returnPos(i)->returnPos(j);
                            if(valorActual != infinito){
                                    int minimo=min(valorActual,(valorFila+valorColumna));
                                    if (minimo!=valorActual){
                                        matrizDn->returnPos(i)->remove(j);
                                        matrizDn->insert(i,j,minimo);
                                        matrizRutas->returnPos(i)->setValue(j,k+1);
                                    }
                            }else{
                                matrizDn->returnPos(i)->remove(j);
                                matrizDn->insert(i,j,(valorFila+valorColumna));
                                matrizRutas->returnPos(i)->setValue(j,k+1);
                            }
                        }
                    }
                }
            }
        }
     }

     return *matrizDn;
}

Matriz<ArrayList<int> *, int> Floyd::getMatrizRutas(){
    return *matrizRutas;
}

Floyd::~Floyd()
{
    //dtor
}
