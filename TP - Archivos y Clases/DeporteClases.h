#ifndef DEPORTECLASES_H_INCLUDED
#define DEPORTECLASES_H_INCLUDED
#include <cstring>
#include "Fecha.h"

class Deporte{
private:
    int _id;
    char _nombre[30];
    int _tipoDeporte;
    int _fechaOrigen;
    bool _estado;
public:
    // Setters
    void setID(int id){_id = id;}
    void setTipoDeporte(int tipo);
    void setFechaOrigen(int fecha);
    void setEstado(bool est){_estado = est;}

    // Getters
    int getID(){return _id;}
    char* getNombre(){return _nombre;}
    int getTipoDeporte(){return _tipoDeporte;}
    int getFechaOrigen(){return _fechaOrigen;}
    bool getEstado(){return _estado;}

    void cargar(int id){
        system("cls");
        int tipo, fechaOrigen;
        setID(id);
        cout << "Nombre: ";
        cin >> _nombre;
        cout << "Tipo: ";
        cin >> tipo;
        setTipoDeporte(tipo);
        cout << "Anio de origen: ";
        cin >> fechaOrigen;
        setFechaOrigen(fechaOrigen);
        _estado = true;
    }

    void mostrar(){
        cout << "ID: " << _id << endl;
        cout << "Nombre: " << _nombre << endl;
        cout << "Tipo: " << _tipoDeporte << endl;
        cout << "Fecha de origen: " << _fechaOrigen << endl;
        cout << "Estado: " << _estado << endl;
    }
};

bool tipoValido(int tipo){
    return tipo >= 1 && tipo <= 21;
}

void Deporte::setTipoDeporte(int tipo){
    while(!tipoValido(tipo)){

        cout << "Tipo invalido, ingrese un tipo valido: ";
        cin >> tipo;
    }
    _tipoDeporte = tipo;
}

void Deporte::setFechaOrigen(int fecha){
    while(fecha < 1800 || fecha > 2023){

        cout << "Anio invalido, ingrese un anio valido: ";
        cin >> fecha;
    }
    _fechaOrigen = fecha;
}

class ArchivoDeportes{
private:
    char _nombre[30];
public:
    ArchivoDeportes(const char *n="deportes.dat");
    bool agregarRegistro(Deporte reg);
    int cantidadRegistros();
    int buscarRegistro(int id);
    Deporte leerRegistro(int pos);
    bool sobreescribirRegistro(Deporte reg, int pos);
    void limpiarArchivo();
};

ArchivoDeportes::ArchivoDeportes(const char *n){
    strcpy(_nombre,n);
}

int ArchivoDeportes::cantidadRegistros(){
    FILE *p;
    p=fopen(_nombre, "rb");
    if(p==NULL){
        return -1;
    }
    fseek(p, 0, 2);///SEEK_END
    int tam=ftell(p);
    fclose(p);
    return tam/sizeof (Deporte);
}

bool ArchivoDeportes::agregarRegistro(Deporte reg){
    FILE *p;
    p=fopen(_nombre, "ab");
    if(p==NULL){
        return false;
    }
    bool escribio=fwrite(&reg, sizeof reg, 1, p);
    fclose(p);
    return escribio;
}

int ArchivoDeportes::buscarRegistro(int id){
    FILE *p;
    Deporte aux;
    int pos=0;
    p=fopen(_nombre, "rb");
    if(p==NULL){
        return -2;
    }
    while(fread(&aux, sizeof aux, 1, p)==1){
        if(aux.getID() == id){
            fclose(p);
            return pos;
        }
        pos++;
    }
    fclose(p);
    return -1;
}

Deporte ArchivoDeportes::leerRegistro(int pos){
    Deporte aux;
    FILE *p;
    p=fopen(_nombre, "rb");
    if(p==NULL){
        aux.setID(-1);
        return aux;
    }
    fseek(p, pos * sizeof aux, 0);
    fread(&aux, sizeof aux, 1, p);
    fclose(p);
    return aux;
}

bool ArchivoDeportes::sobreescribirRegistro(Deporte reg, int pos){
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

void ArchivoDeportes::limpiarArchivo(){
    FILE *p;
    p = fopen(_nombre, "wb");
    if(p==NULL){
        return;
    }
    fclose(p);
}

#endif // DEPORTECLASES_H_INCLUDED
