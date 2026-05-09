//
// Created by nacho on 5/8/2026.
//

#ifndef REPRODUCTOR_H
#define REPRODUCTOR_H

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