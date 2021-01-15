/**
 * practica-10.c - Archivo base de la práctica
 *
 * Práctica: 10
 * Objetivo: Programar el algoritmo de las torres de Hanoi para mover N discos entre 3 agujas
 *           mostrando las instrucciones para realizar el procedimiento.
 *
 * Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 14 de Enero del 2021
 */
#include <stdio.h> // Para operaciones de entrada y salida estándar.

// Constantes de operación.
#define AGUJA_ORIGEN_INICIAL 'A'
#define AGUJA_DESTINO_INICIAL 'C'
#define AGUJA_AUXILIAR_INICIAL 'B'

// Prototipos de funciones
void hanoi(int, char, char, char); // Función recursiva para procedimiento de las torres de Hanoi.

// Función principal.
int main()
{
  // Variables locales.
  int numeroDeDiscos;

  // Mensaje de inicio.
  printf("Práctica 10 - Torres de Hanoi\n\n");

  // Leemos el número de discos para realizar la operación.
  printf("¿Cuántos discos desea utilizar?\n>");
  scanf("%i", &numeroDeDiscos);

  // Mostramos las etiquetas correspondientes a las agujas.
  printf("\n\t~ Aguja origen: %c\n", AGUJA_ORIGEN_INICIAL);
  printf("\t~ Aguja destino: %c\n", AGUJA_DESTINO_INICIAL);
  printf("\t~ Aguja auxiliar: %c\n\n", AGUJA_AUXILIAR_INICIAL);

  // Mensaje inicial.
  printf("Pasos para trasladar %i discos de %c hacia %c usando %c como auxiliar:\n\n", numeroDeDiscos, AGUJA_ORIGEN_INICIAL, AGUJA_DESTINO_INICIAL, AGUJA_AUXILIAR_INICIAL);

  // Realizamos la llamada inicial a la función.
  hanoi(numeroDeDiscos, AGUJA_ORIGEN_INICIAL, AGUJA_DESTINO_INICIAL, AGUJA_AUXILIAR_INICIAL);

  // En este punto, la ejecución de nuestro programa fue exitosa, exit status = 0.
  return 0;
}

/**
 * Hanoi
 * Función recursiva que realiza el procedimiento para resolver el problema de las Torres de Hanoi
 * con un número variable de discos y con etiquetas para cada una de las agujas.
 * @param numeroDeDiscos Un entero mayor a cero que indica el número de discos para el programa.
 * @param agujaOrigen Un caracter con el nombre de la aguja origen.
 * @param agujaDestino Un caracter con el nombre de la aguja destino.
 * @param agujaAuxiliar Un caracter con el nombre de la aguja auxiliar
 */
void hanoi(int numeroDeDiscos, char agujaOrigen, char agujaDestino, char agujaAuxiliar)
{
  // Caso base de recursividad.
  if (numeroDeDiscos <= 1)
  {
    printf("Mover el disco 1 desde la aguja %c a la aguja %c\n", agujaOrigen, agujaDestino);
    return;
  }

  // Paso recursivo.
  hanoi(numeroDeDiscos - 1, agujaOrigen, agujaAuxiliar, agujaDestino);
  printf("Mover el disco %i desde la aguja %c a la aguja %c\n", numeroDeDiscos, agujaOrigen, agujaDestino);
  hanoi(numeroDeDiscos - 1, agujaAuxiliar, agujaDestino, agujaOrigen);
}