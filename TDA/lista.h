#ifndef LISTA_HPP
#define LISTA_HPP

#include "../Cancion/cancion.h" //

struct Nodo {
    cancion* dato;
    Nodo* siguiente;
    Nodo* anterior;


    Nodo(cancion* c) : dato(c), siguiente(nullptr), anterior(nullptr) {}
};

class lista {
private:
    Nodo* primero;
    Nodo* ultimo;
    int tamano;

public:
    lista();
    void insertarFinal(cancion* c);
    int tamanoF();

    Nodo* getFirst();
    Nodo* getLast();

    cancion* get(int indice);
    ~lista();
};

#endif
