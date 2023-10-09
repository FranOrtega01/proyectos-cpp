#ifndef JUGADORCLASES_H_INCLUDED
#define JUGADORCLASES_H_INCLUDED

#include <cstring>

#include "funciones.h"
#include "Fecha.h"
#include "DeporteClases.h"

class ArchivoJugadores;
class Jugador;
//
class Jugador{
private:
    int _dni;
    char _nombre[30];
    char _apellido[30];
    char _email[30];
    char _telefono[30];
    int _claustro;
    int _deporte;
    int _nEquipo;
    Fecha _fechaInscripcion;
    float _matricula;
    bool _estado;
public:
    //Setters
    void setDni(int dni);
    void setEstado(bool estado);
    void setClaustro(int claustro);
    void setDeporte(int deporte);
    void setMatricula(float matricula);
    void setFecha(){
        _fechaInscripcion.cargar();
    }
    //Getters
    int getDni(){return _dni;};
    bool getEstado(){return _estado;};
    Fecha getFecha(){return _fechaInscripcion;};
    int getDeporte(){return _deporte;};
    int getClaustro(){return _claustro;};


    // Methods
    void cargar(int dni){
        float matricula;
        int claustro, deporte;

        setDni(dni);

        cout << "Nombre: ";
        cin >> _nombre;
        cout << "Apellido: ";
        cin >> _apellido;
        cout << "Email: ";
        cin >> _email;
        cout << "Telefono: ";
        cin >> _telefono;
        cout << "Claustro: ";
        cin >> claustro;
        setClaustro(claustro);
        cout << "Deporte: ";
        cin >> deporte;
        setDeporte(deporte);
        cout << "Numero de equipo: ";
        cin >> _nEquipo;
        cout << "Fecha: ";
        _fechaInscripcion.cargar();
        cout << "Matricula: ";
        cin >> matricula;
        setMatricula(matricula);
        _estado = true;
    }

    void mostrar(){
        cout << "DNI: " << _dni << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Apellido: " << _apellido << endl;
        cout << "Email: " << _email << endl;
        cout << "Telefono: " << _telefono << endl;
        cout << "Claustro: " << _claustro << endl;
        cout << "Deporte: " << _deporte << endl;
        cout << "Numero de equipo: " << _nEquipo << endl;
        cout << "Fecha: " << endl;
        _fechaInscripcion.mostrar();
        cout << endl << "Matricula: " << _matricula << endl;
        cout << "Estado: " << _estado << endl;
    }
};

bool claustroValido(int claustro){
    return claustro > 0 && claustro < 5;
}

void Jugador::setDni(int dni){
    _dni = dni;
}

void Jugador::setClaustro(int claustro){
    while(!claustroValido(claustro)){

        cout << "Claustro invalido, ingrese un claustro valido: ";
        cin >> claustro;
    }
    _claustro = claustro;
}

void Jugador::setDeporte(int deporte){
    while(!existeDeporte(deporte)){
        cout << "El deporte no existe, ingrese un deporte valido: ";
        cin >> deporte;
    }

    _deporte = deporte;
}

void Jugador::setMatricula(float matricula){
    if(matricula >= 0){
        _matricula = matricula;
    }else{
        _matricula = 0;
    }
}

void Jugador::setEstado(bool estado){
    _estado = estado;
}


class ArchivoJugadores{
    private:
        char _nombre[30];
    public:
        ArchivoJugadores(const char *n="jugadores.dat");
        bool agregarRegistro(Jugador reg);
        int cantidadRegistros();
        int buscarRegistro(int dni);
        Jugador leerRegistro(int pos);
        bool sobreescribirRegistro(Jugador reg, int pos);
        void limpiarArchivo();
};

ArchivoJugadores::ArchivoJugadores(const char *n){
    strcpy(_nombre,n);
}
//FUNCIONES ARCHIVOS//
int ArchivoJugadores::cantidadRegistros(){
    FILE *p;
    p=fopen(_nombre, "rb");
    if(p==NULL){
        return -1;
    }
    fseek(p, 0, 2);
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Jugador);
}

bool ArchivoJugadores::agregarRegistro(Jugador reg){
    FILE *p;
    p=fopen(_nombre, "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoJugadores::buscarRegistro(int dni){
    FILE *p;
    Jugador aux;
    int pos=0;
    p=fopen(_nombre, "rb");
    if(p==NULL){
        return -2;
    }
    while(fread(&aux, sizeof aux, 1, p)==1){
        if(aux.getDni()==dni){
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

Jugador ArchivoJugadores::leerRegistro(int pos){
    Jugador aux;
    FILE *p;
    p=fopen(_nombre, "rb");
    if(p==NULL){
        aux.setDni(-1);
        return aux;
    }
    fseek(p, pos * sizeof aux, 0);
    fread(&aux, sizeof aux, 1, p);
    fclose(p);
    return aux;
}

bool ArchivoJugadores::sobreescribirRegistro(Jugador reg, int pos){
    FILE *p;
    p=fopen(_nombre, "rb+");
    if(p==NULL){
        return false;
    }
    fseek(p, pos * sizeof reg, 0);
    bool escribio=fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}

void ArchivoJugadores::limpiarArchivo(){
    FILE *p; //la re flashea codeblocks
    p = fopen(_nombre, "wb");
    if(p==NULL){
        return;
    }
    fclose(p);
}


#endif // JUGADORCLASES_H_INCLUDED
