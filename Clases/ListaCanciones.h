#ifndef LISTACANCIONES_H
#define LISTACANCIONES_H

#include "nodo.h"

class ListaCanciones{
private:
    Nodo* primero;
    Nodo* ultimo;
    int largo;

public:
    ListaCanciones();
    void agregar(Cancion* cancion);
    void mostrar();
    Nodo* getPrimero();
    Nodo* getUltimo();
    int getLargo();
    Cancion* obtenerPorPos(int pos);
    void eliminarPorPos(int pos);
    void vaciar();
};

#endif