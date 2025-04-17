#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

int main() {
    // 1) Cria tabela para até 100 objetos
    HashTable *ht = ht_create(100);

    // 2) Insere alguns pares (key, value)
    int v1 = 42, v2 = 99, v3 = 12345;
    ht_insert(ht, 10, &v1);
    ht_insert(ht, 27, &v2);
    ht_insert(ht, 134, &v3);

    // 3) Busca e imprime
    int *p;
    p = ht_search(ht, 27);
    printf("Chave 27 → %d\n", p ? *p : -1);

    p = ht_search(ht, 5);
    printf("Chave 5  → %s\n", p ? "encontrado" : "não encontrada");

    // 4) Libera a tabela
    ht_destroy(ht);
    return 0;
}
