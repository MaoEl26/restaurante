#include "Floyd.h"
#define infinito -1

Floyd::Floyd(int nodos, int nodoInicio, int nodoDestino, Matriz<ArrayList<int> *, int> *matrizPesos){

    this->nodos=nodos;
    this->nodoInicio=nodoInicio;
    this->nodoDestino=nodoDestino;

    matrizDn = new Matriz<ArrayList<int>*,int>(nodos);

    for(int i =0; i<nodos;i++){
        for(int j=0;j<nodos;j++){
            matrizDn->insert(i,j,matrizPesos->returnPos(i)->returnPos(j));
        }
    }

    matrizRutas = new Matriz<ArrayList<int>*,int>(nodos);
    ruta= new ArrayList<int>(nodos);
    ruta->allEqual(-1);

    for(int i=0;i<nodos;i++){
        matrizRutas->returnPos(i)->allEqual(0);
    }
    algoritmoFloyd();
}

void Floyd::algoritmoFloyd(){
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
}

Matriz<ArrayList<int> *, int> Floyd::getMatrizPesos(){
    return *matrizDn;
}

Matriz<ArrayList<int> *, int> Floyd::getMatrizRutas(){
    return *matrizRutas;
}

ArrayList<int> Floyd::getRuta(){
    ruta->goToPos(0);
    ruta->insert(nodoInicio);
    ruta->goToPos(1);
    ruta->insert(nodoDestino);
    bool bandera=false;
    int pos=1;
    while(!bandera){
        int valor=matrizRutas->returnPos(nodoInicio)->returnPos(nodoDestino);
        if (valor==0){
            bandera=true;
        }else{
            nodoInicio=valor-1;
            ruta->goToPos(pos);
            ruta->insert(nodoInicio);
            pos++;
        }
    }
    return *ruta;
}

Floyd::~Floyd()
{
    //dtor
}
