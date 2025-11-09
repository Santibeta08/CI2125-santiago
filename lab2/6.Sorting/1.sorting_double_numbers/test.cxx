///
/// test.cxx
///
/// programa para probar el ordenamiento de datos de tipo 'double' (punto flotante de doble precisión)
///
/// @@@ NOTA: La idea es que este programa funcione como lo hace el ordenamiento de datos enteros
/// la única diferencia es que aqui lo hacemos con valores de punto flotante de doble precisión
///

#include <cstdio>
#include <cstdlib>

#include "sort_double.h"

using std::vector;

// Un simple generador de numeros aleatorios
// de acuerdo a la distribucion uniforme estandard: 0 <= x <= 1
double uniform() {
    double numerator = double(rand());
    double denominator = double(RAND_MAX);
    return numerator / denominator;
}

// Un simple generador de numeros aleatorios en el intervalo [lb .. ub]
// Asume (sin chequear) que lb es menor o igual a ub
double random(double lb, double ub) {
    return (ub - lb) * uniform() + lb;
}

// genera el vector (muestra) de datos para la prueba de ordenamiento
vector<double> generate_vector(int n) {
    vector<double> data = {};
    for (int i = 0; i < n; ++i) {
        double x = random(-8.0, 8.0);
        data.push_back(x);
    }
    return data;
}

// @@@ TIP
// En lo que sigue, usen el ejemplo de ordenamiento de datos enteros como inspiración.
// Pueden copiar las partes que deben completar, PERO ..
// .. no olviden que ahora estan trabajando con datos de tipo 'double' en vez de 'int'

// @@@ TAREA: implementar la funcion 'show' que muestra el vector
void show(const char *label, const vector<double>& data) {
    fprintf(stdout, "%s:\n", label);
    const int n = data.size();
    for (int i = 0; i < n; ++i) {
        double x = data[i];
        // Usamos %10.6f para alinear: 10 de ancho total, 6 dígitos de precisión
        fprintf(stdout, " %10.6f", x);
        if ((i + 1) % 8 == 0 || i == n - 1) {
            fprintf(stdout, "\n");
        }
    }
}

void run(int n) {
    // @@@ TAREA: completar
    vector<double> data = generate_vector(n);
    show("Datos (antes)", data);
    selection_sort(data);
    show("Datos (después)", data);
}

void bad_usage(const char *program) {
    fprintf(stderr, "uso: %s n (para 0 <= n < 128)\n", program);
}

int main(int argc, const char *argv[]) {
    // @@@ TAREA: completar
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