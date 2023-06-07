#ifndef PILHA_H
#define PILHA_H

typedef struct pilha Pilha;

Pilha * criaPilhaVazia();
void push(Pilha *p, int node);
int pop(Pilha *p);
int pilhaVazia(Pilha *p);
void destroiPilha(Pilha*p);
void imprimePilha(Pilha *p);

#endif