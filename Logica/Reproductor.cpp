//
// Created by nacho on 5/8/2026.
//
#ifndef TALLER1_ESTRUCTURADEDATOS_REPRODUCTOR_H
#define TALLER1_ESTRUCTURADEDATOS_REPRODUCTOR_H

#endif //TALLER1_ESTRUCTURADEDATOS_REPRODUCTOR_H
#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H
#include <fstream>
#include "../Clases/ListaCanciones.h"

class Reproductor{
private:
    ListaCanciones canciones;
    ListaCanciones cola;
    Cancion* actual;
    bool reproduciendo;
    bool random;
    int repeticion;

public:
    Reproductor();
    void cargarCanciones();
    void menu();
    void mostrarMenu();
    void reproducirPausa();
    void siguiente();
    void anterior();
    void listarCanciones();
    void agregarCancion();
    void eliminarCancion();
    void guardarEstado();
};
#endif

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
    cout << "Año: ";
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
        "data/music_source.txt",
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
    ofstream archivo("data/music_source.txt");
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
    ofstream archivo("data/status.cfg");
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
        else if(op == 'S' || op == 's') {
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