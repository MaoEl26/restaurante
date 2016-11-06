#include "Dijkstra.h"
#include <stddef.h>
#define infinito -1
#define vacio -300

Dijkstra::Dijkstra(int nodos, int nodoBusqueda,int nodoDestino, Matriz<ArrayList<int> *, int> *matrizPesos)
{
    this->matrizPesos= matrizPesos; //Matriz de pesos original
    this->nodos= nodos; //Cantidad de nodos
    this->nodoBusqueda = nodoBusqueda; //Nodo inicial con el cual se va realizar la matriz de dijsktra
    this->nodoDestino= nodoDestino;
    matrizPesosDijkstra = new Matriz< ArrayList<int>*,int>(nodos); //Guardara los valores de la matriz de dijkstra
    pesosMenores= new ArrayList<int>(nodos); //Guardara los pesos de los nodos menores q se representan con un cuadro en la matriz
    posicionMenores= new ArrayList<int>(nodos);//Guardara los nodos menores q se representan con un cuadro en la matriz
    nodosVisitados = new ArrayList<bool>(nodos);  //Identificara si la columna ya tiene su nodo menor
    rutaNodo = new ArrayList<int>(nodos);
    cantidadNodos();
}

void Dijkstra::cantidadNodos(){

    for (int i=0; i< nodos; i++){
        pesosMenores->append(vacio);
        nodosVisitados->append(false);
    }
    algoritmo();

}

void Dijkstra::algoritmo(){

    pesosMenores->remove(nodoBusqueda);
    pesosMenores->goToPos(nodoBusqueda);
    pesosMenores->insert(0);
    //Marca el numero menor
    nodosVisitados->goToPos(nodoBusqueda);
    nodosVisitados->remove(nodoBusqueda);
    nodosVisitados->insert(true);
    //Pone las posiciones
    for (int i=0; i< nodos; i++){
        posicionMenores->append(nodoBusqueda);
    }
    //Completa la primera fila de la matriz Dijkstra
    for(int i=0;i<nodos;i++){
        matrizPesosDijkstra->insert(0,i,
                                matrizPesos->returnPos(nodoBusqueda)->returnPos(i));
    }

    ultimaFilaCompletada=0;

    //Inserta el peso del valor menor
    int columnaMenor = busquedaNodoMenor(nodoBusqueda);
    int valorFilaAnterior;
    int valorFilaActual;

    for(int i=1;i<nodos-1;i++){
        //Baja el numero menor
        matrizPesosDijkstra->insert(i,columnaMenor,
                                    matrizPesosDijkstra->returnPos(i-1)->returnPos(columnaMenor));
        //Marco la posicion menor
        nodosVisitados->goToPos(columnaMenor);
        nodosVisitados->remove(columnaMenor);
        nodosVisitados->insert(true);

        //Inserta en el peso menor de la columna
        pesosMenores->remove(columnaMenor);
        pesosMenores->goToPos(columnaMenor);
        pesosMenores->insert(matrizPesosDijkstra->returnPos(i-1)->returnPos(columnaMenor));

        for(int j=0;j<nodos;j++){
             if (nodosVisitados->returnPos(j)!=true){
                valorFilaAnterior = matrizPesosDijkstra->returnPos(i-1)->returnPos(j);
                valorFilaActual = matrizPesos->returnPos(columnaMenor)->returnPos(j);
                if (valorFilaActual ==infinito){
                    if (valorFilaActual==0){
                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaAnterior);
                    }
                    else if(valorFilaAnterior > 0){
                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaAnterior);
                    }
                    else if(valorFilaAnterior==infinito){
                        matrizPesosDijkstra->insert(i,j,
                                   valorFilaAnterior);
                    }
                }
                if (valorFilaActual !=infinito){
                    if(valorFilaActual ==0){
                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaAnterior);
                    }
                    else if(valorFilaAnterior== infinito){

                        posicionMenores->goToPos(j);
                        posicionMenores->remove(j);
                        posicionMenores->insert(columnaMenor);
                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaActual);
                    }
                    else if(valorFilaActual< valorFilaAnterior){

                        posicionMenores->goToPos(j);
                        posicionMenores->remove(j);
                        posicionMenores->insert(columnaMenor);

                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaActual);
                    }
                    else if(valorFilaActual> valorFilaAnterior ){
                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaAnterior);
                    }
                    else if(valorFilaActual == valorFilaAnterior){
                        matrizPesosDijkstra->insert(i,j,
                                    valorFilaAnterior);
                    }
                }
            }
        }
        ultimaFilaCompletada++;
        columnaMenor=busquedaNodoMenor(columnaMenor);
    }

    for(int g =0 ; g<nodos;g++){
        if(pesosMenores->returnPos(g)== vacio){

            nodoMayorDistancia=nodoDestino;
            pesosMenores->remove(g);
            pesosMenores->goToPos(g);
            pesosMenores->insert
            (matrizPesosDijkstra->returnPos(ultimaFilaCompletada)->returnPos(g));
        }
    }

    ruta();
}

int Dijkstra::busquedaNodoMenor(int fila){
        int columna;
        int contador =0;
        int valorInicial;
        int valorPosicionActual;

        while (contador<nodos){
            if (nodosVisitados->returnPos(contador)!=true){
                valorInicial = matrizPesosDijkstra->returnPos(ultimaFilaCompletada)->returnPos(contador);
                columna=contador;
                break;
            }
            contador+=1;
        }

        for(int i=0;i < nodos;i++){

            if(nodosVisitados->returnPos(i)!=true){
                valorPosicionActual = matrizPesosDijkstra->returnPos(ultimaFilaCompletada)->returnPos(i);

                if(valorPosicionActual == infinito){
                    if(matrizPesos->returnPos(fila)->returnPos(i) > 0){
                        valorInicial= matrizPesos->returnPos(fila)->returnPos(i);
                        columna= i;
                    }
                }
                else if(valorPosicionActual!= infinito){
                    if(valorInicial== infinito){
                        valorInicial= valorPosicionActual;
                        columna= i;
                    }
                    else if(valorPosicionActual< valorInicial){
                        valorInicial=valorPosicionActual;
                        columna= i;
                    }
                }
            }
        }
        return columna;
}

void Dijkstra::ruta(){
    int nodoPosicion= nodoMayorDistancia;
    bool encontrado= false;
    int pesoTotal=0;
    int peso;
    int columna= 0;
    rutaNodo->insert(nodoDestino);
    while(encontrado!=true){
        peso=pesosMenores->returnPos(nodoPosicion);
        pesoTotal+= peso;
        nodoPosicion= posicionMenores->returnPos(nodoPosicion);
        rutaNodo->insert(nodoPosicion);

        columna++;
        if(pesosMenores->returnPos(nodoPosicion)== 0){
            encontrado= true;
        }
    }

    for(int i =0; i<nodos; i++){
        if(i>=columna){
            rutaNodo->append(infinito);
        }
    }
}

ArrayList<int> Dijkstra::getRutaNodo(){
    return *rutaNodo;
}

Dijkstra::~Dijkstra()
{
    //dtor
}
