#include <math.h>
#include <stdio.h>

void comida1(int c, int n) {

  double maximo;
  double minimo;

  maximo = (double)n / (c - 1);

  double parte_entera;
  double parte_frac = modf(maximo, &parte_entera);
  if (parte_frac >= 0.9) {
    maximo = parte_entera + 1;
  }

  parte_frac = modf(maximo, &parte_entera);
  if (parte_frac != 0.0) {
    minimo = (int)maximo;
  } else {
    minimo = n / c;
  }

  int maximaComida = maximo * c;
  int minimoComida = (minimo * c) + minimo;
  printf("%d %d\n", minimoComida, maximaComida);
}

#include <stdio.h>
void comida(int c, int n) {
  c -= 1;
  int maximo = 0;
  int minimo = 0;
  if (n == 0) {
    printf("%d %d\n", minimo, maximo);
    return;
  } else {
    minimo = (n + ((n - 1) / c));
    maximo = (n + (n / c));
  }

  printf("%d %d\n", minimo, maximo);
}

int main() {
  int numCasos;
  if (scanf("%d", &numCasos) == 1) {
    while (numCasos--) {
      int c, n;
      if (scanf("%d %d", &c, &n) == 2) {
        comida(c, n);
      }
    }
  }
  return 0;
}
