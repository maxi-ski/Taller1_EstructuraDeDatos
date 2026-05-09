#ifndef TALLER1_ESTRUCTURADEDATOS_REPRODUCTOR_H
#define TALLER1_ESTRUCTURADEDATOS_REPRODUCTOR_H

#include <iostream>
#include <fstream>
#include "../Clases/ListaCanciones.h"

using namespace std;

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