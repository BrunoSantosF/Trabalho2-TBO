#include <stdio.h>
#include <stdlib.h>
#include "FilaPrioridade.h"
#include "Item.h"

Item * make_item(int id, double value) {
    Item * t = malloc(sizeof(Item));
    id(t) = id;
    value(t) = value;
    return t;
}

int main() {

    // inicializando a PQ
    fp* PQ = PQ_init(10);

    // inserindo alguns elementos na PQ
    PQ_insert(PQ, make_item(1, 10.0));
    PQ_insert(PQ, make_item(6, 5.0));
    PQ_insert(PQ, make_item(3, 3.0));
    PQ_insert(PQ, make_item(4, 4.0));
    PQ_insert(PQ, make_item(7, 7.0));
    PQ_insert(PQ, make_item(2, 1.0));

    // alterando a prioridade de alguns elementos
    PQ_decrease_key(PQ, 4, 0.5); // agora o nó 4 tem valor 0.5, sua posição no heap deve mudar
    PQ_decrease_key(PQ, 6, 0.1); // agora o nó 6 tem valor 0.1, sua posição no heap deve mudar

    // removendo o menor elemento e imprimindo
    while (!PQ_empty(PQ)) {
        Item * p = PQ_delmin(PQ);
        printf("Identificador %d, prioridade %lf\n", id(p), value(p));
    }

}