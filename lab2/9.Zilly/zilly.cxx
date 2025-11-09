///
/// Zilly in C++
///
/// A partial emulation of Zilly in C++, with sample usage
///

#include <cstdio>

/// Emulator

typedef int Z;

/// Zilly primitive functions | Funciones primitivas de Zilly

// less than | menor que
Z lt(Z n, Z k) {
    // return k < n;
    return k < n ? 1 : 0; // just in case ..
}

// subtract | resta
Z sub(Z n, Z k) {
    return k - n;
}

/// Programmer defined functions | Funciones definidas por el programador

Z chs(Z n) {
    return sub(n, 0);
}

Z add(Z n, Z k) {
    return sub(chs(n), k);
}

/// Test cases | Casos de prueba

void test00() {
    fprintf(stdout, "lt(0, -1) ==> %d\n", lt(0, -1));
    fprintf(stdout, "lt(0,  0) ==> %d\n", lt(0,  0));
    fprintf(stdout, "lt(0,  1) ==> %d\n", lt(0,  1));
}

void test01() {
    fprintf(stdout, "sub( 0, 67) ==> %d\n", sub( 0, 67));
    fprintf(stdout, "sub(67,  0) ==> %d\n", sub(67,  0));
    fprintf(stdout, "sub(42, 67) ==> %d\n", sub(42, 67));
    fprintf(stdout, "sub(67, 42) ==> %d\n", sub(67, 42));
    fprintf(stdout, "sub(42,  0) ==> %d\n", sub(42,  0));
    fprintf(stdout, "sub(42,  0) ==> %d\n", sub(42,  0));
}

void test02() {
    Z r1 = 42 - (67 - 25);
    Z r2 = sub(sub(25, 67), 42); // traducción de la anterior, usando sólo las primitivas de Zilly

    fprintf(stdout, "C++ : %d | Zilly: %d\n", r1, r2);
}

void test03() {
    Z r1 = 1024 - 512 - (67 - (42 - 512));
    
    // <== Ejercicio: deben traducir la expresión anterior usando sólo las primitivas de Zilly
    // r1 = (1024 - 512) - (67 - (42 - 512))
    // k1 = sub(512, 1024)
    // k2_inner = sub(512, 42)
    // k2 = sub(k2_inner, 67) -> sub(sub(512, 42), 67)
    // r2 = sub(k2, k1)
    Z r2 = sub(sub(sub(512, 42), 67), sub(512, 1024));

    fprintf(stdout, "C++ : %d | Zilly: %d\n", r1, r2);
}

void test04() {
    // Ejercicio: defina más casos de prueba .. por ejemplo, para funciones definidas por el programador
    fprintf(stdout, "\n--- Pruebas test04 (definidas por programador) ---\n");
    
    // Pruebas para chs(n) -> 0 - n
    fprintf(stdout, "chs(42)  ==> %d\n", chs(42));   // Esperado: -42
    fprintf(stdout, "chs(-42) ==> %d\n", chs(-42));  // Esperado: 42
    fprintf(stdout, "chs(0)   ==> %d\n", chs(0));    // Esperado: 0

    // Pruebas para add(n, k) -> k + n
    fprintf(stdout, "add(10, 5)   ==> %d\n", add(10, 5));     // Esperado: 15
    fprintf(stdout, "add(10, -5)  ==> %d\n", add(10, -5));    // Esperado: 5
    fprintf(stdout, "add(-10, 5)  ==> %d\n", add(-10, 5));    // Esperado: -5
    fprintf(stdout, "add(-10, -5) ==> %d\n", add(-10, -5));   // Esperado: -15
}

int main() {
    test00();
    test01();
    test02();
    test03();
    test04(); // <-- Llamada a la nueva función de prueba
    return 0;
}