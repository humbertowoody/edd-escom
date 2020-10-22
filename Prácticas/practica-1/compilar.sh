#!/bin/bash

#
# Este pequeño script permite compilar la práctica de forma simple.
#

# Invocamos al compilador y, si todo salió bien, imprimimos un mensaje de confirmación.
gcc practica1.c -o Practica1.out && \
  # Mensaje de confirmación.
  echo "¡Compilado correctamente Practica1.out!";