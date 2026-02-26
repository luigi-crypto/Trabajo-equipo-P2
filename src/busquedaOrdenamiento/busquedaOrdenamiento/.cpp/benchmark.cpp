/**
 * @file benchmark.cpp
 * @brief Implementaciones para sistema de benchmarking de algoritmos
 * @details Mide tiempos de ejecución y genera estadísticas de rendimiento
 */

#include "../.h/benchmark.h"
#include "../.h/sort.h"
#include "../.h/search.h"
#include "../.h/generator.h"

#include <chrono>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <functional>

using std::cout;
using std::endl;
using std::vector;
using std::string;
using Clock = std::chrono::high_resolution_clock;

/**
 * @brief Mide el tiempo de una única ejecución de función
 * @param fn Función a medir (lambda o std::function)
 * @return double Tiempo en milisegundos
 *
 * @complexity O(1) respecto a la medición, O(T(fn)) respecto a la función medida
 */
double medirUnaCorridaMs(const std::function<void()>& fn)
{
    auto t0 = Clock::now();
    fn();
    auto t1 = Clock::now();
    std::chrono::duration<double, std::milli> dt = t1 - t0;
    return dt.count();
}

/**
 * @brief Mide estadísticas de rendimiento sobre múltiples ejecuciones
 * @param fn Función a benchmarkear
 * @param repeticiones Número de repeticiones para estadísticas
 * @param warmup Repeticiones de calentamiento (default: 1)
 * @return Stats Estadísticas calculadas
 *
 * @complexity O(repeticiones × T(fn)) - Ejecuta fn múltiples veces
 * @spacecomplexity O(repeticiones) - Almacena tiempos en vector temporal
 */
Stats medirVariasCorridasMs(const std::function<void()>& fn, int repeticiones, int warmup)
{
    for (int i = 0; i < warmup; i++) fn();

    std::vector<double> t;
    t.reserve(repeticiones);

    for (int i = 0; i < repeticiones; i++)
        t.push_back(medirUnaCorridaMs(fn));

    double prom = std::accumulate(t.begin(), t.end(), 0.0) / t.size();

    double var = 0.0;
    for (double x : t) var += (x - prom) * (x - prom);
    var /= t.size();

    double mn = *std::min_element(t.begin(), t.end());
    double mx = *std::max_element(t.begin(), t.end());

    return { prom, std::sqrt(var), mn, mx };
}

/**
 * @brief Ejecuta benchmarks automáticos y exporta resultados a CSV
 *
 * @complexity Variable según los tamaños de prueba:
 * - Para cada tamaño n: O(n²) métodos cuadráticos, O(n log n) eficientes
 * - Total: O(Σ(n² + n log n)) para todos los tamaños de prueba
 *
 * @spacecomplexity O(n) - Crea copias temporales del arreglo para cada prueba
 *
 * @details
 * Ejecuta todos los algoritmos con tamaños predefinidos (1000, 5000, 10000)
 * y exporta estadísticas detalladas a resultados.csv
 */
void ejecutarBenchmarks()
{
    // Tamaños de prueba: N, N*N, N*M (ejemplo: 1000, 5000, 10000)
    std::vector<int> tamanios = { 1000, 5000, 10000 };
    int repeticiones = 10;

    std::ofstream csv("resultados.csv");
    csv << "algoritmo,n,promedio_ms,desviacion_ms,min_ms,max_ms\n";
    csv << std::fixed << std::setprecision(6);

    cout << "\n=== BENCHMARKS (tiempos en ms) ===\n";

    for (int n : tamanios)
    {
        cout << "\n--- n = " << n << " ---\n";

        std::vector<int> base = generarArreglo(n);

        auto medirOrdenamiento = [&](const string& nombre, auto sortFn)
            {
                Stats s = medirVariasCorridasMs([&]() {
                    std::vector<int> a = base;
                    sortFn(a);
                    }, repeticiones);

                cout << nombre << " -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
                csv << nombre << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
            };

        /// @complexity O(n²) - Burbuja cuadrático
        medirOrdenamiento("Burbuja", [&](std::vector<int>& a) {
            ordenarBurbuja(a.data(), (int)a.size(), false);
            });

        /// @complexity O(n²) - Selección cuadrático
        medirOrdenamiento("Seleccion", [&](std::vector<int>& a) {
            ordenarSeleccion(a.data(), (int)a.size(), false);
            });

        /// @complexity O(n²) peor, O(n) mejor - Inserción adaptable
        medirOrdenamiento("Insercion", [&](std::vector<int>& a) {
            ordenarInsercion(a.data(), (int)a.size(), false);
            });

        /// @complexity O(n log n) promedio, O(n²) peor - QuickSort
        medirOrdenamiento("QuickSort", [&](std::vector<int>& a) {
            int comp = 0, inter = 0;
            quickSort(a.data(), 0, (int)a.size() - 1, comp, inter, false);
            });

        /// @complexity O(n log n) garantizado - MergeSort
        medirOrdenamiento("MergeSort", [&](std::vector<int>& a) {
            int comp = 0;
            mergeSort(a.data(), 0, (int)a.size() - 1, comp, false);
            });

        // Búsqueda Secuencial
        {
            int valor = base[n / 2];
            Stats s = medirVariasCorridasMs([&]() {
                busquedaSecuencial(base.data(), (int)base.size(), valor, false);
                }, repeticiones);

            cout << "BusquedaSecuencial -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << "BusquedaSecuencial" << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        }

        // Búsqueda Binaria
        {
            std::vector<int> ordenado = base;
            std::sort(ordenado.begin(), ordenado.end());
            int valor = ordenado[n / 2];

            Stats s = medirVariasCorridasMs([&]() {
                busquedaBinaria(ordenado.data(), (int)ordenado.size(), valor, false);
                }, repeticiones);

            cout << "BusquedaBinaria -> " << s.promedio_ms << " ± " << s.desviacion_ms << " ms\n";
            csv << "BusquedaBinaria" << "," << n << "," << s.promedio_ms << "," << s.desviacion_ms << "," << s.min_ms << "," << s.max_ms << "\n";
        }
    }

    csv.close();
    cout << "\nListo. Se genero: resultados.csv\n";
}