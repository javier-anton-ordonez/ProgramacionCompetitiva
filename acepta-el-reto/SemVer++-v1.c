#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void versioning(char *version1, char *version2) {
  char *val1;
  char *val2;
  int v1[3];
  int v2[3];

  int i = 0;

  while ((val1 = strsep(&version1, ".")) != NULL && (val2 = strsep(&version2, ".")) != NULL) {
    v1[i] = atoi(val1);
    v2[i] = atoi(val2);
    i++;
  }

  if (v1[0] + 1 == v2[0] && v2[1] == 0 && v2[2] == 0) {
    printf("SI\n");
    return;
  } else if (v1[0] == v2[0] && v2[1] == v1[1] + 1 && v2[2] == 0) {
    printf("SI\n");
    return;
  } else if (v1[0] == v2[0] && v2[1] == v1[1] && v2[2] == v1[2] + 1) {
    printf("SI\n");
    return;
  }
  printf("NO\n");
  return;
}

int main() {
  int numCasos;
  if (scanf("%d", &numCasos) == 1) {
    while (numCasos--) {
      char version1[15];
      char version2[15];
      if (scanf("%s %s", version1, version2) == 2) {
        versioning(version1, version2);
      }
    }
  }
  return 0;
}
