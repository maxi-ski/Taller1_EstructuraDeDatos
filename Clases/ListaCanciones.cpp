#include "ListaCanciones.h"

ListaCanciones::ListaCanciones(){

    primero = nullptr;
    ultimo = nullptr;

    largo = 0;
}

//agregar
void ListaCanciones::agregar(Cancion* cancion){

    Nodo* nuevo = new Nodo(cancion);

    if(primero == nullptr){

        primero = nuevo;
        ultimo = nuevo;
    }
    else{

        ultimo->siguiente = nuevo;

        nuevo->anterior = ultimo;

        ultimo = nuevo;
    }

    largo++;
}
#include "ListaCanciones.h"

