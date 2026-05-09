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

//mostrar
void ListaCanciones::mostrar(){
    Nodo* aux = primero;
    int i = 1;
    while(aux != nullptr){
        cout
            << i
            << ". "
            << aux->cancion->getNombre()
            << " - "
            << aux->cancion->getArtista()
            << endl;
        aux = aux->siguiente;
        i++;
    }
}

//obtener por posicion
Cancion* ListaCanciones::obtenerPorPos(int pos){
    Nodo* aux = primero;
    int i = 1;

    while(aux != nullptr){
        if(i == pos){
            return aux->cancion;
        }
        aux = aux->siguiente;
        i++;
    }

    return nullptr;
}

//eliminar por posicion
void ListaCanciones::eliminarPorPos(int pos){
    if(pos < 1 || pos > largo){
        return;
    }

    Nodo* aux = primero;
    int i = 1;
    while(aux != nullptr){
        if(i == pos){
            if(aux == primero){
                primero = aux->siguiente;
                if(primero != nullptr){
                    primero->anterior = nullptr;
                }
            }
            else{
                aux->anterior->siguiente = aux->siguiente;
            }
            if(aux == ultimo){
                ultimo = aux->anterior;
            }
            else if(aux->siguiente != nullptr){
                aux->siguiente->anterior = aux->anterior;
            }
            delete aux;
            largo--;
            return;
        }

        aux = aux->siguiente;

        i++;
    }
}

//get primero
Nodo* ListaCanciones::getPrimero(){
    return primero;
}
//get largo
int ListaCanciones::getLargo(){
    return largo;
}