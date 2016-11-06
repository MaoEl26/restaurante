#include "controladora.h"

#define nulo 0
#define filasMatriz 5
#include <QTime>
#include<QApplication>


Controladora::Controladora()
{
    ambiente();
    agregarBotonesJugar();
    show();
}
void delay()
{
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
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
    inicioBoton= new Boton(":/Imagenes/B_INICIO.png");
    inicioBoton->setPos(920,310);
    inicioBoton->setScale(1.3);
    connect(inicioBoton, SIGNAL(clicked()), this, SLOT(startMenu()));
    scene->addItem(inicioBoton);

    salirBoton = new Boton(":/Imagenes/B_SALIR.png");
    salirBoton->setPos(1040,310);
    salirBoton->setScale(1.3);
    connect(salirBoton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(salirBoton);
}

void Controladora::getDireccionArchivo(){

    cantidadNodos = nulo;

    filename=QFileDialog::getOpenFileName(this,"Open File","C://","Text File(*.txt)");

    QFile documento(filename);
    if(!documento.open(QIODevice::ReadOnly)){
        QMessageBox::information(this,"Informacion",documento.errorString());
    }else{
       while(!documento.atEnd()){

           documento.readLine();
           cantidadNodos++;

       }
       documento.close();

       matrizAdyacencia = new Matriz<ArrayList<int>*,int>(cantidadNodos);

       QFile documento(filename);
       documento.open(QIODevice::ReadOnly);

       while(!documento.atEnd()){
           for(int i=0; i<cantidadNodos;i++){
               QString linea = documento.readLine();
               QStringList lineaSeparada = linea.split(",");

               for(int j=0;j<cantidadNodos;j++){
                   QString valorConCambioLinea =lineaSeparada[j];
                   QString valorFinal = valorConCambioLinea.split("\r\n",QString::SkipEmptyParts)[0];

                   matrizAdyacencia->insert(i,j,valorFinal.toInt());
               }
           }
       }

       documento.close();

       QStringList url = filename.split("/");
       QString user =url[2];
       path = "C:/Users/"+user+"/Desktop/";

       for(int i=0;i<cantidadNodos;i++){
           for(int j=0;j<cantidadNodos;j++){
               cout<<matrizAdyacencia->returnPos(i)->returnPos(j)<<" ";
           }
           cout<<endl;
       }

       menuSeleccionFunciones();
       }
}

void Controladora::menuSeleccionFunciones(){
    //Limpia la ventana y cambia el fondo
    scene->clear();
    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondoMenuSeleccion.jpg")));
    archivo = "";

    //Añade el boton de salir
    salirBoton = new Boton(":/Imagenes/B_SALIR.png");
    salirBoton->setPos(1200,610);
    salirBoton->setScale(1.3);
    connect(salirBoton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(salirBoton);

    //Crea y establece el estilo que presentaran los RadioButton
    letrasRadio = new QFont("Helvetica",20,50,true);
    estiloRadio = new QPalette();
    estiloRadio->setColor(QPalette::WindowText,Qt::white);

    //Añade los RadioButton
    //Algoritmo de Dijkstra
    dijkstraRadio = new QRadioButton("Dijkstra",this);
    dijkstraRadio->setGeometry(490,220,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    dijkstraRadio->setFont(*letrasRadio);
    dijkstraRadio->setPalette(*estiloRadio);

    dijkstraRadio->show();
    connect(dijkstraRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Floyd
    floydRadio = new QRadioButton("Floyd",this);
    floydRadio->setGeometry(490,270,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    floydRadio->setFont(*letrasRadio);
    floydRadio->setPalette(*estiloRadio);
    floydRadio->show();
    connect(floydRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Prim y Kruskal
    primRadio = new QRadioButton("Prim",this);
    primRadio->setGeometry(490,320,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    primRadio->setFont(*letrasRadio);
    primRadio->setPalette(*estiloRadio);
    primRadio->show();
    connect(primRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Prim y Kruskal
    kruskalRadio = new QRadioButton("Kruskal",this);
    kruskalRadio->setGeometry(490,320,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    kruskalRadio->setFont(*letrasRadio);
    kruskalRadio->setPalette(*estiloRadio);
    kruskalRadio->show();
    connect(kruskalRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Warshall
    warshallRadio = new QRadioButton("Warshall",this);
    warshallRadio->setGeometry(490,370,600,100);//Ingresa las coordenadas y las dimensiones del radio
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

    for(int i =0;i<cantidadNodos;i++){
        if(i==nulo){
            menuDijkstra->addItem("Cocina");
        }else{
            menuDijkstra->addItem("Mesa "+QString::number(i));
        }
    }
    menuDijkstra->show();

    connect(menuDijkstra,SIGNAL(activated(QString)),this,SLOT(guardaNodoDijkstra()));

}

void Controladora::guardaNodoDijkstra(){
    nodoSeleccionado = menuDijkstra->currentIndex();
    if(nodoSeleccionado != nulo){
        nodoSeleccionado--;


        nombreArchivo= dijkstraRadio->text();
        dibujaGrafo();

        //QMessageBox::information(this,"Informacion",menuDijkstra->currentText());
        cout<<nodoSeleccionado<<endl;

    }
}

void Controladora::checkSeleccion(){
    if(dijkstraRadio->isChecked()){
        menuDijkstra->setEnabled(true);
    }else{
        menuDijkstra->setEnabled(false);
    }
    if(floydRadio->isChecked()){
        floyd = new Floyd(cantidadNodos,matrizAdyacencia);

        Matriz<ArrayList<int>*,int> matrizFloyd = floyd->algoritmoFloyd();
        Matriz<ArrayList<int>*,int> matrizRutas = floyd->getMatrizRutas();
        algoritmoDeFloydDoc(matrizFloyd,matrizRutas);
        nombreArchivo= floydRadio->text();
        dibujaGrafo();
    }
    if(primRadio->isChecked()){
        nombreArchivo= primRadio->text();
        dibujaGrafo();
        Kruskal(matrizAdyacencia,cantidadNodos);
    }
    if (kruskalRadio->isChecked()){
        nombreArchivo= kruskalRadio->text();
        dibujaGrafo();
    }
    if(warshallRadio->isChecked()){

        nombreArchivo= warshallRadio->text();
        dibujaGrafo();
    }
}

void Controladora::dibujaGrafo(){
    scene->clear();

    dijkstraRadio->deleteLater();
    floydRadio->deleteLater();
    primRadio->deleteLater();
    kruskalRadio->deleteLater();
    warshallRadio->deleteLater();
    menuDijkstra->deleteLater();

    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondo cuadros.png")));

    areaTexto = new QTextEdit();
    areaTexto->setText(archivo);
    areaTexto->setWindowTitle(nombreArchivo);
    areaTexto->setReadOnly(true);
    areaTexto->show();

    generaDocumento = new Boton(":/Imagenes/B_GUARDAR.png");
    generaDocumento->setPos(0,560);
    generaDocumento->setScale(1.3);
    connect(generaDocumento,SIGNAL(clicked()),this,SLOT(generadorDocumento()));
    scene->addItem(generaDocumento);

    atrasBoton = new Boton(":/Imagenes/B_ATRAS.png");
    atrasBoton->setPos(0,610);
    atrasBoton->setScale(1.3);
    connect(atrasBoton,SIGNAL(clicked()),this,SLOT(retroceder()));
    scene->addItem(atrasBoton);

    cantidadMesas = 0;


    arrayCoordenasX = new ArrayList<int>(cantidadNodos);
    arrayCoordenasY = new ArrayList<int>(cantidadNodos);
    agregaNodos();
}

void Controladora::agregaNodos(){

    for(int i=0;i<filasMatriz;i++){
        arrayCoordenasX->allEqual(-1);
        arrayCoordenasY->allEqual(-1);
    }

    int coorXCocina = 1;
    int coorYCocina = 200;

    QImage mesa(":/Imagenes/cocina.png");
    QGraphicsPixmapItem *itemMesa= new QGraphicsPixmapItem( QPixmap::fromImage(mesa));
    itemMesa->setPos(coorXCocina,coorYCocina);
    itemMesa->setScale(0.7);
    scene->addItem(itemMesa);

    int coorX = 172;

    while(cantidadMesas<cantidadNodos)
    {
        int coorY = 58;
        for(int j=0;j<5;j++){

            if(cantidadMesas==0&&j==0){
                arrayCoordenasX->setValue(cantidadMesas,coorXCocina);
                arrayCoordenasY->setValue(cantidadMesas,coorYCocina);
                coorY+=113;
            }else{
                arrayCoordenasX->setValue(cantidadMesas,coorX);
                arrayCoordenasY->setValue(cantidadMesas,coorY);
                QImage mesa(":/Imagenes/mesa.png");
                QGraphicsPixmapItem *itemMesa= new QGraphicsPixmapItem( QPixmap::fromImage(mesa));
                itemMesa->setPos(coorX,coorY);
                itemMesa->setScale(0.7);
                scene->addItem(itemMesa);
                coorY+=113;
            }
            cantidadMesas++;
            if(cantidadMesas==cantidadNodos){
                break;
            }
            delay();
        }
        coorX+=113;
    }

    for(int i = 0;i<cantidadNodos;i++){
        cout<<"x"<<arrayCoordenasX->returnPos(i)<<" ";
        cout<<"y"<<arrayCoordenasY->returnPos(i)<<" ";
    }
}

void Controladora::retroceder(){
    menuSeleccionFunciones();
}

void Controladora::startMenu(){
    getDireccionArchivo();
}

void Controladora::exit(){
    QCoreApplication::quit();
}

void Controladora::algoritmoDeFloydDoc
(Matriz<ArrayList<int> *, int> matrizFloyd, Matriz<ArrayList<int> *, int> matrizRutas){

    archivo+="Matriz de Adyacencia \r\n";
    for(int i = 0;i<cantidadNodos;i++){
        if(i==nulo){
            archivo+="       Cocina";
        }else{
            archivo+=" Mesa "+QString::number(i);
        }
    }
    archivo+="\r\n";

    for(int i=0;i<cantidadNodos;i++){
        if(i==nulo){
            archivo+="Cocina     ";
        }else{
           archivo+="Mesa "+QString::number(i)+"     ";
        }
        for(int j=0;j<cantidadNodos;j++){
            archivo+=QString::number(matrizFloyd.returnPos(i)->returnPos(j))+"     ";
        }
        archivo+="\r\n";
   }
    archivo+="\r\n Matriz de Rutas \r\n";

    for(int i = 0;i<cantidadNodos;i++){
        if(i==nulo){
            archivo+="       Cocina";
        }else{
            archivo+=" Mesa "+QString::number(i);
        }
    }
    archivo+="\r\n";

    for(int i=0;i<cantidadNodos;i++){

        if(i==nulo){
            archivo+="Cocina     ";
        }else{
            archivo+="Mesa "+QString::number(i)+"     ";
        }

        for(int j=0;j<cantidadNodos;j++){
            archivo+=QString::number(matrizRutas.returnPos(i)->returnPos(j))+"     ";
        }
        archivo+="\r\n";
   }
    return;
}

void Controladora::algoritmoDocumentos(){

}

void Controladora::creaDocumento(){
    bool flag = true;
    QString doc = path+nombreArchivo+".txt";

    while(flag){
        QFile documento(doc);
        if(!documento.exists()){
            documento.open(QIODevice::ReadWrite);

            QTextStream entrada(&documento);
            entrada<<archivo;
            cantidadDocs=0;
            flag=false;
            documento.close();
        }else{
                cantidadDocs++;
                doc = path+nombreArchivo+" "+QString::number(cantidadDocs)+".txt";
        }
    }
}

void Controladora::generadorDocumento(){
    creaDocumento();
}
