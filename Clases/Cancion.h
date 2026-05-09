#ifndef CANCION_H
#define CANCION_H

#include <iostream>

using namespace std;

class Cancion{
private:

    int id;
    string nombre;
    string artista;
    string album;
    int anio;
    int duracion;
    string ruta;

public:

    Cancion();

    Cancion(
        int id,
        string nombre,
        string artista,
        string album,
        int anio,
        int duracion,
        string ruta
    );

    int getId();

    string getNombre();

    string getArtista();

    string getAlbum();

    int getAnio();

    int getDuracion();

    string getRuta();

    void mostrar();
};

#endif