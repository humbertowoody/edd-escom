/**
 * practica2.c - Archivo base de la práctica
 *
 * Práctica: 2
 * Objetivo: Realizar operaciones elementales de pilas preguntando al usuario si desea emplear
 *           pilas estáticas o dinámicas.
 * Equipo:
 *   - Téllez Castilla Laura Daniela (2020630527) <danycastilla27@gmail.com>
 *   - Ramos Mendoza Eduardo (2020630558) <eramosm1400@alumno.ipn.mx>
 *   - Joseph Judá Juanico González (2019630544) <josephjuanico503@gmail.com>
 *   - Humberto Alenadro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara.
 * ESCOM - IPN
 * 27/Oct/2020.
 */
#include <stdio.h>  // Para operaciones de entrada y salida.
#include <stdlib.h> // Para usar `malloc` etc..

// Constantes para el tipo de operación del programa.
#define PILAS_ESTATICAS 2
#define PILAS_DINAMICAS 1

// Constantes para las pilas estáticas.
#define MAX_ELEMENTOS_PILA_ESTATICA 20             // Valor razonable.
#define BANDERA_PILA_ESTATICA_VACIA -1234          // Una bandera para identificar que la pila estática está vacía.
#define BANDERA_PILA_ESTATICA_LLENA -1             // Una bandera para identificar que la pila estática ya está llena.
#define BANDERA_PILA_ESTATICA_OPERACION_CORRECTA 0 // Una bandera para identificar que la operación en la pila estática fue exitosa.

// Constantes para las pilas dinámiicas.
#define NUMERO_PILAS_DINAMICAS 3          // Es lo que nos pide la práctica, pero podrían ser n.
#define BANDERA_PILA_DINAMICA_VACIA -1234 // Una bandera para identificar que la pila está vacía y no utilizar -1 por si el usuario ingresa un elemento -1.

// Constantes para el menú del programa.
#define MENU_SALIR 4        // Opción del menú principal para salir del programa.
#define MENU_MOSTRAR_PILA 1 // Opción del menú principal para mostrar una pila.
#define MENU_PUSH 2         // Opción del menú principal para la operación `push`
#define MENU_POP 3          // Opción del menú principal para la operación `pop`

/**
 * Estructura PilaEstatica
 * Abstrae una pila estática.
 */
typedef struct p_estatica
{
  int dato;     // Para almacenar el dato como un entero.
  int anterior; // Para almacenar el índice al elemento inmediato anterior.
} PilaEstatica;

/**
 * Estructura PilaDinamica
 * Abstrae una pila dinámica.
 */
typedef struct p_dinamica
{
  int dato;                    // Para almacenar el dato como un entero.
  struct p_dinamica *anterior; // Un apuntador con la referencia al elemento inmediato anterior.
} PilaDinamica;

/**
 * Prototipos de funciones para pilas estáticas.
 */
void imprimirPilaEstatica(PilaEstatica *, int);   // Imprime una pila estática en la terminal.
int pushPilaEstatica(PilaEstatica *, int *, int); // Realiza la operación `push` en una pila estática.
int popPilaEstatica(PilaEstatica *, int *);       // Realiza la operación `pop` en una pila estática.

/**
 * Prototipos de funciones para pilas dinámicas.
 */
void imprimirPilaDinamica(PilaDinamica **);  // Imprime una pila dinámica en la terminal.
void pushPilaDinamica(PilaDinamica **, int); // Realiza la operación `push` en una pila dinámica.
int popPilaDinamica(PilaDinamica **);        // Realiza la operación `pop` en una pila dinámica.

/**
 * Prototipos de funciones para operación general del programa.
 */
// int leerMenu();

/**
 * Función principal de programa.
 */
int main(int argc, char *argv[])
{
  // Variables locales.
  int tipoPilas = 0,     // Variable para almacenar el tipo de pilas a emplear en el programa.
      opcionMenu = 0,    // Variable para almacenar la opción del menú seleccionada.
      opcionPila = 0,    // Variable para almacenar, temporalmente, la pila sobre la cual se realizará la operación.
      datoTemporal = -1; // Variable para almacenar, temporalmente, cualquier dato de alguna pila.

  // Variables locales específicas a las pilas estáticas.
  PilaEstatica pilasEstaticas[3][MAX_ELEMENTOS_PILA_ESTATICA]; // Matriz con tres pilas estáticas.
  int topesPilaEstaticas[3] = {-1, -1, -1};                    // Arreglo con los topes de las tres pilas estáticas.

  // Variables locales específicas a las pilas dinámicas.
  PilaDinamica **pilasDinamicas = (PilaDinamica **)malloc(sizeof(PilaDinamica *) * NUMERO_PILAS_DINAMICAS); // Pilas dinámicas en forma de matriz, utilizamos malloc para inicializar con 3 pilas.

  // Mensaje inicial.
  printf("Escuela Superior de Cómputo - IPN\n");
  printf("Estructuras de Datos - Alberto Alcántara\n");
  printf("Práctica 2: Realizar operaciones elementales de pilas preguntando al usuario si desea emplear pilas estáticas o dinámicas\n");
  printf("Equipo:\n");
  printf("  - Téllez Castilla Laura Daniela (2020630527) <danycastilla27@gmail.com>\n");
  printf("  - Ramos Mendoza Eduardo (2020630558) <eramosm1400@alumno.ipn.mx>\n");
  printf("  - Joseph Judá Juanico González (2019630544) <josephjuanico503@gmail.com>\n");
  printf("  - Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>\n\n");

  // Primero es definir qué tipo de pilas desea trabajar.
  do
  {
    printf("¿Qué tipo de pilas deseas utilizar?\n");
    printf(" %i) Pilas dinámicas.\n", PILAS_DINAMICAS);
    printf(" %i) Pilas estáticas (hasta %i elementos por pila).\n", PILAS_ESTATICAS, MAX_ELEMENTOS_PILA_ESTATICA);
    printf("[%i-%i]> ", PILAS_DINAMICAS, PILAS_ESTATICAS);
    scanf("%i", &tipoPilas);
  } while (tipoPilas != PILAS_DINAMICAS && tipoPilas != PILAS_ESTATICAS); // Validación de la entrada.

  // Mostramos confirmación al usuario.
  if (tipoPilas == PILAS_DINAMICAS)
  {
    printf("Has seleccionado la opción de utilizar pilas dinámicas.\n");
  }
  else
  {
    printf("Has seleccionado la opción de utilizar pilas estáticas.\n");
  }

  // Ciclo de operación principal.
  do
  {
    // Ciclo para seleccionar la tarea a realizar.
    do
    {
      printf("\nMenú principal.\n");
      printf("Porfavor, seleccione una opción:\n");
      printf("  %i) Mostrar una pila.\n", MENU_MOSTRAR_PILA);
      printf("  %i) Añadir un elemento a una pila.\n", MENU_PUSH);
      printf("  %i) Extraer, mostrar y eliminar el último elemento en una pila.\n", MENU_POP);
      printf("  -\n");
      printf("  %i) Salir del programa.\n", MENU_SALIR);
      printf("> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu != MENU_MOSTRAR_PILA && opcionMenu != MENU_POP && opcionMenu != MENU_PUSH && opcionMenu != MENU_SALIR); // Validación de la entrada.

    // Mostramos confirmación al usuario.

    // En todas las operaciones, salvo salir, se requiere que el usuario seleccione la pila sobre la cual realizar la operación.
    if (opcionMenu != MENU_SALIR)
    {
      // Preguntamos al usuario la pila a utilizar.
      do
      {
        printf("¿Cuál pila deseas utilizar para la operación seleccionada?\n");
        printf("[1-3]> ");
        scanf("%i", &opcionPila);
      } while (opcionPila < 1 || opcionPila > 3); // Validación de la entrada.

      // Mostramos confirmación al usuario.
      printf("Has seleccionado realizar la operación en la pila: %i\n", opcionPila);
    }

    // Para realizar la operación seleccionada por el usuario.
    switch (opcionMenu)
    {
    case MENU_MOSTRAR_PILA:
      // Mostramos confirmación de la operación a realizar.
      printf("Se mostrará a continuación la pila #%i:\n", opcionPila);

      // Seleccionamos la función dependiendo el tipo de pilas.
      if (tipoPilas == PILAS_DINAMICAS)
      {
        imprimirPilaDinamica(&pilasDinamicas[opcionPila - 1]);
      }
      else
      {
        imprimirPilaEstatica(pilasEstaticas[opcionPila - 1], topesPilaEstaticas[opcionPila - 1]);
      }
      break;
    case MENU_PUSH:
      // Mostramos confirmación de la operación a realizar.
      printf("Se realizará la operación \"push\" en la pila #%i.\n", opcionPila);

      // Leemos el dato a añadir a la pila.
      printf("Introduce el valor para el dato a añadir a la pila #%i:\n", opcionPila);
      printf("> ");
      scanf("%i", &datoTemporal);

      // Seleccionamos la función dependiendo el tipo de pilas.
      if (tipoPilas == PILAS_DINAMICAS)
      {
        pushPilaDinamica(&pilasDinamicas[opcionPila - 1], datoTemporal);
      }
      else
      {
        // Realizamos la verificación de ejecución de la operación.
        if (pushPilaEstatica(pilasEstaticas[opcionPila - 1], &topesPilaEstaticas[opcionPila - 1], datoTemporal) == BANDERA_PILA_ESTATICA_LLENA)
        {
          // Si nos regresaron la bandera para indicar que la pila está llena, mostramos un mensaje al usuario.
          printf("La operación no ha podido realizarse porque la pila #%i ya se encuentra al límite de su capacidad.\n", opcionPila);
        }
      }
      break;
    case MENU_POP:
      // Mostramos confirmación de la operación a realizar.
      printf("Se realizará la operación \"pop\" en la pila #%i.\n", opcionPila);

      // Seleccionamos la función dependiendo del tipo de pilas.
      if (tipoPilas == PILAS_DINAMICAS)
      {
        // Realizamos la operación.
        datoTemporal = popPilaDinamica(&pilasDinamicas[opcionPila - 1]);

        // Verificamos si nos regresaron una bandera.
        if (datoTemporal == BANDERA_PILA_DINAMICA_VACIA)
        {
          printf("La pila #%i está vacía, ningún dato ha sido eliminado.\n", opcionPila);
        }
        else
        {
          printf("El último dato presente en la pila #%i era: %i\n", opcionPila, datoTemporal);
        }
      }
      else
      {
        // Realizamos la operación.
        datoTemporal = popPilaEstatica(pilasEstaticas[opcionPila - 1], &topesPilaEstaticas[opcionPila - 1]);

        // Verificamos si nos regresaron una bandera.
        if (datoTemporal == BANDERA_PILA_ESTATICA_VACIA)
        {
          printf("La pila #%i está vacía, ningún dato ha sido eliminado.\n", opcionPila);
        }
        else
        {
          printf("El último dato presente en la pila #%i era: %i.\n", opcionPila, datoTemporal);
        }
      }
      break;
    case MENU_SALIR: // Salir es el caso default, como en la vida.
    default:
      printf("¡Muchas gracias por utilizar este programa!\n");
      break;
    }
  } while (opcionMenu != MENU_SALIR); // Mientras el usuario no haya seleccionado salir.

  // Mensaje final de ejecución.
  printf("Fin de ejecución.\n\n");

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Implementación de funciones para pilas estáticas.
 */

/**
 * Imprimir Pila Estática
 * Realiza la impresión en la terminal de la pila estática en cuestión.
 * @param pila La pila a imprimir
 * @param tope El valor inicial para el tope de la pila.
 */
void imprimirPilaEstatica(PilaEstatica *pila, int tope)
{
  // Impresión inicial.
  printf("\n|--------|\n");

  // Si la pila está vacía, mostramos un ∅.
  if (tope == -1)
  {
    printf("|   ∅    |\n");
    printf("|--------|\n");
  }

  // Imprimimos mientras tope no sea -1.
  for (/* */; tope > -1; tope--)
  {
    // 6 caracteres de padding.
    printf("| %6i |\n", pila[tope].dato);
    printf("|--------|\n");
  }

  // Salto de línea final.
  printf("\n");
}

/**
 * Push Pila Estática
 * Realiza la operación `push` en una pila estática, añadiendo un elemento al final de la misma.
 * @param pila La pila para realizar la operación.
 * @param tope Una referencia al tope para la pila en cuestión.
 * @param nuevoDato El nuevo dato para el elemento a añadir.
 * @return BANDERA_PILA_ESTATICA_OPERACION_EXITOSA si la operación fue exitosa, BANDERA_PILA_ESTATICA_PILA_LLENA en caso de que la pila ya estuviera llena.
 */
int pushPilaEstatica(PilaEstatica *pila, int *tope, int nuevoDato)
{
  // Variables locales.
  PilaEstatica nuevoElemento; // Creamos el nuevo elemento a añadir en la pila.

  // Asignamos el nuevo dato al elemento a añadir.
  nuevoElemento.dato = nuevoDato;

  // Verificamos si la pila ya se encuentra en el límite de capacidad.
  if (*tope == (MAX_ELEMENTOS_PILA_ESTATICA - 1))
  {
    // La pila ya se encuentra llena, regresamos la bandera BANDERA_PILA_ESTATICA_LLENA.
    return BANDERA_PILA_ESTATICA_LLENA;
  }
  else
  {
    // La operación varía dependiendo si es el primer elemento que ingresamos a la pila.
    if (*tope == -1)
    {
      *tope = 0;                   // Asignamos el tope a 0.
      nuevoElemento.anterior = -1; // Ponemos el elemento inmediato anterior a -1.
    }
    else
    {
      nuevoElemento.anterior = *tope; // Asignamos el tope actual como el elemento anterior de nuestro nuevo elemento.
      *tope += 1;                     // Aumentamos el tope.
    }

    // Asignamos el nuevo elemento a la pila.
    pila[*tope] = nuevoElemento;
  }

  // Si la operación fue exitosa, regresamos un 0.
  return 0;
}

/**
 * Pop Pila Estática
 * Realiza la operación `pop` en una pilia estática, extrayendo y eliminando el último elemento presente en la pila.
 * @param pila La pila para realizar la operación
 * @param tope Una referencia al tope de la pila.
 * @return BANDERA_PILA_ESTATICA_OPERACION_CORRECTA si la operación fue exitosa, BANDERA_PILA_ESTATICA_VACIA si la pila está vacía.
 */
int popPilaEstatica(PilaEstatica *pila, int *tope)
{
  // Variables locales.
  int datoTemporal; // Variable utilizada para almacenar, temporalmente, el dato a ser eliminado.

  // Verificamos que la pila no esté vacía.
  if (*tope == -1)
  {
    // La pila está vacía, regresamos bandera indicando el problema.
    return BANDERA_PILA_ESTATICA_VACIA;
  }
  else
  {
    // Guardamos el valor en la variable temporal.
    datoTemporal = pila[*tope].dato;

    // Limpiamos el elemento en la posición de tope actual.
    pila[*tope].anterior = -1;
    pila[*tope].dato = 0;

    // Reducimos el tope en -1.
    *tope -= 1;

    // Regresamos el dato temporal
    return datoTemporal;
  }
}

/**
 * Implementación de funciones para pilas dinámicas.
 */

/**
 * Imprimir Pila Dinamica
 * Realiza la impresión en la terminal de la pila dinámica en cuestión.
 * @param pila La pila a imprimir.
 */
void imprimirPilaDinamica(PilaDinamica **pila)
{
  // Variables locales.
  PilaDinamica *elementoActual = *pila;

  // Impresión inicial.
  printf("\n|--------|\n");

  // Si la pila está vacía, mostramos un ∅.
  if (elementoActual == NULL)
  {
    printf("|   ∅    |\n");
    printf("|--------|\n");
  }

  // Imprimimos cada elemento hasta que sea nulo.
  while (elementoActual != NULL)
  {
    // 6 caracteres de padding.
    printf("| %6i |\n", elementoActual->dato);
    printf("|--------|\n");

    // Movemos el apuntador al siguiente elemento.
    elementoActual = elementoActual->anterior;
  }

  // Salto de línea final.
  printf("\n");
}

/**
 * Push Pila Dinámica
 * Realiza la operación `push` para pilas dinámicas, añadiendo un nuevo elemento al final.
 * @param pila Una referencia a la pila dinámica a utilizar
 * @param nuevoDato El nuevo dato a almacenar en la pila
 */
void pushPilaDinamica(PilaDinamica **pila, int nuevoDato)
{
  // Declaramos el nuevo elemento para la pila.
  PilaDinamica *nuevoElemento = (PilaDinamica *)malloc(sizeof(PilaDinamica));

  // Revisamos si la pila ya contiene elementos.
  if (*pila == NULL)
  {
    // La pila está vacía, así que el nuevo elemento será el elemento inicial de la pila.
    nuevoElemento->anterior = NULL;
  }
  else
  {
    // La pila ya contiene elementos, así que únicamente la ligamos medaiante el apuntador "anterior".
    nuevoElemento->anterior = *pila;
  }

  // Asignamos el dato al nuevo elemento.
  nuevoElemento->dato = nuevoDato;

  // Colocamos la referencia de nuestra pila en el nuevo elemento.
  *pila = nuevoElemento;
}

/**
 * Pop Pila Dinámica
 * Realiza la operación `pop` para pilas dinámicas, extrayendo y eliminando el último elemento presente en la pila.
 * @param pila La pila de la cual extraer el elemento.
 * @return El último elemento o BANDERA_PILA_DINAMICA_VACIA si la pila está vacía.
 */
int popPilaDinamica(PilaDinamica **pila)
{
  // Variables locales.
  int datoTemporal;           // Para almacenar temporalmente el último elemento en la pila.
  PilaDinamica *pilaTemporal; // Para almacenar temporalmente la pila.

  // Verificamos si la pila tiene elementos.
  if (*pila == NULL)
  {
    // Si la pila está vacía, regresamos la bandera BANDERA_PILA_DINAMICA_VACIA.
    return BANDERA_PILA_DINAMICA_VACIA;
  }
  else
  {
    // Usamos la pila temporal para dereferenciar nuestro apuntador.
    pilaTemporal = *pila;

    // Guardamos el dato que existe en la pila.
    datoTemporal = pilaTemporal->dato;

    // Asignamos la referencia de la pila al elemento inmediato anterior.
    *pila = pilaTemporal->anterior;

    // Liberamos la memoria de nuestra pila temporal.
    free(pilaTemporal);

    // Regresamos el dato temporal, que era el último en nuestra pila.
    return datoTemporal;
  }
}