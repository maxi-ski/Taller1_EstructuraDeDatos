//
// Created by nacho on 5/8/2026.
//
#include "Reproductor.h"

#include <sstream>
#include <ctime>
#include <cstdlib>

Reproductor::Reproductor(){

    actual = nullptr;
    reproduciendo = false;
    random = false;
    repeticion = 0;

    srand(time(nullptr));
}

//cargar canciones
void Reproductor::cargarCanciones(){

    ifstream archivo("Estructura/music_source.txt");

    if(!archivo.is_open()){

        cout << "No se encontro music_source.txt" << endl;

        return;
    }

    string linea;

    while(getline(archivo, linea)){

        if(linea == ""){
            continue;
        }

        stringstream ss(linea);

        string dato;

        string datos[7];

        int i = 0;

        while(getline(ss, dato, ',')){

            datos[i] = dato;

            i++;
        }

        Cancion* nueva = new Cancion(
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

    if(canciones.getLargo() > 0){

        actual = canciones.obtenerPorPos(1);
    }
}

//mostrar menu
void Reproductor::mostrarMenu(){

    system("cls");

    cout << "==========================" << endl;
    cout << "      REPRODUCTOR" << endl;
    cout << "==========================" << endl;
    cout << endl;

    if(actual != nullptr){

        if(reproduciendo){
            cout << "Reproduciendo: ";
        }
        else{
            cout << "En pausa: ";
        }

        cout << actual->getNombre() << endl;

        cout << "Artista: " << actual->getArtista() << endl;

        cout << "Album: "
             << actual->getAlbum()
             << " ["
             << actual->getAnio()
             << "]"
             << endl;
    }
    else{

        cout << "Reproduccion detenida" << endl;
    }

    cout << endl;

    cout << "W - Reproducir/Pausar" << endl;
    cout << "Q - Pista anterior" << endl;
    cout << "E - Pista siguiente" << endl;
    cout << "S - Random" << endl;
    cout << "R - Repeticion" << endl;
    cout << "L - Listado canciones" << endl;
    cout << "X - Salir" << endl;

    cout << endl;

    cout << "Ingrese opcion: ";
}

//play pausa
void Reproductor::reproducirPausa(){

    if(actual == nullptr){
        return;
    }

    reproduciendo = !reproduciendo;

    guardarEstado();
}

//siguiente
void Reproductor::siguiente(){

    if(canciones.getLargo() == 0){
        return;
    }

    int pos = rand() % canciones.getLargo() + 1;

    actual = canciones.obtenerPorPos(pos);

    reproduciendo = true;

    guardarEstado();
}

//anterior
void Reproductor::anterior(){

    if(canciones.getLargo() == 0){
        return;
    }

    int pos = rand() % canciones.getLargo() + 1;

    actual = canciones.obtenerPorPos(pos);

    reproduciendo = true;

    guardarEstado();
}

//listar canciones
void Reproductor::listarCanciones(){

    system("cls");

    cout << "==========================" << endl;
    cout << "   CANCIONES REGISTRADAS" << endl;
    cout << "==========================" << endl;
    cout << endl;

    canciones.mostrar();

    cout << endl;

    cout << "R<num> - reproducir" << endl;
    cout << "A<num> - agregar cola" << endl;
    cout << "N - nueva cancion" << endl;
    cout << "D<num> - eliminar" << endl;
    cout << "V - volver" << endl;

    cout << endl;

    string op;

    cin >> op;

    //volver
    if(op == "V" || op == "v"){
        return;
    }

    //nueva
    if(op == "N" || op == "n"){

        agregarCancion();

        return;
    }

    //reproducir
    if(op[0] == 'R' || op[0] == 'r'){

        int num = stoi(op.substr(1));

        Cancion* c = canciones.obtenerPorPos(num);

        if(c != nullptr){

            actual = c;

            reproduciendo = true;
        }

        guardarEstado();

        return;
    }

    //eliminar
    if(op[0] == 'D' || op[0] == 'd'){

        int num = stoi(op.substr(1));

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

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Artista: ";
    getline(cin, artista);

    cout << "Album: ";
    getline(cin, album);

    cout << "Anio: ";
    cin >> anio;

    cout << "Duracion: ";
    cin >> duracion;

    cin.ignore();

    cout << "Ruta: ";
    getline(cin, ruta);

    int id = canciones.getLargo() + 1;

    Cancion* nueva = new Cancion(
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
        << id << ","
        << nombre << ","
        << artista << ","
        << album << ","
        << anio << ","
        << duracion << ","
        << ruta
        << endl;

    archivo.close();

    guardarEstado();
}

//guardar txt nuevo
void Reproductor::eliminarCancion(){

    ofstream archivo("Estructura/music_source.txt");

    Nodo* aux = canciones.getPrimero();

    while(aux != nullptr){

        Cancion* c = aux->cancion;

        archivo
            << c->getId() << ","
            << c->getNombre() << ","
            << c->getArtista() << ","
            << c->getAlbum() << ","
            << c->getAnio() << ","
            << c->getDuracion() << ","
            << c->getRuta()
            << endl;

        aux = aux->siguiente;
    }

    archivo.close();
}

//guardar cfg
void Reproductor::guardarEstado(){

    ofstream archivo("Estructura/status.cfg");

    archivo << "reproduciendo=" << reproduciendo << endl;
    archivo << "random=" << random << endl;
    archivo << "repeticion=" << repeticion << endl;

    if(actual != nullptr){

        archivo << "actual=" << actual->getId() << endl;
    }
    else{

        archivo << "actual=0" << endl;
    }

    archivo.close();
}

//menu principal
void Reproductor::menu(){

    char op;

    do{

        mostrarMenu();

        cin >> op;

        if(op == 'W' || op == 'w'){

            reproducirPausa();
        }

        else if(op == 'E' || op == 'e'){

            siguiente();
        }
        else if(op == 'Q' || op == 'q'){
            anterior();
        }
        else if(op == 'L' || op == 'l'){
            listarCanciones();
        }

        else if(op == 'S' || op == 's'){
            random = !random;
            guardarEstado();
        }
        else if(op == 'R' || op == 'r'){
            repeticion++;
            if(repeticion > 2){
                repeticion = 0;
            }
            guardarEstado();
        }
    }while(op != 'X' && op != 'x');

    guardarEstado();
}