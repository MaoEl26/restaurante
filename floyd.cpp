#include "Floyd.h"
#define infinito -1

Floyd::Floyd(int nodos, Matriz<ArrayList<int> *, int> *matrizPesos){
    this->nodos=nodos;
    matrizDn = matrizPesos;
    algoritmoFloyd();
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
                                    matrizDn->returnPos(i)->remove(j);
                                    matrizDn->insert(i,j,min(valorActual,(valorFila+valorColumna)));
                            }else{
                                matrizDn->returnPos(i)->remove(j);
                                matrizDn->insert(i,j,(valorFila+valorColumna));
                            }
                        }
                    }
                }
            }
        }
     }
     return *matrizDn;
}


Floyd::~Floyd()
{
    //dtor
}
