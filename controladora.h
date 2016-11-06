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
#include "warshall.h"

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

    int nodoInicioSeleccionado;
    int nodoDestinoSeleccionado;

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
    void controlDibujo(ArrayList<int> nodos);
    //delay();

    int buscaNodo(int nodo,bool llave);

    //Creacion de Documento de los algoritmos
    void algoritmoDocumentos(Matriz<ArrayList<int> *, int> matrizFloyd, Matriz<ArrayList<int> *, int> matrizRutas);
    void algoritmoDocumentos(ArrayList<int> nodosRutas);
    void algoritmoDocumentos(ArrayList<int> nodosInicio,ArrayList<int> nodosDestino);
    void algoritmoDocumentos(Matriz<ArrayList<int> *, int> matriz);

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


    QComboBox *menuInicioDijkstra;
    QComboBox *menuDestinoDijkstra;

    QTextEdit *areaTexto;

    Floyd *floyd;
    Dijkstra *dijkstra;


public slots:
        /// aqui va la respuesta de los boton
        void startMenu();
        void exit();
        void checkSeleccion();
        void guardaNodoInicioDijkstra();
        void guardaNodoDestinoDijkstra();
        void retroceder();
        void retrocederMenuPrincipal();
        void generadorDocumento();

};

#endif // CONTROLADORA_H
