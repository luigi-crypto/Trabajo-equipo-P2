/**
 * @file generator.cpp
 * @brief Implementaciones para generación de arreglos aleatorios
 * @details Gestiona la creación de arreglos con diferentes configuraciones
 */

#include "../.h/generator.h"

#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <limits>

using std::cout;
using std::cin;
using std::endl;
using std::vector;

/**
 * @brief Generador de números aleatorios global (singleton)
 * @return std::mt19937& Referencia al generador inicializado
 * @complexity O(1) - Inicialización lazy una sola vez
 */
std::mt19937& rngGlobal() {
    static std::mt19937 rng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());
    return rng;
}

/**
 * @brief Genera un arreglo de enteros aleatorios
 * @param n Tamaño del arreglo
 * @param minVal Valor mínimo (default: 1)
 * @param maxVal Valor máximo (default: 100000)
 * @return std::vector<int> Vector con valores aleatorios
 *
 * @complexity O(n) - Genera n números aleatorios secuencialmente
 * @spacecomplexity O(n) - Almacena n enteros en el vector
 */
std::vector<int> generarArreglo(int n, int minVal, int maxVal)
{
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) a[i] = dist(rngGlobal());
    return a;
}

/**
 * @brief Menú interactivo para generar arreglos con diferentes configuraciones
 * @param outN Parámetro de salida con el tamaño final del arreglo
 * @return std::vector<int> Arreglo generado según especificaciones del usuario
 *
 * @complexity O(n) o O(rango) según el modo seleccionado
 * @spacecomplexity O(n) - Retorna vector del tamaño solicitado
 */
std::vector<int> generarArregloInteractivo(int& outN)
{
    static std::random_device rd;
    static std::mt19937 rng(rd());

    cout << "\n=== GENERADOR DE ARREGLOS ALEATORIOS ===\n";
    cout << "Tamanos disponibles:\n";
    cout << "1) N\n";
    cout << "2) N*N\n";
    cout << "3) N*M\n";

    auto leerEnteroRango = [&](const std::string& prompt, int minV, int maxV) -> int {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x && x >= minV && x <= maxV) return x;
            cout << "Entrada invalida. Debe estar entre " << minV << " y " << maxV << ".\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        };

    auto leerEnteroSeguro = [&](const std::string& prompt, int minPermitido) -> int {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x && x >= minPermitido) return x;
            cout << "Entrada invalida. Debe ser un entero >= " << minPermitido << ".\n";
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        };

    int tipo = leerEnteroRango("Elige tipo (1-3): ", 1, 3);
    int N = leerEnteroSeguro("Ingresa N (>=1): ", 1);
    int M = 1;
    if (tipo == 3) M = leerEnteroSeguro("Ingresa M (>=1): ", 1);

    // Calcular tamaño: N, N*N, o N*M
    long long size = 0;
    if (tipo == 1) size = (long long)N;
    else if (tipo == 2) size = (long long)N * (long long)N;
    else size = (long long)N * (long long)M;

    // Límite de seguridad: 5 millones de elementos
    const long long LIM = 5'000'000;
    if (size > LIM) {
        cout << "AVISO: Tamaño limitado a " << LIM << " elementos\n";
        size = LIM;
    }

    cout << "\nModo de generacion:\n";
    cout << "1) Permitir repetidos\n";
    cout << "2) NO permitir repetidos\n";
    int modo = leerEnteroRango("Elige modo (1-2): ", 1, 2);

    cout << "\nDefine el rango de valores:\n";
    int minVal = leerEnteroSeguro("Min: ", -1'000'000);
    int maxVal = leerEnteroSeguro("Max: ", -1'000'000);

    std::vector<int> arr;
    arr.reserve((size_t)size);

    if (modo == 1) {
        // Con repetidos: O(n)
        if (minVal > maxVal) std::swap(minVal, maxVal);
        std::uniform_int_distribution<int> dist(minVal, maxVal);
        for (size_t i = 0; i < (size_t)size; ++i)
            arr.push_back(dist(rng));
    }
    else {
        // Sin repetidos: O(rango) donde rango = maxVal - minVal + 1
        if (minVal > maxVal) std::swap(minVal, maxVal);
        long long rango = (long long)maxVal - (long long)minVal + 1LL;
        if (rango < size) maxVal = minVal + (int)size - 1;

        std::vector<int> pool;
        for (int x = minVal; x <= maxVal; ++x) pool.push_back(x);
        std::shuffle(pool.begin(), pool.end(), rng);
        pool.resize((size_t)size);
        arr = std::move(pool);
    }

    outN = (int)size;
    cout << "Arreglo generado con tamano: " << outN << "\n";
    return arr;
}