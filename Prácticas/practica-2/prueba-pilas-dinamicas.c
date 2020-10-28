// Librerías.
#include <stdio.h>
#include <stdlib.h>

// Constantes.
#define MAX_VALUE 999999 // Máximo valor dentro de un elemento de la pila.
#define MAX_PILAS 5      // Máximo número de pilas.
#define MENU_PUSH 1      // Identificador para la opción "push" del menú.
#define MENU_TOP 2       // Identificador para la opción "top" del menú.
#define MENU_POP 3       // Identificador para la opción "pop" del menú.
#define MENU_IMPRIMIR 4  // Identificador para la opción "imprimir" del menú.
#define MENU_SALIR 5     // Identificador para la opción "salir" del menú.

/**
 * Pila
 */
typedef struct pila_s
{
  int valor;               // El valor del elemento en la pila.
  struct pila_s *anterior; // Puntero al elemento anterior.
} Pila;

// Variable global.
Pila *tope = NULL;

/**
 * Prototipos de funciones.
 */
int pop(Pila **);            // Sacar el último elemento en la pila.
int top(Pila **);            // Regresa el valor del último elemento de la pila.
int push(int, Pila **);      // Agregar elementos a la pila.
void imprimir_pila(Pila **); // Imprimir la pila.

/**
 * Función principal.
 */
int main(int argc, char *argv[])
{
  // Variables locales.
  Pila **pilas;     // Las pilas dentro del programa.
  int numero_pilas, // Número de pilas en el programa.
      opcion_menu,  // Variable para almacenar la opción seleccionada del menú.
      opcion_pila,  // Variable para almacenar la opción de pila seleccionada para la operación.
      temporal;     // Variable genérica.

  // Mensaje inicial.
  printf("ESCOM - IPN\n");
  printf("Pilas - Humberto Alcocer\n\n");

  // Leemos el número de pilas que habrá en nuestro programa..
  do
  {
    printf("¿Cuántas pilas desea tener?\n[1-%i]> ", MAX_PILAS);
    scanf("%i", &numero_pilas);
  } while (numero_pilas < 1 || numero_pilas > MAX_PILAS); // Validar que esté en un rango razonable.

  // Asignamos la memoria de forma dinámica.
  pilas = (Pila **)malloc(sizeof(Pila *) * numero_pilas);

  do
  {
    // Mostramos menú.
    printf("Menú de opciones\n");
    printf("  %i - Añadir elemento (push).\n", MENU_PUSH);
    printf("  %i - Mostrar el valor del último elemento (top).\n", MENU_TOP);
    printf("  %i - Mostrar su valor y eliminar el último elemento (pop).\n", MENU_POP);
    printf("  %i - Mostrar una pila.\n", MENU_IMPRIMIR);
    printf("\n");
    printf("  %i - Salir del programa.\n", MENU_SALIR);
    printf("\n");
    printf("Introduzca su opción: ");
    scanf("%i", &opcion_menu);

    // En todas las operaciones
    if (opcion_menu != MENU_SALIR)
    {
      // Leer la pila en la que trabajaremos.
      do
      {
        printf("¿En cuál pila desea realizar la operación?\n[1-%i]> ", numero_pilas);
        scanf("%i", &opcion_pila);
      } while (opcion_pila < 1 || opcion_pila > numero_pilas); // Validar input.
    }

    // Interpretar menú.
    switch (opcion_menu)
    {
    case MENU_PUSH:
      // Leemos el dato.
      do
      {
        printf("¿Qué valor desea introducir en la pila #%i?\n(Máximo: %i)> ", opcion_pila, MAX_VALUE);
        scanf("%i", &temporal);
      } while (temporal > MAX_VALUE || temporal < (MAX_VALUE * -1)); // Validar entrada.

      // Realizamos la operación.
      push(temporal, &pilas[opcion_pila - 1]);
      break;
    case MENU_TOP:
      // Realizamos la operación.
      temporal = top(&pilas[opcion_pila - 1]);

      // Decidimos qué mostrar.
      if (temporal == -1)
      {
        printf("¡No hay elementos para mostrar en la pila #%i!\n", opcion_pila);
      }
      else
      {
        // Imprimimos resultado.
        printf("El último elemento de la pila #%i es: %i\n", opcion_pila, temporal);
      }
      break;
    case MENU_POP:
      // Realizamos la operación.
      temporal = pop(&pilas[opcion_pila - 1]);

      // Decidimos qué mostrar.
      if (temporal == -1)
      {
        printf("¡No hay elementos para sacar de la pila #%i!\n", opcion_pila);
      }
      else
      {
        // Imprimimos resultado.
        printf("El último elemento de la pila #%i era: %i\n", opcion_pila, temporal);
      }
      break;
    case MENU_IMPRIMIR:
      // Imprimimos la pila.
      printf("Pila #%i:\n", opcion_pila);
      imprimir_pila(&pilas[opcion_pila - 1]);
      break;
    case MENU_SALIR:
      printf("¡Gracias por usar este programa! :)\n");
      break;
    default:
      printf("La opción no es válida.\n");
      break;
    }

  } while (opcion_menu != MENU_SALIR); // Ejecución contínua.

  // Liberar memoria.
  free(pilas);

  // Mensaje final.
  printf("Fin de ejecución.\n\n");

  // Ejecución exitosa, exit status 0.
  return 0;
}

/**
 * Push
 * Agrega un elemento a la pila.
 * @param nuevo_valor El nuevo valor a añadir en la pila.
 * @param pila Un apuntador a la pila existente
 * @return 0 si todo salió bien, -1 si hubo un error de validación.
 */
int push(int nuevo_valor, Pila **pila)
{
  // Validamos el nuevo_valor.
  if (nuevo_valor > MAX_VALUE)
  {
    // El valor no es válido.
    return -1;
  }

  // Declaramos el nuevo elemento de la pila.
  Pila *nuevo;

  // Asignamos dinámicamente la memoria a utilizar.
  nuevo = (Pila *)malloc(sizeof(Pila));

  // Revisamos si la Pila ya contiene elementos.
  if (*pila == NULL)
  {
    // La pila está vacía, así que el nuevo valor será el valor inicial de la pila.
    nuevo->valor = nuevo_valor;
    nuevo->anterior = NULL;
    *pila = nuevo;
  }
  else
  {
    // La pila ya tiene elementos, así que únicamente la ligamos mediante el apuntador "anterior".
    nuevo->anterior = *pila;
    nuevo->valor = nuevo_valor;
    *pila = nuevo;
  }

  // Todo se ejecutó correctamente, regresamos 0.
  return 0;
}

/**
 * Imprimir Pila
 * Imprime una pila en pantalla con un formato pre-establecido.
 * @param pila_a_imprimir La pila que queremos imprimir.
 * @return void
 */
void imprimir_pila(Pila **pila_a_imprimir)
{
  // Variables locales.
  Pila *elemento_actual = *pila_a_imprimir;

  // Mensaje inicial
  printf("\n|--------|\n");

  // Si la pila está vacía, mostramos un mensaje.
  if (elemento_actual == NULL)
  {
    printf("|   ∅    |\n");
    printf("|--------|\n");
  }

  // Imprimimos todos los elementos hasta que sea nulo.
  while (elemento_actual != NULL)
  {
    // 6 caracteres de padding.
    printf("| %6d |\n", elemento_actual->valor);
    printf("|--------|\n");

    // Nos movemos al siguiente apuntador.
    elemento_actual = elemento_actual->anterior;
  }

  // Salto de línea final.
  printf("\n");
}

/**
 * Pop
 * Saca el último elemento ingresado en la pila.
 * @param pila La pila en cuestión.
 * @return El último elemento o -1 si la pila está vacía.
 */
int pop(Pila **pila)
{
  // Variables locales.
  Pila *pila_temporal;
  int valor_temporal;

  // Verificar si la pila está vacía.
  if (*pila == NULL)
  {
    return -1;
  }
  else
  {
    // Usamos una pila temporal para la operación.
    pila_temporal = *pila;
    valor_temporal = pila_temporal->valor;
    *pila = pila_temporal->anterior;

    // Liberamos la memoria empleada.
    free(pila_temporal);

    // Regresamos el valor del último elemento eliminado.
    return valor_temporal;
  }
}

/**
 * Pop
 * Regresa el valor del último elemento ingresado en la pila.
 * @param pila La pila en cuestión.
 * @return El valor del último elemento o -1 si la pila está vacía.
 */
int top(Pila **pila)
{
  if (*pila == NULL)
  {
    return -1;
  }
  else
  {
    return (*pila)->valor;
  }
}