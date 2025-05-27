#include <iostream>
#include <conio.h>
#include <windows.h>
#include <random>
#include <algorithm>
#include "cpu.h"
#include "gotoxy.h"
#include "logica.h"
#include "interfaz.h"
#include "audio.h"

using namespace std;
int jug1=0, cpu_puntaje=0; //Contadores para victorias

// Función para verificar movimientos ganadores
bool movimientoGanador(char jugador, int& fila, int& columna) { //Filas y columnas por referencia para devolver los movimientos ganadores
	// Verifica si el jugador especificado puede ganar en el siguiente movimiento
    // Busca líneas con 2 símbolos iguales y un espacio vacío
    
    // Verificar filas
    for (int i = 0; i < 3; i++) {
        int contador = 0, columna_vacia = -1; //Se cuentan las casillas del jugador y guarda columna vacia si existe
        //Recorre cada columna de la fila actual
        for (int j = 0; j < 3; j++) {
            if (matrizJuego[i][j] == jugador) contador++; //Incrementa si encuentra simbolo del jugador
            else if (matrizJuego[i][j] == ' ') columna_vacia = j; //Guarda posicion vacia
        }
        if (contador == 2 && columna_vacia != -1) { //Si hay dos fichas del jugador y una vacia es jugada ganadora
            fila = i;
            columna = columna_vacia;
            return true;
        }
    }

    // Verificar columnas
    for (int j = 0; j < 3; j++) {
        int contador = 0, fila_vacia = -1;
        //Recorre cada fila de la columna actual
        for (int i = 0; i < 3; i++) { //Se cuentan las casillas del jugador y guarda columna vacia si existe
            if (matrizJuego[i][j] == jugador) contador++; //Incrementa si encuentra simbolo del jugador
            else if (matrizJuego[i][j] == ' ') fila_vacia = i; //Guarda posicion vacia
        }
        if (contador == 2 && fila_vacia != -1) { //Si hay dos fichas del jugador y una vacia es jugada ganadora
            fila = fila_vacia;
            columna = j;
            return true;
        }
    }

    // Verificar diagonal principal
    int contador = 0, posicion_vacia = -1;
    for (int i = 0; i < 3; i++) {
        if (matrizJuego[i][i] == jugador) contador++; // Celda [0][0], [1][1], [2][2], si encuentra simbolo incrementa
        else if (matrizJuego[i][i] == ' ') posicion_vacia = i; //Guarda posicion vacia
    }
    if (contador == 2 && posicion_vacia != -1) { //Si hay dos fichas del jugador y una vacia es jugada ganadora
        fila = posicion_vacia;
        columna = posicion_vacia;
        return true;
    }

    // Verificar diagonal secundaria
    contador = 0;
    posicion_vacia = -1;
    for (int i = 0; i < 3; i++) { 
        if (matrizJuego[i][2-i] == jugador) contador++; // Celda [0][2], [1][1], [2][0], si encuentra simbolo incrementa 
        else if (matrizJuego[i][2-i] == ' ') posicion_vacia = i; //Guarda posicion vacia
    }
    if (contador == 2 && posicion_vacia != -1) { //Si hay dos fichas del jugador y una vacia es jugada ganadora
        fila = posicion_vacia;
        columna = 2-posicion_vacia;
        return true;
    }

    return false; // No se encontró movimiento ganador
}

// Función para elegir la mejor jugada
void mejorJugada(int& fila, int& columna) {
    // 1. Buscar jugada ganadora para la CPU (O)
    if (movimientoGanador('O', fila, columna)) return;
    
    // 2. Bloquear jugada ganadora del jugador (X)
    if (movimientoGanador('X', fila, columna)) return;
    
    // 3. Tomar el centro si está disponible 
    if (matrizJuego[1][1] == ' ') { //Si el centro esta vacio
        fila = 1; //Toma la coordenada de fila central
        columna = 1; //Toma la coordenada de columna central
        return;
    }
    
    // 4. Tomar una esquina si está disponible
    vector<pair<int, int>> esquinas = {{0,0}, {0,2}, {2,0}, {2,2}};
    random_shuffle(esquinas.begin(), esquinas.end()); //Se mezcla el orden de las esquinas para que no se elijan siempre las mismas
    for (auto pos : esquinas) { //Mira las esquinas
        if (matrizJuego[pos.first][pos.second] == ' ') { //Si la esquina esta vacia
            fila = pos.first; //Toma la coordenada de fila
            columna = pos.second;//Toma la coordenada de columna
            return;
        }
    }
    
    // 5. Tomar cualquier posición disponible
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (matrizJuego[i][j] == ' ') { //Si es vacio
                fila = i; //Toma esa coordenada de fila
                columna = j; //Toma esa coordenada de columna
                return;
            }
        }
    }
}

void cpu() {
    random_device rd; //Genera numeros aleatorios
    mt19937 gen(rd());//Se provee una semilla que evita que la secuencia sea predecible
    uniform_int_distribution<int> dist(0, 2); //Generara numeros entre 0 y 2, concordando con la matriz 3x3 del juego

    int fila = 0, columna = 0;
    bool juegoTerminado = false;
    playBackgroundMusic("musicatablero.wav"); //Se reproduce la musica de fondo para el juego
    
    turnoJugador1 = true;
    gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<jug1<<endl; //Mensaje para contador de jugador 1
    gotoxy (92, 7);cout<<"Victorias CPU: "<<cpu_puntaje<<endl; //Mensaje para contador de cpu
    
    //Mientras que el juego no haya terminado, se ejecutara toda la logica del modo
    while (!juegoTerminado) {
        if (turnoJugador1) {   //Turno del jugador
            gotoxy(posiciones[fila][columna][0], posiciones[fila][columna][1]); //Posiciona al jugador en las coordenadas x/y de cada casilla
            
            if (kbhit()) { //Detecta si se presiono una tecla
                int tecla = getch(); //Lee las teclas presionadas
                if (tecla == 224) { //Codigo especial de las flechas
                    tecla = getch();
                    switch (tecla) { //Maneja el movimiento del jugador
                        case 72: if (fila > 0) fila--; break; //Flecha arriba
                        case 80: if (fila < 2) fila++; break; //Flecha abajo
                        case 75: if (columna > 0) columna--; break; //Flecha izquierda
                        case 77: if (columna < 2) columna++; break; //Flecha derecha
                    }
                } else if (tecla == 13) { //Si la tecla es enter para colocar "X" u "O"
                    if (matrizJuego[fila][columna] == ' ') { //Si la celda esta vacia
                    	playEffect("sonidoboton.wav"); //Reproduce el sonido 
                        matrizJuego[fila][columna] = 'X'; //Se marca con X
                        dibujarSimbolo(fila, columna, 'X'); //Se dibuja el simbolo

                        if (hayGanador()) { //Si gana el jugador 1
                            gotoxy(35, 28);//Coordenada donde se imprime el mensaje
                            poner_color(9);
                            pauseBackgroundMusic(); //Se pausa la musica para poner el sonido de victoria
                            playEffect("victoria.wav");
                            cout << "Jugador 1 (X) gana!"; //Se imprime el mensaje de victoria
                            if (turnoJugador1){
                                jug1++; //Se le suma una victoria
                            }
                            gotoxy (92, 5);cout<<"Victorias Jugador 1: "<<jug1<<endl; //Se actualiza
                            getch(); 
                            juegoTerminado = true; //Se da por terminado el juego 
                            break;
                        } else if (hayEmpate()) { //Si hay empate
                            gotoxy(41, 28); //Coordenada donde se imprime el mensaje
                            cout << "Empate!"; //Se imprime el mensaje de empate
                            getch();
                            juegoTerminado = true; //Se da por terminado el juego
                            break;
                        }
                        turnoJugador1 = false; //Por cada enter, se le cede el turno a la cpu
                    }
                }
            }
        } else {
            gotoxy(32, 28); cout << "Turno de la CPU...         "; //Imprime el mensaje para indicar que es turno de la cpu
            Sleep(500);
            gotoxy(32, 28); cout << "                         "; //Se borra
            
            // La CPU decide su movimiento usando la estrategia mejorada
            mejorJugada(fila, columna);

            matrizJuego[fila][columna] = 'O'; //Se marca con O
            dibujarSimbolo(fila, columna, 'O'); //Dibuja la O
            
            if (hayGanador()) { //Si la CPU gana
                gotoxy(32, 28); cout << "                         "; //Borra primero el mensaje anterior
                gotoxy(38, 28); //Coordenada donde se imprime el mensaje de victoria de CPU
                poner_color(9);
                pauseBackgroundMusic(); //Se pausa la musica de fondo
                playEffect("victoriacpu.wav"); //Se reproduce el sonido de victoria de CPU, el cual es derrota para el jugador
                cout << "La CPU gana!";//Imprime el mensaje de victoria de CPU
                if (!turnoJugador1){
                    cpu_puntaje++; //Se le suma una victoria a la CPU
                }
                gotoxy (92, 7);cout<<"Victorias CPU: "<<cpu_puntaje<<endl;
                getch();
                juegoTerminado = true; //Se da por terminado el juego
                break;
            } else if (hayEmpate()) {
                gotoxy(32, 28); cout << "                         "; //Espacio para borrar el mensaje de turno de CPU
                gotoxy(41, 28); //Coordenada del mensaje de empate
                cout << "Empate!"; //Se imprime el mensaje de empate
                getch();
                juegoTerminado = true; //Se da por terminado el juego
                break;
            }
            turnoJugador1 = true; //Se da el turno al jugador 1
        }
        Sleep(50); //Para que no sean tan inmediatas las acciones de la cpu
    }
    mciSendString("close all", NULL, 0, NULL); //Cierra todo sonido

    char respuesta; 
    gotoxy(26, 28); cout << "Desea iniciar una nueva partida? (S/N): "; //Se pregunta al usuario si desea continuar
    cin >> respuesta;
    
    if (respuesta == 'S' || respuesta == 's') { //Si su respuesta es si
    	playEffect("sonidoboton.wav"); //Se reproduce sonido al haber seleccionado
        gotoxy(26, 28); cout << "                                         "; //Se borra el mensaje anterior
        reiniciarTablero(); //Se reinicia el tablero
        tablero(); //Se llama de nuevo a la funcion para iniciar un nuevo juego
        cpu(); //Se llama a logica del modo de juego
    } else {
    	playEffect("sonidoboton.wav");//Se reproduce sonido al haber seleccionado
        system("cls"); //Se borra todo y se muestran los creditos
        gotoxy (12,4); cout<<"Grupo Conformado por:"<<endl;
        gotoxy (12,6); cout<<"1. Fabian Coronel Morato"<<endl;
        gotoxy (12,8); cout<<"2. Andres Pomares Navarro"<<endl;
        gotoxy (12,10); cout<<"3. Cesar Beltran Alvarado"<<endl;
        gotoxy (12,12); cout<<"Clase: Programacion II"<<endl;
        gotoxy (10,14); cout<<"Profesor: Tomas Campo Cadernas"<<endl;
        gotoxy (6,16); cout<<"Institucion: Universidad del Magdalena"<<endl;
        gotoxy(15,18); cout << "Gracias por jugar!";
    }
}