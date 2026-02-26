/**
 * @file menu.cpp
 * @brief Implementaciones de funciones del menú interactivo y UI
 * @details Gestiona la interfaz de usuario, menús y visualización
 */

#include "../.h/menu.h"
#include "../.h/search.h"
#include "../.h/sort.h"
#include "../.h/generator.h"
#include "../.h/benchmark.h"

#include <iostream>
#include <vector>
#include <algorithm>

using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

/**
 * @brief Implementación de ejecutarMenuPrincipal
 * @details Bucle principal que muestra menú y distribuye opciones
 */
void ejecutarMenuPrincipal()
{
    int opcion;
    vector<int> arregloVec;
    int n = 0;
    bool verbose = false;

    arregloVec = generarArregloInteractivo(n);

    do
    {
        mostrarMenu();
        cin >> opcion;

        switch (opcion)
        {
        case 0:
            manejarRegeneracion(arregloVec, n, verbose);
            break;

        case 1:
            manejarBusquedaSecuencial(arregloVec, n, verbose);
            break;

        case 2:
            manejarBusquedaBinaria(arregloVec, n, verbose);
            break;

        case 3:
            manejarOrdenamiento(arregloVec, n, verbose);
            break;

        case 4:
            manejarBenchmarks();
            break;

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);
}

/**
 * @brief Implementación de manejarRegeneracion
 */
void manejarRegeneracion(vector<int>& arregloVec, int& n, bool& verbose)
{
    arregloVec = generarArregloInteractivo(n);
    cout << "Mostrar proceso paso a paso? (1=Si / 0=No): ";
    cin >> verbose;
}

/**
 * @brief Implementación de manejarBusquedaSecuencial
 */
void manejarBusquedaSecuencial(const vector<int>& arregloVec, int n, bool verbose)
{
    mostrarArreglo(arregloVec.data(), n);
    int valor = pedirValor();
    int posicion = busquedaSecuencial(arregloVec.data(), n, valor, verbose);

    if (posicion != -1)
        cout << "Valor encontrado en posicion: " << posicion << endl;
    else
        cout << "Valor no encontrado.\n";
}

/**
 * @brief Implementación de manejarBusquedaBinaria
 */
void manejarBusquedaBinaria(vector<int>& arregloVec, int n, bool verbose)
{
    cout << "\nOrdenando arreglo con burbuja...\n";
    ordenarBurbuja(arregloVec.data(), n, verbose);
    mostrarArreglo(arregloVec.data(), n);

    int valor = pedirValor();
    int posicion = busquedaBinaria(arregloVec.data(), n, valor, verbose);

    if (posicion != -1)
        cout << "Valor encontrado en posicion: " << posicion << endl;
    else
        cout << "Valor no encontrado.\n";
}

/**
 * @brief Implementación de manejarOrdenamiento
 */
void manejarOrdenamiento(vector<int>& arregloVec, int n, bool verbose)
{
    int metodo = mostrarMenuOrdenamiento();
    int comparaciones = 0;
    int intercambios = 0;

    if (metodo == 1)
    {
        ordenarBurbuja(arregloVec.data(), n, verbose);
    }
    else if (metodo == 2)
    {
        ordenarSeleccion(arregloVec.data(), n, verbose);
    }
    else if (metodo == 3)
    {
        ordenarInsercion(arregloVec.data(), n, verbose);
    }
    else if (metodo == 4)
    {
        quickSort(arregloVec.data(), 0, n - 1, comparaciones, intercambios, verbose);
        cout << "Comparaciones: " << comparaciones << endl;
        cout << "Intercambios: " << intercambios << endl;
    }
    else if (metodo == 5)
    {
        mergeSort(arregloVec.data(), 0, n - 1, comparaciones, verbose);
        cout << "Comparaciones: " << comparaciones << endl;
    }
    else
    {
        cout << "Metodo invalido.\n";
    }

    cout << "\nArreglo ordenado:\n";
    mostrarArreglo(arregloVec.data(), n);
}

/**
 * @brief Implementación de manejarBenchmarks
 */
void manejarBenchmarks()
{
    ejecutarBenchmarks();
}

/**
 * @brief Implementación de mostrarMenu
 * @brief Muestra el menú principal de opciones
 */
void mostrarMenu()
{
    cout << "\n=== MENU PRINCIPAL ===\n";
    cout << "0) Regenerar arreglo\n";
    cout << "1) Busqueda Secuencial\n";
    cout << "2) Busqueda Binaria (con ordenamiento burbuja)\n";
    cout << "3) Ordenamiento\n";
    cout << "4) Benchmarks automaticos\n";
    cout << "5) Salir\n";
    cout << "Elige opcion: ";
}

/**
 * @brief Implementación de mostrarMenuOrdenamiento
 * @brief Muestra el submenú de métodos de ordenamiento
 * @return int Opción seleccionada por el usuario (1-5)
 */
int mostrarMenuOrdenamiento()
{
    cout << "\n=== METODOS DE ORDENAMIENTO ===\n";
    cout << "1) Burbuja\n";
    cout << "2) Seleccion\n";
    cout << "3) Insercion\n";
    cout << "4) QuickSort\n";
    cout << "5) MergeSort\n";
    cout << "Elige metodo (1-5): ";

    int metodo;
    cin >> metodo;
    return metodo;
}

/**
 * @brief Implementación de pedirValor
 * @brief Solicita al usuario un valor entero para búsqueda
 * @return int Valor ingresado por el usuario
 */
int pedirValor()
{
    cout << "Ingresa valor a buscar: ";
    int valor;
    cin >> valor;
    return valor;
}

/**
 * @brief Implementación de mostrarArreglo
 * @brief Muestra el contenido de un arreglo en pantalla
 * @param arr Puntero al arreglo de enteros
 * @param n Tamaño del arreglo
 */
void mostrarArreglo(const int* arr, int n)
{
    cout << "Arreglo: ";
    for (int i = 0; i < n && i < 20; ++i)
    {
        cout << arr[i] << " ";
    }
    if (n > 20) cout << "... (" << n << " elementos totales)";
    cout << endl;
}