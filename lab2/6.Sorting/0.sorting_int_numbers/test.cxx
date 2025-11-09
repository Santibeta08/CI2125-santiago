///
/// test.cxx
///
/// programa para probar el ordenamiento de datos de tipo 'int' (enteros)
///

#include <cstdio>
#include <cstdlib>

#include "sort_int.h"

using std::vector;

// Un simple generador de numeros aleatorios en el intervalo [lb .. ub]
int random(int lb, int ub) {
    int range = ub - lb + 1;
    return (rand() % range) + lb;
}

// genera el vector (muestra) de datos para la prueba de ordenamiento
vector<int> generate_vector(int n) {
    vector<int> data = {}; // inicializamos el vector como una lista vacía
    for (int i = 0; i < n; ++i) {
        int x = random(-16, 16);
        data.push_back(x);
    }
    return data;
}

// muestra el vector
void show(const char *label, const vector<int>& data) {
    fprintf(stdout, "%s:\n", label); // imprimimos la etiqueta
    const int n = data.size();
    for (int i = 0; i < n; ++i) {
        int x = data[i];
        fprintf(stdout, " %3d", x); // imprimimos cada elemento con 3 espacios de ancho
        if ((i + 1) % 16 == 0 || i == n - 1) {
            fprintf(stdout, "\n"); // 16 elementos por linea, o si es el último
        }
    }
}

// corre el programa
void run(int n) {
    vector<int> data = generate_vector(n);
    show("Datos (antes)", data);
    selection_sort(data);
    show("Datos (después)", data);
}

// procesa la linea de comandos
void bad_usage(const char *program) {
    fprintf(stderr, "uso: %s n (para 0 <= n < 128)\n", program);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        bad_usage(argv[0]);
        return 2;
    }
    int n = atoi(argv[1]);
    if (n < 0 || n >= 128) {
        bad_usage(argv[0]);
        return 2;
    }
    run(n);
    return 0;
}