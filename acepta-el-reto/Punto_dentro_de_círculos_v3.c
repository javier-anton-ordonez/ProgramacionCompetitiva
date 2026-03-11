#include <stdio.h>
void calcularradios(long long radio, long long cordx, long long cordy, long long cordcirx,
                    long long cordciry, int *numero) {
  if (radio < 1) {
    return;
  }

  long long cordPtox = cordx - cordcirx;
  long long cordPtoy = cordy - cordciry;
  long long mid = radio / 2;
  if (cordPtox * cordPtox + cordPtoy * cordPtoy <= radio * radio) {
    (*numero)++;
  }
  switch ((cordPtox < 0) * 2 + (cordPtoy < 0)) {
    case 0:
      calcularradios(mid, cordx, cordy, cordcirx + radio, cordciry, numero);
      calcularradios(mid, cordx, cordy, cordcirx, cordciry + radio, numero);
      break;
    case 1:
      calcularradios(mid, cordx, cordy, cordcirx + radio, cordciry, numero);
      calcularradios(mid, cordx, cordy, cordcirx, cordciry - radio, numero);
      break;
    case 2:
      calcularradios(mid, cordx, cordy, cordcirx - radio, cordciry, numero);
      calcularradios(mid, cordx, cordy, cordcirx, cordciry + radio, numero);
      break;

    case 3:
      calcularradios(mid, cordx, cordy, cordcirx - radio, cordciry, numero);
      calcularradios(mid, cordx, cordy, cordcirx, cordciry - radio, numero);
      break;
  }
}

int main() {
  long long radio, cordx, cordy;
  while (scanf("%lld %lld %lld", &radio, &cordx, &cordy) == 3) {
    int numero = 0;
    calcularradios(radio, cordx, cordy, 0, 0, &numero);
    printf("%d\n", numero);
  }
  return 0;
}

/*
  if (cordPtox >= 0 && cordPtoy >= 0) {
    calcularradios(mid, cordx, cordy, cordcirx + radio,
 cordciry, numero); calcularradios(mid, cordx, cordy, cordcirx,
 cordciry + radio, numero);

  } else if (cordPtox < 0 && cordPtoy >= 0) {
    calcularradios(mid, cordx, cordy, cordcirx - radio,
 cordciry, numero); calcularradios(mid, cordx, cordy, cordcirx,
 cordciry + radio, numero);

  } else if (cordPtox < 0 && cordPtoy < 0) {
    calcularradios(mid, cordx, cordy, cordcirx - radio,
 cordciry, numero); calcularradios(mid, cordx, cordy, cordcirx,
 cordciry - radio, numero);

  } else {
    calcularradios(mid, cordx, cordy, cordcirx + radio,
 cordciry, numero); calcularradios(mid, cordx, cordy, cordcirx,
 cordciry - radio, numero);
  }

 *  if (sqrt(cordx * cordx + cordy * cordy) > radio) {
    return numero;
  } else {
    numero++;
    calcularradios(midradio, cordx, 0, numero);
    calcularradios(midradio, -cordx, 0, numero);
    calcularradios(midradio, 0, -cordy, numero);
    calcularradios(midradio, 0, cordy, numero);
  }

 *
 *
 *
 * */
