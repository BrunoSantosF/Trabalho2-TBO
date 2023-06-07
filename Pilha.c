#include <stdio.h>
#include <stdlib.h>
#include "Pilha.h"

typedef struct celula Celula;

struct celula {
    int node;
    Celula * ant;
};

struct pilha {
    Celula * ultimo;
};

Pilha * criaPilhaVazia(){
    Pilha  *  p = malloc(sizeof(Pilha));
    p->ultimo = NULL;
    return p;
}

void push(Pilha *p, int node){
    Celula * novo = malloc(sizeof(Celula));
    novo->node = node;
    novo->ant = p->ultimo;
    p->ultimo = novo;
}

int pop(Pilha *p){
    if (pilhaVazia(p)) return 0;

    Celula*temp = p->ultimo;
    p->ultimo = p->ultimo->ant;

    int val  =  temp->node;
    free(temp);

    return val;
}

int pilhaVazia(Pilha *p){
    if (p->ultimo==NULL) return 1;
    else return 0;
}

void imprimePilha(Pilha *p){
    Celula * atual = p->ultimo;
    while (atual) {
        if (!atual->ant) printf("%d\n", atual->node);
        else printf("%d;", atual->node);
        atual=atual->ant;
    }
}

void destroiPilha(Pilha*p){
    Celula * atual = p->ultimo;
    while (atual)  {
        Celula * temp = atual->ant;
        free(atual);
        atual=temp;
    }
    free(p);
}