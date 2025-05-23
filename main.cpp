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
    
    int modo;
    menu();
    leerModo(modo);
    return 0;
}