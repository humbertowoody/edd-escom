/**
 * practica-8.c - Archivo base de la práctica
 *
 * Práctica: 8
 * Objetivo: Implementar el código para realizar una multiplicación de forma
 *           recursiva.
 *
 * Alumno: Humberto Alejandro Ortega Alcocer
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 5 de Diciembre del 2020
 */
#include <stdio.h> // Para operaciones de entrada y salida.

// Prototipos de funciones.
int multiplicacion(int, int); // Producto de dos números de forma recursiva.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int numA, numB;

  // Mensaje inicial.
  printf("\tMultiplicación de dos números de forma recursiva.\n\n");
  
  // Leemos el primer número.
  printf("Ingrese el primer número: ");
  scanf("%i", &numA);

  // Leemos el segundo número.
  printf("Ingrese el segundo número: ");
  scanf("%i", &numB);
  
  // Mostramos el resultado.
  printf("El resultado de %i x %i = %i\n\n", numA, numB, multiplicacion(numA, numB));

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Multiplicación
 * Función para realizar la operación multiplicación de forma recursiva.
 * @param a El primer operando
 * @param b El segundo operando
 * @return El resultado de la operación
 */
int multiplicacion(int a, int b)
{
  // Caso base
  if (b <= 0)
  {
    return 0;
  }
  
  // Otro caso.
  return multiplicacion(a, b-1) + a;
}
