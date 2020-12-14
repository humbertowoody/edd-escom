/**
 * practica-9.c - Archivo base de la práctica
 *
 * Práctica: 9
 * Objetivo: Programar la secuencia de Fibonacci recursiva.
 *
 * Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 14 de Diciembre del 2020
 */
#include <stdio.h> // Para operaciones de entrada y salida estándar.

// Prototipos de funciones.
long long int fibonacci(int);

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int valor;

  // Mensaje inicial.
  printf("Cálculo de Fibonacci\n\n");

  // Leer el dato inicial.
  printf("Ingresa el valor inicial: ");
  scanf("%i", &valor);

  // Imprimir el resultado.
  printf("El resultado de la función Fibonacci para %i es: %lli\n", valor, fibonacci(valor));

  // Mensaje final.
  printf("¡Gracias por utilizar este programa!\n\n");

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

// Implementación de funciones.

/**
 * Fibonacci
 * Calcula el resultado de la serie Fibonacci para un valor determinado.
 * @param valor El valor a calcular.
 * @returns Un long long int con el resultado.
 */
long long int fibonacci(int valor)
{
  // Caso base.
  if (valor <= 1)
  {
    return valor;
  }
  else
  {
    // Paso recursivo.
    return fibonacci(valor - 1) + fibonacci(valor - 2);
  }
}