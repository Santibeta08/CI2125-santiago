///
/// sort_string.cxx
///

#include "sort_string.h"

#include <cstdio>

using std::string;
using std::vector;

int min(int lb, int ub, const vector<string>& data) {
    // @@@ TAREA: completar
    const int n = data.size();

    // Chequeo de precondiciones
    if (n == 0) {
        return -1;
    }
    if (lb < 0 || lb >= ub) {
        return -1;
    }
    if (ub > n) {
        return -1;
    }

    // Algoritmo para conseguir el índice del menor elemento
    int mindex = lb;
    string minimum = data[mindex]; // <-- TIPO STRING

    for (int i = lb + 1; i < ub; ++i) {
        // C++ compara strings alfabéticamente por defecto
        if (data[i] < minimum) {
            mindex = i;
            minimum = data[mindex]; // <-- TIPO STRING
        }
    }
    return mindex;
}

int min(const vector<string>& data) {
    const int n = data.size();
    int index = min(0, n, data);
    if (index < 0) {
        exit(EXIT_FAILURE);
    }
    return index;
}

void selection_sort(vector<string>& data) {
    // @@@ TAREA: completar
    const int n = data.size();
    if (n == 0) {
        return;
    }

    for (int i = 0; i < n - 1; ++i) {
        
        int mindex = min(i, n, data);

        {
            // swap data[i] <-> data[mindex]
            string tmp = data[i]; // <-- TIPO STRING
            data[i] = data[mindex];
            data[mindex] = tmp;
        }
    }
}