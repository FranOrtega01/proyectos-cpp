#include <iostream>
using namespace std;

#include "menuDeportes.h"
#include "menuJugadores.h"
#include "menuConfiguracion.h"
#include "menuReportes.h"
int main()
{
    int opc;

    while(true){
        system("cls");
        cout << "MENU PRINCIPAL" << endl;
        cout << "----------------------------------" << endl;
        cout << "1) MENU JUGADORES" << endl;
        cout << "2) MENU DEPORTES" << endl;
        cout << "3) REPORTES" << endl;
        cout << "4) CONFIGURACION" << endl;
        cout << "----------------------------------" << endl;
        cout << "0) FIN DEL PROGRAMA" << endl;
        cout << "Seleccione una de las opciones: ";
        cin >> opc;
        switch(opc){
        case 1:
            menuJugadores();
            break;
        case 2:
            menuDeportes();
            break;
        case 3:
            menuReportes();
            break;
        case 4:
            menuConfiguracion();
            break;
        case 0:
            return 0;
        default:
            cout << "Opcion invalida." << endl;
            system("pause");
            break;
        }
    }
    return 0;
}
