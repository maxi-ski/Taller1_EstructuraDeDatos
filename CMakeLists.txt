cmake_minimum_required(VERSION 4.2)
project(Taller1_EstructuraDeDatos)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller1_EstructuraDeDatos Main/main.cpp
        Cancion/Cancion.cpp
        Cancion/Cancion.h
        TDA/lista.cpp
        TDA/lista.h
        Clases/Cancion.h
        Clases/Cancion.cpp
        Logica/Reproductor.h
        Logica/Reproductor.cpp
        Clases/Nodo.h
        Clases/ListaCanciones.h
        Clases/ListaCanciones.cpp
)
