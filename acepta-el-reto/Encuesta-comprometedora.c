#include <stdio.h>

void encuesta(long long s, long long n) {
  // printf("\n");
  long long total = s + n;

  if (total == 0) {
    printf("0\n");
    return;
  }
  // printf("Total: %lld\n", total);
  // printf("S: %lld\n", s);
  // printf("N: %lld\n", n);
  double probs = (double)s / total;
  double probn = (double)n / total;

  // printf("Probs: %f\n", probs);
  // printf("Probn: %f\n", probn);

  /*int porcentaje = probs + probn;
  if (porcentaje != 1) {
    // printf("Exception: %f\n", probs + probn);
    return;
  }*/

  // int ecuacion = ((probs - 0.5) / 0.5) * 100;
  double ecuacion = (probs - 0.5) / 0.5;
  int resultado = (int)(ecuacion * 100.0 + 0.5);
  // printf("%d\n", ecuacion);
  printf("%d\n", resultado);
  return;
}

int main() {
  long long numCasos;
  if (scanf("%lld", &numCasos) == 1) {
    while (numCasos--) {
      long long numero1, numero2;
      if (scanf("%lld %lld", &numero1, &numero2) == 2) {
        encuesta(numero1, numero2);
      }
    }
  }
  return 0;
}
