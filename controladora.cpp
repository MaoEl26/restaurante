#include "controladora.h"
#include <QTime>
#include <QApplication>

#define nulo 0
#define filasMatriz 5
#define columnasMatriz 10
#define infinito -1


Controladora::Controladora()
{
    ambiente();
    agregarBotonesJugar();
    show();
}

void delay(){
    //Realiza un retraso entre un dibujo y otro
    QTime dieTime= QTime::currentTime().addSecs(3);
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

    //Agrega y da funcion al boton salir
    salirBoton = new Boton(":/Imagenes/B_SALIR.png");
    salirBoton->setPos(1040,310);
    salirBoton->setScale(1.3);
    connect(salirBoton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(salirBoton);
}

void Controladora::getDireccionArchivo(){

    cantidadNodos = nulo;

    //Guarda el path del archivo a utilizar
    filename=QFileDialog::getOpenFileName(this,"Open File","C://","Text File(*.txt)");

    //Crea una variable con los datos del documento
    QFile documento(filename);
    if(!documento.open(QIODevice::ReadOnly)){
        //Mensaje de error cuando no se puede acceder al documento
        QMessageBox::information(this,"Informacion",documento.errorString());
    }else{
        //Busca la cantidad de limeas que tiene el documento
       while(!documento.atEnd()){

           documento.readLine();
           cantidadNodos++;

       }
       documento.close();

      //Inicializa la matriz de adyacencia
       matrizAdyacencia = new Matriz<ArrayList<int>*,int>(cantidadNodos);

       //Reabre el documento
       QFile documento(filename);
       documento.open(QIODevice::ReadOnly);

       //Lee el documento linea por linea y almacena el valor en la matriz de adyacencia
       while(!documento.atEnd()){
           for(int i=0; i<cantidadNodos;i++){
               //Lee y almacena la linea
               QString linea = documento.readLine();
               //Separa la linea segun el simbolo que separa las columnas
               QStringList lineaSeparada = linea.split(",");

               for(int j=0;j<cantidadNodos;j++){
                   //Almacena en un string la pos j de la linea separa
                   QString valorConCambioLinea =lineaSeparada[j];
                   //Elinima del string el valor de retorno de carro y cambio de linea
                   QString valorFinal = valorConCambioLinea.split("\r\n",QString::SkipEmptyParts)[0];
                   //Almacena el valor en la matriz
                   matrizAdyacencia->insert(i,j,valorFinal.toInt());
               }
           }
       }
        //Cierra el documento
       documento.close();

       //Guarga la direccion del path separada por el caracter /
       QStringList url = filename.split("/");
       //Extrae la pos 2 del arreglo, la cual sería el nombre de usuario
       QString user =url[2];
       //Concatena todos los valores y los almacena en un string
       path = "C:/Users/"+user+"/Desktop/";

       //Llama a la funcion en la cual se encuentra los RadioButton y ComboBox
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
    salirBoton->setPos(1200,9);
    salirBoton->setScale(1);
    connect(salirBoton,SIGNAL(clicked()),this,SLOT(exit()));
    scene->addItem(salirBoton);

    atrasBoton = new Boton(":/Imagenes/B_ATRAS.png");
    atrasBoton->setPos(0,9);
    atrasBoton->setScale(1);
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

    //Combo Box de seleccionar nodo inicial Dijkstra
    menuInicioDijkstra = new QComboBox(this);
    menuInicioDijkstra->setGeometry(625,260,75,25);
    menuInicioDijkstra->setEnabled(false);
    menuInicioDijkstra->addItem("Inicio");//0

    //Combo Box de seleccionar nodo destino dijkstra
    menuDestinoDijkstra = new QComboBox(this);
    menuDestinoDijkstra->setGeometry(710,260,75,25);
    menuDestinoDijkstra->setEnabled(false);
    menuDestinoDijkstra->addItem("Destino");//0

    //Combo Box para seleccionar el nodo incio para graficar recorrido Floyd
    menuInicioFloyd = new QComboBox(this);
    menuInicioFloyd->setGeometry(625,310,75,25);
    menuInicioFloyd->setEnabled(false);
    menuInicioFloyd->addItem("Inicio");//0

    //Combo Box para seleccionar el nodo destino para graficar recorrido Floyd
    menuDestinoFloyd = new QComboBox(this);
    menuDestinoFloyd->setGeometry(710,310,75,25);
    menuDestinoFloyd->setEnabled(false);
    menuDestinoFloyd->addItem("Destino");//0

    //Inserta los elementos en base a la cantidad de nodos
    for(int i =0;i<cantidadNodos;i++){
        if(i==nulo){
            menuDestinoDijkstra->addItem("Cocina");
            menuInicioDijkstra->addItem("Cocina");
            menuDestinoFloyd->addItem("Cocina");
            menuInicioFloyd->addItem("Cocina");
        }else{
            menuInicioDijkstra->addItem("Mesa "+QString::number(i));
            menuDestinoDijkstra->addItem("Mesa "+QString::number(i));
            menuInicioFloyd->addItem("Mesa "+QString::number(i));
            menuDestinoFloyd->addItem("Mesa "+QString::number(i));
        }
    }
    //Muestra los combo box en pantalla
    menuInicioDijkstra->show();
    menuDestinoDijkstra->show();
    menuInicioFloyd->show();
    menuDestinoFloyd->show();

    //Le agrega la función
    connect(menuInicioDijkstra,SIGNAL(activated(QString)),this,SLOT(guardaNodoInicioDijkstra()));
    connect(menuDestinoDijkstra,SIGNAL(activated(QString)),this,SLOT(guardaNodoDestinoDijkstra()));
    connect(menuInicioFloyd,SIGNAL(activated(QString)),this,SLOT(guardaNodoInicioFloyd()));
    connect(menuDestinoFloyd,SIGNAL(activated(QString)),this,SLOT(guardaNodoDestinoFloyd()));

}

void Controladora::guardaNodoInicioDijkstra(){
    //Esta función almacena el valor del nodo de incio para el
    // algorito de Dijkstra, y habilita el segundo combo box para selecionar
    // el nodo de destino, solo activa mientras sea diferente valor inicial

    nodoInicioSeleccionado = menuInicioDijkstra->currentIndex();

    if(nodoInicioSeleccionado != nulo){

        nodoInicioSeleccionado--;

        menuDestinoDijkstra->setEnabled(true);     
    }else{
        menuDestinoDijkstra->setEnabled(false);
    }
}

void Controladora::guardaNodoDestinoDijkstra(){
    //Esta funcion almacena el valor del nodo destino para el
    // algoritmo de Dijkstra, y luego llama a las funciones
    // necesarias para graficar y crea el documento

    nodoDestinoSeleccionado = menuDestinoDijkstra->currentIndex();

    if(nodoDestinoSeleccionado != nulo){

        nombreArchivo= dijkstraRadio->text();//Almacena el nombre que tendra el archivo

        nodoDestinoSeleccionado--;//Disminuye en uno el valor para coincidir con los valores
                                  // de la matriz de adyacencia
         if (nodoDestinoSeleccionado!=nodoInicioSeleccionado){
            //Inicializa el algoritmo
            dijkstra = new Dijkstra
                    (cantidadNodos,nodoInicioSeleccionado,nodoDestinoSeleccionado,matrizAdyacencia);

            ArrayList<int> ruta = dijkstra->getRutaNodo();//Almacena el arreglo de las rutas

            algoritmoDocumentos(ruta);//Crea el documento con el arreglo de las rutas para luego
                                      // desplegarlo en pantalla

            dibujaGrafo();//LLama a la funcion que dibuja el grafo
            algoritmoUsado=1;
        }
    }
}

void Controladora::guardaNodoInicioFloyd(){
    //Esta funcion almacena el nodo de incio para graficar el
    // algoritmo de Floyd y habilita el segundo combo box para ingresar
    // el siguiente nodo
    nodoInicioSeleccionado = menuInicioFloyd->currentIndex();

    if(nodoInicioSeleccionado != nulo){

        //Decrementa en uno el valor para coincidir con la matriz
        //de adyacencia
        nodoInicioSeleccionado--;

        menuDestinoFloyd->setEnabled(true);
    }else{
        menuDestinoFloyd->setEnabled(false);
    }
}

void Controladora::guardaNodoDestinoFloyd(){
    //Esta funcion almacena el nodo destino de Floyd para la graficación
    // y crea las instacias necesarias para poder graficar y la creacion del documento

    nodoDestinoSeleccionado = menuDestinoFloyd->currentIndex();

    if(nodoDestinoSeleccionado != nulo){

        nombreArchivo= floydRadio->text();//Almacena el nombre para la creacion del
                                          // del archivo

        nodoDestinoSeleccionado--; //Disminuye en uno el nodo para coincidir
                                   // con la matriz de adyacencia
        if (nodoDestinoSeleccionado!=nodoInicioSeleccionado){


            //Crea la instancia del algoritmo de Floyd
            floyd = new Floyd(cantidadNodos,matrizAdyacencia,archivo);

            //Almacena la matriz de rutas para la creacion del documento
            Matriz<ArrayList<int>*,int> matrizRutas = floyd->getMatrizRutas();

            //Almacena el array de la ruta en un variable para la graficación
            ArrayList<int> ruta = floyd->getRuta(nodoInicioSeleccionado,nodoDestinoSeleccionado);

            archivo=floyd->getArchivo();

            //Crea el documento y lo muestra en pantalla
            algoritmoDocumentos(matrizRutas,ruta);

            //LLama a la funcion que dibuja el grafico
            dibujaGrafo();

            ruta = floyd->getRuta(nodoInicioSeleccionado,nodoDestinoSeleccionado);

            //Llama a la funcion que dibuja la ruta
            algoritmoUsado=2;
        }
    }//Salida
}

void Controladora::checkSeleccion(){
    //Analiza cual fue el radioButton seleccionado
    if(dijkstraRadio->isChecked()){
        //Habilita el combo box del nodo de inicio
        menuInicioDijkstra->setEnabled(true);

    }else{
        //Deshabilita los combo box
        menuInicioDijkstra->setEnabled(false);

        menuDestinoDijkstra->setEnabled(false);
    }

    if(floydRadio->isChecked()){
        //Habilita el combo box del nodo de inicio
        menuInicioFloyd->setEnabled(true);

    }else{
        //Deshabilita los combo box
        menuInicioFloyd->setEnabled(false);

        menuDestinoFloyd->setEnabled(false);
    }

    if(primRadio->isChecked()){
        algoritmoUsado=3;
        nombreArchivo= primRadio->text();//Almacena el nombe del archivo

        //Crea la instacia del algoritmo
        alPrim = new Prim(cantidadNodos,matrizAdyacencia);

        //Almacena los arreglos con los nodos de cada ruta
        ArrayList<int> nodosInicio = alPrim->getRutaInicial();

        ArrayList<int> nodosDestino =alPrim->getRutaDestino();

        ArrayList<int> pesoRuta = alPrim->getPesos();

        //Crea el documento con la ruta
        algoritmoDocumentos(nodosInicio,nodosDestino,pesoRuta);

        //Dibuja el grafo de la matriz de adyacencia
        dibujaGrafo();
    }

    if (kruskalRadio->isChecked()){
        algoritmoUsado=4;
        nombreArchivo= kruskalRadio->text();//Almacena el nombre para crear el archivo

        kruskal = new Kruskal(matrizAdyacencia,cantidadNodos);//Crea la instancia del algoritmo

        //Almacena los array con los valores del recorrido
        ArrayList<int> nodosInicio = kruskal->getRutaInicial();

        ArrayList<int> nodosDestino =kruskal->getRutaDestino();

        ArrayList<int> pesoRuta =kruskal->getPesoRuta();

        //Crea el documento para luego ser almacenado
        algoritmoDocumentos(nodosInicio,nodosDestino,pesoRuta);

        dibujaGrafo();//Dibuja el grafo de la matriz de adyacencia

    }

    if(warshallRadio->isChecked()){
        nombreArchivo= warshallRadio->text();//Almacena el nombre para crear el archivo

        //Crea la instancia del algorimo
        warshall = new Warshall(cantidadNodos,matrizAdyacencia);

        //Almacena la matriz de resultado del algoritmo
        Matriz<ArrayList<int>*,int> matrizWarshall = warshall->getMatriz();

        algoritmoDocumentos(matrizWarshall);//Agrega la matriz al documento

        dibujaGrafo();//Dibuja el grafo de la matriz de adyacencia
    }
}

void Controladora::deleteEtiquetas(){
    //Esconde y elimina los combobox despues de ser utilizados

    dijkstraRadio->setVisible(false);
    floydRadio->setVisible(false);
    primRadio->setVisible(false);
    kruskalRadio->setVisible(false);
    warshallRadio->setVisible(false);
    menuInicioDijkstra->setVisible(false);
    menuDestinoDijkstra->setVisible(false);
    menuInicioFloyd->setVisible(false);
    menuDestinoFloyd->setVisible(false);

    dijkstraRadio->deleteLater();
    floydRadio->deleteLater();
    primRadio->deleteLater();
    kruskalRadio->deleteLater();
    warshallRadio->deleteLater();
    menuInicioDijkstra->deleteLater();
    menuDestinoDijkstra->deleteLater();
    menuInicioFloyd->deleteLater();
    menuDestinoFloyd->deleteLater();
}

void Controladora::dibujaGrafo(){
    //En esta funcion crea la ventana emergente con el archivo creado
    //Inicializa el lapiz con el que se dibujaran las aritas y elimina
    //los combo box, ademas crea los botones de crear el texto y devolverse,
    //inicializa los arreglos para el almacenamiento de las coordenadas y pos de las mesas
    scene->clear();
    menuPrincipal= false;

    pen = new QPen ();

    pen->setWidth(10);

    deleteEtiquetas();

    scene->setBackgroundBrush(QBrush(QImage(":/Imagenes/fondo cuadros.png")));

    areaTexto = new QTextEdit();
    areaTexto->setText(archivo);
    areaTexto->setWindowTitle(nombreArchivo);
    areaTexto->setReadOnly(true);
    areaTexto->show();

    generaDocumento = new Boton(":/Imagenes/B_GUARDAR.png");
    generaDocumento->setPos(0,50);
    generaDocumento->setScale(1);
    connect(generaDocumento,SIGNAL(clicked()),this,SLOT(generadorDocumento()));
    scene->addItem(generaDocumento);

    atrasBoton = new Boton(":/Imagenes/B_ATRAS.png");
    atrasBoton->setPos(0,9);
    atrasBoton->setScale(1);
    connect(atrasBoton,SIGNAL(clicked()),this,SLOT(retroceder()));
    scene->addItem(atrasBoton);

    siguiente = new Boton(":/Imagenes/siguiente.png");
    siguiente->setPos(1202,9);
    siguiente->setScale(0.5);
    connect(siguiente,SIGNAL(clicked()),this,SLOT(siguienteLinea()));
    scene->addItem(siguiente);

    sennalDelay = new Boton(":/Imagenes/cancelar.png");
    sennalDelay->setPos(1146,9);
    sennalDelay->setScale(0.5);
    connect(sennalDelay,SIGNAL(clicked()),this,SLOT(detenerDelay()));
    scene->addItem(sennalDelay);

    cantidadMesas = 0;

    matrizUbicaciones = new Matriz<ArrayList<int>*,int>(filasMatriz,columnasMatriz);
    arrayCoordenasX = new ArrayList<int>(50);
    arrayCoordenasY = new ArrayList<int>(50);

    agregaNodos();
}

void Controladora::agregaNodos(){
    //Esta funcion agrega las mesas en pantalla y almacena las coordenas
    // y posicion en una matriz y luego dibuja las aritas correspondientes

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
                QGraphicsTextItem *text = new QGraphicsTextItem(QString::number(cantidadMesas),itemMesa);
                text->setScale(1.5);
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

    for(int i=0;i<cantidadNodos;i++){
        if(menuPrincipal== false){
        for(int j=0;j<cantidadNodos;j++){
            if(menuPrincipal){
                break;
            }
            int valor = matrizAdyacencia->returnPos(i)->returnPos(j);

            if (valor!=-1&& valor!=0 ){
                int r = rand() % 75+180;
                int g = rand() % 115+35;
                int b = rand() % 115+35;
                QColor color(r,g,b);
                pen->setColor(color);
                dibujaLinea(i,j);
                if(detieneDelay== false){
                    delay();
                }
            }
        }
        }
    }
    pen->setWidth(4);
}

int Controladora::buscaNodo(int nodo,bool llave){
    //Busca la fila y columna en la que se encuentra segun,
    //la llave booleana ingresada en base a la matriz creada

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
    //Controla el dibujo de las conexiones cuando se ingresan 2 arreglos

        srand(time(NULL));

        for(int i=0;i<cantidadNodos;i++){
           int nodoInicio = nodosInicio.returnPos(i);
            int nodoDestino = nodosDestino.returnPos(i);
            if(nodoDestino == -1 || nodoInicio == -1){
                break;
            }

           // int r = rand() % (255);
            //int g = rand() % (255);
            //int b = rand() % (255);

           // QColor color(r,g,b);
           // pen->setColor(Qt::blue);

            dibujaLinea(nodoInicio,nodoDestino);
            delay();
        }
}

void Controladora::controlDibujo(ArrayList<int> nodos){
    //Controla el dibujo de las conexiones cuando se inserta un solo arreglo

    srand(time(NULL));

    for(int i=0;i<cantidadNodos;i++){
        int nodoInicio = nodos.returnPos(i);
        int nodoDestino = nodos.returnPos(i+1);

        if(nodoDestino != -1 && nodoInicio != -1 ){

         //   int r = rand() % 255 + 96;
           // int g = rand() % 255 + 117;
            //int b = rand() % 255 + 113;

           // QColor color(r,g,b);
            //pen->setColor(Qt::blue);

            dibujaLinea(nodoInicio,nodoDestino);

            delay();
        }
    }
}

void Controladora::dibujaLinea(int nodoInicio,int nodoDestino){
    /*Dibuja las lineas correspondientes a cada conexion en base a su pos
      en la matriz creada */

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

    //Se valida para dar el valor de distancia entre columnas
    if(filaNodoInicio != filaNodoDestino || (nodoDestino==0 || nodoInicio == 0) ){
    distanciaColumnas=56.5;
    coorXDestino=coorXInicio;
    coorYDestino=coorYInicio;

    line = scene->addLine(coorXInicio,coorYInicio,
                          coorXDestino=coorXDestino+distanciaColumnas,coorYDestino,*pen);

    coorXInicio=coorXDestino;

    //Se valida para la creacion de 2 lineas adicionales para que no choque contra las mesas
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

    }else  {

        int columnaInicio= buscaNodo(nodoInicio,true);
        int columnaDestino = buscaNodo(nodoDestino,true);
        if(columnaDestino != 0 || columnaInicio!=0){
        if((columnaInicio-columnaDestino)< 0){
            int distancia= abs(columnaInicio-columnaDestino);

            distanciaColumnas=113*(distancia);

            line = scene->addLine(coorXInicio,coorYInicio,
                                  coorXInicio+distanciaColumnas,coorYInicio,*pen);
            coorXInicio=coorXInicio+distanciaColumnas;
        }

        else if((columnaInicio-columnaDestino)!= 0){

                int distancia= (columnaInicio-columnaDestino);

                distanciaColumnas=113*(distancia);
                line = scene->addLine(coorXInicio,coorYInicio,
                                      coorXInicio-distanciaColumnas,coorYInicio,*pen);
                coorXInicio=coorXInicio-distanciaColumnas;

            }
        line = scene->addLine(coorXInicio,coorYInicio,
                              coorXInicio,coorYInicio-20,*pen);
        }

    }

}
void Controladora::retroceder(){
    //Slot para poder devolverse al menu de seleccion de algoritmos
    detieneDelay = false;
    menuPrincipal= true;
    menuSeleccionFunciones();

}

void Controladora::retrocederMenuPrincipal(){
    //Slot para eliminar radiobuttons y combobox para
   // devolverse a la pag de inicio

    deleteEtiquetas();
    agregarBotonesJugar();


}

void Controladora::startMenu(){
    //Llama a la funcion que obtiene el path del archivo
    // y que lo almacena

    getDireccionArchivo();
}

void Controladora::exit(){
    //Cierra la aplicacion
    QCoreApplication::quit();
}

void Controladora::algoritmoDocumentos
(Matriz<ArrayList<int> *, int> matrizRutas, ArrayList<int> nodosRutas){


    archivo+="Matriz de Rutas \r\n";

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
    int pesoRuta= floyd->getPesoRuta();
    archivo+="\r\n Recorrido de la ruta seleccionada \r\n";
    for(int i = 0;i<cantidadNodos;i++){
        int nodo = nodosRutas.returnPos(i);
        if(nodo==nulo){
            archivo+="Cocina";
        }else if (nodo!=-1){
            archivo+=" Mesa "+QString::number(nodo);
        }
    }
    archivo+="\r\nPeso del Recorrido: "+QString::number(pesoRuta);
    archivo+="\r\n";
    archivo+="\r\n Recorrido de las rutas posibles \r\n";
    for(int i = 0;i<cantidadNodos;i++){
        for(int j = 0; j<cantidadNodos;j++){
            if(j!=i){
                ArrayList<int> rutas=floyd->getRuta(i,j);
                int pesoRuta= floyd->getPesoRuta();

                for(int k =0;k<cantidadNodos-1;k++){
                    int nodo = rutas.returnPos(k);
                    if(nodo==nulo){
                        archivo+=" Cocina";
                    }else if (nodo!=-1){
                        archivo+=" Mesa "+QString::number(nodo);
                    }
                }
                archivo+="\r\nPeso del Recorrido: "+QString::number(pesoRuta);
                archivo+="\r\n\r\n";
            }
      }

    }

    return;
}

void Controladora::algoritmoDocumentos(Matriz<ArrayList<int> *, int> matriz){

    archivo+="Matriz de Adyacencia Entrante \r\n";
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

    archivo+="\r\n\r\nMatriz de Adyacencia Resultante \r\n";
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

    ArrayList<int> pesosRutaDijkstra = dijkstra->getRutaPesos();
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

    int pesoTotal=0;
    archivo+="\r\nRecorrido de la ruta seleccionada:\r\n\r\n";
    for(int i = 0;i<cantidadNodos;i++){
        int nodo = nodosRutas.returnPos(i);
        if(nodo==nulo){
            archivo+="Cocina";
        }else if (nodo!=-1){
            archivo+=" Mesa "+QString::number(nodo);
        }
    }
    archivo+="\r\n";
        for(int i = 0;i<cantidadNodos;i++){
            int peso = pesosRutaDijkstra.returnPos(i);
            if (peso!=-1){
            pesoTotal+=peso;
            archivo+="    "+QString::number(peso)+"     ";
            }
        }
        archivo+="\r\n\r\n";
        archivo+="Peso total del recorrido: "+QString::number(pesoTotal)+"\r\n";

    return;
}

void Controladora::algoritmoDocumentos(ArrayList<int> nodosInicio, ArrayList<int> nodosDestino,
                                       ArrayList<int> pesoRuta){
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

    int pesoTotal=0;

    for(int i = 0;i<cantidadNodos;i++){
        int nodoInicio = nodosInicio.returnPos(i);
        int nodoDestino = nodosDestino.returnPos(i);
        int peso = pesoRuta.returnPos(i);

        if(nodoInicio==nulo){
            archivo+=" Cocina ";

        }else if (nodoInicio!=-1 ){

            archivo+=" Mesa "+QString::number(nodoInicio);
        }
        if (nodoDestino==nulo){

            archivo+=" Cocina ";

        }else if (nodoDestino!=-1 ){

            archivo+=" Mesa "+QString::number(nodoDestino);
        }
        if(nodoDestino!=-1&&nodoInicio!=-1){
            archivo+=" peso: "+QString::number(peso);
            pesoTotal+=peso;
        }
        archivo+="\r\n";
    }
    archivo+="Peso total del recorrido: "+QString::number(pesoTotal);

    return;
}

void Controladora::creaDocumento(){
    //Crea el documento con el string generado, primero valida
    // que no exista para despues crearlo
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
    //Llama a la funcion que crea el documento
    creaDocumento();
}

void Controladora::siguienteLinea()
{
    int color = rand() % 8+1;

    if(color== 1){pen->setColor(Qt::blue);}
    else if(color==2){pen->setColor(Qt::white);}
    else if(color== 3){pen->setColor(Qt::darkMagenta);}
    else if(color== 4){pen->setColor(Qt::black);}
    else if(color== 5){pen->setColor(Qt::yellow);}
    else if(color== 6){pen->setColor(Qt::green);}
    else if(color== 7){pen->setColor(Qt::darkCyan);}


    if(algoritmoUsado == 1){
        int nodoInicio = dijkstra->getRutaNodo().returnPos(posNodo);
        int nodoDestino = dijkstra->getRutaNodo().returnPos(posNodo+1);
        if(nodoDestino != -1 && nodoInicio != -1 ){
            dibujaLinea(nodoInicio,nodoDestino);
            posNodo++;
        }
        else{
            posNodo=0;
            algoritmoUsado=-1;
        }

    }
    else if(algoritmoUsado ==2){
         ArrayList<int> ruta = floyd->getRuta(nodoInicioSeleccionado,nodoDestinoSeleccionado);
         int nodoInicio = ruta.returnPos(posNodo);
         int nodoDestino = ruta.returnPos(posNodo+1);
         if(nodoDestino != -1 && nodoInicio != -1 ){
             dibujaLinea(nodoInicio,nodoDestino);
             posNodo++;
         }
         else{
             posNodo=0;
             algoritmoUsado=-1;
         }
    }
    else if(algoritmoUsado ==3){
        int nodoInicio = alPrim->getRutaInicial().returnPos(posNodo);
        int nodoDestino = alPrim->getRutaDestino().returnPos(posNodo);
        if(nodoDestino != -1 || nodoInicio != -1){
            dibujaLinea(nodoInicio,nodoDestino);
            posNodo++;
        }
        else{
            posNodo=0;
            algoritmoUsado=-1;
        }
    }
    else if (algoritmoUsado ==4){
        int nodoInicio = kruskal->getRutaInicial().returnPos(posNodo);
        int nodoDestino = kruskal->getRutaDestino().returnPos(posNodo);
        if(nodoDestino != -1 || nodoInicio != -1){
            dibujaLinea(nodoInicio,nodoDestino);
            posNodo++;
        }
        else{
            posNodo=0;
            algoritmoUsado=-1;
        }
    }
}

void Controladora::detenerDelay()
{
    detieneDelay=true;
}


