cmake_minimum_required(VERSION 4.2)
project(Taller1_EstructuraDeDatos)

set(CMAKE_CXX_STANDARD 20)

add_executable(Taller1_EstructuraDeDatos Main/main.cpp
        Main/main.cpp
        Logica/Reproductor.cpp
        Logica/Reproductor.h
        Clases/Cancion.cpp
        Clases/Cancion.h
        Clases/ListaCanciones.cpp
        Clases/ListaCanciones.h
        Clases/Nodo.h
)
