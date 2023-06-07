#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "Item.h"

typedef struct filaPrioridade fp;

Item * make_item(int id, double value);
fp* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(fp* f, Item * v);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item * PQ_delmin(fp* f);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(fp* f, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item * PQ_min(fp* f);          // Retorna Item com menor campo 'value' da PQ
bool PQ_empty(fp* f);        // Retorna True se a PQ não tem elementos
int  PQ_size(fp* f);         // Número de elementos na PQ
void PQ_finish(fp* f);       // Libera memória

#endif