#ifndef PQ_H
#define PQ_H

/* CÓDIGO DISPONIBILIZADO PELO PROFESSOR, APENAS REFORMULADO PARA NÃO UTILIZAR VARIÁVEIS GLOBAIS*/


#include <stdbool.h>
#include "Item.h"

typedef struct filaPrioridade fp;


/// @brief 
/// @param id 
/// @param value 
/// @return 
Item * make_item(int id, double value);

/// @brief cria uma min PQ com capacidade maxN
/// @param maxN tamanho da fila de prioridade
/// @return nova fila de prioridade
fp* PQ_init(int maxN); 

/// @brief Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
/// @param f uma fila de prioridade
/// @param v item a ser inserido
void PQ_insert(fp* f, Item * v);   

/// @brief Remove Item com menor campo 'value' da PQ
/// @param f uma fila de prioridade
/// @return o menor item da fila
Item * PQ_delmin(fp* f);

/// @brief Muda a prioridade do nó com identificador 'id' para 'value'
/// @param f uma fila de prioridade
/// @param id identificador do nó
/// @param value novo valor do nó
void PQ_decrease_key(fp* f, int id, double value);

/// @brief Retorna Item com menor campo 'value' da fila de prioridade, não o retira
/// @param f uma fila de prioridade
/// @return item com menor campo "value"
Item * PQ_min(fp* f);

/// @brief verifica se a fila não tem elementos
/// @param f uma fila de prioridade
/// @return true, se a fila não tem elementos
bool PQ_empty(fp* f);

/// @brief verifica o tamanho da fila
/// @param f uma fila de prioridade
/// @return Número de elementos na fila
int  PQ_size(fp* f);

/// @brief Libera memória
/// @param f uma fila de prioridade
void PQ_finish(fp* f);


#endif