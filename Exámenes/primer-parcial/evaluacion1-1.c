/**
 * evaluacion1-1.c
 *
 * Examen Primer Departamental
 * Evaluación 1.1
 * Planteamiento:
 *  Implementar el código de pila dinámica para 2 pilas de
 *  enteros. El funcionamiento será de la siguente forma:
 *
 *    - Hacer un menú con las opciones insertar, eliminar, mostrar
 *      elementos eliminados y limpiar memoria.
 *
 *    - Las funciones insertar y eliminar elementos solo deben actuar
 *      sobre la pila 1.
 *
 *    - Cuando se solicite eliminar un elemento de la pila 1, éste se
 *      deberá mover hacia la pila 2.
 *
 *    - La opción “mostrar elementos eliminados” deberá mostrar el
 *      contenido de la pila 2.
 *
 *    - La función “Limpiar memoria” deberá vaciar por completo la
 *      pila 2.
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
#define MENU_INSERTAR 1
#define MENU_ELIMINAR 2
#define MENU_MOSTRAR 3
#define MENU_LIMPIAR 4
#define MENU_SALIR 5
#define BANDERA_PILA_VACIA -32356

// Estructura para la pila.
typedef struct pila_int
{
  int dato;
  struct pila_int *anterior;
} PilaInt;

// Prototipos de funciones.
void mostrarMenu();         // Función para imprimir el menú en pantalla.
void push(PilaInt **, int); // Para añadir elementos a una pila.
int pop(PilaInt **);        // Para sacar el último elemento en una pila.
void imprimir(PilaInt **);  // Para imprimir los contenidos de una pila.

// Función principal.
int main(int argc, char *argv[])
{
  // Variables locales.
  int opcionMenu,        // Para almacenar la opción del menú seleccionada.
      valorTemporal;     // Para operaciones temporales.
  PilaInt *pila1 = NULL, // Para almacenar los elementos iniciales.
      *pila2 = NULL;     // Para funcionar como una "papelera de reciclaje".

  // Ciclo principal para el menú.
  do
  {
    mostrarMenu();
    do
    {
      printf("> ");
      scanf("%i", &opcionMenu);
    } while (opcionMenu < 1 || opcionMenu > 5); // Validación de entrada.

    // Realizamos la operación correspondiente.
    switch (opcionMenu)
    {
    case MENU_INSERTAR:
      // Leemos el dato a insertar.
      printf("Ingrese el valor a insertar en la pila: ");
      scanf("%i", &valorTemporal);
      // Lo metemos en la pila 1.
      push(&pila1, valorTemporal);
      break;
    case MENU_ELIMINAR:
      // Extraemos el último dato en pila 1.
      valorTemporal = pop(&pila1);

      // Verificamos si el resultado de pop es BANDERA_PILA_VACIA
      if (valorTemporal == BANDERA_PILA_VACIA)
      {
        printf("No es posible eliminar un elemento de la pila 1 porque se encuentra vacía.\n");
      }
      else
      {
        // Insertamos el dato en la pila 2.
        push(&pila2, valorTemporal);
        printf("Se ha eliminado de la pila 1 el elemento %i y se ha movido a la pila 2.\n", valorTemporal);
      }

      break;
    case MENU_MOSTRAR:
      // Imprimimos el contenido de la pila 2.
      printf("El contenido de la pila 2 es:\n");
      imprimir(&pila2);
      break;
    case MENU_LIMPIAR:
      // Vaciamos la pila 2.
      while (pop(&pila2) != BANDERA_PILA_VACIA)
        ;
      printf("Se han eliminado todos los elementos en la pila 2.\n");
      break;
    default:
      printf("¡Gracias por utilizar este programa!\n");
      break;
    } // Fin de switch.

  } while (opcionMenu != MENU_SALIR); // Fin de ciclo de menú principal.

  // En este punto la ejecución fue exitosa, exit status = 0.
  return 0;
}

/**
 * Pop
 * Realiza la operación `pop` para pilas dinámicas, extrayendo y eliminando el último elemento presente en la pila.
 * @param pila La pila de la cual extraer el elemento.
 * @return El último elemento o BANDERA_PILA_VACIA si la pila está vacía.
 */
int pop(PilaInt **pila)
{
  // Variables locales.
  int datoTemporal;      // Para almacenar temporalmente el último elemento en la pila.
  PilaInt *pilaTemporal; // Para almacenar temporalmente la pila.

  // Verificamos si la pila tiene elementos.
  if (*pila == NULL)
  {
    // Si la pila está vacía, regresamos la bandera BANDERA_PILA_VACIA.
    return BANDERA_PILA_VACIA;
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

/**
 * Push
 * Realiza la operación `push` para pilas dinámicas, añadiendo un nuevo elemento al final.
 * @param pila Una referencia a la pila dinámica a utilizar
 * @param nuevoDato El nuevo dato a almacenar en la pila
 */
void push(PilaInt **pila, int nuevoDato)
{
  // Declaramos el nuevo elemento para la pila.
  PilaInt *nuevoElemento = (PilaInt *)malloc(sizeof(PilaInt));

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
 * Imprimir
 * Realiza la impresión en la terminal de la pila dinámica en cuestión.
 * @param pila La pila a imprimir.
 */
void imprimir(PilaInt **pila)
{
  // Variables locales.
  PilaInt *elementoActual = *pila;

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
 * Mostrar menu.
 * Imprime el menú principal de la aplicación.
 */
void mostrarMenu()
{
  printf("Menú principal\n\nSeleccione una de las siguientes opciones:\n");
  printf("\t1) Insertar elemento (Pila 1).\n");
  printf("\t2) Eliminar último elemento (Pila 1).\n");
  printf("\t3) Mostrar elementos eliminados (Pila 2).\n");
  printf("\t4) Limpiar memoria (Pila 2).\n\t-\n");
  printf("\t5) Salir.\n");
}
