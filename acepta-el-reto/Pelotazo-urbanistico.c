#include <stdio.h>

long long maximo_comun_divisor(long long a, long long b) {
  long long temporal; // Para no perder b
  while (b != 0) {
    temporal = b;
    b = a % b;
    a = temporal;
  }
  return a;
}

void casas(long long w, long long h) {
  long long minimo = 1;
  if (w == h) {
    printf("%lld\n", minimo);
    return;
  }
  long long mcd = maximo_comun_divisor(w, h);
  long long x = mcd;
  long long x2 = x * x;
  long long area = (long)w * (long)h;
  minimo = area / x2;
  printf("%lld\n", minimo);

  // printf("X: %d\n", x);
  // printf("X2: %d\n", x2);
  // printf("MCD: %d\n", mcd);
  // printf("tmp: %d\n", tmp);
  // printf("W * H: %lld\n", area);
}

int main() {
  int numCasos;
  if (scanf("%d", &numCasos) == 1) {
    while (numCasos--) {
      long long w, h;
      if (scanf("%lld %lld", &w, &h) == 2) {
        casas(w, h);
      }
    }
  }
  return 0;
}
