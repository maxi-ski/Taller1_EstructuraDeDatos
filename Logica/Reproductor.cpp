#include "Reproductor.h"
#include <sstream>
#include <ctime>
#include <cstdlib>

Reproductor::Reproductor(){
    actual=nullptr;
    reproduciendo=false;
    random=false;
    repeticion=0;
    srand(time(nullptr));
}
//estado visual
string Reproductor::estadoActual(){
    string estado="";

    if(random){
        estado+="S";
    }

    if(repeticion==1){
        if(estado!=""){
            estado+="-";
        }
        estado+="R1";
    }
    else if(repeticion==2){
        if(estado!=""){
            estado+="-";
        }
        estado+="RA";
    }

    return estado;
}

//llenar cola
void Reproductor::llenarColaAleatoria(){
    cola=ListaCanciones();
    Nodo* aux=canciones.getPrimero();
    while(aux!=nullptr){
        if(aux->cancion!=actual){
            cola.agregar(aux->cancion);
        }
        aux=aux->siguiente;
    }
}

//cargar canciones
void Reproductor::cargarCanciones(){
    ifstream archivo("Estructura/music_source.txt");
    if(!archivo.is_open()){
        cout<<"No se encontro music_source.txt"<<endl;
        return;
    }
    string linea;
    while(getline(archivo,linea)){

        if(linea==""){
            continue;
        }
        stringstream ss(linea);
        string dato;
        string datos[7];
        int i=0;
        while(getline(ss,dato,',')){
            datos[i]=dato;
            i++;
        }
        Cancion* nueva=new Cancion(
            stoi(datos[0]),
            datos[1],
            datos[2],
            datos[3],
            stoi(datos[4]),
            stoi(datos[5]),
            datos[6]
        );

        canciones.agregar(nueva);
    }
    archivo.close();
    if(canciones.getLargo()>0){
        actual=canciones.obtenerPorPos(1);
        llenarColaAleatoria();
    }
}

//mostrar menu
void Reproductor::mostrarMenu(){
    system("cls");
    cout<<"=========================="<<endl;
    cout<<"      REPRODUCTOR"<<endl;
    cout<<"=========================="<<endl;
    cout<<endl;
    if(actual!=nullptr){
        cout<<"Actual ";
        string estado=estadoActual();
        if(estado!=""){
            cout<<"("<<estado<<")";
        }
        cout<<": ";
        cout
            <<actual->getNombre()
            <<" - "
            <<actual->getArtista()
            <<endl;
    }
    else{
        cout<<"Sin canciones"<<endl;
    }

    cout<<endl;
    cout<<"W - Reproducir/Pausar"<<endl;
    cout<<"Q - Pista anterior"<<endl;
    cout<<"E - Pista siguiente"<<endl;
    cout<<"S - Random"<<endl;
    cout<<"R - Repeticion"<<endl;
    cout<<"A - Ver lista reproduccion"<<endl;
    cout<<"L - Listado canciones"<<endl;
    cout<<"X - Salir"<<endl;
    cout<<endl;
    cout<<"Ingrese opcion: ";
}

//play pausa
void Reproductor::reproducirPausa(){
    if(actual==nullptr){
        return;
    }
    reproduciendo=!reproduciendo;
    guardarEstado();
}

//siguiente
void Reproductor::siguiente(){
    if(actual==nullptr){
        return;
    }
    if(repeticion==1){
        guardarEstado();
        return;
    }

    Nodo* primeroCola=cola.getPrimero();
    if(primeroCola==nullptr){
        if(repeticion==2){
            llenarColaAleatoria();
            primeroCola=cola.getPrimero();
            if(primeroCola==nullptr){
                return;
            }
        }
        else{
            return;
        }
    }

    actual=primeroCola->cancion;
    cola.eliminarPorPos(1);
    reproduciendo=true;
    guardarEstado();
}

//anterior
void Reproductor::anterior(){
    if(canciones.getLargo()==0){
        return;
    }
    int pos=rand()%canciones.getLargo()+1;
    actual=canciones.obtenerPorPos(pos);
    reproduciendo=true;
    guardarEstado();
}

//ver cola
void Reproductor::verCola(){
    if(actual==nullptr){
        return;
    }

    system("cls");
    cout<<"Actual ";
    string estado=estadoActual();
    if(estado!=""){
        cout<<"("<<estado<<")";
    }
    cout<<": ";
    cout
        <<actual->getNombre()
        <<" - "
        <<actual->getArtista()
        <<endl;
    cout<<endl;
    cout<<"Lista de reproduccion actual:"<<endl;

    Nodo* aux=cola.getPrimero();

    if(aux==nullptr){
        cout<<"Vacia"<<endl;
    }
    else{
        int i=1;
        while(aux!=nullptr){
            cout
                <<i
                <<". "
                <<aux->cancion->getNombre()
                <<" - "
                <<aux->cancion->getArtista()
                <<endl;
            aux=aux->siguiente;
            i++;
        }
        cout<<endl;
        cout<<"S<num> - Saltar"<<endl;
    }

    cout<<"V - Volver"<<endl;
    cout<<endl;
    string op;
    cin>>op;

    if(op=="V"||op=="v"){
        return;
    }

    if(op[0]=='S'||op[0]=='s'){
        int num=stoi(op.substr(1));
        Cancion* c=cola.obtenerPorPos(num);
        if(c!=nullptr){
            actual=c;
            for(int i=0;i<num;i++){
                cola.eliminarPorPos(1);
            }
            reproduciendo=true;
        }
        guardarEstado();
    }
}

//listar canciones
void Reproductor::listarCanciones(){
    system("cls");
    cout<<"Canciones registradas:"<<endl;
    cout<<endl;
    canciones.mostrar();
    cout<<endl;
    cout<<"R<num> - Reproducir"<<endl;
    cout<<"A<num> - Agregar cola"<<endl;
    cout<<"N - Nueva cancion"<<endl;
    cout<<"D<num> - Eliminar"<<endl;
    cout<<"V - Volver"<<endl;

    cout<<endl;
    string op;
    cin>>op;
    if(op=="V"||op=="v"){
        return;
    }

    if(op=="N"||op=="n"){
        agregarCancion();
        return;
    }
    if(op[0]=='R'||op[0]=='r'){
        int num=stoi(op.substr(1));
        Cancion* c=canciones.obtenerPorPos(num);
        if(c!=nullptr){
            actual=c;
            reproduciendo=true;
            llenarColaAleatoria();
        }
        guardarEstado();
        return;
    }

    if(op[0]=='A'||op[0]=='a'){
        int num=stoi(op.substr(1));
        Cancion* c=canciones.obtenerPorPos(num);
        if(c!=nullptr){
            cola.agregar(c);
        }
        guardarEstado();
        return;
    }

    if(op[0]=='D'||op[0]=='d'){
        int num=stoi(op.substr(1));
        canciones.eliminarPorPos(num);
        eliminarCancion();
        guardarEstado();
        return;
    }
}

//agregar cancion
void Reproductor::agregarCancion(){

    cin.ignore();

    string nombre;
    string artista;
    string album;
    string ruta;

    int anio;
    int duracion;

    cout<<"Nombre: ";
    getline(cin,nombre);

    cout<<"Artista: ";
    getline(cin,artista);

    cout<<"Album: ";
    getline(cin,album);

    cout<<"Anio: ";
    cin>>anio;

    cout<<"Duracion: ";
    cin>>duracion;

    cin.ignore();

    cout<<"Ruta: ";
    getline(cin,ruta);

    int id=canciones.getLargo()+1;

    Cancion* nueva=new Cancion(
        id,
        nombre,
        artista,
        album,
        anio,
        duracion,
        ruta
    );

    canciones.agregar(nueva);

    ofstream archivo(
        "Estructura/music_source.txt",
        ios::app
    );

    archivo
        <<id<<","
        <<nombre<<","
        <<artista<<","
        <<album<<","
        <<anio<<","
        <<duracion<<","
        <<ruta
        <<endl;

    archivo.close();

    guardarEstado();
}

//guardar txt nuevo
void Reproductor::eliminarCancion(){

    ofstream archivo("Estructura/music_source.txt");

    Nodo* aux=canciones.getPrimero();

    while(aux!=nullptr){

        Cancion* c=aux->cancion;

        archivo
            <<c->getId()<<","
            <<c->getNombre()<<","
            <<c->getArtista()<<","
            <<c->getAlbum()<<","
            <<c->getAnio()<<","
            <<c->getDuracion()<<","
            <<c->getRuta()
            <<endl;

        aux=aux->siguiente;
    }

    archivo.close();
}

//guardar cfg
void Reproductor::guardarEstado(){

    ofstream archivo("Estructura/status.cfg");

    archivo<<"reproduciendo="<<reproduciendo<<endl;
    archivo<<"random="<<random<<endl;
    archivo<<"repeticion="<<repeticion<<endl;

    if(actual!=nullptr){
        archivo<<"actual="<<actual->getId()<<endl;
    }
    else{
        archivo<<"actual=0"<<endl;
    }

    archivo.close();
}

//menu principal
void Reproductor::menu(){

    char op;

    do{

        mostrarMenu();

        cin>>op;

        if(op=='W'||op=='w'){
            reproducirPausa();
        }

        else if(op=='E'||op=='e'){
            siguiente();
        }

        else if(op=='Q'||op=='q'){
            anterior();
        }

        else if(op=='L'||op=='l'){
            listarCanciones();
        }

        else if(op=='A'||op=='a'){
            verCola();
        }

        else if(op=='S'||op=='s'){
            random=!random;
            guardarEstado();
        }

        else if(op=='R'||op=='r'){

            repeticion++;

            if(repeticion>2){
                repeticion=0;
            }

            guardarEstado();
        }

    }while(op!='X'&&op!='x');

    guardarEstado();
}