#include <stdio.h>
#include <stdlib.h>
#include "PQ.h"


typedef struct filaPrioridade{
    Item* fila; //conteudo do vetor
    int* mapa; //indices do vetor
    int N;
} fp;

static void swap(fp* f, int i, int j) {
    exch(f->fila[i], f->fila[j]);
    f->mapa[id(f->fila[i])] = i;
    f->mapa[id(f->fila[j])] = j;
}

void fix_up(fp* f, Item *a, int k) {
    while (k > 1 && more(a[k/2], a[k])) {
        swap(f, k, k/2);
        k = k/2;
    }
}

void fix_down(fp* f, Item *a, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(a[j], a[j+1])){
      j++;
    }
    if (!more(a[k], a[j])) {
      break;
    }
    swap(f ,k, j);
    k = j;
  }
}

fp* PQ_init(int maxN) {
    fp* f = malloc(sizeof(fp));
    f->fila = malloc((maxN+1) * sizeof(Item));
    f->mapa = malloc((maxN+1) * sizeof (int));
    f->N = 0;
    return f;
}

void PQ_insert(fp* f, Item v) {
    f->N++;
    f->fila[f->N] = v;
    f->mapa[id(v)] = f->N;
    fix_up(f, &v, f->N);
}

Item PQ_delmin(fp* f){
    Item min = f->fila[1];
    swap(f, 1, f->N);
    f->N--;
    fix_down(f, &min, f->N, 1);
    return min;
}

Item PQ_min(fp* f) {
    return f->fila[1];
}

//TODO: entender isso aqui
void PQ_decrease_key(fp* f, int id, double value) {
    int i = f->mapa[id];
    value(f->fila[i]) = value;
    fix_up(f, i);
}

bool PQ_empty(fp* f) {
    return f->N == 0;
}

int  PQ_size(fp* f) {
    return f->N;
}

void PQ_finish(fp* f) {
    free(f->fila);
    free(f->mapa);
    free(f);
}