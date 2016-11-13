#ifndef FLOYD_H
#define FLOYD_H

#include "Matriz.h"

#include <QString>

#include <iostream>
#include <stdlib.h>

using namespace std;

class Floyd
{
    public:
        Floyd(int nodos, Matriz<ArrayList<int> *, int> *matrizPesos, QString archivo);
        void algoritmoFloyd();
        Matriz<ArrayList<int> *, int> getMatrizRutas();
        Matriz<ArrayList<int> *, int> getMatrizPesos();
        ArrayList<int> getRuta(int nodoInicio,int nodoDestino);
        int getPesoRuta();
        QString getArchivo();
        virtual ~Floyd();

    protected:

        Matriz< ArrayList<int>*,int> *matrizRutas;
        Matriz< ArrayList<int>*,int> *matrizDn;
        ArrayList<int> *ruta;

        int pesoRuta;
        int nodos;
        int nodoInicio;
        int nodoDestino;

        QString archivo;
    private:
};

#endif // FLOYD_H
