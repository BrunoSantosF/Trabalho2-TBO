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

void fix_up(fp* f, int k) {
    while (k > 1 && more(f->fila[(k-1)/2], f->fila[k])) {
        swap(f, k, (k-1)/2);
        k = (k-1)/2;
    }
}

void fix_down(fp* f, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    //encontra qual é o maior filho
    if (j < sz && more(f->fila[j+1], f->fila[j+2])){
      j++;
    }
    if (!more(f->fila[k], f->fila[j+1])) {
      break;
    }
    swap(f ,k, j+1);
    k = j+1;
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
    fix_up(f, f->N);
}

Item PQ_delmin(fp* f){
    Item min = f->fila[0];
    swap(f, 0, f->N);
    f->N--;
    fix_down(f, f->N, 0);
    return min;
}

Item PQ_min(fp* f) {
    return f->fila[0];
}

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