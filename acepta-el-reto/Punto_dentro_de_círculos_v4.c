#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct {
  long long radio;
  long long cordx;
  long long cordy;
  long long cordcirx;
  long long cordciry;
  int *numero;
} Datos;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void calcularradios(long long, long long, long long, long long, long long, int *);
void *thread_calcular(void *arg) {

  Datos *d = (Datos *)arg;

  calcularradios(d->radio, d->cordx, d->cordy, d->cordcirx, d->cordciry, d->numero);

  return NULL;
}

void calcularradios(long long radio, long long cordx, long long cordy, long long cordcirx,
                    long long cordciry, int *numero) {
  if (radio < 1) {
    return;
  }
  pthread_t t1, t2, t3, t4;
  Datos *datos1 = NULL;
  Datos *datos2 = NULL;
  Datos *datos3 = NULL;
  Datos *datos4 = NULL;
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
  long long cordPtox = cordx - cordcirx;
  long long cordPtoy = cordy - cordciry;
  long long radio2 = radio * radio;
  long long midradio = radio / 2;
  if (cordPtox * cordPtox + cordPtoy * cordPtoy <= radio2) {
    pthread_mutex_lock(&lock);
    (*numero)++;
    pthread_mutex_unlock(&lock);
  }
  cordPtox = cordx - (cordcirx + midradio);
  cordPtoy = cordy - cordciry;
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2) {
    datos1 = malloc(sizeof(Datos));

    datos1->radio = midradio;
    datos1->cordx = cordx;
    datos1->cordy = cordy;
    datos1->cordcirx = cordcirx + radio;
    datos1->cordciry = cordciry;
    datos1->numero = numero;

    pthread_create(&t1, NULL, thread_calcular, datos1);
    c1 = 1;
  }

  cordPtox = cordx - (cordcirx - midradio);
  cordPtoy = cordy - cordciry;
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2) {
    datos2 = malloc(sizeof(Datos));
    datos2->radio = midradio;
    datos2->cordx = cordx;
    datos2->cordy = cordy;
    datos2->cordcirx = cordcirx - radio;
    datos2->cordciry = cordciry;
    datos2->numero = numero;

    pthread_create(&t2, NULL, thread_calcular, datos2);
    c2 = 1;
  }
  cordPtox = cordx - cordcirx;
  cordPtoy = cordy - (cordciry + midradio);
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2) {
    datos3 = malloc(sizeof(Datos));
    datos3->radio = midradio;
    datos3->cordx = cordx;
    datos3->cordy = cordy;
    datos3->cordcirx = cordcirx;
    datos3->cordciry = cordciry + radio;
    datos3->numero = numero;

    pthread_create(&t3, NULL, thread_calcular, datos3);
    c3 = 1;
  }
  cordPtox = cordx - cordcirx;
  cordPtoy = cordy - (cordciry - midradio);
  if ((cordPtox * cordPtox) + (cordPtoy * cordPtoy) <= radio2) {
    datos4 = malloc(sizeof(Datos));
    datos4->radio = midradio;
    datos4->cordx = cordx;
    datos4->cordy = cordy;
    datos4->cordcirx = cordcirx;
    datos4->cordciry = cordciry - radio;
    datos4->numero = numero;

    pthread_create(&t4, NULL, thread_calcular, datos4);
    c4 = 1;
  }
  if (c1) {
    pthread_join(t1, NULL);
    free(datos1);
  }
  if (c2) {
    pthread_join(t2, NULL);
    free(datos2);
  }
  if (c3) {
    pthread_join(t3, NULL);
    free(datos3);
  }
  if (c4) {
    pthread_join(t4, NULL);
    free(datos4);
  }
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
