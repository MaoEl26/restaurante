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
#include <QTextBrowser>
#include <QTextEdit>


#include <time.h>
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
    QString nombreArchivo;
    QString archivo;

    int nodoSeleccionado;
    int cantidadNodos;
    int cantidadMesas;
    QTimer *timer;

    int cantidadDocs = 0;

    Matriz<ArrayList<int>*,int> *matrizAdyacencia;
    Matriz<ArrayList<int>*,int> *matrizUbicaciones;

    ArrayList<int> *arrayCoordenasX;
    ArrayList<int> *arrayCoordenasY;

public:
    Controladora();

    void ambiente();
    void agregarBotonesJugar();
    void getDireccionArchivo();
    void menuSeleccionFunciones();
    void dibujaGrafo();
    void agregaNodos();
    void creaDocumento();
    void dibujaLinea(int nodoInicio,int nodoDestino);
    void deleteEtiquetas();
    void controlDibujo(ArrayList<int> nodosInicio, ArrayList<int> nodosDestino);
    void controlDibujo(ArrayList<int> *nodos);
    //delay();

    int buscaNodo(int nodo,bool llave);

    //Creacion de Documento de los algoritmos
    void algoritmoDeFloydDoc(Matriz<ArrayList<int> *, int> matrizFloyd, Matriz<ArrayList<int> *, int> matrizRutas);
    void algoritmoDocumentos();

    QGraphicsScene *scene;
    QGraphicsLineItem *line;

    QFont *letrasRadio;
    QPalette *estiloRadio;
    QPen *pen;

    QLabel *mesas;

    Boton *inicioBoton;
    Boton *salirBoton;
    Boton *atrasBoton;
    Boton *generaDocumento;

    QRadioButton *dijkstraRadio;
    QRadioButton *floydRadio;
    QRadioButton *primRadio;
    QRadioButton *kruskalRadio;
    QRadioButton *warshallRadio;


    QComboBox *menuDijkstra;

    QTextEdit *areaTexto;

    Floyd *floyd;


public slots:
        /// aqui va la respuesta de los boton
        void startMenu();
        void exit();
        void checkSeleccion();
        void guardaNodoDijkstra();
        void retroceder();
        void generadorDocumento();

};

#endif // CONTROLADORA_H
