#ifndef NODO_H
#define NODO_H

#include "Cancion.h"

class Nodo{
public:

    Cancion* cancion;
    Nodo* siguiente;
    Nodo* anterior;

    Nodo(Cancion* cancion){

        this->cancion = cancion;
        siguiente = nullptr;
        anterior = nullptr;
    }
};

#endif