#pragma once
/**
 * @file menu.h
 * @brief Declaraciones de funciones para el menú interactivo del programa
 * @details Gestiona la interfaz de usuario, menús principales y submenús
 */

#ifndef MENU_H
#define MENU_H

#include <vector>

 /**
  * @brief Ejecuta el bucle principal del menú interactivo
  * @details Controla el flujo principal del programa mostrando opciones
  *          y delegando a las funciones correspondientes
  * @complexity O(k × n²) peor caso, O(k × n log n) promedio donde k es
  *             la cantidad de operaciones del usuario
  */
void ejecutarMenuPrincipal();

/**
 * @brief Maneja la opción de regenerar el arreglo
 * @param arregloVec Referencia al vector de enteros a regenerar
 * @param n Referencia al tamaño actual del arreglo
 * @param verbose Referencia al flag de modo detallado
 * @complexity O(n) - Depende del tamaño del nuevo arreglo generado
 */
void manejarRegeneracion(std::vector<int>& arregloVec, int& n, bool& verbose);

/**
 * @brief Ejecuta búsqueda secuencial sobre el arreglo
 * @param arregloVec Vector de enteros (puede estar desordenado)
 * @param n Tamaño del arreglo
 * @param verbose Si true, muestra proceso paso a paso
 * @complexity O(n) - Búsqueda lineal completa en peor caso
 */
void manejarBusquedaSecuencial(const std::vector<int>& arregloVec, int n, bool verbose);

/**
 * @brief Ordena con burbuja y ejecuta búsqueda binaria
 * @param arregloVec Vector de enteros (se modifica ordenándolo)
 * @param n Tamaño del arreglo
 * @param verbose Si true, muestra proceso paso a paso
 * @complexity O(n²) - Dominado por ordenamiento burbuja
 */
void manejarBusquedaBinaria(std::vector<int>& arregloVec, int n, bool verbose);

/**
 * @brief Muestra menú de ordenamiento y ejecuta método seleccionado
 * @param arregloVec Vector de enteros a ordenar (se modifica)
 * @param n Tamaño del arreglo
 * @param verbose Si true, muestra proceso paso a paso
 * @complexity Variable: O(n²) a O(n log n) según método elegido
 */
void manejarOrdenamiento(std::vector<int>& arregloVec, int n, bool verbose);

/**
 * @brief Ejecuta benchmarks automáticos y exporta resultados
 * @complexity O(Σ(n² + n log n)) para todos los tamaños de prueba
 */
void manejarBenchmarks();

/**
 * @brief Muestra el menú principal de opciones
 * @complexity O(1) - Solo impresión de texto
 */
void mostrarMenu();

/**
 * @brief Muestra el submenú de métodos de ordenamiento
 * @return int Opción seleccionada por el usuario (1-5)
 * @complexity O(1) - Solo impresión y lectura
 */
int mostrarMenuOrdenamiento();

/**
 * @brief Solicita al usuario un valor entero para búsqueda
 * @return int Valor ingresado por el usuario
 * @complexity O(1) - Operación de I/O
 */
int pedirValor();

/**
 * @brief Muestra el contenido de un arreglo en pantalla
 * @param arr Puntero al arreglo de enteros
 * @param n Tamaño del arreglo
 * @complexity O(n) - Recorre todo el arreglo para mostrarlo
 */
void mostrarArreglo(const int* arr, int n);

#endif // MENU_H