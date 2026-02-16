#include <stdio.h>

int main() {
  int numCasos, v1_0, v1_1, v1_2, v2_0, v2_1, v2_2;
  scanf("%d", &numCasos);
  while (numCasos--) {
    scanf("%d.%d.%d %d.%d.%d", &v1_0, &v1_1, &v1_2, &v2_0, &v2_1, &v2_2);
    puts((v1_0 + 1 == v2_0 && v2_1 == 0 && v2_2 == 0) ||
         (v1_0 == v2_0 && v1_1 + 1 == v2_1 && v2_2 == 0) ||
         (v1_0 == v2_0 && v1_1 == v2_1 && v1_2 + 1 == v2_2) ? "SI" : "NO");
  }
  return 0;
}
