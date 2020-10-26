/**
 * practica1.c - Archivo base de la práctica.
 *
 * Práctica: 1.
 * Objetivo: Realizar la impresión de una matriz de tamaño dinámico (n·m)
 * Equipo:
 *   - Téllez Castilla Laura Daniela (2020630527) <danycastilla27@gmail.com>
 *   - Ramos Mendoza Eduardo (2020630558) <eramosm1400@alumno.ipn.mx>
 *   - Joseph Judá Juanico González (2019630544) <josephjuanico503@gmail.com>
 *   - Humberto Alenadro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos
 * Grupo: 1CMX
 * Profesor: Alberto Alcántara.
 * ESCOM - IPN
 * 11/Oct/2020.
 */
#include <stdio.h>  // Para operaciones de I/O.
#include <stdlib.h> // Para usar malloc.

// Constante para determinar si nuestro programa finalizó correctamente.
#ifndef FIN_DE_PROGRAMA_CORRECTO
#define FIN_DE_PROGRAMA_CORRECTO 0
#endif

// Constante para determinar el número mínimo de filas válidas para nuestra matriz.
#ifndef MIN_FILAS
#define MIN_FILAS 1
#endif

// Constante para determinar el número máximo de filas válidas para nuestra matriz.
#ifndef MAX_FILAS
#define MAX_FILAS 10
#endif

// Constante para determinar el número mínimo de columnas válidas para nuestra matriz.
#ifndef MIN_COLS
#define MIN_COLS 1
#endif

// Constante para determinar el número máximo de columnas válidas para nuestra matriz.
#ifndef MAX_COLS
#define MAX_COLS 10
#endif

/**
 * Prototipos de funciones a utilizar en el programa.
 */
void imprimir_matriz(int **, int *, int);
void leer_filas_matriz(int **, int *, int);

/**
 * Función principal
 * En esta función incluímos la lógica de control base para el programa.
 */
int main(int argc, char *argv[])
{
  // Variables locales.
  int numero_filas;              // Número de filas especificado por el usuario para la matriz.
  int *numero_columnas_por_fila; // Arreglo con el número de columnas para cada fila dentro de la matriz.
  int **matriz;                  // Matriz de operaciones.

  // Mensajes de inicio.
  printf("Escuela Superior de Cómputo - IPN\n");
  printf("Estructuras de Datos - Alberto Alcántara\n");
  printf("Práctica 1: Realizar la impresión de una matriz de tamaño dinámico.\n");
  printf("Equipo:\n");
  printf("  - Téllez Castilla Laura Daniela (2020630527) <danycastilla27@gmail.com>\n");
  printf("  - Ramos Mendoza Eduardo (2020630558) <eramosm1400@alumno.ipn.mx>\n");
  printf("  - Joseph Judá Juanico González (2019630544) <josephjuanico503@gmail.com>\n");
  printf("  - Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>\n\n");

  // Rutina para leer el número de filas.
  do
  {
    printf("¿Cuántas filas tendrá la matriz?\n[%i - %i]> ", MIN_FILAS, MAX_FILAS);
    scanf("%i", &numero_filas);
  } while (numero_filas < MIN_FILAS || numero_filas > MAX_FILAS); // Validamos que el valor se encuentre en un rango aceptable.

  // Ajustamos dinámicamente la memoria asignada al arreglo con el número de columnas por fila.
  numero_columnas_por_fila = (int *)malloc(sizeof(int) * numero_filas);

  // Ajustamos dinámicamente la memoria asignada a la matriz.
  matriz = (int **)(malloc(sizeof(int *) * numero_filas));

  // Rutina para leer cada fila.
  leer_filas_matriz(matriz, numero_columnas_por_fila, numero_filas);

  // Corroboramos los datos con el usuario.
  printf("Se han leído correctamente los valores para %i filas.\n\n", numero_filas);

  // Imprimimos la matriz leída.
  printf("Matriz leída:\n");
  imprimir_matriz(matriz, numero_columnas_por_fila, numero_filas);

  // Imprimimos mensaje de finalización.
  printf("Fin del programa.\n");

  // Regresamos un valor no-erróneo (0) como "exit status".
  return FIN_DE_PROGRAMA_CORRECTO;
}

/**
 * Implementación de las funciones empleadas en el programa.
 */

/**
 * Leer Matriz
 * Esta función pregunta al usuario los valores que desea almacenar (sobreescribiendo si hubiera valores previos)
 * dentro de la matriz de forma secuencial.
 * Parámetros:
 *   - int ** matriz_final Un arreglo bidimensional dónde almacenaremos los datos.
 *   - int * columnas Un arreglo con el número de columnas para cada fila.
 *   - int filas El número de filas a leer.
 * Valor de retorno: void.
 */
void leer_filas_matriz(int **matriz_final, int *columnas, int filas)
{
  // Informar al usuario sobre la operación a realizar.
  printf("Se realizará la captura de %i filas en la matriz.\n\n", filas);

  // Recorremos la matriz.
  for (int fila_actual = 0; fila_actual < filas; fila_actual++)
  {
    // Preguntamos al usuario por el número de columnas para cada fila.
    do
    {
      printf("¿Cuántas columnas tendrá la fila %i?\n[%i - %i]> ", fila_actual + 1, MIN_COLS, MAX_COLS);
      scanf("%i", columnas + fila_actual);                                          // Evitamos hacer un &[] innecesario.
    } while (columnas[fila_actual] < MIN_COLS || columnas[fila_actual] > MAX_COLS); // Verificamos que el valor se encuentre dentro de un rango válido.

    // Imprimimos un mensaje de confirmación para el usuario.
    printf("Se leerán %i columnas para la fila %i.\n", columnas[fila_actual], fila_actual + 1);

    // Asignamos la memoria necesaria para las columnas especificadas.
    matriz_final[fila_actual] = (int *)malloc(sizeof(int) * columnas[fila_actual] + 1);

    // Realizamos la lectura de los valores para las columnas especificadas.
    for (int columna_actual = 0; columna_actual < columnas[fila_actual]; columna_actual++)
    {
      // Solicitamos el valor para la coordenada actual.
      printf("Introduce el valor para la fila %i, columna %i: ", fila_actual + 1, columna_actual + 1);

      // Almacenamos el valor en la coordenada actual.
      scanf("%i", &matriz_final[fila_actual][columna_actual]);
    }

    // Imprimimos un salto de línea.
    printf("\n");
  }
}

/**
 * Imprimir Matriz
 * Esta función imprime una matriz en la salida estándar utilizando notación de Teoría de Conjuntos.
 * Parámetros:
 *   - int ** matriz La matriz a imprimir.
 *   - int * columnas Un arreglo con el número de columnas para cada fila.
 *   - int filas El número de filas en la matriz.
 * Valor de retorno: void.
 */
void imprimir_matriz(int **matriz, int *columnas, int filas)
{
  // Corchete inicial.
  printf("{\n");

  // Recorremos la matriz.
  for (int fila_actual = 0; fila_actual < filas; fila_actual++)
  {
    // Corchete inicial para cada fila.
    printf("  {");
    for (int columna_actual = 0; columna_actual < columnas[fila_actual]; columna_actual++)
    {
      // Imprimimos el valor en la coordenada actual.
      printf("%i", matriz[fila_actual][columna_actual]);

      // Verificamos si es el último elemento por fila para determinar si imprimir, o no, una ','.
      if (columna_actual + 1 < columnas[fila_actual])
      {
        printf(",");
      }
    }
    // Corchete final para cada fila.
    printf("}");

    // Si es la última fila, no imprimimos una coma.
    if (fila_actual + 1 < filas)
    {
      printf(",");
    }

    // Salto de línea.
    printf("\n");
  }

  // Corchete final.
  printf("}\n");
}
