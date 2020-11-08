/**
 * Practica3.c - Archivo base de la práctica
 *
 * Práctica: 3
 * Objetivo: Implementar un programa en C que, dada una cadena en infijo,
 * la convierta en sus correspondientes versiones en postfijo y prefijo y realice las evaluaciones en ambos formatos.
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
 * 07/Nov/2020
 */
#include <stdio.h>  // Operaciones de entrada y salida estándar.
#include <stdlib.h> // Para usar `malloc` etc...
#include <math.h>   // Para usar `pow` etc...
#include <string.h> // Para usar `strlen` etc..

// Constantes de operación.
#define TAM_MAX_EXPRESION 100                  // El tamaño máximo de la expresión inicial. 100 es un valor razonable.
#define OPCION_EJECUCION_PREFIJA 1             // La opción para la ejecución de la conversión a notación prefija.
#define OPCION_EJECUCION_POSTFIJA 2            // La opción para la ejecución de la conversión a notación postfija.
#define BANDERA_PILA_DINAMICA_CHAR_VACIA '\0'  // Usamos un caracter que no se pueda encontrar en la expresión.
#define BANDERA_PILA_DINAMICA_NUM_VACIA -32256 // Usamos un valor que difícilmente encontraremos dentro de la evaluación.

// Estructura para las pilas dinámicas con valores de caracter.
typedef struct p_dinamica_char
{
  char datoCaracter;                // Para almacenar el dato como un caracter.
  struct p_dinamica_char *anterior; // Un apuntador con la referencia al elemento inmediato anterior.
} PilaDinamicaChar;

// Estructura para las pilas dinámicas con valores numéricos.
typedef struct p_dinamica_num
{
  float datoNumerico;
  struct p_dinamica_num *anterior;
} PilaDinamicaNum;

/**
 * Prototipos de funciones a implementar.
 */
void convertirAPrefijoYResolver(char *);  // Función que realiza la conversión a prefijo y evalúa.
void convertirAPostfijoYResolver(char *); // Función que realiza la conversión a postfijo y evalúa.

void pushPilaDinamicaChar(PilaDinamicaChar **, char);                        // Realiza la operación `push` en una pila dinámica de caracteres.
char popPilaDinamicaChar(PilaDinamicaChar **);                               // Realiza la operación `pop` en una pila dinámica de caracteres.
char verUltimoPilaDinamicaChar(PilaDinamicaChar **);                         // Para mostrar el último elemento en la pila dinámica de caracteres.
void volcarPilaDinamicaChar(PilaDinamicaChar **, PilaDinamicaChar **, char); // Realiza el volcado de una pila dinámica de caracteres en otra hasta un límite.
void imprimirPilaDinamicaChar(PilaDinamicaChar **);                          // Función para imprimir una pila dinámica de caracteres.
void pushPilaDinamicaNum(PilaDinamicaNum **, float);                         // Realiza la operación `push` en una pila dinámica de números.
float popPilaDinamicaNum(PilaDinamicaNum **);                                // Realiza la operación `pop` en una pila dinámica de números.

float evaluarExpresion(float, char, float); // Realiza la evaluación de dos números y un operador.
int precedenciaOperador(char);              // Regresa un valor entero dependiendo la precedencia de un operador.
int esOperando(char);                       // Regresa 1 si el valor es un operando, 0 si no lo es.
int esOperador(char);                       // Regresa 1 si el valor es operador, 0 si no es operador.
int esParentesisIzquierdo(char);            // Determina si un caracter es paréntesis izquierdo.
int esParentesisDerecho(char);              // Determina si un caracter es paréntesis derecho.
char *invertirCadena(char *);               // Invierte una cadena de caracteres.

/**
 * Función principal del programa.
 */
int main(int argc, char *argv[])
{
  // Variables locales
  char expresion[TAM_MAX_EXPRESION]; // Para almacenar la expresión ingresada por el usuario.
  int opcionEjecucion;               // Variable para almacenar la opción de la ejecución: 1 - prefijo, 2 - postfijo.

  // Leer la expresión.
  printf("Ingresa la cadena a convertir: ");
  scanf("%s", expresion);

  // Mostramos las opciones.
  printf("Seleccione el formato de la salida:\n");
  printf("  1) Prefijo.\n");
  printf("  2) Postfijo.\n\n");

  // Leemos la opción de ejecución.
  do
  {
    printf("> ");
    scanf("%i", &opcionEjecucion);
  } while (opcionEjecucion != OPCION_EJECUCION_PREFIJA && opcionEjecucion != OPCION_EJECUCION_POSTFIJA);

  // Determinamos la ejecución a seguir.
  if (opcionEjecucion == OPCION_EJECUCION_PREFIJA)
  {
    convertirAPrefijoYResolver(expresion);
  }
  else
  {
    convertirAPostfijoYResolver(expresion);
  }

  // En este punto, la ejecución fue correcta, exit status = 0.
  return 0;
}

/**
 * Convertir a prefijo y resolver
 * Esta función toma una cadena en notación infija, la convierte a prefija y
 * la evalúa.
 */
void convertirAPrefijoYResolver(char *expresion)
{
  // Variables locales.
  PilaDinamicaChar *pilaO = NULL,         // La pila para los operadores.
      *pilaEF = NULL;                     // La pila para la expresión final.
  PilaDinamicaNum *pilaEvaluacion = NULL; // La pila para realizar la evaluación.
  char *elementoActual;                   // Un apuntador para cada elemento dentro de la expresión inicial.
  float resultado;                        // La variable para almacenar el resultado final de la evaluación.

  // Primero invertimos la expresión.
  expresion = invertirCadena(expresion);

  // Asignamos el elemento actual al inicio de la expresión invertida.
  elementoActual = expresion;

  // Mientras el apuntador no sea EOF.
  while (*elementoActual != '\0')
  {
    // Impresión para debugging.
    // printf("Elemento actual: %c, precedencia: %i\nPilaEF: ", *elementoActual, precedenciaOperador(*elementoActual));
    // imprimirPilaDinamicaChar(&pilaEF);
    // printf("\nPilaO: ");
    // imprimirPilaDinamicaChar(&pilaO);
    // printf("\n");

    // Determinamos qué tipo de elemento es el que encontramos en la cadena.
    if (esOperando(*elementoActual))
    {
      // Añadimos el operando a la pila con la expresión final.
      pushPilaDinamicaChar(&pilaEF, *elementoActual);
    }
    else if (esOperador(*elementoActual) || esParentesisDerecho(*elementoActual) || esParentesisIzquierdo(*elementoActual))
    {
      // Determinamos la prioridad del operador.
      if (precedenciaOperador(*elementoActual) == precedenciaOperador(verUltimoPilaDinamicaChar(&pilaO)))
      {
        // Sacamos el último elemento de la pilaO y lo metemos en la pilaEF.
        // pushPilaDinamicaChar(&pilaEF, popPilaDinamicaChar(&pilaO));

        // Introducimos el operador en la pilaO.
        pushPilaDinamicaChar(&pilaO, *elementoActual);
      }
      else if (precedenciaOperador(*elementoActual) > precedenciaOperador(verUltimoPilaDinamicaChar(&pilaO)))
      {
        if (esParentesisIzquierdo(*elementoActual))
        {
          // Si es paréntesis izquierdo sacamos el último elemento de la pilaO y lo insertamos en la pilaEF.
          pushPilaDinamicaChar(&pilaEF, popPilaDinamicaChar(&pilaO));
        }
        else if (esParentesisDerecho(*elementoActual))
        {
          // Si es paréntesis derecho lo insertamos en la pilaO.
          pushPilaDinamicaChar(&pilaO, *elementoActual);
        }
        else
        {
          // En otro caso, ingresamos el operador en la pilaO.
          pushPilaDinamicaChar(&pilaO, *elementoActual);
        }
      }
      else if (precedenciaOperador(*elementoActual) < precedenciaOperador(verUltimoPilaDinamicaChar(&pilaO)) || verUltimoPilaDinamicaChar(&pilaO) != '\0')
      {
        // Si no es paréntesis derecho ni es el último elemento de la pila.
        if (!esParentesisDerecho(verUltimoPilaDinamicaChar(&pilaO)) && verUltimoPilaDinamicaChar(&pilaO) != '\0')
        {
          pushPilaDinamicaChar(&pilaEF, popPilaDinamicaChar(&pilaO));
        }

        // Añadimos el elemento en la pilaO.
        pushPilaDinamicaChar(&pilaO, *elementoActual);
      }
    }
    else
    {
      // Volcamos la pilaO en pilaEF hasta '\0'
      volcarPilaDinamicaChar(&pilaO, &pilaEF, '\0');
    }

    // Aumentamos el apuntador en 1.
    elementoActual++;
  }
  // Volcamos los operadores restantes en la pilaEF.
  volcarPilaDinamicaChar(&pilaO, &pilaEF, '\0');

  // Volcamos la pilaEF en pilaO para invertir el orden.
  volcarPilaDinamicaChar(&pilaEF, &pilaO, '\0');

  // Imprimimos las conclusiones de la operación.
  printf("La cadena en prefijo es: ");
  imprimirPilaDinamicaChar(&pilaO);
  printf("\n");

  // Realizamos la evaluación.
  while (verUltimoPilaDinamicaChar(&pilaO) != '\0')
  {
    // Verificamos si el elemento es un operando.
    if (esOperando(verUltimoPilaDinamicaChar(&pilaO)))
    {
      // Insertamos en la pila de evaluación el número.
      pushPilaDinamicaNum(&pilaEvaluacion, (float)(popPilaDinamicaChar(&pilaO) - '0'));
    }
    else
    {
      // Extraemos los elementos para la operación a realizar.
      float izq = popPilaDinamicaNum(&pilaEvaluacion);
      char operador = popPilaDinamicaChar(&pilaO);
      float der = popPilaDinamicaNum(&pilaEvaluacion);

      // Guardamos el resultado en la pila de evaluación.
      pushPilaDinamicaNum(&pilaEvaluacion, evaluarExpresion(izq, operador, der));
    }
  }

  // El resultado será el elemento restante en la pila de evaluación.
  resultado = popPilaDinamicaNum(&pilaEvaluacion);

  printf("El resultado de la evaluación es: %.2f\n", resultado);
}

/**
 * Convertir a postfijo y resolver.
 * Esta función toma una cadena en notación infija, la convierte a postfija y
 * la evalúa.
 */
void convertirAPostfijoYResolver(char *expresion)
{
  // Variables locales.
  PilaDinamicaChar *pilaO = NULL,         // La pila para los operadores.
      *pilaEF = NULL;                     // La pila para la expresión final.
  PilaDinamicaNum *pilaEvaluacion = NULL; // La pila para realizar la evaluación.
  char *elementoActual = expresion;       // Un apuntador para cada elemento dentro de la expresión inicial.
  float resultado;                        // La variable para almacenar el resultado final de la evaluación.

  // Mientras el apuntador no sea EOF.
  while (*elementoActual != '\0')
  {
    // Impresión para debugging.
    // printf("Elemento actual: %c\nPilaEF: ", *elementoActual);
    // imprimirPilaDinamicaChar(&pilaEF);
    // printf("\nPilaO: ");
    // imprimirPilaDinamicaChar(&pilaO);
    // printf("\n");

    // Determinamos qué tipo de elemento es el que encontramos en la cadena.
    if (esOperando(*elementoActual))
    {
      // Añadimos el operando a la pila con la expresión final.
      pushPilaDinamicaChar(&pilaEF, *elementoActual);
    }
    else if (esOperador(*elementoActual))
    {
      // Determinamos la prioridad del operador.
      if (precedenciaOperador(*elementoActual) == precedenciaOperador(verUltimoPilaDinamicaChar(&pilaO)))
      {
        // Sacamos el último elemento de la pilaO y lo metemos en la pilaEF.
        pushPilaDinamicaChar(&pilaEF, popPilaDinamicaChar(&pilaO));

        // Introducimos el operador en la pilaO.
        pushPilaDinamicaChar(&pilaO, *elementoActual);
      }
      else if (precedenciaOperador(*elementoActual) > precedenciaOperador(verUltimoPilaDinamicaChar(&pilaO)))
      {
        if (esParentesisIzquierdo(*elementoActual))
        {
          // Si es paréntesis izquierdo, ingresamos el operador actual en la pilaO.
          pushPilaDinamicaChar(&pilaO, *elementoActual);
        }
        else if (esParentesisDerecho(*elementoActual))
        {
          // Si es paréntesis derecho, volcamos pilaO en pilaEF hasta '('
          volcarPilaDinamicaChar(&pilaO, &pilaEF, '(');
        }
        else
        {
          // En otro caso, ingresamos el operador en la pilaO.
          pushPilaDinamicaChar(&pilaO, *elementoActual);
        }
      }
      else if (precedenciaOperador(*elementoActual) < precedenciaOperador(verUltimoPilaDinamicaChar(&pilaO)) || verUltimoPilaDinamicaChar(&pilaO) != '\0')
      {
        // Verificamos si el operador es un paréntesis izquierdo y si la pila no está vacía.
        if (!esParentesisIzquierdo(verUltimoPilaDinamicaChar(&pilaO)) && verUltimoPilaDinamicaChar(&pilaO) != '\0')
        {
          // Volcamos la pilaO en pilaEF totalmente.
          volcarPilaDinamicaChar(&pilaO, &pilaEF, '\0');
        }

        // Añadimos el elemento en la pilaO.
        pushPilaDinamicaChar(&pilaO, *elementoActual);
      }
    }
    else
    {
      // Volcamos la pilaO en pilaEF hasta '\0'
      volcarPilaDinamicaChar(&pilaO, &pilaEF, '\0');
    }

    // Aumentamos el apuntador en 1.
    elementoActual++;
  }
  // Volcamos los operadores restantes en la pilaEF.
  volcarPilaDinamicaChar(&pilaO, &pilaEF, '\0');

  // Volcamos la pilaEF en pilaO para invertir el orden.
  volcarPilaDinamicaChar(&pilaEF, &pilaO, '\0');

  // Imprimimos las conclusiones de la operación.
  printf("La cadena en postfijo es: ");
  imprimirPilaDinamicaChar(&pilaO);
  printf("\n");

  // Realizamos la evaluación.
  while (verUltimoPilaDinamicaChar(&pilaO) != '\0')
  {
    // Verificamos si el elemento es un operando.
    if (esOperando(verUltimoPilaDinamicaChar(&pilaO)))
    {
      // Insertamos en la pila de evaluación el número.
      pushPilaDinamicaNum(&pilaEvaluacion, (float)(popPilaDinamicaChar(&pilaO) - '0'));
    }
    else
    {
      // Extraemos los elementos para la operación a realizar.
      float izq = popPilaDinamicaNum(&pilaEvaluacion);
      char operador = popPilaDinamicaChar(&pilaO);
      float der = popPilaDinamicaNum(&pilaEvaluacion);

      // Guardamos el resultado en la pila de evaluación.
      pushPilaDinamicaNum(&pilaEvaluacion, evaluarExpresion(izq, operador, der));
    }
  }

  // El resultado será el elemento restante en la pila de evaluación.
  resultado = popPilaDinamicaNum(&pilaEvaluacion);

  printf("El resultado de la evaluación es: %.2f\n", resultado);
}

/**
 * Push Pila Dinámica Caracteres.
 * Realiza la operación `push` para pilas dinámicas de caracteres, añadiendo un nuevo elemento al final.
 * @param pila Una referencia a la pila dinámica a utilizar
 * @param nuevoDato El nuevo dato a almacenar en la pila.
 */
void pushPilaDinamicaChar(PilaDinamicaChar **pila, char nuevoDato)
{
  // Declaramos el nuevo elemento para la pila.
  PilaDinamicaChar *nuevoElemento = (PilaDinamicaChar *)malloc(sizeof(PilaDinamicaChar));

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
  nuevoElemento->datoCaracter = nuevoDato;

  // Colocamos la referencia de nuestra pila en el nuevo elemento.
  *pila = nuevoElemento;
}

/**
 * Pop Pila Dinámica Char
 * Realiza la operación `pop` para pilas dinámicas de caracteres, extrayendo y eliminando el último elemento presente en la pila.
 * @param pila La pila de la cual extraer el elemento.
 * @return El último elemento o BANDERA_PILA_DINAMICA_CHAR_VACIA si la pila está vacía.
 */
char popPilaDinamicaChar(PilaDinamicaChar **pila)
{
  // Variables locales.
  char datoTemporal;              // Para almacenar temporalmente el último elemento en la pila.
  PilaDinamicaChar *pilaTemporal; // Para almacenar temporalmente la pila.

  // Verificamos si la pila tiene elementos.
  if (*pila == NULL)
  {
    // Si la pila está vacía, regresamos la bandera BANDERA_PILA_DINAMICA_CHAR_VACIA.
    return BANDERA_PILA_DINAMICA_CHAR_VACIA;
  }
  else
  {
    // Usamos la pila temporal para dereferenciar nuestro apuntador.
    pilaTemporal = *pila;

    // Guardamos el dato que existe en la pila.
    datoTemporal = pilaTemporal->datoCaracter;

    // Asignamos la referencia de la pila al elemento inmediato anterior.
    *pila = pilaTemporal->anterior;

    // Liberamos la memoria de nuestra pila temporal.
    free(pilaTemporal);

    // Regresamos el dato temporal, que era el último en nuestra pila.
    return datoTemporal;
  }
}

/**
 * Push Pila Dinámica Números.
 * Realiza la operación `push` para pilas dinámicas de números, añadiendo un nuevo elemento al final.
 * @param pila Una referencia a la pila dinámica a utilizar
 * @param nuevoDato El nuevo dato a almacenar en la pila.
 */
void pushPilaDinamicaNum(PilaDinamicaNum **pila, float nuevoDato)
{
  // Declaramos el nuevo elemento para la pila.
  PilaDinamicaNum *nuevoElemento = (PilaDinamicaNum *)malloc(sizeof(PilaDinamicaNum));

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
  nuevoElemento->datoNumerico = nuevoDato;

  // Colocamos la referencia de nuestra pila en el nuevo elemento.
  *pila = nuevoElemento;
}

/**
 * Pop Pila Dinámica Números
 * Realiza la operación `pop` para pilas dinámicas de números, extrayendo y eliminando el último elemento presente en la pila.
 * @param pila La pila de la cual extraer el elemento.
 * @return El último elemento o BANDERA_PILA_DINAMICA_NUM_VACIA si la pila está vacía.
 */
float popPilaDinamicaNum(PilaDinamicaNum **pila)
{
  // Variables locales.
  float datoTemporal;            // Para almacenar temporalmente el último elemento en la pila.
  PilaDinamicaNum *pilaTemporal; // Para almacenar temporalmente la pila.

  // Verificamos si la pila tiene elementos.
  if (*pila == NULL)
  {
    // Si la pila está vacía, regresamos la bandera BANDERA_PILA_DINAMICA_NUM_VACIA.
    return BANDERA_PILA_DINAMICA_NUM_VACIA;
  }
  else
  {
    // Usamos la pila temporal para dereferenciar nuestro apuntador.
    pilaTemporal = *pila;

    // Guardamos el dato que existe en la pila.
    datoTemporal = pilaTemporal->datoNumerico;

    // Asignamos la referencia de la pila al elemento inmediato anterior.
    *pila = pilaTemporal->anterior;

    // Liberamos la memoria de nuestra pila temporal.
    free(pilaTemporal);

    // Regresamos el dato temporal, que era el último en nuestra pila.
    return datoTemporal;
  }
}

/**
 * Ver último pila dinámica char
 * Permite visualizar el dato presente en el último elemento presente en una pila dinámica sin eliminarlo de la misma.
 * @param pila La pila de la cual extraer el elemento.
 * @return El dato presente en el último elemento de la pila o BANDERA_PILA_DINAMICA_CHAR_VACIA si la pila está vacía.
 */
char verUltimoPilaDinamicaChar(PilaDinamicaChar **pila)
{
  // Verificamos si la pila se encuentra vacía.
  if (*pila == NULL)
  {
    // Si la pila está vacía, regresamos la bandera BANDERA_PILA_DINAMICA_CHAR_VACIA.
    return BANDERA_PILA_DINAMICA_CHAR_VACIA;
  }
  else
  {
    // Regresamos el dato presente en el último elemento de la pila.
    return (*pila)->datoCaracter;
  }
}

/**
 * Volcar pila dinámica char.
 * Permite volcar una pila dentro de otra hasta encontrar un elemento en particular.
 * @param pilaOrigen La pila origen para sacar elementos.
 * @param pilaDestino La pila destino para insertar elementos.
 * @param delimitador El caracter delimitador para la operación a realizar.
 */
void volcarPilaDinamicaChar(PilaDinamicaChar **pilaOrigen, PilaDinamicaChar **pilaDestino, char delimitador)
{
  // Se realiza la operación mientras el elemento no sea igual al delimitador.
  while (verUltimoPilaDinamicaChar(pilaOrigen) != delimitador)
  {
    // Sacamos un elemento de la pila origen y lo ingresamos en la pila destino.
    pushPilaDinamicaChar(pilaDestino, popPilaDinamicaChar(pilaOrigen));
  }
}

/**
 * Imprimir pila dinámica char.
 * Imprime en la terminal una pila dinámica con el formato para este programa.
 * @param pila La pila a imprimir.
 */
void imprimirPilaDinamicaChar(PilaDinamicaChar **pila)
{
  // Variables locales.
  PilaDinamicaChar *temporal = *pila; // Creamos una variable temporal.

  while (temporal != NULL)
  {
    printf("%c ", temporal->datoCaracter);
    temporal = temporal->anterior;
  }
}

/**
 * Precedencia Operador
 * Determina la precedencia de un operador.
 * @param operador El caracter a probar.
 * @return Un entero de mayor tamaño si la precedencia es mayor, de menor tamaño si la precedencia es menor, 0 si no es un operador.
 */
int precedenciaOperador(char operador)
{
  // Utilizamos un switch para determinar la precedencia de cada operador.
  switch (operador)
  {
  case '(':
  case ')':
    return 4; // Paréntesis tienen la precedencia más elevada.
  case '^':
    return 3; // La potencia es la siguiente en precedencia.
  case '*':
  case '/':
    return 2; // La multiplicación y la división son las siguientes.
  case '+':
  case '-':
    return 1; // La suma y resta son las últimas operaciones en precedencia.
  default:
    return 0; // No es un operador.
  }
}

/**
 * Es Operador.
 * Función que determina si un caracter corresponde a un operador.
 * @param caracter El caracter a probar.
 * @return Un valor entero siendo 1 si el caracter es un operador o 0 en caso contrario.
 */
int esOperador(char caracter)
{
  if (caracter == '^' || caracter == '*' || caracter == '/' || caracter == '+' || caracter == '-')
  {
    // Es un operador.
    return 1;
  }

  // No es un operador.
  return 0;
}

/**
 * Es operando.
 * Regresa 1 si el caracter es un operando, 0 en caso contrario.
 * @param caracter El caracter a probar.
 * @return Un valor entero siendo 1 si el caracter es un operando o 0 en caso contrario.
 */
int esOperando(char caracter)
{
  // Un operando es todo caracter aquél que no es operador ni paréntesis izquierdo o derecho.
  if (!esOperador(caracter) && !esParentesisIzquierdo(caracter) && !esParentesisDerecho(caracter))
  {
    // Es un operando.
    return 1;
  }

  // No es un operando.
  return 0;
}

/**
 * Es paréntesis izquierdo.
 * Regresa 1 si el caracter es paréntesis izquierdo, 0 en caso contrario.
 * @param caracter El caracter a probar.
 * @return Un valor entero siendo 1 si el caracter es un paréntesis izquierdo o 0 en caso contrario.
 */
int esParentesisIzquierdo(char caracter)
{
  if (caracter == '(')
  {
    // Es paréntesis izquierdo.
    return 1;
  }

  // No es paréntesis izquierdo.
  return 0;
}

/**
 * Es paréntesis derecho.
 * Regresa 1 si el caracter es paréntesis derecho, 0 en caso contrario.
 * @param caracter El caracter a probar.
 * @return Un valor entero siendo 1 si el caracter es un paréntesis derecho o 0 en caso contrario.
 */
int esParentesisDerecho(char caracter)
{
  if (caracter == ')')
  {
    // Es paréntesis derecho.
    return 1;
  }

  // No es paréntesis derecho.
  return 0;
}

/**
 * Evaluar expresión.
 * Realiza la evaluación de una expresión entre dos valores en función del operador proporcionado.
 * @param valor1 El primer valor para la expresión.
 * @param operador El operador para la expresión.
 * @param valor2 El segundo valor para la expresión.
 * @return Un valor de punto flotante con el resultado de la operación.
 */
float evaluarExpresion(float valor1, char operador, float valor2)
{
  // Variables locales.
  float resultado;

  // Realizamos la operación correspondiente al símbolo del operador proporcionado.
  switch (operador)
  {
  // Potencia.
  case '^':
    resultado = powf(valor1, valor2);
    break;
  // Multiplicación.
  case '*':
    resultado = valor1 * valor2;
    break;
  // División.
  case '/':
    resultado = valor1 / valor2;
    break;
  // Suma.
  case '+':
    resultado = valor1 + valor2;
    break;
  // Resta.
  case '-':
    resultado = valor1 - valor2;
    break;
  // No es un operador válido.
  default:
    resultado = 0; // Regresamos 0.
    break;
  }

  // Regresamos el resultado de la evaluación.
  return resultado;
}

/**
 * Invertir cadena.
 * Invierte una cadena en orden.
 * @param cadenaOriginal La cadena original a invertir.
 * @return Una cadena invertida.
 */
char *invertirCadena(char *cadenaOriginal)
{
  // Variables locales.
  size_t longitudCadena = strlen(cadenaOriginal);                        // La longitud de la cadena original.
  char *resultado = (char *)malloc((longitudCadena + 1) * sizeof(char)); // El resultado.

  // Primero asignamos el fin de la cadena a nuestro resultado.
  resultado[longitudCadena] = '\0';

  // Ciclo para realizar la inversión.
  int i;
  for (i = 0; i < longitudCadena; i++)
  {
    resultado[i] = cadenaOriginal[longitudCadena - 1 - i];
  }

  // Regresamos la cadena invertida.
  return resultado;
}
