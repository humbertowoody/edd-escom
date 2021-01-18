/**
 * practica-11.c - Archivo base de la práctica
 *
 * Práctica: 11
 * Objetivo: Programar una lista de listas dónde el nodo inicial de cada una de éstas
 *           contenga el valor de las decenas de los elementos y los elementos dentro
 *           de cada una de estas listas estén ordenados.
 *
 * Alumno: Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 14 de Enero del 2021
 */
#include <stdio.h>  // Para operaciones de entrada y salida estándar
#include <stdlib.h> // Para usar `malloc` etc...

// Constantes de operación.
#define MENU_INSERTAR 1
#define MENU_IMPRIMIR 2
#define MENU_SALIR 3

// Estructura para las operaciones.
typedef struct nodo_lista
{
  int dato;                     // El dato a almacenar en el nodo.
  struct nodo_lista *siguiente; // Un apuntador al siguiente nodo inmediato.
  struct nodo_lista *anterior;  // Un apuntador al nodo inmediato anterior.
  struct nodo_lista *sublista;  // Un apuntador a la sublista (si existe).
} NodoLista;

// Prototipos de funciones.
void insertar(NodoLista **, int); // Función para insertar un nuevo elemento a la estructura.
void imprimir(NodoLista **);      // Función para imprimir los contenidos de la estructura.

// Función principal.
int main()
{
  // Variables locales.
  int opcionMenu,               // Para almacenar la opción del menú seleccionada por el usuario.
      temporal;                 // Para almacenar el valor temporal ingresado por el usuario.
  NodoLista *nodosLista = NULL; // Los datos almacenados en la estructura.

  do
  {
    // Mostramos el menú.
    printf("\t\tMenú Principal\n\n");
    printf("\t%i) Insertar elemento.\n", MENU_INSERTAR);
    printf("\t%i) Imprimir contenido.\n", MENU_IMPRIMIR);
    printf("\t-\n");
    printf("\t%i) Salir.\n\n", MENU_SALIR);

    // Leer la opción seleccionada.
    do
    {
      printf("[%i - %i]> ", MENU_INSERTAR, MENU_SALIR);
      scanf("%i", &opcionMenu);
    } while (opcionMenu < MENU_INSERTAR || opcionMenu > MENU_SALIR); // Validación de entrada.

    // Verificamos la operación a realizar.
    if (opcionMenu == MENU_INSERTAR)
    {
      // Leemos el número a insertar.
      printf("Introduce el número a insertar en la estructura: ");
      scanf("%i", &temporal);

      // Realizamos la inserción.
      insertar(&nodosLista, temporal);
    }
    else if (opcionMenu == MENU_IMPRIMIR)
    {
      // Realizamos la operación.
      imprimir(&nodosLista);
    }
    else
    {
      printf("¡Gracias por utilizar este programa!\n\n");
    }
  } while (opcionMenu != MENU_SALIR);

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Insertar
 * Añade un elemento a la estructura siguiendo las condiciones planteadas
 * por el profesor.
 * @param estructura La estructura con la información.
 * @param nuevoDato Un entero a añadir en la estructura
 */
void insertar(NodoLista **nodoInicial, int nuevoDato)
{
  // Variables locales.
  NodoLista *nuevoElemento,                                            // El nuevo nodo superior a insertar (de ser necesario)
      *nuevoElementoSubLista = (NodoLista *)malloc(sizeof(NodoLista)), // El nuevo nodo a insertar (siempre)
          *elementoActual = *nodoInicial,                              // Para iterar sobre la lista principal.
      *elementoActualSubLista,                                         // Para iterar sobre la lista secundaria.
      *temporal;                                                       // Para operaciones temporales.
  int decenaDato = nuevoDato / 10;                                     // La decena del dato a insertar.

  // Colocamos el dato del nuevo elemento.
  nuevoElementoSubLista->dato = nuevoDato;

  // Verificamos si la pila tiene elementos.
  if (elementoActual == NULL)
  {
    // Nodo hijo.
    nuevoElementoSubLista->anterior = NULL;
    nuevoElementoSubLista->siguiente = NULL;
    nuevoElementoSubLista->sublista = NULL;

    // Nodo padre.
    nuevoElemento = (NodoLista *)malloc(sizeof(NodoLista));
    nuevoElemento->anterior = NULL;
    nuevoElemento->siguiente = NULL;
    nuevoElemento->dato = decenaDato;
    nuevoElemento->sublista = nuevoElementoSubLista;

    // Asignamos al inicio.
    *nodoInicial = nuevoElemento;
  }
  else
  {
    // Buscamos la posición de la decena.
    while (elementoActual->siguiente != NULL && elementoActual->dato < decenaDato)
    {
      elementoActual = elementoActual->siguiente;
    }

    // printf("Nos paramos en: %i\n", elementoActual->dato);

    // Verificamos si encontramos la decena exacta de nuestro elemento.
    if (elementoActual->dato == decenaDato)
    {
      // Insertamos el elemento en la sublista directamente.
      // printf("La decena ya existe, insertando directamente.\n");

      elementoActualSubLista = elementoActual->sublista;

      // Buscamos la posición del elemento para la sublista.
      while (elementoActualSubLista->siguiente != NULL && elementoActualSubLista->dato < nuevoDato)
      {
        elementoActualSubLista = elementoActualSubLista->siguiente;
      }

      // Verificamos si nuestro elemento ya existe.
      if (elementoActualSubLista->dato == nuevoDato)
      {
        printf("\nYa existe el elemento. Se omite su inserción\n");
        free(nuevoElementoSubLista);
      }
      // Verificamos si no existe el elemento y debe ir antes del elemento actual.
      else if (elementoActualSubLista->dato > nuevoDato)
      {
        nuevoElementoSubLista->siguiente = elementoActualSubLista;

        // Verificamos si el elemento anterior es nulo.
        if (elementoActualSubLista->anterior == NULL)
        {
          temporal = NULL;
        }
        else
        {
          temporal = elementoActualSubLista->anterior;
          temporal->siguiente = nuevoElementoSubLista;
        }

        nuevoElementoSubLista->anterior = temporal;

        elementoActualSubLista->anterior = nuevoElementoSubLista;

        // Verificamos si el nuevo elemento corresponde al inicio de la sublista.
        if (nuevoElementoSubLista->anterior == NULL)
        {
          elementoActual->sublista = nuevoElementoSubLista;
        }
      }
      // Verificamos si no existe el elemento y debe ir después del elemento actual.
      else
      {
        nuevoElementoSubLista->anterior = elementoActualSubLista;

        // Verificamos si el elemento anterior es nulo.
        if (elementoActualSubLista->siguiente == NULL)
        {
          temporal = NULL;
        }
        else
        {
          temporal = elementoActualSubLista->siguiente;
          temporal->anterior = nuevoElementoSubLista;
        }

        nuevoElementoSubLista->siguiente = temporal;

        elementoActualSubLista->siguiente = nuevoElementoSubLista;
      }
    }
    // Verificamos si nuestra decena no se encontró y debe ir antes del elemento actual.
    else if (elementoActual->dato > decenaDato)
    {
      // Insertamos la decena antes del elemento actual.
      nuevoElemento = (NodoLista *)malloc(sizeof(NodoLista));
      nuevoElemento->dato = decenaDato;
      nuevoElemento->siguiente = elementoActual;
      nuevoElemento->sublista = nuevoElementoSubLista;

      nuevoElementoSubLista->anterior = NULL;
      nuevoElementoSubLista->siguiente = NULL;
      nuevoElementoSubLista->sublista = NULL;

      // Verificamos si el elemento anterior es nulo.
      if (elementoActual->anterior == NULL)
      {
        temporal = NULL;
      }
      else
      {
        temporal = elementoActual->anterior;
        temporal->siguiente = nuevoElemento;
      }

      nuevoElemento->anterior = temporal;

      elementoActual->anterior = nuevoElemento;

      // Verificamos si el nuevo elemento corresponde al inicio de la lista.
      if (nuevoElemento->anterior == NULL)
      {
        (*nodoInicial) = nuevoElemento;
      }
    }
    // Verificamos si nuestra decena no se encontró y debe ir después del elemento actual.
    else if (elementoActual->dato < decenaDato)
    {
      // Insertamos la decena antes del elemento actual.
      nuevoElemento = (NodoLista *)malloc(sizeof(NodoLista));
      nuevoElemento->dato = decenaDato;
      nuevoElemento->anterior = elementoActual;
      nuevoElemento->sublista = nuevoElementoSubLista;

      nuevoElementoSubLista->anterior = NULL;
      nuevoElementoSubLista->siguiente = NULL;
      nuevoElementoSubLista->sublista = NULL;

      // Verificamos si el elemento anterior es nulo.
      if (elementoActual->siguiente == NULL)
      {
        temporal = NULL;
      }
      else
      {
        temporal = elementoActual->siguiente;
        temporal->anterior = nuevoElemento;
      }

      nuevoElemento->siguiente = temporal;

      elementoActual->siguiente = nuevoElemento;
    }
  }
}

/**
 * Imprimir
 * Muestra los contenidos de la estructura de datos.
 * @param nodoInicial El nodo inicial de la lista de listas a imprimir.
 */
void imprimir(NodoLista **nodoInicial)
{
  // Variables locales.
  NodoLista *elementoActual = *nodoInicial, // Para iterar sobre la lista principal.
      *elementoActualSubLista;              // Para iterar sobre las sublistas.

  // Verificamos si la lista está vacía.
  if (elementoActual == NULL)
  {
    printf("\n\tLista de listas vacía, inserte algún dato e inténtelo de nuevo.\n");
  }
  else
  {
    printf("\n\nContenidos de la lista de listas:\n\n");
  }

  // Imprimimos cada elemento hasta que sea nulo.
  while (elementoActual != NULL)
  {
    // Mostramos el elemento actual.
    printf("| %4i |", elementoActual->dato);

    // Obtenemos el primer elemento de la sublista.
    elementoActualSubLista = elementoActual->sublista;

    // Recorremos la sublista.
    while (elementoActualSubLista != NULL)
    {
      // Mostramos el elemento actual de la sublista.
      printf(" %4i |", elementoActualSubLista->dato);

      // Avanzamos el elemento actual de la sublista.
      elementoActualSubLista = elementoActualSubLista->siguiente;
    }

    // Salto de línea.
    printf("\n");

    // Avanzamos el apuntador.
    elementoActual = elementoActual->siguiente;
  }

  // Salto de línea final.
  printf("\n");
}
