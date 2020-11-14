/**
 * practica4.c - Archivo base de la práctica
 *
 * Práctica: 4
 * Objetivo: Implementar las colas estática y dinámica para que trabajen con 3 colas diferentes, las tres colas deberán ser de enteros.
 *
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
 * 13/Noviembre/2020.
 */
#include <stdio.h>  // Para operaciones de entrada y salida estándar...
#include <stdlib.h> // Para usar `malloc` etc...

// Constantes de operación
#define TAM_MAX_COLA_ESTATICA 100          // El número máximo de elementos en la cola estática.
#define EJECUCION_COLAS_DINAMICAS 1        // Constante para determinar la ejecución utilizando colas dinámicas.
#define EJECUCION_COLAS_ESTATICAS 2        // Constante para determinar la ejecución utilizando  colas estáticas.
#define MENU_INSERTAR 1                    // Opción del menú principal para la operación "insertar".
#define MENU_IMPRIMIR 2                    // Opción del menú principal para la operación "imprimir".
#define MENU_ELIMINAR 3                    // Opción del menú principal para la operación "eliminar".
#define MENU_SALIR 4                       // Opción del menú principal para salir del programa.
#define BANDERA_COLA_ESTATICA_VACIA -32256 // Bandera para cuando nuestra cola estática se encuentre vacía.
#define BANDERA_COLA_ESTATICA_LLENA 32356  // Bandera para cuando nuestra cola estática esté llena.
#define BANDERA_COLA_DINAMICA_VACIA -32256 // Bandera para cuando nuestra cola dinámica esté vacía.

// Estructura dinámica para colas.
typedef struct cola_dinamica
{
  int dato;
  struct cola_din *siguiente;
} ColaDinamica;

// Prototipos de funciones para colas dinámicas.
void encolarColaDinamica(ColaDinamica **, ColaDinamica **, int); // Añade un dato a una cola dinámica.
int desencolarColaDinamica(ColaDinamica **, ColaDinamica **);    // Elimina el primer dato presente en una cola dinámica.
void imprimirColaDinamica(ColaDinamica **);                      // Imprime una cola dinámica.

// Prototipos de funciones para colas estáticas.
int encolarColaEstatica(int *, int *, int);    // Añade un elemento a una cola estática.
int desencolarColaEstatica(int *, int, int *); // Extrae un elemento de una cola estática.
void imprimirColaEstatica(int, int, int *);    // Muestra una cola estática.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int opcionEjecucion, // Para el tipo de ejecución (colas dinámicas vs. estáticas)
      opcionCola,      // Para la cola en la cual realizar la operación seleccionada.
      opcionMenu,      // Para la opción del menú con la operación a realizar.
      temporal;        // Dato temporal para operaciones variadas.
  // Apuntadores para las colas dinámicas.
  ColaDinamica *inicioColaDinamica1 = NULL,
               *finColaDinamica1 = NULL,
               *inicioColaDinamica2 = NULL,
               *finColaDinamica2 = NULL,
               *inicioColaDinamica3 = NULL,
               *finColaDinamica3 = NULL;
  // Elementos para las colas estáticas.
  int colaEstatica1[TAM_MAX_COLA_ESTATICA],
      colaEstatica2[TAM_MAX_COLA_ESTATICA],
      colaEstatica3[TAM_MAX_COLA_ESTATICA],
      inicioColaEstatica1 = -1,
      finColaEstatica1 = -1,
      inicioColaEstatica2 = -1,
      finColaEstatica2 = -1,
      inicioColaEstatica3 = -1,
      finColaEstatica3 = -1;

  // Definir el tipo de ejecución.
  printf("¿Qué tipo de colas desea utilizar?\n");
  printf("\t%i) Dinámicas.\n", EJECUCION_COLAS_DINAMICAS);
  printf("\t%i) Estáticas (máximo de %i elementos).\n\n", EJECUCION_COLAS_ESTATICAS, TAM_MAX_COLA_ESTATICA);

  // Ciclo para leer y validar la entrada.
  do
  {
    printf("> ");
    scanf("%i", &opcionEjecucion);
  } while (opcionEjecucion != EJECUCION_COLAS_DINAMICAS && opcionEjecucion != EJECUCION_COLAS_ESTATICAS);

  // Ciclo de menú principal.
  do
  {
    // Imprimimos el menú.
    printf("Menú Principal\n\n");
    printf("Seleccione una opción:\n\n");
    printf("\t%i) Insertar un elemento.\n", MENU_INSERTAR);
    printf("\t%i) Imprimir una cola.\n", MENU_IMPRIMIR);
    printf("\t%i) Eliminar el primer elemento de una cola.\n", MENU_ELIMINAR);
    printf("\t -\n");
    printf("\t%i) Salir del programa.\n\n", MENU_SALIR);

    // Leemos la opción seleccionada.
    do
    {
      printf("> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu < 1 || opcionMenu > 4); // Validamos la opción seleccionada.

    // Leemos la cola en la cual realizaremos la operación si no se eligió la opción de salir.
    if (opcionMenu != MENU_SALIR)
    {
      do
      {
        printf("¿En qué cola desea realizar la operación?\n[1-3]> ");
        scanf("%i", &opcionCola);
      } while (opcionCola < 1 || opcionCola > 3); // Validamos la opción de la cola seleccionada.
    }

    // Realizamos la operación correspondiente.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos el dato a insertar.
      printf("Ingresa el dato a insertar en la cola #%i:\n> ", opcionCola);
      scanf("%i", &temporal);

      // Determinamos el tipo de cola para la operación.
      if (opcionEjecucion == EJECUCION_COLAS_DINAMICAS)
      {
        // Determinamos la cola particular para la operación.
        if (opcionCola == 1)
        {
          // Insertamos un elemento en la cola dinámica 1.
          encolarColaDinamica(&inicioColaDinamica1, &finColaDinamica1, temporal);
        }
        else if (opcionCola == 2)
        {
          // Insertamos un elemento en la cola dinámica 2.
          encolarColaDinamica(&inicioColaDinamica2, &finColaDinamica2, temporal);
        }
        else
        {
          // Insertamos un elemento en la cola dinámica 3.
          encolarColaDinamica(&inicioColaDinamica3, &finColaDinamica3, temporal);
        }
      }
      else
      {
        // Determinamos la cola particular para la operación.
        if (opcionCola == 1)
        {
          // Insertamos un elemento en la cola estática 1.
          temporal = encolarColaEstatica(&finColaEstatica1, colaEstatica1, temporal);
        }
        else if (opcionCola == 2)
        {
          // Insertamos un elemento en la cola estática 2.
          temporal = encolarColaEstatica(&finColaEstatica2, colaEstatica2, temporal);
        }
        else
        {
          // Insertamos un elemento en la cola estática 3.
          temporal = encolarColaEstatica(&finColaEstatica3, colaEstatica3, temporal);
        }

        // Verificamos si recibimos una BANDERA_COLA_ESTATICA_LLENA.
        if (temporal == BANDERA_COLA_ESTATICA_LLENA)
        {
          printf("No se ha podido añadir el elemento a la cola estática porque ésta se encuentra llena.\n");
        }
      }
      break;
    case MENU_ELIMINAR:
      // Determinamos el tipo de cola para la ejecución.
      if (opcionEjecucion == EJECUCION_COLAS_DINAMICAS)
      {
        // Determinamos la cola particular para la operación.
        if (opcionCola == 1)
        {
          // Eliminamos el primer elemento presente en la cola dinámica 1.
          temporal = desencolarColaDinamica(&inicioColaDinamica1, &finColaDinamica2);
        }
        else if (opcionCola == 2)
        {
          // Eliminamos el primer elemento presente en la cola dinámica 2.
          temporal = desencolarColaDinamica(&inicioColaDinamica2, &finColaDinamica2);
        }
        else
        {
          // Eliminamos el primer elemento presente en la cola dinámica 3.
          temporal = desencolarColaDinamica(&inicioColaDinamica3, &finColaDinamica3);
        }

        // Verificamos si recibimos una BANDERA_COLA_DINAMICA_VACIA.
        if (temporal == BANDERA_COLA_DINAMICA_VACIA)
        {
          printf("No se ha podido eliminar ningún elemento de la cola dinámica %i porque ésta se encuentra vacía.\n", opcionCola);
        }
        else
        {
          printf("Se ha eliminado el primer elemento en la cola dinámica %i: %i\n", opcionCola, temporal);
        }
      }
      else
      {
        // Determinamos la cola particular para la operación.
        if (opcionCola == 1)
        {
          // Eliminamos el primer elemento presente en la cola estática 1.
          temporal = desencolarColaEstatica(&inicioColaEstatica1, finColaEstatica1, colaEstatica1);
        }
        else if (opcionCola == 2)
        {
          // Eliminamos el primer elemento presente en la cola estática 2.
          temporal = desencolarColaEstatica(&inicioColaEstatica2, finColaEstatica2, colaEstatica2);
        }
        else
        {
          // Eliminamos el primer elemento presente en la cola estática 3.
          temporal = desencolarColaEstatica(&inicioColaEstatica3, finColaEstatica3, colaEstatica3);
        }

        // Verificamos si recibimos una BANDERA_COLA_ESTATICA_VACIA.
        if (temporal == BANDERA_COLA_ESTATICA_VACIA)
        {
          printf("No se ha podido eliminar ningún elemento de la cola estática %i porque ésta se encuentra vacía.\n", opcionCola);
        }
        else
        {
          printf("Se ha eliminado el primer elemento en la cola estática %i: %i\n", opcionCola, temporal);
        }
      }
      break;
    case MENU_IMPRIMIR:
      // Determinamos el tipo de cola para la ejecución.
      if (opcionEjecucion == EJECUCION_COLAS_DINAMICAS)
      {
        // Mensaje para impresión.
        printf("Los elementos presentes en la cola dinámica %i son: ", opcionCola);

        // Determinamos la cola particular para la operación.
        if (opcionCola == 1)
        {
          // Mostramos los elementos dentro de la cola dinámica 1.
          imprimirColaDinamica(&inicioColaDinamica1);
        }
        else if (opcionCola == 2)
        {
          // Mostramos los elementos dentro de la cola dinámica 2.
          imprimirColaDinamica(&inicioColaDinamica2);
        }
        else
        {
          // Mostramos los elementos dentro de la cola dinámica 3.
          imprimirColaDinamica(&inicioColaDinamica3);
        }
      }
      else
      {
        // Mensaje para impresión.
        printf("Los elementos presentes en la cola estática %i son: ", opcionCola);

        // Determinamos la cola particular para la operación.
        if (opcionCola == 1)
        {
          // Mostramos los elementos dentro de la cola estática 1.
          imprimirColaEstatica(inicioColaEstatica1, finColaEstatica1, colaEstatica1);
        }
        else if (opcionCola == 2)
        {
          // Mostramos los elementos dentro de la cola estática 2.
          imprimirColaEstatica(inicioColaEstatica2, finColaEstatica2, colaEstatica2);
        }
        else
        {
          // Mostramos los elementos dentro de la cola estática 3.
          imprimirColaEstatica(inicioColaEstatica3, finColaEstatica3, colaEstatica3);
        }
      }

      // Salto de línea final.
      printf("\n");
      break;
    default:
      printf("¡Gracias por utilizar este programa!\n");
      break;
    }
  } while (opcionMenu != MENU_SALIR);

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Encolar cola dinámica
 * Añade un elemento al final de una cola dinámica.
 * @param inicio Un apuntador al inicio de la cola.
 * @param fin Un apuntador al final de la cola.
 * @param dato El dato a añadir a la cola.
 */
void encolarColaDinamica(ColaDinamica **inicio, ColaDinamica **fin, int nuevoElemento)
{
  // Variables locales.
  ColaDinamica *temporal = (ColaDinamica *)malloc(sizeof(ColaDinamica)),
               *finTemporal;

  // Creamos el nuevo elemento.
  temporal->dato = nuevoElemento;
  temporal->siguiente = NULL;

  // Revisamos si la cola contiene elementos previos.
  if (*fin == NULL)
  {
    // Si la cola no tiene elementos previos, el inicio y el fin serán el nuevo elemento.
    *inicio = temporal;
    *fin = temporal;
  }
  else
  {
    // Si la cola tiene elementos previos, movemos nuestro elemento al final de la misma.
    finTemporal = *fin;
    finTemporal->siguiente = temporal;
    *fin = finTemporal->siguiente;
  }
}

/**
 * Desencolar cola dinámica.
 * Extrae y elimina el primer elemento presente en una cola dinámica.
 * @param inicio Un apuntador al inicio de la cola en cuestión.
 * @return Un entero con el primer elemento presente en la cola o BANDERA_COLA_DINAMICA_VACIA si la cola dinámica está vacía.
 */
int desencolarColaDinamica(ColaDinamica **inicio, ColaDinamica **fin)
{
  // Variables locales.
  ColaDinamica *colaTemporal;
  int datoTemporal;

  // Verificamos si la cola está vacía.
  if (*inicio == NULL)
  {
    // Si la cola está vacía regresamos una BANDERA_COLA_DINAMICA_VACIA.
    return BANDERA_COLA_DINAMICA_VACIA;
  }
  else
  {
    // Si la cola no está vacía, hacemos una copia temporal del inicio de la cola.
    colaTemporal = *inicio;

    // Asignamos al inicio de la cola al siguiente elemento inmediato.
    *inicio = colaTemporal->siguiente;

    // Extraemos el dato presente en el inicio anterior.
    datoTemporal = colaTemporal->dato;

    // Liberamos la memoria del elemento que era el inicio anterior.
    free(colaTemporal);

    // Regresamos el dato temporal.
    return datoTemporal;
  }
}

/**
 * Imprimir cola dinámica.
 * Muestra en la terminal el contenido de una cola dinámica.
 * @param inicio Un apuntador al inicio de la cola dinámica.
 */
void imprimirColaDinamica(ColaDinamica **inicio)
{
  // Variables locales.
  ColaDinamica *temporal = *inicio;

  // Ciclo para recorrer los elementos.
  while (temporal != NULL)
  {
    printf("%i ", temporal->dato);
    temporal = temporal->siguiente;
  }
}

/**
 * Encolar cola estática.
 * Añade un elemento al final de una cola estática si ésta aún tiene espacio suficiente.
 * @param inicio Un apuntador al índice del inicio de la cola estática.
 * @param fin Un apuntador al índice del final de la cola estática.
 * @param cola El arreglo con los elementos dentro de la cola.
 * @return Un entero uno si la operación fue exitosa o BANDERA_COLA_ESTATICA_LLENA si la cola está llena.
 */
int encolarColaEstatica(int *fin, int *cola, int nuevoElemento)
{
  // Verificamos si la cola está llena.
  if ((*fin + 1) >= TAM_MAX_COLA_ESTATICA)
  {
    // Regresamos la BANDERA_COLA_ESTATICA_LLENA porque ya no hay espacio en la cola.
    return BANDERA_COLA_ESTATICA_LLENA;
  }
  else
  {
    // Añadimos el elemento en la posición del índice final.
    cola[*fin] = nuevoElemento;

    // Aumentamos el índice final en uno.
    *fin += 1;

    // Regresamos un uno porque la ejecución fue correcta.
    return 1;
  }
}

/**
 * Desencolar cola estática.
 * Elimina el primer elemento presente en una cola estática y lo devuelve.
 * @param inicio Un apuntador al índice de inicio de la cola estática.
 * @param fin Un apuntador al índice del final de la cola estática.
 * @param cola El arreglo con los elementos dentro de la cola.
 * @return Un entero con el primer elemento presente en la cola estática o BANDERA_COLA_ESTATICA_VACIA si la cola está vacía.
 */
int desencolarColaEstatica(int *inicio, int fin, int *cola)
{
  // Variables locales.
  int temporal;

  // Verificamos que la cola no esté vacía.
  if (*inicio == fin)
  {
    // Regresamos la BANDERA_COLA_ESTATICA_VACIA.
    return BANDERA_COLA_ESTATICA_VACIA;
  }
  else
  {
    // Asignamos el valor temporal al inicio de la cola.
    temporal = cola[*inicio];

    // Aumentamos el inicio en uno.
    *inicio += 1;

    // Regresamos el valor temporal.
    return temporal;
  }
}

/**
 * Imprimir cola estática.
 * Muestra en la terminal el contenido de una cola estática.
 * @param inicio El índice del primer elemento en nuestra cola.
 * @param fin El índice del último elemento en nuestra cola.
 * @param cola El arreglo con los elementos dentro de la cola.
 */
void imprimirColaEstatica(int inicio, int fin, int *cola)
{
  // Variables locales.
  int i = inicio;

  // Ciclo para recorrer los elementos.
  for (/* Nada que inicializar por aquí */; i < fin && i < TAM_MAX_COLA_ESTATICA; i++)
  {
    printf("%i ", cola[i]);
  }
}
