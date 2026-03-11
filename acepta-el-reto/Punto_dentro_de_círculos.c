#include <stdio.h>
void calcularradios(long long radio, long long cordx, long long cordy, long long cordcirx,
                    long long cordciry, int *numero) {
  if (radio < 1) {
    return;
  }
  // CORDX = Cordenadas del punto en eje x
  // CORDY = Cordenadas del punto en eje y
  // CORDCIRX = Cordenadas del circulo en x
  // CORDCIRY = Cordenadas del circulo en y
  // cordPtox = distancia del punto al centro de la circunferencia en el eje x
  // cordPtoy = Distancia del punto al centro de la circunferencia en el eje y
  long long cordPtox = cordx - cordcirx;
  long long cordPtoy = cordy - cordciry;

  if (cordPtox * cordPtox + cordPtoy * cordPtoy <= radio * radio) {
    (*numero)++;
  }
  // cordPtox = Distancia de un punto respecto a la futura posicion de un circulo
  cordPtox = cordx - (cordcirx + radio / 2);
  cordPtoy = cordy - cordciry;

  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= (radio * 2) * (radio * 2))
    calcularradios(radio / 2, cordx, cordy, cordcirx + radio, cordciry, numero);

  cordPtox = cordx - (cordcirx - radio / 2);
  cordPtoy = cordy - cordciry;

  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= (radio * 2) * (radio * 2))
    calcularradios(radio / 2, cordx, cordy, cordcirx - radio, cordciry, numero);

  cordPtox = cordx - cordcirx;
  cordPtoy = cordy - (cordciry + radio / 2);
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= (radio * 2) * (radio * 2))
    calcularradios(radio / 2, cordx, cordy, cordcirx, cordciry + radio, numero);

  cordPtox = cordx - cordcirx;
  cordPtoy = cordy - (cordciry - radio / 2);
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= (radio * 2) * (radio * 2))
    calcularradios(radio / 2, cordx, cordy, cordcirx, cordciry - radio, numero);
}

int main() {
  long long radio, cordx, cordy;
  while (scanf("%lld %lld %lld", &radio, &cordx, &cordy) == 3) {
    int numero = 0;
    int *pnumero = &numero;
    calcularradios(radio, cordx, cordy, 0, 0, pnumero);
    printf("%d\n", *pnumero);
  }
  return 0;
}

/*
 *
 *  if (sqrt(cordx * cordx + cordy * cordy) > radio) {
    return numero;
  } else {
    numero++;
    calcularradios(radio / 2, cordx, 0, numero);
    calcularradios(radio / 2, -cordx, 0, numero);
    calcularradios(radio / 2, 0, -cordy, numero);
    calcularradios(radio / 2, 0, cordy, numero);
  }

 *
 *
 *
 * */
