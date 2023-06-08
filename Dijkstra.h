#ifndef DIJSKTRA_H
#define DIJSKTRA_H
#include "Pilha.h"

void ordenarDistancias(double ** distancias, int qtdDistancias);
int * calculaMenorCaminho(double ** distancias, int qtdDistancias, int qtdNo, int origem, int destino, int * tamanhoCaminho);

#endif