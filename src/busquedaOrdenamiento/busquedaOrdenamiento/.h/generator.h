#pragma once
/**
 * @file generator.h
 * @brief Declaraciones para generación de arreglos aleatorios
 */

#ifndef GENERATOR_H
#define GENERATOR_H

#include <vector>
#include <random>

 /**
  * @brief Genera un arreglo de enteros aleatorios
  * @param n Tamaño del arreglo
  * @param minVal Valor mínimo (default: 1)
  * @param maxVal Valor máximo (default: 100000)
  * @return std::vector<int> Vector con valores aleatorios
  * @complexity O(n)
  */
std::vector<int> generarArreglo(int n, int minVal = 1, int maxVal = 100000);

/**
 * @brief Menú interactivo para generar arreglos con diferentes configuraciones
 * @param outN Parámetro de salida con el tamaño final del arreglo
 * @return std::vector<int> Arreglo generado según especificaciones del usuario
 * @complexity O(n) o O(rango) según el modo seleccionado
 */
std::vector<int> generarArregloInteractivo(int& outN);

/**
 * @brief Generador de números aleatorios global (singleton)
 * @return std::mt19937& Referencia al generador inicializado
 * @complexity O(1)
 */
std::mt19937& rngGlobal();

#endif // GENERATOR_H