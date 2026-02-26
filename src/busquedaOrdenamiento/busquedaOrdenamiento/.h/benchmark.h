#pragma once
/**
 * @file benchmark.h
 * @brief Declaraciones para sistema de benchmarking de algoritmos
 */

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <functional>
#include <vector>

 /**
  * @struct Stats
  * @brief Estructura para almacenar estadísticas de rendimiento
  * @complexity O(1) - Solo almacena 4 valores double
  */
struct Stats {
    double promedio_ms;      ///< Promedio de tiempo en milisegundos
    double desviacion_ms;    ///< Desviación estándar
    double min_ms;           ///< Tiempo mínimo registrado
    double max_ms;           ///< Tiempo máximo registrado
};

/**
 * @brief Mide el tiempo de una única ejecución de función
 * @param fn Función a medir (lambda o std::function)
 * @return double Tiempo en milisegundos
 * @complexity O(1) respecto a la medición, O(T(fn)) respecto a la función medida
 */
double medirUnaCorridaMs(const std::function<void()>& fn);

/**
 * @brief Mide estadísticas de rendimiento sobre múltiples ejecuciones
 * @param fn Función a benchmarkear
 * @param repeticiones Número de repeticiones para estadísticas
 * @param warmup Repeticiones de calentamiento (default: 1)
 * @return Stats Estadísticas calculadas
 * @complexity O(repeticiones × T(fn))
 */
Stats medirVariasCorridasMs(const std::function<void()>& fn, int repeticiones, int warmup = 1);

/**
 * @brief Ejecuta benchmarks automáticos y exporta resultados a CSV
 * @complexity Variable según los tamaños de prueba
 * @spacecomplexity O(n) - Crea copias temporales del arreglo para cada prueba
 */
void ejecutarBenchmarks();

#endif // BENCHMARK_H