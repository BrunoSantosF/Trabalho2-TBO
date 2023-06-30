#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

typedef struct celula Celula;

struct celula {
	int destino;
	double distancia;
	double velocidade;
	Celula * prox;
};

struct lista {
	Celula * prim;
    Celula * ult;
};

Lista * inicializaLista(){
	Lista * lista = malloc(sizeof(Lista));
	lista->prim = NULL;
    lista->ult = NULL;
	return lista;
}

void insereItem(Lista * lista, int destino, double velocidade, double distancia){
    Celula * novo = malloc(sizeof(Celula));
	novo->destino = destino;
	novo->distancia = distancia;
	novo->velocidade = velocidade;
    novo->prox = NULL;

    // lista vazia
    if (lista->prim==NULL) {
        lista->prim=novo;

    // lista com um item
    } else if (lista->prim==lista->ult) {
        lista->prim->prox=novo;
    
    // lista com varios itens
    } else {
        lista->ult->prox = novo;
    }

    lista->ult=novo;
}

double getDistancia(Lista * lista, int destino){
    Celula * item = lista->prim;
    while (item!=NULL && item->destino!=destino) item = item->prox;
    
    if (item==NULL) return -1;

    return item->distancia;
}

double getVelocidade(Lista * lista, int destino){
    Celula * item = lista->prim;
    while (item!=NULL && item->destino!=destino) item = item->prox;
    
    if (item==NULL) return -1;

    return item->velocidade;
}

double getTempoVizinho(Lista * lista, int nmrVizinho) {
    int i=0;
    Celula * item = lista->prim;
    while (item!=NULL && i++!=nmrVizinho) item = item->prox;
    if (item==NULL) return -1;
    return (item->distancia / 1000) / item->velocidade;
}

int getDestinoVizinho(Lista * lista, int nmrVizinho) {
    int i=0;
    Celula * item = lista->prim;
    while (item!=NULL && i++!=nmrVizinho) item = item->prox;
    if (item==NULL) return -1;
    return item->destino;
}

void mudaVelocidade(Lista * lista, int destino, double novaVelocidade){
    Celula * item = lista->prim;
    while (item!=NULL && item->destino!=destino) item = item->prox;
    item->velocidade = novaVelocidade;
}

void imprimeLista(Lista * lista){
    Celula * item = lista->prim;
    while (item!=NULL) {
        printf("%lf->", item->distancia);
        item = item->prox;
    }
    printf("\n");
}

void liberaLista(Lista * lista) {
    Celula * atual = lista->prim;
    while (atual!=NULL) {
        Celula * prox = atual->prox;
        free(atual);
        atual = prox;   
    }
    
    free(lista);
}