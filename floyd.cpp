#include "Floyd.h"
#define infinito -1

Floyd::Floyd(){creaMatriz();}

void Floyd::creaMatriz(){

    cout<<"Cantidad de nodos "<<endl;
    cin>>nodos;
    matrizD0 = new Matriz< ArrayList<int>*,int>(nodos);
    matrizDn = new Matriz< ArrayList<int>*,int>(nodos);

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
                    matrizD0->insert(i,j,peso);
                    matrizDn->insert(i,j,peso);
                }else{
                    matrizD0->insert(i,j,infinito);
                    matrizDn->insert(i,j,infinito);
                }
           }else{
                matrizD0->insert(i,j,0);
                matrizDn->insert(i,j,0);
          }
        }
    }
    algoritmoFloyd();
}

void Floyd::algoritmoFloyd(){
    int valorActual;
    int valorFila;
    int valorColumna;
     cout<<" Matriz Incial "<<endl;
     print(matrizD0);

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
        cout<<" Matriz Optima D("<<k+1<<")"<<endl;
        print(matrizDn);
     }
}

void Floyd::print(Matriz< ArrayList<int>*,int> *matriz){
    cout<<"  ";
    for(int i=0;i<nodos;i++){
        cout<<"v"<<i<<" ";
    }
    cout<<endl;
    for(int i=0;i<nodos;i++){
            cout<<"v"<<i<<" ";
        for(int j=0;j<nodos;j++){
            int valor = matriz->returnPos(i)->returnPos(j);
            cout<<valor<<" ";
        }
        cout<<endl;
    }
    return;
}

Floyd::~Floyd()
{
    //dtor
}
