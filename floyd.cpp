#include "Floyd.h"
#define infinito -1
#define nulo 0

Floyd::Floyd(int nodos, Matriz<ArrayList<int> *, int> *matrizPesos,QString archivo){

    this->nodos=nodos;
    this->archivo=archivo;

    matrizDn = new Matriz<ArrayList<int>*,int>(nodos);

    for(int i =0; i<nodos;i++){
        for(int j=0;j<nodos;j++){
            matrizDn->insert(i,j,matrizPesos->returnPos(i)->returnPos(j));
        }
    }

    matrizRutas = new Matriz<ArrayList<int>*,int>(nodos);
    ruta= new ArrayList<int>(nodos);

    for(int i=0;i<nodos;i++){
        matrizRutas->returnPos(i)->allEqual(0);
    }
    algoritmoFloyd();
}

void Floyd::algoritmoFloyd(){
    int valorActual;
    int valorFila;
    int valorColumna;

    archivo+="Matriz de Adyacencia D("+QString::number(0)+")\r\n";
    for(int i = 0;i<nodos;i++){
        if(i==nulo){
            archivo+="       Cocina";
        }else{
            archivo+=" Mesa "+QString::number(i);
        }
    }
    archivo+="\r\n";

    for(int i=0;i<nodos;i++){
        if(i==nulo){
            archivo+="Cocina     ";
        }else{
           archivo+="Mesa "+QString::number(i)+"     ";
        }
        for(int j=0;j<nodos;j++){
            archivo+=QString::number(matrizDn->returnPos(i)->returnPos(j))+"     ";
        }
        archivo+="\r\n";
   }
    archivo+="\r\n";

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
        archivo+="Matriz de Adyacencia D("+QString::number(k+1)+")\r\n";
        for(int i = 0;i<nodos;i++){
            if(i==nulo){
                archivo+="       Cocina";
            }else{
                archivo+=" Mesa "+QString::number(i);
            }
        }
        archivo+="\r\n";

        for(int i=0;i<nodos;i++){
            if(i==nulo){
                archivo+="Cocina     ";
            }else{
               archivo+="Mesa "+QString::number(i)+"     ";
            }
            for(int j=0;j<nodos;j++){
                archivo+=QString::number(matrizDn->returnPos(i)->returnPos(j))+"     ";
            }
            archivo+="\r\n";
       }
        archivo+="\r\n";
     }
}

Matriz<ArrayList<int> *, int> Floyd::getMatrizPesos(){
    return *matrizDn;
}

Matriz<ArrayList<int> *, int> Floyd::getMatrizRutas(){
    return *matrizRutas;
}

ArrayList<int> Floyd::getRuta(int nodoInicio, int nodoDestino){

    ruta->clear();
    pesoRuta = 0;

    ruta->allEqual(-1);

    ruta->goToPos(0);
    ruta->insert(nodoInicio);

    ruta->goToPos(1);
    ruta->insert(nodoDestino);

    bool bandera=false;
    int pos=1;

    while(!bandera){
        int valor=matrizRutas->returnPos(nodoInicio)->returnPos(nodoDestino);

        int peso=matrizDn->returnPos(nodoInicio)->returnPos(nodoDestino);
        pesoRuta+=peso;

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

QString Floyd::getArchivo(){
    return archivo;
}

int Floyd::getPesoRuta(){
    return pesoRuta;
}

Floyd::~Floyd()
{
    //dtor
}
