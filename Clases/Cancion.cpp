#include "Cancion.h"

Cancion::Cancion(){

    id = 0;
    nombre = "";
    artista = "";
    album = "";
    anio = 0;
    duracion = 0;
    ruta = "";
}

Cancion::Cancion(
    int id,
    string nombre,
    string artista,
    string album,
    int anio,
    int duracion,
    string ruta
){

    this->id = id;
    this->nombre = nombre;
    this->artista = artista;
    this->album = album;
    this->anio = anio;
    this->duracion = duracion;
    this->ruta = ruta;
}

int Cancion::getId(){
    return id;
}

string Cancion::getNombre(){
    return nombre;
}

string Cancion::getArtista(){
    return artista;
}

string Cancion::getAlbum(){
    return album;
}

int Cancion::getAnio(){
    return anio;
}

int Cancion::getDuracion(){
    return duracion;
}

string Cancion::getRuta(){
    return ruta;
}

void Cancion::mostrar(){

    cout << nombre << " - " << artista << endl;
}