/**
 * practica7.c - Archivo base de la práctica
 *
 * Práctica: 7
 * Objetivo: Implementar el código para insertar, eliminar y buscar un elemento en una lista doble.
 *
 * Equipo:
    - Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 5/Diciembre/2020
*/
#include <stdio.h>  // Para operaciones de entrada y salida.
#include <stdlib.h> // Para usar `malloc` etc...

// Constantes de menú.
#define MENU_INSERTAR 1
#define MENU_ELIMINAR_POR_ID 2
#define MENU_ELIMINAR_POR_DATO 3
#define MENU_BUSCAR_POR_ID 4
#define MENU_BUSCAR_POR_DATO 5
#define MENU_MOSTRAR 6
#define MENU_SALIR 7

// Constantes de operación.
#define BANDERA_LISTA_VACIA -32256
#define BANDERA_INDICE_NO_ENCONTRADO -32255
#define BANDERA_DATO_NO_ENCONTRADO -32254

// Estructura para los nodos de la lista doblemente ligada.
typedef struct nodo
{
  int id;                 // Un id para el nodo.
  int dato;               // El dato dentro del nodo.
  struct nodo *anterior;  // Un apuntador al nodo anterior.
  struct nodo *siguiente; // Un apuntador al nodo siguiente.
} Nodo;

// Prototipos de funciones.
void insertar(Nodo **, int, int);  // Añade un nuevo elemento a una lista.
Nodo *buscarPorID(Nodo **, int);   // Buscar por ID un elemento de la lista.
Nodo *buscarPorDato(Nodo **, int); // Buscar por Dato un elemento de la lista.
int eliminarPorID(Nodo **, int);   // Elimina, si existe, el primer elemento que tenga el ID proporcionado.
int eliminarPorDato(Nodo **, int); // Elimina, si existe, el primer elemento que tenga el Dato proporcionado.
void mostrar(Nodo **);             // Imprime el contenido de la lista en la terminal.

// Función principal
int main(int argc, char *argv[])
{
  // Variables locales.
  Nodo *inicio = NULL,
       *nodoTemporal = NULL;
  int opcionMenu,
      datoTemporal,
      indiceTemporal;

  // Ciclo para menú principal.
  do
  {
    // Mostramos las opciones del menú.
    printf("\tMenú principal.\n\n");
    printf("Seleccione una operación a realizar:\n\n");
    printf("\t%i) Insertar un nuevo elemento.\n", MENU_INSERTAR);
    printf("\t%i) Eliminar un elemento por ID.\n", MENU_ELIMINAR_POR_ID);
    printf("\t%i) Eliminar un elemento por dato.\n", MENU_ELIMINAR_POR_DATO);
    printf("\t%i) Buscar un elemento por ID.\n", MENU_BUSCAR_POR_ID);
    printf("\t%i) Buscar un elemento por dato.\n", MENU_BUSCAR_POR_DATO);
    printf("\t%i) Mostrar lista.\n", MENU_MOSTRAR);
    printf("\t-\n");
    printf("\t%i) Salir.\n\n", MENU_SALIR);

    // Leer la opción del menú.
    do
    {
      printf("[%i-%i]> ", MENU_INSERTAR, MENU_SALIR);
      scanf("%i", &opcionMenu);
    } while (opcionMenu < MENU_INSERTAR || opcionMenu > MENU_SALIR); // Validación de entrada.

    // Realizamos la operación apropiada.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos el dato a introducir.
      printf("Dato para el elemento: ");
      scanf("%i", &datoTemporal);

      // Leemos el índice para insertar.
      printf("Índice para el elemento: ");
      scanf("%i", &indiceTemporal);

      // Insertamos el elemento.
      insertar(&inicio, datoTemporal, indiceTemporal);
      break;
    case MENU_ELIMINAR_POR_ID:
      // Leemos el índice a eliminar.
      printf("Índice del elemento a eliminar: ");
      scanf("%i", &indiceTemporal);

      // Realizamos la operación y almacenamos el valor de retorno.
      datoTemporal = eliminarPorID(&inicio, indiceTemporal);

      // Verificamos si recibimos alguna bandera o el dato.
      if (datoTemporal == BANDERA_LISTA_VACIA)
      {
        printf("No es posible eliminar elementos si la lista está vacía.\n");
      }
      else if (datoTemporal == BANDERA_INDICE_NO_ENCONTRADO)
      {
        printf("No se pudo encontrar y eliminar un elemento con el índice #%i.\n", indiceTemporal);
      }
      else
      {
        printf("Se eliminó el elemento con el índice #%i, que contenía el dato: %i.\n", indiceTemporal, datoTemporal);
      }
      break;
    case MENU_ELIMINAR_POR_DATO:
      // Leemos el dato a eliminar.
      printf("Dato del elemento a eliminar: ");
      scanf("%i", &datoTemporal);

      // Realizamos la operación y almacenamos el valor de retorno.
      indiceTemporal = eliminarPorDato(&inicio, datoTemporal);

      // Verificamos si recibimos alguna bandera o el índice.
      if (indiceTemporal == BANDERA_LISTA_VACIA)
      {
        printf("No es posible eliminar elementos si la lista está vacía.\n");
      }
      else if (indiceTemporal == BANDERA_DATO_NO_ENCONTRADO)
      {
        printf("No se pudo encontrar y eliminar un elemento con el dato: %i.\n", datoTemporal);
      }
      else
      {
        printf("Se eliminó el elemento con el dato \"%i\", que tenía el índice: #%i.\n", datoTemporal, indiceTemporal);
      }
      break;
    case MENU_BUSCAR_POR_ID:
      // Leemos el índice a buscar.
      printf("Índice del elemento a buscar: ");
      scanf("%i", &indiceTemporal);

      // Realizamos la operación y guardamos el resultado.
      nodoTemporal = buscarPorID(&inicio, indiceTemporal);

      // Verificamos si se encontró un elemento.
      if (nodoTemporal != NULL)
      {
        // Si se encontró un elemento, mostramos su información.
        printf("El elemento con el índice #%i contiene: %i\n", indiceTemporal, nodoTemporal->dato);
      }
      else
      {
        // No se encontró un elemento, mostramos un mensaje.
        printf("No se ha podido encontrar algún elemento con el índice: %i.\n", indiceTemporal);
      }
      break;
    case MENU_BUSCAR_POR_DATO:
      // Leemos el índice a buscar.
      printf("Dato del elemento a buscar: ");
      scanf("%i", &datoTemporal);

      // Realizamos la operación y guardamos el resultado.
      nodoTemporal = buscarPorDato(&inicio, datoTemporal);

      // Verificamos si se encontró un elemento.
      if (nodoTemporal != NULL)
      {
        // Si se encontró un elemento, mostramos su información.
        printf("El elemento con el dato \"%i\" tiene el índice: %i\n", datoTemporal, nodoTemporal->id);
      }
      else
      {
        // No se encontró un elemento, mostramos un mensaje.
        printf("No se ha podido encontrar algún elemento con el dato: %i.\n", datoTemporal);
      }
      break;
    case MENU_MOSTRAR:
      // Aquí realmente sólamente hay que llamar a la función mostrar.
      mostrar(&inicio);
      break;
    case MENU_SALIR:
    default:
      printf("¡Gracias por utilizar este programa!\n\n");
      break;
    }
  } while (opcionMenu != MENU_SALIR);

  // En este punto, la ejecución fue exitosa, exit status = 0.
  return 0;
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
      *anterior;                              // Un apuntador temporal para el elemento anterior.

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
      // Comenzamos avanzando al siguiente elemento del inicio.
      anterior = temporal;
      temporal = temporal->siguiente;

      // Iteramos mientras el siguiente elemento no sea nulo.
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

        // Iteramos con el siguiente elemento en la lista.
        anterior = temporal;
        temporal = temporal->siguiente;
      }

      // Si llegamos a este punto, quiere decir que no encontramos ningún punto
      // en medio de la lista dónde colocar el elemento ordenado así que lo
      // añadimos al final.
      anterior->siguiente = nuevo;

      // El siguiente de nuestro nuevo elemento será NULL ya que corresonde al fin
      // de nuestra lista.
      nuevo->siguiente = NULL;
    }
  }
}

/**
 * Buscar por ID
 * Realiza la búsqueda dentro de los nodos de la lista doblemente ligada mediante
 * IDs.
 * @param inicio Un apuntador al inicio de la lista.
 * @param indice El índice a buscar en la lista.
 * @return Un apuntador al elemento encontrado o NULL si no se encontró.
 */
Nodo *buscarPorID(Nodo **inicio, int indice)
{
  // Variables locales.
  Nodo *temporal; // Apuntador temporal para recorrer la lista.

  // Verificamos si la lista está vacía.
  if ((*inicio) == NULL)
  {
    return NULL;
  }
  else
  {
    // Iteramos sobre la lista.
    for (temporal = (*inicio); temporal != NULL; temporal = temporal->siguiente)
    {
      // Si encontramos el índice, regresamos un apuntador al elemento.
      if (temporal->id == indice)
      {
        return temporal;
      }
    }

    // Si recorrimos el ciclo sin éxito, regresamos NULL.
    return NULL;
  }
}

/**
 * Buscar por Dato
 * Realiza la búsqueda dentro de los nodos de la lista doblemente ligada mediante
 * Datos.
 * @param inicio Un apuntador al inicio de la lista.
 * @param dato El dato a buscar en la lista.
 * @return Un apuntador al elemento encontrado o NULL si no se encontró.
 */
Nodo *buscarPorDato(Nodo **inicio, int dato)
{
  // Variables locales.
  Nodo *temporal; // Apuntador temporal para recorrer la lista.

  // Verificamos si la lista está vacía.
  if ((*inicio) == NULL)
  {
    return NULL;
  }
  else
  {
    // Iteramos sobre la lista.
    for (temporal = (*inicio); temporal != NULL; temporal = temporal->siguiente)
    {
      // Si encontramos el índice, regresamos un apuntador al elemento.
      if (temporal->dato == dato)
      {
        return temporal;
      }
    }

    // Si recorrimos el ciclo sin éxito, regresamos NULL.
    return NULL;
  }
}

// int eliminarPorID(Nodo **, int);   // Elimina, si existe, el primer elemento que tenga el ID proporcionado.
// int eliminarPorDato(Nodo **, int);

/**
 * Eliminar por ID.
 * Busca un elemento con el ID proporcionado y lo elimina de la lista doblemente
 * ligada, en caso de no encontrarlo o que la lista esté vacía, regresa las banderas
 * correspondientes.
 * @param inicio Un apuntador al primer elemento de la lista ligada.
 * @param indice El índice del elemento a buscar y eliminar.
 * @return Un entero siendo el dato del elemento que fue eliminado, o si no pudo encontrarse el elemento, o si la lista está vacía, una bandera correspondiente.
 */
int eliminarPorID(Nodo **inicio, int indice)
{
  // Variables locales.
  Nodo *encontrado, // Para almacenar el dato encontrado para eliminar.
      *anterior;    // Para almacenar una referencia al elemento inmediato anterior.
  int temporal;     // Para almacenar, temporalmente, el dato a regresar.

  // Revisamos si la lista no está vacía.
  if ((*inicio) == NULL)
  {
    return BANDERA_LISTA_VACIA;
  }
  else
  {
    // Buscamos el elemento a eliminar.
    encontrado = buscarPorID(inicio, indice);

    // Verificamos si encontramos el elemento a eliminar.
    if (encontrado != NULL)
    {
      // Usamos una variable temporal "anterior" para poder hacer operaciones.
      for (anterior = (*inicio); anterior != NULL && anterior->siguiente != encontrado; anterior = anterior->siguiente)
        ;

      // Verificamos si anterior existe.
      if (anterior == NULL)
      {
        // Anterior no existe, es el inicio.
        (*inicio) = encontrado->siguiente;
      }
      else
      {
        // Ajustamos anterior para saltar el elemento actual.
        anterior->siguiente = encontrado->siguiente;
      }

      // Guardamos el dato en temporal.
      temporal = encontrado->dato;

      // Liberamos la memoria utilizada por el elemento.
      free(encontrado);

      // Regresamos el dato encontrado guardado previamente.
      return temporal;
    }
    else
    {
      // No pudimos encontrar el índice.
      return BANDERA_INDICE_NO_ENCONTRADO;
    }
  }
}

/**
 * Eliminar por Dato.
 * Busca un elemento con el Dato proporcionado y lo elimina de la lista doblemente
 * ligada, en caso de no encontrarlo o que la lista esté vacía, regresa las banderas
 * correspondientes.
 * @param inicio Un apuntador al primer elemento de la lista doblemente ligada.
 * @param dato El dato del elemento a buscar y eliminar.
 * @return Un entero siendo el dato del elemento que fue eliminado, o si no pudo encontrarse el elemento, o si la lista está vacía, una bandera correspondiente.
 */
int eliminarPorDato(Nodo **inicio, int dato)
{
  // Variables locales.
  Nodo *encontrado, // Para almacenar el dato encontrado para eliminar.
      *anterior;    // Para almacenar una referencia al elemento inmediato anterior.
  int temporal;     // Para almacenar, temporalmente, el índice a regresar.

  // Revisamos si la lista no está vacía.
  if ((*inicio) == NULL)
  {
    return BANDERA_LISTA_VACIA;
  }
  else
  {
    // Buscamos el elemento a eliminar.
    encontrado = buscarPorDato(inicio, dato);

    // Verificamos si encontramos el elemento a eliminar.
    if (encontrado != NULL)
    {
      // Usamos una variable temporal "anterior" para poder hacer operaciones.
      for (anterior = (*inicio); anterior != NULL && anterior->siguiente != encontrado; anterior = anterior->siguiente)
        ;

      // Verificamos si es el primer elemento.
      if (anterior == NULL)
      {
        // Es el primer elemento.
        (*inicio) = encontrado->siguiente;
      }
      else
      {
        // No es el primer elemento.
        anterior->siguiente = encontrado->siguiente;
      }

      // Guardamos el índice en temporal.
      temporal = encontrado->id;

      // Liberamos la memoria utilizada por el elemento.
      free(encontrado);

      // Regresamos el índice encontrado guardado previamente.
      return temporal;
    }
    else
    {
      // No pudimos encontrar el dato.
      return BANDERA_DATO_NO_ENCONTRADO;
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
