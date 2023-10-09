#ifndef FECHA_H
#define FECHA_H

#include <ctime>

class Fecha{
    private:
        int _day, _month, _year;
    public:

        int getDay(){return _day;}
        int getMonth(){return _month;}
        int getYear(){return _year;}

        bool fechaValida(){

            time_t now = time(0);
            tm* localTime = localtime(&now);

            int yearActual = localTime->tm_year + 1900;
            int monthActual = localTime->tm_mon + 1;
            int dayActual = localTime->tm_mday;

            int _year = getYear();
            int _month = getMonth();
            int _day = getDay();

            if(_year < 1) return false;
            if(_year > yearActual) return false;
            if(_month < 1 || _month > 12) return false;
            if(_year == yearActual && _month > monthActual) return false;
            if(_day < 1 || _day > 31) return false;
            if(_year == yearActual && _month == monthActual && _day > dayActual) return false;

            return true;
        }

        void cargar(){
            while(true){
                cout << "DIA: ";
                cin>>_day;
                cout << "MES: ";
                cin>>_month;
                cout << "ANIO: ";
                cin>>_year;
                if(fechaValida()){
                    break;
                }else{
                    cout << endl << "La fecha es invalida, vuelva a ingresar una fecha." << endl;
                }
            }
        }
        void mostrar(){
            cout<<_day<<"/"<<_month<<"/"<<_year;
        }
};



#endif // FECHA_H
