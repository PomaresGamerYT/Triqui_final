#include <iostream>
#include "gotoxy.h"
#include "modo.h"
#include "interfaz.h"
#include "logica.h"
#include "jvsj.h"
#include "cpu.h"
#include "audio.h"


using namespace std;

int leerModo(int& modo) {
    bool entradaValida = false;
    playBackgroundMusic("musicamenu.wav");
    while (!entradaValida) {
        gotoxy(29,28); cout << "Seleccione su modo de juego: ";
        cin >> modo;

        if (modo >= 1 && modo <= 3) {
            entradaValida = true;
            playEffect("sonidoboton.wav");
        } else {
            gotoxy(29,30); cout << "Ingrese una opcion valida por favor.";
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }

    if (modo==3){
        system ("cls");
        gotoxy (12,2); cout<<"Grupo Conformado por:"<<endl;
        gotoxy (12,4); cout<<"1. Fabian Coronel Morato"<<endl;
        gotoxy (12,6); cout<<"2. Andres Pomares Navarro"<<endl;
        gotoxy (12,8); cout<<"3. Cesar Beltran Alvarado"<<endl;
        gotoxy (12,10); cout<<"4.                      "<<endl;
        gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
        gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
        gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
        exit(0);
    }

    system("cls");
    tablero();

    switch (modo) {
        case 1:
            jvsj();
            break;
        case 2:
            gotoxy (1,1);cout << "2.Modo Jugador 1 vs CPU.";
            cpu();
            break;
    }

    return modo;
}