#include "controladora.h"
#include <QTime>
#include <QApplication>

#define nulo 0
#define filasMatriz 5
#define columnasMatriz 10


Controladora::Controladora()
{
    ambiente();
    agregarBotonesJugar();
    show();
}
void delay(){
    QTime dieTime= QTime::currentTime().addSecs(4);
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

    atrasBoton = new Boton(":/Imagenes/B_ATRAS.png");
    atrasBoton->setPos(0,610);
    atrasBoton->setScale(1.3);
    connect(atrasBoton,SIGNAL(clicked()),this,SLOT(retrocederMenuPrincipal()));
    scene->addItem(atrasBoton);

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

    //Algoritmo de Prim
    primRadio = new QRadioButton("Prim",this);
    primRadio->setGeometry(490,320,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    primRadio->setFont(*letrasRadio);
    primRadio->setPalette(*estiloRadio);
    primRadio->show();
    connect(primRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Kruskal
    kruskalRadio = new QRadioButton("Kruskal",this);
    kruskalRadio->setGeometry(490,370,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    kruskalRadio->setFont(*letrasRadio);
    kruskalRadio->setPalette(*estiloRadio);
    kruskalRadio->show();
    connect(kruskalRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Algoritmo de Warshall
    warshallRadio = new QRadioButton("Warshall",this);
    warshallRadio->setGeometry(490,420,600,100);//Ingresa las coordenadas y las dimensiones del radio
    //Establece los estilos y lo muestra en pantalla
    warshallRadio->setFont(*letrasRadio);
    warshallRadio->setPalette(*estiloRadio);
    warshallRadio->show();
    connect(warshallRadio,SIGNAL(clicked(bool)),this,SLOT(checkSeleccion()));

    //Menu de nodos a seleccionar Dijkstra
    menuInicioDijkstra = new QComboBox(this);
    menuInicioDijkstra->setGeometry(700,240,75,25);
    menuInicioDijkstra->setEnabled(false);
    menuInicioDijkstra->addItem("");//0

    menuDestinoDijkstra = new QComboBox(this);
    menuDestinoDijkstra->setGeometry(700,270,75,25);
    menuDestinoDijkstra->setEnabled(false);
    menuDestinoDijkstra->addItem("");//0

    for(int i =0;i<cantidadNodos;i++){
        if(i==nulo){
            menuDestinoDijkstra->addItem("Cocina");
            menuInicioDijkstra->addItem("Cocina");
        }else{
            menuInicioDijkstra->addItem("Mesa "+QString::number(i));
            menuDestinoDijkstra->addItem("Mesa "+QString::number(i));
        }
    }
    menuInicioDijkstra->show();
    menuDestinoDijkstra->show();

    connect(menuInicioDijkstra,SIGNAL(activated(QString)),this,SLOT(guardaNodoInicioDijkstra()));
    connect(menuDestinoDijkstra,SIGNAL(activated(QString)),this,SLOT(guardaNodoDestinoDijkstra()));

}

void Controladora::guardaNodoInicioDijkstra(){

    nodoInicioSeleccionado = menuInicioDijkstra->currentIndex();

    if(nodoInicioSeleccionado != nulo){

        nodoInicioSeleccionado--;

        menuDestinoDijkstra->setEnabled(true);     
    }
}

void Controladora::guardaNodoDestinoDijkstra(){

    nodoDestinoSeleccionado = menuDestinoDijkstra->currentIndex();

    if(nodoDestinoSeleccionado != nulo){

        nombreArchivo= dijkstraRadio->text();

        nodoDestinoSeleccionado--;

        Dijkstra *dijkstra = new Dijkstra
                (cantidadNodos,nodoInicioSeleccionado,nodoDestinoSeleccionado,matrizAdyacencia);

        ArrayList<int> ruta = dijkstra->getRutaNodo();

        algoritmoDocumentos(ruta);

        dibujaGrafo();

        controlDibujo(ruta);
    }
}

void Controladora::checkSeleccion(){
    if(dijkstraRadio->isChecked()){

        menuInicioDijkstra->setEnabled(true);

    }else{

        menuInicioDijkstra->setEnabled(false);

        menuDestinoDijkstra->setEnabled(false);
    }
    if(floydRadio->isChecked()){

        nombreArchivo= floydRadio->text();

        Floyd *floyd = new Floyd(cantidadNodos,matrizAdyacencia);

        Matriz<ArrayList<int>*,int> matrizFloyd = floyd->algoritmoFloyd();

        Matriz<ArrayList<int>*,int> matrizRutas = floyd->getMatrizRutas();

        algoritmoDocumentos(matrizFloyd,matrizRutas);

        dibujaGrafo();
    }
    if(primRadio->isChecked()){

        nombreArchivo= primRadio->text();

        Prim *alPrim = new Prim(cantidadNodos,matrizAdyacencia);

        ArrayList<int> nodosInicio = alPrim->getRutaInicial();

        ArrayList<int> nodosDestino =alPrim->getRutaDestino();

        algoritmoDocumentos(nodosInicio,nodosDestino);

        dibujaGrafo();

        controlDibujo(nodosInicio,nodosDestino);
    }
    if (kruskalRadio->isChecked()){

        nombreArchivo= kruskalRadio->text();

        Kruskal *kruskal = new Kruskal(matrizAdyacencia,cantidadNodos);

        ArrayList<int> nodosInicio = kruskal->getRutaInicial();

        ArrayList<int> nodosDestino =kruskal->getRutaDestino();

        algoritmoDocumentos(nodosInicio,nodosDestino);

        dibujaGrafo();

        controlDibujo(nodosInicio,nodosDestino);
    }
    if(warshallRadio->isChecked()){

        nombreArchivo= warshallRadio->text();

        Warshall *warshall = new Warshall(cantidadNodos,matrizAdyacencia);

        Matriz<ArrayList<int>*,int> matrizWarshall = warshall->getMatriz();

        algoritmoDocumentos(matrizWarshall);

        dibujaGrafo();
    }
}

void Controladora::deleteEtiquetas(){

    dijkstraRadio->setVisible(false);
    floydRadio->setVisible(false);
    primRadio->setVisible(false);
    kruskalRadio->setVisible(false);
    warshallRadio->setVisible(false);
    menuInicioDijkstra->setVisible(false);
    menuDestinoDijkstra->setVisible(false);

    dijkstraRadio->deleteLater();
    floydRadio->deleteLater();
    primRadio->deleteLater();
    kruskalRadio->deleteLater();
    warshallRadio->deleteLater();
    menuInicioDijkstra->deleteLater();
    menuDestinoDijkstra->deleteLater();
}

void Controladora::dibujaGrafo(){
    scene->clear();

    pen = new QPen ();

    pen->setWidth(6);

    deleteEtiquetas();

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

    matrizUbicaciones = new Matriz<ArrayList<int>*,int>(filasMatriz,columnasMatriz);
    arrayCoordenasX = new ArrayList<int>(50);
    arrayCoordenasY = new ArrayList<int>(50);
    agregaNodos();
}

void Controladora::agregaNodos(){

    for(int i=0;i<filasMatriz;i++){
        matrizUbicaciones->returnPos(i)->allEqual(-1);
        arrayCoordenasX->allEqual(-1);
        arrayCoordenasY->allEqual(-1);
    }

    int coorXCocina = 18;
    int coorYCocina = 170;

    QImage mesa(":/Imagenes/cocina.png");
    QGraphicsPixmapItem *itemMesa= new QGraphicsPixmapItem( QPixmap::fromImage(mesa));
    itemMesa->setPos(coorXCocina,coorYCocina);
    itemMesa->setScale(0.7);
    scene->addItem(itemMesa);

    int coorX = 172;
    int i=0;
    while(cantidadMesas<cantidadNodos){
        int coorY = 58;

        for(int j=0;j<5;j++){

            if(cantidadMesas==0&&j==0){
                matrizUbicaciones->returnPos(j)->setValue(i,cantidadMesas);
                arrayCoordenasX->setValue(cantidadMesas,coorXCocina);
                arrayCoordenasY->setValue(cantidadMesas,coorYCocina);
                coorY+=113;
            }else{
                matrizUbicaciones->returnPos(j)->setValue(i,cantidadMesas);
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
        }
        coorX+=113;
        i++;
    }

}

int Controladora::buscaNodo(int nodo,bool llave){
    bool bandera=true;
    int i=0;
    while(i<filasMatriz && bandera){
        int j=0;
        while(j<columnasMatriz && bandera){
            if(nodo==matrizUbicaciones->returnPos(i)->returnPos(j)){
                if(llave) return j; else  return i;
            }
            j++;
        }
        i++;
    }
    return 0;
}

void Controladora::controlDibujo(ArrayList<int> nodosInicio, ArrayList<int> nodosDestino){
        srand(time(NULL));

        for(int i=0;i<cantidadNodos;i++){
           int nodoInicio = nodosInicio.returnPos(i);
            int nodoDestino = nodosDestino.returnPos(i);
            if(nodoDestino == -1 || nodoInicio == -1){
                break;
            }

            int r = rand() % (255);
            int g = rand() % (255);
            int b = rand() % (255);

            QColor color(r,g,b);
            pen->setColor(color);

            dibujaLinea(nodoInicio,nodoDestino);
            delay();

        }
}

void Controladora::controlDibujo(ArrayList<int> nodos){

    srand(time(NULL));

    for(int i=0;i<cantidadNodos;i++){
        int nodoInicio = nodos.returnPos(i);
        int nodoDestino = nodos.returnPos(i+1);

        if(nodoDestino != -1 && nodoInicio != -1 ){
            int r = rand() % (255);
            int g = rand() % (255);
            int b = rand() % (255);

            QColor color(r,g,b);
            pen->setColor(color);

            dibujaLinea(nodoInicio,nodoDestino);
            delay();
        }
    }
}

void Controladora::dibujaLinea(int nodoInicio,int nodoDestino){

    int coorXDestino=arrayCoordenasX->returnPos(nodoInicio)+28.5;
    int coorYDestino=arrayCoordenasY->returnPos(nodoInicio)+80.5;
    int coorXInicio;
    int coorYInicio;

    line = scene->addLine(arrayCoordenasX->returnPos(nodoInicio)+28.5,arrayCoordenasY->returnPos(nodoInicio)+60.5,
                          coorXInicio =coorXDestino,coorYInicio = coorYDestino,*pen);

    int filaNodoInicio =buscaNodo(nodoInicio,false);
    int filaNodoDestino =buscaNodo(nodoDestino,false);
    int columnaNodoInicio =buscaNodo(nodoInicio,true);
    int columnaNodoDestino =buscaNodo(nodoDestino,true);
    int distanciaColumnas=columnaNodoInicio-columnaNodoDestino;

    distanciaColumnas = abs(distanciaColumnas);


    if(filaNodoInicio != filaNodoDestino || (nodoDestino==0 || nodoInicio == 0) ){
    distanciaColumnas=56.5;

    }else  distanciaColumnas=56.5*(distanciaColumnas+1);


    coorXDestino=coorXInicio;
    coorYDestino=coorYInicio;

    line = scene->addLine(coorXInicio,coorYInicio,
                          coorXDestino=coorXDestino+distanciaColumnas,coorYDestino,*pen);

    coorXInicio=coorXDestino;

    if(filaNodoInicio != filaNodoDestino || nodoDestino==0 || nodoInicio == 0){

            line = scene->addLine(coorXInicio,coorYInicio,
                                  coorXDestino,
                                  coorYDestino=arrayCoordenasY->returnPos(nodoDestino)+80.5,*pen);
            coorYInicio=coorYDestino;
        coorXInicio=coorXDestino;
        coorXDestino=arrayCoordenasX->returnPos(nodoDestino);

        line = scene->addLine(coorXInicio,coorYInicio,
                              coorXDestino=coorXDestino+28.5,coorYDestino,*pen);
        coorXInicio=coorXDestino;
}
        line = scene->addLine(coorXInicio,coorYInicio,
                              coorXDestino ,arrayCoordenasY->returnPos(nodoDestino)+60.5,*pen);
}

void Controladora::retroceder(){
    menuSeleccionFunciones();
}

void Controladora::retrocederMenuPrincipal(){
    deleteEtiquetas();
    agregarBotonesJugar();
}

void Controladora::startMenu(){
    getDireccionArchivo();
}

void Controladora::exit(){
    QCoreApplication::quit();
}

void Controladora::algoritmoDocumentos
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

void Controladora::algoritmoDocumentos(Matriz<ArrayList<int> *, int> matriz){
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
            archivo+=QString::number(matriz.returnPos(i)->returnPos(j))+"     ";
        }
        archivo+="\r\n";
   }
    return;
}

void Controladora::algoritmoDocumentos(ArrayList<int> nodosRutas){

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
            archivo+=QString::number(matrizAdyacencia->returnPos(i)->returnPos(j))+"     ";
        }
        archivo+="\r\n";
   }

    archivo+="\r\n Recorrido de la ruta seleccionada \r\n";
    for(int i = 0;i<cantidadNodos;i++){
        int nodo = nodosRutas.returnPos(i);
        if(nodo==nulo){
            archivo+="Cocina";
        }else if (nodo!=-1){
            archivo+=" Mesa "+QString::number(nodo);
        }
    }
    archivo+="\r\n";

    return;
}

void Controladora::algoritmoDocumentos(ArrayList<int> nodosInicio, ArrayList<int> nodosDestino){
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
            archivo+=QString::number(matrizAdyacencia->returnPos(i)->returnPos(j))+"     ";
        }
        archivo+="\r\n";
   }

    archivo+="\r\n Recorrido de las rutas \r\n";

    for(int i = 0;i<cantidadNodos;i++){
        int nodoInicio = nodosInicio.returnPos(i);
        int nodoDestino = nodosDestino.returnPos(i);

        if(nodoInicio==nulo){
            archivo+=" Cocina ";

        }else if (nodoInicio!=-1 ){

            archivo+=" Mesa "+QString::number(nodoInicio);
        }
        if (nodoDestino==nulo){

            archivo+=" Cocina ";

        }if (nodoDestino!=-1 ){

            archivo+=" Mesa "+QString::number(nodoDestino);
        }
        archivo+="\r\n";
    }
    archivo+="\r\n";

    return;
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
