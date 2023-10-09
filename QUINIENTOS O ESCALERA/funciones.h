#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

// Menu
void mostrarOpciones(const char*, int, int, bool);

void titulo();
void linea(int, int);
void lineaCorta(int, int);
void lineaVer(int, int, int);

// Dados
void dibujarDado(int, int, int);
void dibujarCuadrado(int, int);
void dibujarPuntos(int, int, int);
void dados();
void generarDados(int[], int);

//Interfaces
void interfazRonda(int,char[],int);
void interfazRonda2(int,char[], char[], int, int);
void interfazTirada(int,int, char[], int, int);
void interfazFin(int, int, char[], int);
void interfazTurnos(int, int, int, int, char[], char[]);
void interfazFin2(int, char[], char[], int , int );

// Combinaciones
int ContadorDeDadosIguales(int[], int[]);
int seis6(int[]);
int seisIguales(int[]);
int escalera(int[]);

// Vectores
void cargarVector(int[], int);
void mostrarVector(int[], int);
int sumarVector(int[], int);

#endif // FUNCIONES_H_INCLUDED
