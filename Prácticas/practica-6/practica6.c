/**
 * practica6.c - Archivo base de la práctica
 *
 * Práctica: 5
 * Objetivo: Implementar una cola estática circular.
 *
 * Equipo:
    - Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 19/Noviembre/2020
*/
#include <stdio.h>  // Para operaciones de entrada y salida estándar.
#include <stdlib.h> // Para usar `malloc` etc...
#include <string.h> // Para usar `strcpy` etc...

// Constantes de operación
#define MENU_SALIR 4            // Opción para salir del programa.
#define MENU_INSERTAR 1         // Opción para la operación "insertar"
#define MENU_ELIMINAR 2         // Opción para la operación "eliminar"
#define MENU_IMPRIMIR 3         // Opción para la operación "imprimir"
#define BANDERA_COLA_VACIA '\0' // Bandera para cuando la cola está vacía.
#define TAM_MAX_CADENAS 100     // El tamaño máximo para las cadenas del programa, 100 es un valor razonable.

// Estructura para la cola de prioridades
typedef struct nodo_cola_prioridades
{
  char cadena[TAM_MAX_CADENAS];            // La cadena con el dato.
  struct nodo_cola_prioridades *siguiente; // Un apuntador al siguiente elemento en la cola.
} NodoColaPrioridades;

// Prototipos de funciones.
void insertar(NodoColaPrioridades **, char *); // Para insertar un nuevo elemento en la cola de prioridades.
char *eliminar(NodoColaPrioridades **);        // Para eliminar el primer elemento presente en la cola de prioridades.
void imprimir(NodoColaPrioridades **);         // Para mostrar el contenido de una cola de prioridades.
int precedencia(char *, char *);               // Para determinar si dos cadenas de caracteres son menores (-1), iguales (0) o mayores (1) entre sí.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int opcionMenu;                          // Para la opción seleccionada en el menú principal.
  char entradaTemporal[TAM_MAX_CADENAS],   // Para la entrada proporcionada por el usuario.
      *salidaTemporal;                     // Para el valor de retorno de algunas operaciones.
  NodoColaPrioridades *nodoInicial = NULL; // El nodo inicial de nuestra cola de prioridades.

  // Ciclo de ejecución principal.
  do
  {
    // Mostramos las opciones del menú.
    printf("Operaciones disponibles:\n\n");
    printf("\t%i) Insertar nueva cadena en la cola.\n", MENU_INSERTAR);
    printf("\t%i) Eliminar el primer elemento en la cola.\n", MENU_ELIMINAR);
    printf("\t%i) Imprimir los elementos presentes en la cola.\n", MENU_IMPRIMIR);
    printf("\t-\n");
    printf("\t%i) Salir del programa.\n\n", MENU_SALIR);

    // Leemos la operación a realizar.
    do
    {
      printf("> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu < 1 || opcionMenu > 4); // Validación de la entrada.

    // Realizamos la operación seleccionada.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos la cadena a insertar.
      printf("Introduzca la cadena a insertar:\n> ");
      scanf("%s", entradaTemporal);

      // Insertamos la cadena en la cola de prioridades.
      insertar(&nodoInicial, entradaTemporal);

      // Mensaje de confirmación.
      printf("Se ha insertado correctamente la cadena: \"%s\" en la cola de prioridades.\n", entradaTemporal);
      break;
    case MENU_ELIMINAR:
      // Realizamos la operación y almacenamos el resultado.
      salidaTemporal = eliminar(&nodoInicial);

      // Verificamos si no recibimos una BANDERA_COLA_VACIA
      if (salidaTemporal[0] == BANDERA_COLA_VACIA)
      {
        printf("No se ha podido eliminar ningún elemento porque la cola está vacía.\n");
      }
      else
      {
        printf("Se ha eliminado el primer elemento presente en la cola de prioridades: \"%s\".\n", salidaTemporal);
      }
      break;
    case MENU_IMPRIMIR:
      // Realizamos la operación.
      printf("El contenido de la cola es:\n\t");
      imprimir(&nodoInicial);
      printf("\n");
      break;
    default:
      printf("¡Gracias por utilizar este programa!\n\n");
      break;
    }
  } while (opcionMenu != MENU_SALIR); // Se ejecutará hasta que el usuario seleccione la opción de salir.

  // Limpiamos la memoria para la cola de prioridades.
  while (eliminar(&nodoInicial)[0] != BANDERA_COLA_VACIA)
    ; // Oh pero qué elegancia la de francia.

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Insertar
 * Añade un elemento en la cola de prioridades en la posición adecuada dentro del conjunto de datos ordenados.
 * @param nodoInicial Un apuntador al nodo inicial de nuestra cola de prioridades
 * @param cadenaNuevoElemento La cadena para el nuevo elemento dentro de la cola de prioridades.
 */
void insertar(NodoColaPrioridades **nodoInicial, char cadenaNuevoElemento[TAM_MAX_CADENAS])
{
  // Variables locales.
  NodoColaPrioridades *nuevoElemento = (NodoColaPrioridades *)malloc(sizeof(NodoColaPrioridades));
  NodoColaPrioridades *temporal;

  // Asignamos el valor proporcionado para el nuevo elemento.
  strcpy(nuevoElemento->cadena, cadenaNuevoElemento);

  // Verificamos si la cola está vacía.
  if (*nodoInicial == NULL)
  {
    // Asignamos el siguiente elemento a nulo.
    nuevoElemento->siguiente = NULL;

    // Asignamos el apuntador al nodo inicial a nuestro nuevo elemento.
    *nodoInicial = nuevoElemento;
  }
  else
  {
    // Asignamos el nodoInicial a nuestra variable temporal.
    temporal = *nodoInicial;

    // Ciclo para encontrar la posición idónea para insertar el elemento.
    while (temporal->siguiente != NULL && precedencia(nuevoElemento->cadena, temporal->siguiente->cadena) != -1)
    {
      temporal = temporal->siguiente;
    }

    // Asignamos el apuntador del nuevo elemento hacia su siguiente elemento como el elemento inmediato siguiente de temporal
    // y después asignamos el siguiente elemento de temporal como nuestro nuevo elemento.
    nuevoElemento->siguiente = temporal->siguiente;
    temporal->siguiente = nuevoElemento;
  }
}

/**
 * Precedencia
 * Verifica si una cadena debe ir antes (-1), después (1) o es igual a otra (0).
 * @param primerCadena La primer cadena de caracteres para la verificación.
 * @param segundaCadena La segunda cadena de caracteres para la verificación.
 * @return Un entero 1 si la primer cadena es "mayor" a la segunda, un -1 si la primer cadena es "menor" a la segunda, 0 si son iguales.
 */
int precedencia(char *primerCadena, char *segundaCadena)
{
  // Variables locales.
  int indice = 0; // El índice para las operaciones.

  // Iteramos en la longitud de ambas cadenas.
  while (primerCadena[indice] != '\0' && segundaCadena[indice] != '\0')
  {
    // Verificamos si la primer cadena en el índice actual es mayor al valor de la segunda en el mismo índice.
    if (primerCadena[indice] > segundaCadena[indice])
    {
      return 1; // cadena 1 debe ir después de cadena 2.
    }

    // Verificamos si la primer cadena en el índice actual es menor al valor de la segunda en el mismo índice.
    if (primerCadena[indice] < segundaCadena[indice])
    {
      return -1; // cadena 1 debe ir antes de cadena 2.
    }

    // Si ninguna verificación terminó el ciclo, aumentamos el índice.
    indice++;
  }

  // Si se completó el ciclo y no hubo diferencias, las cadenas son iguales (0)
  return 0;
}

/**
 * Eliminar
 * Elimina el primer elemento presente en la cola de prioridades.
 * @param nodoInicial Un apuntador al primer elemento presente en la cola de prioridades
 * @return Una cadena de caracteres con el elemento presente en el primer nodo de la cola de prioridades BANDERA_COLA_VACIA si la cola está vacía.
 */
char *eliminar(NodoColaPrioridades **nodoInicial)
{
  // Variables locales.
  NodoColaPrioridades *nodoTemporal;
  char *datoTemporal;

  // Verificamos que la cola no esté vacía.
  if (*nodoInicial == NULL)
  {
    return BANDERA_COLA_VACIA;
  }
  else
  {
    // Guardamos la cadena en dato temporal.
    datoTemporal = (*nodoInicial)->cadena;

    // Guardamos la dirección de nodoInicial en nodoTemporal.
    nodoTemporal = *nodoInicial;

    // Realizamos la asignación.
    (*nodoInicial) = (*nodoInicial)->siguiente;

    // Liberamos la memoria para nodoTemporal.
    free(nodoTemporal);

    // Regresamos el dato temporal.
    return datoTemporal;
  }
}

/**
 * Imprimir
 * Muestra los contenidos de una cola de prioridades en la terminal.
 * @param inicio Un apuntador al elemento inicial de la cola de prioridades.
 */
void imprimir(NodoColaPrioridades **nodoInicial)
{
  // Variables locales.
  NodoColaPrioridades *temporal = *nodoInicial;

  // Caracter inicial
  printf("[ ");

  while (temporal != NULL)
  {
    // Imprimmos la cadena.
    printf("%s", temporal->cadena);

    // Verificamos si es el último elemento para imprimir la coma.
    if (temporal->siguiente != NULL)
    {
      printf(", ");
    }

    // Avanzamos al siguiente elemento.
    temporal = temporal->siguiente;
  }

  // Caracter final.
  printf(" ]");
}
