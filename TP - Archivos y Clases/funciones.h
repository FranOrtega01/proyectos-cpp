#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

#include "DeporteClases.h"
#include "JugadorClases.h"

//bool existeDNI(int dni){
//    ArchivoJugadores file;
//    Jugador aux;
//
//    int tam = file.cantidadRegistros();
//
//    for(int i = 0; i < tam; i++){
//        if(file.leerRegistro(i).getDni() == dni) return true;
//    }
//    return false;
//}

bool existeDeporte(int deporte){
    ArchivoDeportes file;

    int tam = file.cantidadRegistros();

    for(int i = 0; i < tam; i++){
        if(file.leerRegistro(i).getID() == deporte) return true;
    }
    return false;
}


#endif // FUNCIONES_H_INCLUDED
