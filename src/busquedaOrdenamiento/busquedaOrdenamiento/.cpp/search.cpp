#include "../.h/search.h"
#include <iostream>

using namespace std;

int busquedaSecuencial(const int* arr, int n, int valor, bool verbose)
{
    // tu implementación aquí (no debe modificar arr[])
    for (int i = 0; i < n; i++) {
        if (arr[i] == valor) return i;  // lectura solo, no modifica
    }
    return -1;
}


int busquedaBinaria(int arreglo[], int n, int valor, bool verbose)
{
    // 0/ Busca dividiendo el rango (requiere arreglo ordenado)
    int izquierda = 0;
    int derecha = n - 1;

    while (izquierda <= derecha)
    {
        int medio = (izquierda + derecha) / 2;

        if (verbose)
            cout << "[Binaria] izq=" << izquierda << " der=" << derecha
                 << " medio=" << medio << " valMedio=" << arreglo[medio] << "\n";

        if (arreglo[medio] == valor) return medio;
        else if (arreglo[medio] < valor) izquierda = medio + 1;
        else derecha = medio - 1;
    }

    return -1;
}