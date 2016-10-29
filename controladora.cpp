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
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondo_Menu.jpg")));

    //Boton de inicio del Juego
    startButton= new Boton(":/Imagenes/B_INICIO.png");
    startButton->setPos(920,310);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startMenu()));
    scene->addItem(startButton);

    exitButton = new Boton(":/Imagenes/B_SALIR.png");
    exitButton->setPos(1040,310);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(exitButton);
}

void Controladora::getDireccionArchivo(){
    QString filename=QFileDialog::getOpenFileName(this,"Open File","C://","Text File(*.txt)");

    QFile documento(filename);
    if(!documento.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"Informacion",documento.errorString());
    }else{
   cout<<"URL "<<filename.toStdString()<<endl;
   QTextStream openDoc(&documento);
   cout<<"Doc "<<openDoc.readAll().toStdString()<<endl;
   documento.close();
   scene->clear();
   menuSeleccionFunciones();
    }
}

void Controladora::menuSeleccionFunciones(){
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondoMenuSeleccion.jpg")));
    exitButton = new Boton(":/Imagenes/B_SALIR.png");
    exitButton->setPos(1200,610);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(exitButton);
}

void Controladora::startMenu(){
    getDireccionArchivo();
    //menuSeleccionFunciones();
}
void Controladora::exit(){
    QCoreApplication::quit();
}
