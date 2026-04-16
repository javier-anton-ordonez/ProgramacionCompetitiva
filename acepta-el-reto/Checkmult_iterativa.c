#include <stdio.h>
#include <string.h>

void chemult(char *num) {

  int ceros = 0;
  while (1) {
    int i = 0;

    int total = 1;
    int haycero = 0;
    for (; num[i]; i++) {
      if (num[i] == '0') {
        ceros++;
      } else {
        total *= num[i] - '0';
        haycero = 1;
      }
    }
    if (!haycero) {
      total = 0;
    }

    if (total < 10) {
      printf("%d%d\n", total, ceros);
      break;
    }
    sprintf(num, "%d", total);
  }
}

int main() {
  char num[100];

  while (fgets(num, sizeof(num), stdin)) {
    num[strcspn(num, "\n")] = '\0'; // quitar salto de línea

    if (strcmp(num, "0") == 0)
      break;

    chemult(num);
  }
  return 0;
}
