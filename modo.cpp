#include <iostream>
#include "gotoxy.h"
#include "modo.h"
#include "interfaz.h"
#include "logica.h"
#include "jvsj.h"
#include "cpu.h"
#include "audio.h"


using namespace std;

int leerModo(int& modo) { //Se da como parametro de referencia el modo para que los cambios se reflejen en main
    bool entradaValida = false; //Se define la entrada
    playBackgroundMusic("musicamenu.wav"); //Se reproduce la musica del menu
    while (!entradaValida) { //Mientras que aun no cambie la entrada
        gotoxy(29,28); cout << "Seleccione su modo de juego: "; //Se pide el modo de juego
        cin >> modo;

        if (modo >= 1 && modo <= 3) { //Si esta dentro de uno de los tres disponibles
            entradaValida = true;  //Cambia la entrada
            playEffect("sonidoboton.wav"); //Reproduce sonido de seleccion
        } else { //Si selecciona algo fuera de los modos
            gotoxy(29,30); cout << "Ingrese una opcion valida por favor."; //Se muestra el siguiente mensaje
            cin.clear(); // Limpia errores de entrada
            cin.ignore(1000, '\n'); // Descarta la entrada incorrecta
        } 
    }

    if (modo==3){ //Si se selecciona el modo 3 que es salir
        system ("cls"); //Borra todo lo anterior y muestra los creditos
        gotoxy (12,4); cout<<"Grupo Conformado por:"<<endl;
        gotoxy (12,6); cout<<"1. Fabian Coronel Morato"<<endl;
        gotoxy (12,8); cout<<"2. Andres Pomares Navarro"<<endl;
        gotoxy (12,10); cout<<"3. Cesar Beltran Alvarado"<<endl;
        gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
        gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
        gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
        exit(0); //Sale del juego
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