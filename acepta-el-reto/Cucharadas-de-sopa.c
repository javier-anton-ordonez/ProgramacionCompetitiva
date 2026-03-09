#include <stdio.h>

/*
 *
 La entrada comienza con un número indicando cuántos casos de prueba deberán ser procesados.

 Cada caso de prueba está compuesto por tres números, 0 ≤ a,b ≤ n ≤ 1000 indicando cuántas
 cucharadas dice Mafalda que se ha tomado como mínimo, cuántas cucharadas dice el padre que se ha
 tomado como máximo, y cuántas cucharadas había puesto realmente en el plato la madre. Se garantiza
 que en el plato siempre hay al menos una cucharada.

 Para cada caso de prueba, se escribirá el número de respuestas correctas que tiene la pregunta
 "¿Cuántas cucharadas ha comido Mafalda?" que cumplan las afirmaciones de la niña y de su padre.

 * */

/*
 * Mafalda dice el MINIMO
 * Padre dice el MAXIMO
 * */

void cucharadas(long long mafalda, long long padre, long long madre) {
  int opciones = 0;

  if (mafalda + padre > madre) {
    int i = padre;
    for (; i >= 0; i--) {
      if (mafalda + opciones + i == madre)
        opciones++;
    }
  } else if (mafalda + padre == madre) {
    int j = 0;
    for (; padre - j >= 0; j++) {
      if (mafalda + j + padre - j == madre)
        opciones++;
    }
  } else if (mafalda + padre < madre) {
    int w = mafalda;
    for (; w <= madre; w++) {
      if (w - opciones + padre == madre)
        opciones++;
    }
  }

  printf("%d\n", opciones);
}

int main() {
  long long numCasos;
  if (scanf("%lld", &numCasos) == 1) {
    while (numCasos--) {
      long long mafalda, padre, madre;
      if (scanf("%lld %lld %lld", &mafalda, &padre, &madre) == 3) {
        cucharadas(mafalda, padre, madre);
      }
    }
  }
  return 0;
}
