#include <iostream>
#include <windows.h>
#include "interfaz.h"
#include "gotoxy.h"
#include "logica.h"
#include "modo.h"

using namespace std;

int main() {
    keybd_event(VK_MENU, 0, 0, 0);
    keybd_event(VK_RETURN, 0, 0, 0);
    keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
    
    int modo; //Se define la variable modo que esta siendo usada como referencia
    menu();  // Se llama al menu
    leerModo(modo); //Se selecciona el modo e inicia el juego
    return 0;
}