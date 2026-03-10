#include <stdio.h>
void calcularradios(long long radio, long long cordx, long long cordy, long long cordcirx,
                    long long cordciry, int *numero) {
  if (radio < 1) {
    return;
  }

  long long cordPtox = cordx - cordcirx;
  long long cordPtoy = cordy - cordciry;
  long long radio2 = radio * radio;
  long long midradio = radio / 2;

  if (cordPtox * cordPtox + cordPtoy * cordPtoy <= radio2) {
    (*numero)++;
  }
  cordPtox = cordx - (cordcirx + radio);
  cordPtoy = cordy - cordciry;
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2)
    calcularradios(midradio, cordx, cordy, cordcirx + radio, cordciry, numero);

  cordPtox = cordx - (cordcirx - radio);
  cordPtoy = cordy - cordciry;
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2)
    calcularradios(midradio, cordx, cordy, cordcirx - radio, cordciry, numero);

  cordPtox = cordx - cordcirx;
  cordPtoy = cordy - (cordciry + radio);
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2)
    calcularradios(midradio, cordx, cordy, cordcirx, cordciry + radio, numero);

  cordPtox = cordx - cordcirx;
  cordPtoy = cordy - (cordciry - radio);
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2)
    calcularradios(midradio, cordx, cordy, cordcirx, cordciry - radio, numero);
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
 *
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
