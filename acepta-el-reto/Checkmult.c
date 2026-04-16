#include <stdio.h>
#include <string.h>

void chemult(char *num, int ceros) {
  int numeroFinal = 0;
  int numeroCeros = ceros;
  int i = 0;
  int hayNoCero = 0;
  for (; num[i]; i++) {
    if (num[i] == '0') {
      numeroCeros++;
    } else {
      if (numeroFinal == 0)
        numeroFinal = num[i] - '0';
      else
        numeroFinal *= num[i] - '0';
    }
  }
  if (numeroFinal >= 10) {
    char str[20];
    snprintf(str, sizeof(str), "%d", numeroFinal);
    chemult(str, numeroCeros);
  } else {
    printf("%d", numeroFinal);
    printf("%d\n", numeroCeros);
  }
}

int main() {
  char num[100];

  while (fgets(num, sizeof(num), stdin)) {
    num[strcspn(num, "\n")] = '\0'; // quitar salto de línea

    if (strcmp(num, "0") == 0)
      break;

    chemult(num, 0);
  }
  return 0;
}
