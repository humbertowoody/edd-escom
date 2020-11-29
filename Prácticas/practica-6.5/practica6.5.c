/**
 * practica6.5.c - Archivo base de la práctica
 *
 * Práctica: 6 (+.5 porque la tarea de cola de prioridades le puse práctica 6 perdón :c )
 * Objetivo: Implementar una lista simplemente ligada dónde existan operaciones de inserción,
 *           eliminación e impresión y, además, los datos sean insertados en orden ascendente.
 *
 * Equipo:
    - Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 28/Noviembre/2020
*/
#include <stdio.h>  // Para operaciones de entrada y salida.
#include <stdlib.h> // Para usar `malloc` etc...

// Constantes de menú.
#define MENU_SALIR 4
#define MENU_INSERTAR 1
#define MENU_ELIMINAR 2
#define MENU_MOSTRAR 3

// Constantes de operación
#define BANDERA_INDICE_NO_ENCONTRADO -32256

// Estructura para los nodos de la lista simplemente ligada.
typedef struct nodo
{
  int id;                 // Para almacenar la posición del elemento dentro de la lista.
  int dato;               // Para almacenar el dato en la estructura.
  struct nodo *siguiente; // Un apuntador al siguiente elemento de la lista.
} Nodo;

// Prototipos de funciones
void insertar(Nodo **, int, int); // Para insertar un nuevo elemento en la lista.
void mostrar(Nodo **);            // Para imprimir los elementos de la lista.
int eliminar(Nodo **, int);       // Para eliminar un elemento dentro de la lista.

// Función principal
int main(int argc, char *argv[])
{
  // Variables locales.
  Nodo *inicio = NULL; // Apuntador al inicio de la lista simplemente ligada.
  int opcionMenu,      // Variable para almacenar la opción del menú que se haya seleccionado.
      valorTemporal,   // Variable para almacenar valores de forma temporal.
      indiceTemporal;  // Variable para almacenar un índice de forma temporal.

  // Ciclo para menú principal.
  do
  {
    // Mostramos las opciones del menú.
    printf("\tMenú principal.\n\n");
    printf("Seleccione una operación a realizar:\n\n");
    printf("\t%i) Insertar un nuevo elemento.\n", MENU_INSERTAR);
    printf("\t%i) Eliminar un elemento.\n", MENU_ELIMINAR);
    printf("\t%i) Mostrar lista.\n", MENU_MOSTRAR);
    printf("\t-\n");
    printf("\t%i) Salir.\n\n", MENU_SALIR);

    // Leer la opción del menú.
    do
    {
      printf("[1-4]> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu < 1 || opcionMenu > 4);

    // Realizamos la operación apropiada.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos el valor a introducir.
      printf("Valor a introducir: ");
      scanf("%i", &valorTemporal);

      // Leemos el índice para insertar.
      printf("Índice para el elemento: ");
      scanf("%i", &indiceTemporal);

      // Insertamos el elemento.
      insertar(&inicio, valorTemporal, indiceTemporal);
      break;
    case MENU_ELIMINAR:
      // Leemos el índice a eliminar.
      printf("Índice del elemento a eliminar: ");
      scanf("%i", &indiceTemporal);

      // Realizamos la operación y almacenamos el valor de retorno.
      valorTemporal = eliminar(&inicio, indiceTemporal);

      // Verificamos si el resultado es BANDERA_INDICE_NO_ENCONTRADO
      if (valorTemporal == BANDERA_INDICE_NO_ENCONTRADO)
      {
        printf("El índice no existe, revísalo e inténtalo de nuevo.\n");
      }
      else
      {
        // Si no fue la bandera, quiere decir que la función nos ha regresado
        // el dato presente en el elemento eliminado. Lo mostramos.
        printf("Se ha eliminado el elemento con el índice [%i] que contenía: %i.\n", indiceTemporal, valorTemporal);
      }
      break;
    case MENU_MOSTRAR:
      // Realmente sólamente hay que llamar a la función mostrar.
      mostrar(&inicio);
      break;
    case MENU_SALIR:
    default:
      printf("¡Gracias por utilizar este programa!\n\n");
      break;
    }

  } while (opcionMenu != MENU_SALIR);
}

/**
 * Insertar
 * Añade un elemento en una lista ligada, para eso recibe un índice y el dato a
 * almacenar. En caso de que el índice ya exista, recorre los índices de los
 * elementos subsecuentes.
 * @param inicio Un apuntador al inicio de la lista.
 * @param valor El valor a almacenar
 * @param indice El índice para la posición del nuevo elemento.
 */
void insertar(Nodo **inicio, int valor, int indice)
{
  // Variables locales.
  Nodo *nuevo = (Nodo *)malloc(sizeof(Nodo)), // Asignamos la memoria necesaria para el nuevo elemento.
      *temporal = *inicio,                    // Temporal nos permite iterar sobre la lista, se inicializa con la referencia
                                              // al primer elemento de la lista.
      *anterior;                              // Esta variable es para tener una referencia al elemento inmediato anterior en la lista.

  // Asignamos los valores del nuevo elemento.
  nuevo->dato = valor;
  nuevo->id = indice;

  // Verificamos si la lista está vacía.
  if (temporal == NULL)
  {
    // Si la lista está vacía, nuestro nuevo elemento será el nuevo inicio.
    (*inicio) = nuevo;

    // El siguiente elmento es NULL puesto que la lista está vacía.
    nuevo->siguiente = NULL;
  }
  else
  {
    // Verificamos si tenemos que insertar al inicio de la lista.
    if (indice <= temporal->id)
    {
      // El inicio será nuestro nuevo elemento.
      (*inicio) = nuevo;

      // El siguiente elemento del inicio, será nuestro temporal (inicio anterior).
      nuevo->siguiente = temporal;
    }
    else
    {
      // Iniciamos con anterior siendo el actual temporal.
      anterior = temporal;

      // Aumentamos temporal al siguiente elemento.
      temporal = temporal->siguiente;

      // Iteramos mientras no sea nulo.
      while (temporal != NULL)
      {
        // Verificamos si nuestro indice es mayor o igual al del elemento
        // actual.
        if (indice > anterior->id && indice <= temporal->id)
        {
          // Si el índice fue mayor o igual, insertaremos nuestro nuevo elemento
          // en la posición actual.
          nuevo->siguiente = temporal;
          anterior->siguiente = nuevo;

          // Usamos un `return` para finalizar la ejecución de la función.
          return;
        }

        // Anterior será el elemento actual.
        anterior = temporal;

        // Iteramos con el siguiente elemento de la lista.
        temporal = temporal->siguiente;
      }

      // En caso de que lleguemos a este punto, quiere decir que el elemento deberá
      // insertarse como siguiente inmediato del "anterior" ya que llegamos al final
      // de la lista y ningún índice fue menor.
      anterior->siguiente = nuevo;

      // El siguiente de nuestro nuevo elemento será NULL ya que corresonde al fin
      // de nuestra lista.
      nuevo->siguiente = NULL;
    }
  }
}

/**
 * Eliminar
 * Elimina un elemento presente en una lista simplemente ligada mediante
 * el índice proporcionado. En caso de que el índice no exista, regresará
 * una BANDERA_INDICE_NO_ENCONTRADO.
 * @param inicio Un apuntador al primer elemento presente en la lista.
 * @param indice Un entero con el índice a buscar en nuestra lista.
 * @return Un entero con el valor presente en el elemento con el índice especificado, o una BANDERA_INDICE_NO_ENCONTRADO si el índice no fue encontrado.
 */
int eliminar(Nodo **inicio, int indiceAEliminar)
{
  // Variables locales.
  Nodo *temporal = *inicio, // Inicializamos temporal al inicio de nuestra lista.
      *anterior;            // Variable para la iteración en una lista simplemente ligada.
  int datoTemporal;         // Variable para almacenar el dato temporal mientras liberamos la memoria
                            // del elemento a eliminar en la lista.

  // Revisamos si la lista no está vacía.
  if (temporal == NULL)
  {
    // Regresamos la bandera.
    return BANDERA_INDICE_NO_ENCONTRADO;
  }
  else
  {
    // Verificamos si el primer elemento (inicio) corresponde al índice especificado.
    if (temporal->id == indiceAEliminar)
    {
      // Guardamos el dato que estaba presente en el elemento que eliminaremos para poder
      // regrearlo posteriormente.
      datoTemporal = temporal->dato;

      // Desplazamos el apuntador de inicio al siguiente elemento de temporal.
      (*inicio) = temporal->siguiente;

      // Liberamos la memoria de temporal
      free(temporal);

      // Regresamos el dato que estaba presente en temporal.
      return datoTemporal;
    }
    else
    {
      // Dado que el primer elemento no es aquél que buscamos eliminar, avanzamos el apuntador
      // temporal y colocamos anterior al inicio.
      anterior = temporal;
      temporal = temporal->siguiente;
      // Iteramos sobre la lista en busca del índice especificado.
      while (temporal != NULL)
      {
        // Verificamos el índice.
        if (temporal->id == indiceAEliminar)
        {
          // Guardamos el dato que estaba presente en el elemento que eliminaremos para poder
          // regresarlo posteriormente.
          datoTemporal = temporal->dato;

          // Eliminamos la relación del elemento anterior con el elemento
          // actual.
          anterior->siguiente = temporal->siguiente;

          // Liberamos la memoria del elemento temporal.
          free(temporal);

          // Regresamos el dato temporal.
          return datoTemporal;
        }

        // Ahora nuestro elemento "anterior" será el actual "temporal".
        anterior = temporal;

        // Aumentamos temporal al siguiente elemento.
        temporal = temporal->siguiente;
      }

      // Si terminamos el ciclo y no encontramos el índice que buscábamos, regresamos
      // la bandera.
      return BANDERA_INDICE_NO_ENCONTRADO;
    }
  }
}

/**
 * Mostrar
 * Imprime en la terminal todos los elementos presentes en nuestra lista
 * simplemente ligada.
 * @param inicio La referencia al apuntador de inicio de nuestra lista.
 */
void mostrar(Nodo **inicio)
{
  // Variables locales.
  Nodo *temporal = *inicio; // Apuntador temporal al inicio de la lista.

  // Verificamos si la lista está vacía.
  if (temporal == NULL)
  {
    printf("¡La lista se encuentra vacía!\n");
  }
  else
  {
    // Mensaje inicial.
    printf("Elementos de la lista:\n\n");
    printf("|-----------------|\n");
    printf("| Índice |  Dato  |\n");

    // Iteramos por la lista.
    while (temporal != NULL)
    {
      // Mostramos el elemento.
      printf("|-----------------|\n");
      printf("| %6i | %6i |\n", temporal->id, temporal->dato);

      // Avanzamos el apuntador.
      temporal = temporal->siguiente;
    }

    // Barra final.
    printf("|-----------------|\n\n");
  }
}
