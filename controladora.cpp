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

    filename=QFileDialog::getOpenFileName(this,"Open File","C://","Text File(*.txt)");

    QFile documento(filename);
    if(!documento.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"Informacion",documento.errorString());
    }else{
   cout<<"URL "<<filename.toStdString()<<endl;
   QTextStream openDoc(&documento);
   cout<<"Doc "<<openDoc.readAll().toStdString()<<endl;
   documento.close();
   //separaDoc();
   scene->clear();
   menuSeleccionFunciones();
   }
}

//void Controladora::separaDoc(){
//    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
//    db.setDatabaseName("DRIVER={Microsoft Excel Driver(*.xls)};DBQ=" + filename);

//    if(db.open()){
//        QSqlQuery query("select * from[Sheet1" + QString("$]"));
//        while (query.next())
//        {
//        QString column1= query.value(0).toString();
//        qDebug() << column1;
//        }
//    }else{
//        QMessageBox::information(this,"Informacion","NO EXISTE");
//    }

//}

void Controladora::menuSeleccionFunciones(){
    //Limpia la ventana y cambia el fondo
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondoMenuSeleccion.jpg")));
    //Añade el boton de salir
    exitButton = new Boton(":/Imagenes/B_SALIR.png");
    exitButton->setPos(1200,610);
    connect(exitButton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(exitButton);

    //Crea y establece el estilo que presentaran los RadioButton
    letrasRadio = new QFont("Helvetica",20,50,true);
    estiloRadio = new QPalette();
    estiloRadio->setColor(QPalette::WindowText,Qt::white);

    //Añade los RadioButton
    dijkstraRadio = new QRadioButton("Dijkstra",this);
    dijkstraRadio->setGeometry(490,220,600,100);//Ingresa las coordenadas y las dimensiones del radio
    dijkstraRadio->setText("Dijtaaaascf");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    dijkstraRadio->setFont(*letrasRadio);
    dijkstraRadio->setPalette(*estiloRadio);
    dijkstraRadio->show();

    floydRadio = new QRadioButton("Floyd",this);
    floydRadio->setGeometry(490,270,600,100);//Ingresa las coordenadas y las dimensiones del radio
    floydRadio->setText("FloydElGrande");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    floydRadio->setFont(*letrasRadio);
    floydRadio->setPalette(*estiloRadio);
    floydRadio->show();

    primYkruskalRadio = new QRadioButton("primKruskal",this);
    primYkruskalRadio->setGeometry(490,320,600,100);//Ingresa las coordenadas y las dimensiones del radio
    primYkruskalRadio->setText("PrimYKruskalLapeste");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    primYkruskalRadio->setFont(*letrasRadio);
    primYkruskalRadio->setPalette(*estiloRadio);
    primYkruskalRadio->show();

    warshallRadio = new QRadioButton("warshall",this);
    warshallRadio->setGeometry(490,370,600,100);//Ingresa las coordenadas y las dimensiones del radio
    warshallRadio->setText("WarshallElcomplicado");//Cambia el texto que se muestra en pantalla
    //Establece los estilos y lo muestra en pantalla
    warshallRadio->setFont(*letrasRadio);
    warshallRadio->setPalette(*estiloRadio);
    warshallRadio->show();

    menuDijkstra = new QComboBox(this);
    menuDijkstra->setGeometry(660,260,70,25);
    menuDijkstra->show();

}

void Controladora::startMenu(){
    getDireccionArchivo();
    //menuSeleccionFunciones();
}
void Controladora::exit(){
    QCoreApplication::quit();
}
