#include <stdio.h>

long long maximo_comun_divisor(long long a, long long b) {
  long long temporal;
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
  long long x2 = x * x;   // ya no overflow
  long long area = w * h; // ya no overflow

  minimo = area / x2;

  printf("%lld\n", minimo);
}

void casas2(long long w, long long h) {
  long long minimo = 1;

  if (w == h) {
    printf("%lld\n", minimo);
    return;
  }

  long long mcd = maximo_comun_divisor(w, h);

  long long area = w * h; // ya no overflow

  minimo = area / (mcd * mcd);

  printf("%lld\n", minimo);
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
