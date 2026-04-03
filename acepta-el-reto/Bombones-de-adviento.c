#include <stdio.h>
void main(int argc, char *argv[]) {

  long long numero1, numero2;
  long long maximo;
  while (1) {
    maximo = 0;
    numero1 = 0;
    numero2 = 0;
    scanf("%lld", &numero2);
    if (numero2 == 0) {
      break;
    }
    while (numero2 != 0) {

      if (numero1 + numero2 > maximo) {
        maximo = numero1 + numero2;
      }

      numero1 = numero2;
      scanf("%lld", &numero2);
    }
    printf("%lld\n", maximo);
  }
}
