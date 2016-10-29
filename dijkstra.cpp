#include "Dijkstra.h"
#include <stddef.h>
#define infinito -1
#define vacio -300

Dijkstra::Dijkstra()
{
    cantidadNodos();
}

void Dijkstra::cantidadNodos(){
    cout<<"Cantidad de nodos "<<endl;
    cin>>nodos;
    //Inicializa los arreglos y matrices
    matrizPesos = new Matriz< ArrayList<int>*,int>(nodos);
    matrizPesosDijkstra = new Matriz< ArrayList<int>*,int>(nodos);
    pesosMenores= new ArrayList<int>(nodos);
    posicionMenores= new ArrayList<int>(nodos);
    nodosVisitados = new ArrayList<bool>(nodos);

    //
    for (int i=0; i< nodos; i++){
        pesosMenores->append(vacio);
        nodosVisitados->append(false);
    }
    for(int i=0;i<nodos;i++){
        for(int j=0; j<nodos;j++){
            if (j!=i){
                string conexion;
                cout<<"Los nodos v"<<i<<" y v"<<j<<" estan conectados?\nSi lo estan ingrese el peso,"<<
                "de lo contrario ingrese N "<<endl;
                cin>>conexion;
                string numero = conexion;
                conexion=toupper(conexion[0]);
                if(conexion!="N"){
                    int peso;
                    peso = atoi(numero.c_str());
                    matrizPesos->insert(i,j,peso);
                }else{
                    matrizPesos->insert(i,j,infinito);
                }
           }else{
                matrizPesos->insert(i,j,0);
          }
        }
    }

   algoritmo();
   cout<<endl;
}

void Dijkstra::algoritmo(){
    int nodoBusqueda;
    cout<<"Ingrese el nodo a buscar, apartir de 0 a "<<nodos-1<<endl;
    cin>>nodoBusqueda;
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
                        //cout<< "Columna menor: "<<columnaMenor<<"valor: "<<valorFilaActual<<endl;

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
            pesosMenores->remove(g);
            pesosMenores->goToPos(g);
            pesosMenores->insert
            (matrizPesosDijkstra->returnPos(ultimaFilaCompletada)->returnPos(g));
        }
    }

    ruta(nodoBusqueda);
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

void Dijkstra::ruta(int nodoBusqueda){
    cout <<endl<< "Rutas"<<endl;

    int nodoPosicion;
    bool encontrado;
    int pesoTotal;
    int peso;
    for (int i=0 ; i< nodos; i++ ){
        cout<< "===Ruta destino: V"<<i<<"==="<<endl;
        nodoPosicion= i;
        //cout << "V"<<posicionMenores->returnPos(nodoPosicion)<<endl;
        pesoTotal=0;
        encontrado= false;

        while(encontrado!=true){
            peso=pesosMenores->returnPos(nodoPosicion);
            pesoTotal+= peso;
            nodoPosicion= posicionMenores->returnPos(nodoPosicion);

            cout << "V"<<nodoPosicion<<"  ->peso: "<<peso<<endl ;
            if(pesosMenores->returnPos(nodoPosicion)== 0){
                encontrado= true;
            }

        }
        cout << "V"<<posicionMenores->returnPos(nodoPosicion)<<"  ->peso: 0"<<endl;
        cout<< "Peso total: "<< pesoTotal<< endl<<endl;
    }
}


Dijkstra::~Dijkstra()
{
    //dtor
}
