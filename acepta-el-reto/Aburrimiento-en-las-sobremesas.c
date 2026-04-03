#include <stdio.h>

int main() {
  int numero = -1;

  scanf("%d", &numero);
  while (numero != 0) {

    printf("%d\n", ((numero * (numero + 1)) / 2) * 3);

    scanf("%d", &numero);
  }

  return 0;
}
