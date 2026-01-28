#include <stdio.h>

int getanumber(int numero, int select) {
  int i = select;

  int valor;
  for (; i != 0; i--) {
    int j = i - 1;
    int dividendo = 10;
    for (; j > 0; j--) {
      dividendo = dividendo * 10;
    }
    // printf("%d\n", dividendo);
    valor = (numero % dividendo) / (dividendo / 10);
    return valor;
  }
}
int ordenar(int num) {
  int valor = 0;
  int valores[4];
  int i = 0;

  for (; i < 4; i++) {
    valores[i] = getanumber(num, i + 1);
  }

  for (i = 0; i < 4; i++) {

    int max = 0;
    int j = 0;
    int index = 0;
    for (j = 0; j < 4; j++) {

      if (valores[j] > max) {
        max = valores[j];
        index = j;
      }
    }

    valores[index] = -1;
    switch (i + 1) {
      case 1:
        valor += max * 1000;
        break;

      case 2:
        valor += max * 100;
        break;

      case 3:
        valor += max * 10;
        break;

      case 4:
        valor += max * 1;
        break;
    }
  }
  return valor;
}
void kaprekar(int numero) {
  int iteraciones = 0;
  if (numero == 6174) {
    printf("%d\n", iteraciones);
    return;
  }

  do {

    numero = ordenar(numero);
    int valor = 0;
    int i;
    for (i = 4; i >= 1; i--) {
      int num = getanumber(numero, i);

      switch (i) {
        case 1:
          valor += num * 1000;
          break;

        case 2:
          valor += num * 100;
          break;

        case 3:
          valor += num * 10;
          break;

        case 4:
          valor += num * 1;
          break;
      }
      // printf("Valor: %d", valor);
      // scanf("%d");
    }
    // printf("\n");

    // printf("numero: %d\n", numero);

    // printf("valor: %d\n", valor);
    numero = numero - valor;
    iteraciones++;
  } while (numero != 6174 && iteraciones < 8);
  printf("%d\n", iteraciones);
}

int main() {
  int numCasos;
  if (scanf("%d", &numCasos) == 1) {
    while (numCasos--) {
      int numero;
      if (scanf("%d", &numero) == 1) {
        kaprekar(numero);
      }
    }
  }
  return 0;
}
