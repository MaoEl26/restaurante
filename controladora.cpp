#include "controladora.h"

Controladora::Controladora()
{
    ambiente();
    agregarBotonesJugar();
    show();
}

void Controladora::ambiente(){
    //Crea la ventana donde se crearan los elementos
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 1300, 660);
    setScene(scene);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1305,655);
}
void Controladora::agregarBotonesJugar(){

    //Limpia la escena y establece un nuevo fondo
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondo cuadros.png")));

    //Boton de inicio del Juego
    startButton= new Boton(":/Imagenes/startButton.png");
    startButton->setPos(130,130);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startMenu()));
    scene->addItem(startButton);
}

void Controladora::getDireccionArchivo(){
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"C://","Text File(*.XML)");
    QMessageBox::information(this,tr("File Name"),filename);
}

void Controladora::startMenu(){
    getDireccionArchivo();
    //QCoreApplication::quit();
}
