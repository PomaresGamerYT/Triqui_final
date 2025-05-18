#include <iostream>
#include "gotoxy.h"
#include "modo.h"
#include "interfaz.h"
#include "logica.h"
#include "jvsj.h"
#include "cpu.h"

using namespace std;

// funcion para saber que eligio en el menu
int leerModo(int& modo) {
    bool entradaValida = false;
// cuando se equivoquen con el numero
    while (!entradaValida) {
        gotoxy(29,28); cout << "Seleccione su modo de juego: ";
        cin >> modo;

        if (modo >= 1 && modo <= 3) {
            entradaValida = true;
        } else {
            gotoxy(29,30); cout << "Ingrese una opcion valida por favor.";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
   //Si se elige salir, saldran los creditos y se finalizara la sesion
    if (modo==3){
    	system ("cls");
    	gotoxy (12,2); cout<<"Grupo Conformado por:"<<endl;
    	gotoxy (12,4); cout<<"Fabian Coronel Morato"<<endl;
    	gotoxy (12,6); cout<<"Andres Pomares Navarro"<<endl;
    	gotoxy (12,8); cout<<"Cesar Beltran Alvarado"<<endl;
    	gotoxy (12,10); cout<<"Isai Cabeza De la Hoz"<<endl;
    	gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
    	gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
    	gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
        exit(0);
	}
   
    system("cls");
    tablero();
// Entra al modo de juego o se sale del programa
    switch (modo) {
        case 1:
            gotoxy (1,1);cout << "1.Modo Jugador 1 vs Jugador 2.";
            jvsj();
            break;
        case 2:
            gotoxy (1,1);cout << "2.Modo Jugador 1 vs CPU.";
            cpu();
            break;
    }

    return modo;
}
