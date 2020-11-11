/**
 * evaluacion1-2.c
 *
 * Examen Primer Departamental
 * Evaluación 1.2
 * Planteamiento:
 *  Implementar el código de cola dinámica para 2 colas de
 *  enteros. El funcionamiento será de la siguente forma:
 *
 *    - Hacer un menú con las opciones insertar y eliminar para cada
 *      una de las colas.
 *
 *    - Implementar una función llamada “Unir colas”
 *
 *    - Cuando se solicite unir ambas colas, éstas se deben fusionar
 *      como una sola con sus propias funciones insertar y eliminar.
 *
 * Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 * Materia: Estructuras de Datos
 * Profesor: Alberto Jesús Alcántara Méndez
 * Escuela Superior de Cómputo - IPN
 * Miércoles 11 de Noviembre del 2020.
 */
#include <stdio.h>  // Para operaciones de entrada y salida estándar
#include <stdlib.h> // Para usra `malloc` etc...

// Constantes de operación.
#define BANDERA_COLA_VACIA -32256
#define MENU_INSERTAR 1
#define MENU_ELIMINAR 2
#define MENU_UNIR 3
#define MENU_SALIR 4

// Estructura de cola dinámica para enteros.
typedef struct cola_int
{
  int dato;
  struct cola_int *siguiente;
} ColaInt;

// Prototipos de funciones.
void encolar(ColaInt **, ColaInt **, int); // Añade un elemento a la cola.
int desencolar(ColaInt **);                // Eliminar el primer elemento de la cola.
void imprimirMenu();                       // Para mostrar el menú principal.
void mostrarCola(ColaInt **);              // Imprime una cola en la terminal.

// Función principal
int main(int argc, char *argv[])
{
  // Variables locales.
  ColaInt *inicioCola1 = NULL,          // El inicio de la primer cola.
      *finCola1 = NULL,                 // El final de la primer cola.
          *inicioCola2 = NULL,          // El inicio de la segunda cola.
              *finCola2 = NULL,         // El final de la segunda cola.
                  *inicioCola3 = NULL,  // El inicio de la tercer cola.
                      *finCola3 = NULL; // El final de la tercer cola.
  int opcionMenu,                       // Para almacenar la opción seleccionada del menú principal.
      opcionCola,                       // Para almacenar la opción de la cola para realizar la operación.
      maxColas,                         // Para almacenar el número máximo de colas disponibles temporalmente para una operación.
      datoTemporal;                     // Para almacenar cualquier dato temporal que debamos utilizar en el programa.
  do
  {
    // Mostramos el menú principal.
    imprimirMenu();

    // Impresión para debug.
    printf("\nContenido de las colas:\n");
    printf("\tCola 1: ");
    mostrarCola(&inicioCola1);
    printf("\n\tCola 2: ");
    mostrarCola(&inicioCola2);
    printf("\n\tCola 3: ");
    mostrarCola(&inicioCola3);
    printf("\n");

    do
    {
      printf("> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu < 1 || opcionMenu > 4); // Validar entrada.

    // Verificamos el número de colas disponibles.
    if (inicioCola3 == NULL && finCola3 == NULL)
    {
      // Sólamente existen la cola 1 y la 2.
      maxColas = 2;
    }
    else
    {
      // Existen la cola 1, la 2 y la unión de esas dos, la cola 3.
      maxColas = 3;
    }

    // Realizamos la operación correspondiente.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos en qué cola se realizará la operación.
      printf("¿En qué cola desea realizar la operación?\n");
      do
      {
        printf("[1-%i]> ", maxColas);
        scanf("%i", &opcionCola);
      } while (opcionCola < 1 || opcionCola > maxColas); // Validación de entrada.

      // Leemos el dato a insertar en la cola.
      printf("Ingrese el dato a insertar en la cola %i: ", opcionCola);
      scanf("%i", &datoTemporal);

      // Insertamos el dato en la cola.
      if (opcionCola == 1)
      {
        encolar(&inicioCola1, &finCola1, datoTemporal);
      }
      else if (opcionCola == 2)
      {
        encolar(&inicioCola2, &finCola2, datoTemporal);
      }
      else if (opcionCola == 3 && maxColas == 3)
      {
        encolar(&inicioCola3, &finCola3, datoTemporal);
      }
      break;
    case MENU_ELIMINAR:
      // Leemos en qué cola se realizará la operación.
      printf("¿En qué cola desea realizar la operación?\n");
      do
      {
        printf("[1-%i]> ", maxColas);
        scanf("%i", &opcionCola);
      } while (opcionCola < 1 || opcionCola > maxColas); // Validación de entrada.

      // Extraemos el dato en la cola.
      if (opcionCola == 1)
      {
        datoTemporal = desencolar(&inicioCola1);
      }
      else if (opcionCola == 2)
      {
        datoTemporal = desencolar(&inicioCola2);
      }
      else if (opcionCola == 3 && maxColas == 3)
      {
        datoTemporal = desencolar(&inicioCola3);
      }

      // Verificamos si el dato fue una bandera indicando que la cola estaba vacía.
      if (datoTemporal == BANDERA_COLA_VACIA)
      {
        printf("No se ha eliminado ningún dato puesto que la cola %i se encuentra vacía.\n", opcionCola);
      }
      else
      {
        // Mostramos el dato que sacamos.
        printf("El dato eliminado de la cola %i es: %i\n", opcionCola, datoTemporal);
      }

      break;
    case MENU_UNIR:
      // Verificamos que las dos colas no estén vacías.
      if (inicioCola1 != NULL && finCola1 != NULL && inicioCola2 != NULL && finCola2 != NULL)
      {
        // Para unir las dos colas, sólamente movemos los apuntadores.
        inicioCola3 = inicioCola1;         // La cola 3 inicia con el inicio de la cola 1.
        finCola3 = finCola2;               // La cola 3 finaliza en el final de la cola 2.
        finCola1->siguiente = inicioCola2; // La cola 3 es contínua entre la cola 1 y la cola 2.

        // Limpiamos los datos para las colas 1 y 2.
        inicioCola1 = NULL;
        finCola1 = NULL;
        inicioCola2 = NULL;
        finCola2 = NULL;
      }
      else
      {
        printf("No es posible realizar la unión de dos colas si alguna se encuentra vacía.\n");
      }

    default:
      printf("¡Gracias por utilizar este programa!\n");
      break;
    } // Fin de switch.

  } while (opcionMenu != MENU_SALIR); // Fin de menú principal.

  // En este punto, la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Encolar
 * Añade un elemento al final de la cola.
 * @param inicioCola Un apuntador al inicio de la cola.
 * @param finCola un apuntador al final de la cola.
 * @param dato El dato a añadir en la cola.
 */
void encolar(ColaInt **inicioCola, ColaInt **finCola, int dato)
{
  // Variables locales.
  ColaInt *temporal = (ColaInt *)malloc(sizeof(ColaInt));

  // Creamos el nuevo elemento.
  temporal->dato = dato;
  temporal->siguiente = NULL;

  // Revisamos si la cola contiene elementos previos.
  if (*finCola == NULL)
  {
    // Si la cola no tiene elementos previos, el inicio y el fin serán el nuevo elemento.
    *inicioCola = temporal;
    *finCola = temporal;
  }
  else
  {
    // Si la cola tiene elementos previos, movemos nuestro elemento al final de la misma.
    ColaInt *finTemp = *finCola;
    finTemp->siguiente = temporal;
    *finCola = finTemp->siguiente;
    // free(finTemp);
  }
}

/**
 * Desencolar
 * Extrae y elimina el primer elemento presente en una cola.
 * @param inicioCola El apuntador al inicio de la cola en cuestión.
 */
int desencolar(ColaInt **inicioCola)
{
  // Variables locales.
  ColaInt *colaTemporal; // Elemento de cola temporal para realizar la operación.
  int datoTemporal;      // Variable para almacenar, temporalmente, el dato que regresa la función.

  // Verificamos si la cola está vacía.
  if (*inicioCola == NULL)
  {
    // Si la cola está vacía regresamos BANDERA_COLA_VACIA.
    return BANDERA_COLA_VACIA;
  }
  else
  {
    // Hacemos una copia temporal del inicio de la cola.
    colaTemporal = *inicioCola;
    // Asignamos al inicio de la cola al siguiente elemento inmediato.
    *inicioCola = colaTemporal->siguiente;
    // Extraemos el dato presente en el inicio anterior.
    datoTemporal = colaTemporal->dato;
    // Eliminamos el elemento que era el inicio anterior.
    free(colaTemporal);
    // Regresamos el dato temporal.
    return datoTemporal;
  }
}

/**
 * Imprimir menu
 * Muestra el menú principal del programa en la terminal.
 */
void imprimirMenu()
{
  printf("Menú principal\n\nSeleccione la operación a realizar:\n\n");
  printf("\t1) Insertar.\n");
  printf("\t2) Eliminar.\n");
  printf("\t3) Unir colas.\n");
  printf("\t-\n");
  printf("\t4) Salir del programa.\n");
}

/**
 * Mostrar cola
 * Imprime el contenido de una cola en la terminal.
 */
void mostrarCola(ColaInt **inicio)
{
  // Variables locales.
  ColaInt *temporal = *inicio; // Una variable temporal para iterar en los elementos de la cola.

  // Ciclo para recorrer los elementos.
  while (temporal != NULL)
  {
    printf("%i, ", temporal->dato);
    temporal = temporal->siguiente;
  }
}