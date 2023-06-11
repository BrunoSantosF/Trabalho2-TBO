#ifndef PILHA_H
#define PILHA_H

typedef struct pilha Pilha;


/// @brief cria uma nova pilha
/// @return a pilha criada
Pilha * criaPilhaVazia();

/// @brief coloca novo elemento na pilha
/// @param p uma pilha
/// @param node novo elemento
void push(Pilha *p, int node);

/// @brief retira um elemento da pilha
/// @param p uma pilha
/// @return o elemento
int pop(Pilha *p);

/// @brief verifica se a pilha está vazia
/// @param p uma pilha
/// @return true, se a pilha estiver vazia
int pilhaVazia(Pilha *p);

/// @brief libera a memória da pilha
/// @param p uma pilha 
void destroiPilha(Pilha*p);

/// @brief imprime os elementos da pilha
/// @param p uma pilha
void imprimePilha(Pilha *p);


#endif