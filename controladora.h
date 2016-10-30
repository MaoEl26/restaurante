#ifndef CONTROLADORA_H
#define CONTROLADORA_H
#include "boton.h"
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
//#include <QtSql/QSqlDatabase>

#include <iostream>
using namespace std;

class Controladora : public QGraphicsView
{
  Q_OBJECT

protected:
    QString filename;

public:
    Controladora();

    void ambiente();
    void agregarBotonesJugar();
    void getDireccionArchivo();
    void menuSeleccionFunciones();
//    void separaDoc();

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


public slots:
        /// aqui va la respuesta de los boton
        void startMenu();
        void exit();
};

#endif // CONTROLADORA_H
