#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

Lista * inicializaLista();
void insereItem(Lista * lista, int destino, double velocidade, double distancia);
double getDistancia(Lista * lista, int destino);
double getVelocidade(Lista * lista, int destino);
void mudaVelocidade(Lista * lista, int destino, double novaVelocidade);
void liberaLista(Lista * lista);
double getTempoVizinho(Lista * lista, int nmrVizinho);
void imprimeLista(Lista * lista);
int getDestinoVizinho(Lista * lista, int nmrVizinho);

#endif