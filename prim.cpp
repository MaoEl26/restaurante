#include "Prim.h"
#define infinito -1
#define vacio -300

Prim::Prim()
{
    cantidadNodos();
}

void Prim::cantidadNodos(){
    cout<<"Cantidad de nodos "<<endl;
    cin>>nodos;

    //Inicializa los arreglos y matrices
    matrizPesos = new Matriz< ArrayList<int>*,int>(nodos);
    matrizValoresUsados = new Matriz< ArrayList<bool>*,bool>(nodos);
    nodosVisitados = new ArrayList<bool>(nodos);
    nodosInicial = new ArrayList<int>(nodos);
    nodosDestinos = new ArrayList<int>(nodos);
    cantidadNodosVisitados=1;

    //Pone todos los elementos de la matriz en 0 y false
    for(int i=0; i<nodos;i++){
        matrizPesos->returnPos(i)->allEqual(0);
        matrizValoresUsados->returnPos(i)->allEqual(false);
    }
    pesoMayor=0;
    nodosVisitados->allEqual(false);
    nodosVisitados->setValue(0,true);

    //Pide pesos del grafo al usuario
    for(int i=0;i<nodos;i++){
        for(int j=0; j<nodos;j++){
            if (j!=i){
                if((matrizPesos->returnPos(i)->returnPos(j))== 0){
                string conexion;
                cout<<"Los nodos v"<<i<<" y v"<<j<<" estan conectados?\nSi lo estan ingrese el peso,"<<
                "de lo contrario ingrese N "<<endl;
                cin>>conexion;
                string numero = conexion;
                conexion=toupper(conexion[0]);
                if(conexion!="N"){
                    int peso;
                    peso = atoi(numero.c_str());
                    matrizPesos->returnPos(i)->setValue(j,peso);
                    matrizPesos->returnPos(j)->setValue(i,peso);
                    if(peso> pesoMayor){
                        pesoMayor=peso;
                    }

                }else{
                    matrizPesos->returnPos(i)->setValue(j,infinito);
                    matrizPesos->returnPos(j)->setValue(i,infinito);
                }
            }
           }else{
               matrizPesos->returnPos(i)->setValue(j,0);
               matrizValoresUsados->returnPos(i)->setValue(j,true);
          }
        }
    }

    for(int i=0 ;i<nodos; i++){
            for(int j=0; j<nodos;j++){
                cout<<matrizPesos->returnPos(i)->returnPos(j)<<" ";
            }
       cout<<endl;
    }
    algoritmo();
}

void Prim::algoritmo(){

    while(cantidadNodosVisitados!= nodos){
        busquedaNodoMenor();
        matrizValoresUsados->returnPos(filaMenor)->setValue(columnaMenor,true);
        matrizValoresUsados->returnPos(columnaMenor)->setValue(filaMenor,true);
        nodosVisitados->setValue(columnaMenor,true);
        cout<<"V"<<filaMenor<<"---> V"<<columnaMenor<< " Valor: "<<
        matrizPesos->returnPos(filaMenor)->returnPos(columnaMenor)<<endl;
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
Prim::~Prim()
{
    //dtor
}
