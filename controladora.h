#ifndef CONTROLADORA_H
#define CONTROLADORA_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QWidget>
#include <QBrush>
#include <QDebug>
#include <QImage>
#include <QMouseEvent>
#include <QPointF>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QFrame>
#include <QCoreApplication>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QComboBox>
#include <QRadioButton>
#include <QDir>
#include <QTextBrowser>

#include "boton.h"
#include "matriz.h"
#include "arraylist.h"
#include "floyd.h"
#include "prim.h"
#include "dijkstra.h"
#include "kruskal.h"

#include <iostream>
using namespace std;

class Controladora : public QGraphicsView
{
  Q_OBJECT

protected:
    QString filename;
    QString path;

    int nodoSeleccionado;
    int cantidadNodos;

    int cantidadDocs = 0;

    Matriz<ArrayList<int>*,int> *matrizAdyacencia;

public:
    Controladora();

    void ambiente();
    void agregarBotonesJugar();
    void getDireccionArchivo();
    void menuSeleccionFunciones();
    void dibujaGrafo();
    void creaDocumento(QString nombre);

    //Creacion de Documento de los algoritmos
    void algoritmoDeFloydDoc(Matriz<ArrayList<int> *, int> matrizFloyd, Matriz<ArrayList<int> *, int> matrizRutas);
    void algoritmoDeWarshallDoc();

    QGraphicsScene *scene;

    QFont *letrasRadio;
    QPalette *estiloRadio;

    Boton *startButton;
    Boton *exitButton;

    QRadioButton *dijkstraRadio;
    QRadioButton *floydRadio;
    QRadioButton *primYkruskalRadio;
    QRadioButton *warshallRadio;

    QComboBox *menuDijkstra;

    QTextBrowser *areaTexto;

    QString archivo;

    Floyd *floyd;


public slots:
        /// aqui va la respuesta de los boton
        void startMenu();
        void exit();
        void checkSeleccion();
        void guardaNodoDijkstra();
};

#endif // CONTROLADORA_H
