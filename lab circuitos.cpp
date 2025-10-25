#include <iostream>
#include <iomanip>

int op_or(int p, int q) {
    return p || q;
}

int op_and(int p, int q) {
    return p && q;
}

int op_nand(int p, int q) {
    return !(p && q);
}

int D(int x, int y, int z) {
    int out_OR = op_or(x, y);
    int out_NAND = op_nand(y, z);
    int r = op_and(out_OR, out_NAND);
    return r;
}

int main() {
    std::cout << "Tabla de Verdad del Circuito D (C++)" << std::endl;
    std::cout << "---------------------------------" << std::endl;
    std::cout << "| x | y | z |  r = D(x,y,z) |" << std::endl;
    std::cout << "---------------------------------" << std::endl;

    for (int x = 1; x >= 0; --x) {
        for (int y = 1; y >= 0; --y) {
            for (int z = 1; z >= 0; --z) {
                std::cout << "| " << x << " | " << y << " | " << z << " |       "
                          << D(x, y, z) << "       |" << std::endl;
            }
        }
    }
    std::cout << "---------------------------------" << std::endl;
    return 0;
}