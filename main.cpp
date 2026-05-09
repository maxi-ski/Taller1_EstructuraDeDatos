#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Cancion/cancion.h"

using namespace std;

struct Node {
    cancion* dato;
    Node* next;
    Node(cancion* c) {
        this->dato = c;
        this->next = nullptr;
    }   };
Node* head = nullptr;

void agregarALista(cancion* nueva) {
    Node* nuevoNodo = new Node(nueva);
    if (head == nullptr) {
        head = nuevoNodo;
    } else {
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = nuevoNodo;
    }
}

int main() {

    return 0;
}