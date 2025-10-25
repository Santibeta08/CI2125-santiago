#include <iostream>
using namespace std;

/**
 * Esta es la función que hicimos.
 * Imprime tu nombre, carnet y un valor de verdad.
 */
void my_info(int mode, bool b) {
    
    // 1. Imprimimos el nombre
    cout << "Santiago ";
    
    // 2. Imprimimos el carnet
    cout << 2110071;

    // 3. Revisamos las condiciones
    if (mode == 1) {
        if (b == true) {
            cout << " verdadero";
        } else {
            cout << " falso";
        }
    } else { // Si mode NO es 1
        if (b == true) {
            cout << " true";
        } else {
            cout << " false";
        }
    }
    
    // Agregamos un salto de línea
    cout << endl; 
}


/**
 * Esta es la función principal.
 * El programa SIEMPRE empieza a ejecutar desde aquí.
 */
int main() {
    
    cout << "--- Iniciando Pruebas ---" << endl;

    // Prueba 1: mode = 1 y b = true
    // Debería imprimir: Santiago2110071verdadero
    cout << "Prueba 1: ";
    my_info(1, true);

    // Prueba 2: mode = 1 y b = false
    // Debería imprimir: Santiago2110071falso
    cout << "Prueba 2: ";
    my_info(1, false);

    // Prueba 3: mode = 5 (distinto de 1) y b = true
    // Debería imprimir: Santiago2110071true
    cout << "Prueba 3: ";
    my_info(5, true);

    // Prueba 4: mode = 0 (distinto de 1) y b = false
    // Debería imprimir: Santiago2110071false
    cout << "Prueba 4: ";
    my_info(0, false);

    cout << "--- Pruebas Terminadas ---" << endl;

    return 0; // Indica que el programa terminó bien
}