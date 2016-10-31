#include "controladora.h"

#define nulo 0

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
    startButton->setScale(1.3);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startMenu()));
    scene->addItem(startButton);

    exitButton = new Boton(":/Imagenes/B_SALIR.png");
    exitButton->setPos(1040,310);
    exitButton->setScale(1.3);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(exitButton);
}

void Controladora::getDireccionArchivo(){

    filename=QFileDialog::getOpenFileName(this,"Open File","C://","Text File(*.txt)");

    QFile documento(filename);
    if(!documento.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"Informacion",documento.errorString());
    }else{
   cout<<"URL "<<filename.toStdString()<<endl;
   QTextStream openDoc(&documento);
   cout<<"Doc "<<openDoc.readAll().toStdString()<<endl;
   documento.close();

   menuSeleccionFunciones();
   }
}

void Controladora::menuSeleccionFunciones(){
    //Limpia la ventana y cambia el fondo
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondoMenuSeleccion.jpg")));

    //Añade el boton de salir
    exitButton = new Boton(":/Imagenes/B_SALIR.png");
    exitButton->setPos(1200,610);
    exitButton->setScale(1.3);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(exitButton);

    //Crea y establece el estilo que presentaran los RadioButton
    letrasRadio = new QFont("Helvetica",20,50,true);
    estiloRadio = new QPalette();
    estiloRadio->setColor(QPalette::WindowText,Qt::white);

    //Añade los RadioButton
    //Algoritmo de Dijkstra
    dijkstraRadio = new QRadioButton("Dijkstra",this);
    dijkstraRadio->setGeometry(490,220,600,100);//Ingresa las coordenadas y las dimensiones del radio
    dijkstraRadio->setText("Dijtaaaascf");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    dijkstraRadio->setFont(*letrasRadio);
    dijkstraRadio->setPalette(*estiloRadio);
    dijkstraRadio->show();
    connect(dijkstraRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Floyd
    floydRadio = new QRadioButton("Floyd",this);
    floydRadio->setGeometry(490,270,600,100);//Ingresa las coordenadas y las dimensiones del radio
    floydRadio->setText("FloydElGrande");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    floydRadio->setFont(*letrasRadio);
    floydRadio->setPalette(*estiloRadio);
    floydRadio->show();
    connect(floydRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Prim y Kruskal
    primYkruskalRadio = new QRadioButton("primKruskal",this);
    primYkruskalRadio->setGeometry(490,320,600,100);//Ingresa las coordenadas y las dimensiones del radio
    primYkruskalRadio->setText("PrimYKruskalLapeste");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    primYkruskalRadio->setFont(*letrasRadio);
    primYkruskalRadio->setPalette(*estiloRadio);
    primYkruskalRadio->show();
    connect(primYkruskalRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Warshall
    warshallRadio = new QRadioButton("warshall",this);
    warshallRadio->setGeometry(490,370,600,100);//Ingresa las coordenadas y las dimensiones del radio
    warshallRadio->setText("WarshallElcomplicado");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    warshallRadio->setFont(*letrasRadio);
    warshallRadio->setPalette(*estiloRadio);
    warshallRadio->show();
    connect(warshallRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Menu de nodos a seleccionar Dijkstra
    menuDijkstra = new QComboBox(this);
    menuDijkstra->setGeometry(700,260,75,25);
    menuDijkstra->setEnabled(false);
    menuDijkstra->addItem("");//0
    menuDijkstra->addItem("Cocina");//0
    menuDijkstra->addItem("Mesa 1");//1
    menuDijkstra->addItem("Mesa 2");//2
    menuDijkstra->addItem("Mesa 3");//3
    menuDijkstra->show();
    connect(menuDijkstra,SIGNAL(activated(QString)),this,SLOT(guardaNodoDijkstra()));

}

void Controladora::guardaNodoDijkstra(){
    nodoSeleccionado = menuDijkstra->currentIndex();
    if(nodoSeleccionado != nulo){
        nodoSeleccionado--;
        QMessageBox::information(this,"Informacion",menuDijkstra->currentText());
        cout<<nodoSeleccionado<<endl;
    }
}

void Controladora::checkSeleccion(){
    if(dijkstraRadio->isChecked()){
        menuDijkstra->setEnabled(true);
        QMessageBox::information(this,"Informacion","Dijkstra");
    }else{
        menuDijkstra->setEnabled(false);
    }
    if(floydRadio->isChecked()){
        QMessageBox::information(this,"Informacion","Floyd");
    }
    if(primYkruskalRadio->isChecked()){
        QMessageBox::information(this,"Informacion","Prim y Kruskal");
    }
    if(warshallRadio->isChecked()){
        QMessageBox::information(this,"Informacion","Cerradura Transitiva");
    }
}

void Controladora::startMenu(){
    getDireccionArchivo();
    //menuSeleccionFunciones();
}
void Controladora::exit(){
    QCoreApplication::quit();
}
