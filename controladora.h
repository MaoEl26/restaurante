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
#include <QMessageBox>
#include <iostream>
using namespace std;
class Controladora : public QGraphicsView
{
  Q_OBJECT
public:
    Controladora();
    void ambiente();
    void agregarBotonesJugar();
    void getDireccionArchivo();
    QGraphicsScene *scene;
    Boton *startButton;


public slots:
        /// aqui va la respuesta de los boton
        void startMenu();
};

#endif // CONTROLADORA_H
