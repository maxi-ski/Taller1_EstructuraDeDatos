#include "cancion.h"

// Constructor por defecto
cancion::cancion() {
    this->id = 0;
    this->nombre = "";
    this->artista = "";
    this->album = "";
    this->año = 0;
    this->duracion = 0;
    this->ruta = "";
}

// Constructor con parámetros
cancion::cancion(int id, string nombre, string artista, string album, int año, int duracion, string ruta) {
    this->id = id;
    this->nombre = nombre;
    this->artista = artista;
    this->album = album;
    this->año = año;
    this->duracion = duracion;
    this->ruta = ruta;
}

int cancion::getId() {
    return this->id;
}

string cancion::getNombre() {
    return this->nombre;
}

string cancion::getArtista() {
    return this->artista;
}

void cancion::View() {
    cout << this->id << ". " << this->nombre << endl;
    cout << this->artista << endl;
}