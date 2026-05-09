#ifndef CANCION_HPP
#define CANCION_HPP

#include <iostream>
#include <string>

using namespace std;

class cancion {
private:
    int id;
    string nombre;
    string artista;
    string album;
    int año;
    int duracion;
    string ruta;

public:
    cancion();
    cancion(int id, string nombre, string artista, string album, int año, int duracion, string ruta);

    int getId();
    string getNombre();
    string getArtista();
    void View();
};

#endif