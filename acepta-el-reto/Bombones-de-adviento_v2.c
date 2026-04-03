#include <stdio.h>

#define BUF_SIZE 1048576

char buf[BUF_SIZE];
char *p = buf;

static inline long long readLong() {
  long long n = 0;
  while (*p < '0') p++;
  while (*p >= '0') {
    n = (n << 3) + (n << 1) + (*p++ - '0');
  }
  return n;
}

static inline void writeLong(long long n) {
  char tmp[20];
  int i = 0;
  do {
    tmp[i++] = n % 10 + '0';
    n /= 10;
  } while (n);
  while (i--) putchar_unlocked(tmp[i]);
  putchar_unlocked('\n');
}

int main() {
  fread(buf, 1, BUF_SIZE, stdin);
  
  register long long tmp, numero1, numero2, maximo, suma;
  
  while (1) {
    maximo = 0;
    numero1 = 0;
    tmp = readLong();
    if (tmp == 0) break;
    
    numero2 = tmp;
    tmp = readLong();
    
    while (tmp != 0) {
      suma = numero2 + tmp;
      if (suma > maximo) maximo = suma;
      numero2 = tmp;
      tmp = readLong();
    }
    
    writeLong(maximo);
  }
  
  return 0;
}
