/**
 * practica5.c - Archivo base de la práctica
 *
 * Práctica: 5
 * Objetivo: Implementar una cola estática circular.
 *
 * Equipo:
 *   - Humberto Alejandro Ortega Alcocer (2016630495) <hortegaa1500@alumno.ipn.mx>
 *
 * Materia: Estructuras de Datos.
 * Grupo: 1CM4
 * Profesor: Alberto Alcántara
 * ESCOM - IPN
 * 18/Noviembre/2020
 */
#include <stdio.h> // Para operaciones de entrada y salida estándar.

// Constantes de operación.
#define TAM_MAX_COLA 10           // 10 es un valor razonable.
#define MENU_SALIR 4              // Para la opción "salir" del menú.
#define MENU_INSERTAR 1           // Para la opción "insertar" del menú.
#define MENU_ELIMINAR 2           // Para la opción "eliminar" del menú.
#define MENU_IMPRIMIR 3           // Para la opción de "imprimir" del menú.
#define BANDERA_COLA_LLENA -32256 // Bandera para cuando la cola se encuentre llena.
#define BANDERA_COLA_VACIA -32255 // Bandera para cuando la cola se encuentre vacía.

// Prototipos de funciones.
void imprimirColaCircular(int, int, int *);         // Para mostrar el contenido dentro de una cola circular.
int insertarEnColaCircular(int, int *, int *, int); // Para insertar un elemento en una cola circular.
int eliminarColaCircular(int *, int, int *);        // Para eliminar un elemento de una cola circular.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int inicio = 0,                 // El índice del inicio de la cola.
      fin = 0,                    // El índice del final de la cola.
      colaCircular[TAM_MAX_COLA], // La cola.
      opcionMenu,                 // Para almacenar la opción del menú seleccionada.
      datoTemporal,               // Para almacenar datos temporales durante la ejecución.
      respuestaTemporal;          // Para almacenar una respuesta temporal de alguna función.

  // Mensaje inicial.
  printf("Práctica 5 - Colas Circulares\n");
  printf("Tamaño máximo de la cola: %i\n\n", TAM_MAX_COLA - 1);

  // Ciclo principal.
  do
  {
    // Mostramos el menú.
    printf("Seleccione la operación a realizar:\n\n");
    printf("\t%i) Insertar un elemento en la cola.\n", MENU_INSERTAR);
    printf("\t%i) Eliminar el primer elemento en la cola.\n", MENU_ELIMINAR);
    printf("\t%i) Imprimir el contenido de la cola.\n", MENU_IMPRIMIR);
    printf("\t-\n");
    printf("\t%i) Salir del programa.\n\n", MENU_SALIR);

    // Leemos la opción.
    do
    {
      printf("> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu < 1 || opcionMenu > 4); // Validamos la entrada.

    // Realizamos la operación apropiada.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos el dato a insertar.
      printf("¿Qué dato desea ingresar?\n> ");
      scanf("%i", &datoTemporal);

      // Realizamos la operación.
      respuestaTemporal = insertarEnColaCircular(inicio, &fin, colaCircular, datoTemporal);

      // Verificamos si no recibimos una BANDERA_COLA_LLENA.
      if (respuestaTemporal == BANDERA_COLA_LLENA)
      {
        printf("No fue posible insertar un elemento en la cola porque ésta se encuentra llena.\n");
      }
      else
      {
        printf("Se insertó correctamente el dato %i en la cola circular.\n", datoTemporal);
      }

      // Fin de la operación insertar.
      break;
    case MENU_ELIMINAR:
      // Realizamos la operación.
      respuestaTemporal = eliminarColaCircular(&inicio, fin, colaCircular);

      // Verificamos si no recibimos una BANDERA_COLA_VACIA.
      if (respuestaTemporal == BANDERA_COLA_VACIA)
      {
        printf("No se ha podido eliminar ningún elemento dado que la cola se encuentra vacía.\n");
      }
      else
      {
        printf("Se ha eliminado el elemento: %i de la cola circular.\n", respuestaTemporal);
      }

      // Fin de la operación eliminar.
      break;
    case MENU_IMPRIMIR:
      // Mostramos un mensaje con los contenidos.
      printf("El contenido de la cola es: ");

      // Mostramos la cola.
      imprimirColaCircular(inicio, fin, colaCircular);

      // Salto de línea final.
      printf("\n");

      // Fin de la operación imprimir.
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
 * Insertar en cola circular.
 * Inserta un nuevo elemento en la cola circular.
 * @param inicio Un apuntador a la variable con el índice del inicio de la cola circular.
 * @param fin Un apuntador a la variable con el índice del fin de la cola circular.
 * @param cola El arreglo con los elementos dentro de la cola.
 * @param nuevoDato El nuevo dato a insertar en la cola.
 * @return Un entero 0 si la operación fue exitosa, BANDERA_COLA_LLENA si la cola ya se encuentra llena.
 */
int insertarEnColaCircular(int inicio, int *fin, int *cola, int nuevoDato)
{
  // Variables locales.
  int finTemporal = *fin; // Variable para almacenar temporalmente el índice final.

  // Verificamos si tenemos espacio para aumentar el índice y, sino, regresamos una bandera.
  if ((*fin + 1) >= TAM_MAX_COLA)
  {
    if (inicio == 0)
    {
      return BANDERA_COLA_LLENA;
    }
    else
    {
      *fin = 0;
    }
  }
  else
  {
    if ((*fin + 1) == inicio)
    {
      return BANDERA_COLA_LLENA;
    }
    else
    {
      *fin += 1;
    }
  }

  // Realizamos la operación de inserción.
  cola[finTemporal] = nuevoDato;

  // Regresamos 0 porque no hubo error.
  return 0;
}

/**
 * Eliminar cola circular
 * Elimina el primer elemento presente en la cola circular.
 * @param inicio Un apuntador con el índice al inicio de la cola.
 * @param fin El índice de la posición del último elemento dentro de la cola.
 * @param cola La cola en cuestión.
 * @return Un entero con el primer dato presente en la cola o BANDER_COLA_VACIA si ya no hay elementos dentro de la cola.
 */
int eliminarColaCircular(int *inicio, int fin, int *cola)
{
  // Variables locales.
  int datoTemporal = cola[*inicio]; // El valor original en la posición de inicio.

  // Verificamos si la cola no está vacía.
  if (*inicio == fin)
  {
    return BANDERA_COLA_VACIA;
  }
  else
  {
    // Verificamos si requerimos regresar el índice a 0 o podemos aumentar en 1.
    if ((*inicio + 1) >= TAM_MAX_COLA)
    {
      *inicio = 0;
    }
    else
    {
      *inicio += 1;
    }
  }

  // Regresamos el dato temporal.
  return datoTemporal;
}

/**
 * Imprimir cola circular.
 * Muestra en la terminal el contenido de una cola circular.
 * @param inicio El índicio del primer elemento presente en la cola circular en la cola circular.
 * @param fin El índice del último elemento presente en la cola circular.
 * @param cola Un arreglo con los elementos dentro de la cola
 */
void imprimirColaCircular(int inicio, int fin, int *cola)
{
  // Iteramos desde inicio hasta el final.
  while (inicio != fin)
  {
    // Imprimimos el dato en la posición de inicio.
    printf("%i ", cola[inicio]);

    // Aumentamos el índice apropiadamente.
    if ((inicio + 1) >= TAM_MAX_COLA)
    {
      inicio = 0;
    }
    else
    {
      inicio++;
    }
  }
}
