#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

// --------- Funções Hash ---------

// hash1: mapeia key em [0..9] (divisão simples)
static size_t hash1(int key) {
    return (size_t)(abs(key) % 10);
}

// hash2: mapeia key em [0..bucket_count-1]
// usamos um método diferente: multiplicação de Knuth
static size_t hash2(int key, size_t bucket_count) {
    const double A = 0.6180339887; // fracção de ouro
    double frac = (key * A) - (int)(key * A);
    return (size_t)(frac * bucket_count);
}

// --------- Criação e destruição ---------

HashTable *ht_create(size_t n) {
    HashTable *ht = malloc(sizeof(HashTable));
    ht->size = n;
    size_t per = (n + 9) / 10; // ceil(n/10)
    for (int i = 0; i < 10; i++) {
        ht->subtables[i].bucket_count = per;
        ht->subtables[i].buckets = calloc(per, sizeof(Bucket));
    }
    return ht;
}

void ht_destroy(HashTable *ht) {
    // Para cada sub-tabela e cada bucket, percorre lista e libera items
    for (int i = 0; i < 10; i++) {
        SubTable *st = &ht->subtables[i];
        for (size_t j = 0; j < st->bucket_count; j++) {
            Item *cur = st->buckets[j].head;
            while (cur) {
                Item *next = cur->next;
                free(cur);
                cur = next;
            }
        }
        free(st->buckets);
    }
    free(ht);
}

// --------- Inserção ---------

void ht_insert(HashTable *ht, int key, void *value) {
    size_t idx1 = hash1(key);
    SubTable *st = &ht->subtables[idx1];
    size_t idx2 = hash2(key, st->bucket_count);
    // Cria novo item
    Item *it = malloc(sizeof(Item));
    it->key = key;
    it->value = value;
    // Insere no início da lista dupla
    it->prev = NULL;
    it->next = st->buckets[idx2].head;
    if (it->next) it->next->prev = it;
    st->buckets[idx2].head = it;
}

// --------- Busca ---------

void *ht_search(HashTable *ht, int key) {
    size_t idx1 = hash1(key);
    SubTable *st = &ht->subtables[idx1];
    size_t idx2 = hash2(key, st->bucket_count);
    // Percorre lista procurando key
    for (Item *cur = st->buckets[idx2].head; cur; cur = cur->next) {
        if (cur->key == key) return cur->value;
    }
    return NULL;
}
