
#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stddef.h>

// --------- Tipos ---------

// Objeto armazenado na tabela
typedef struct Item {
    int key;            // chave única
    void *value;        // ponteiro para dados associados
    struct Item *next;  // próximo item na lista duplamente ligada
    struct Item *prev;  // anterior
} Item;

// Bucket (lista dupla) no segundo nível
typedef struct {
    Item *head;         // início da lista
} Bucket;

// Sub-tabela (nível 2)
typedef struct {
    size_t bucket_count; // número de buckets: n/10
    Bucket *buckets;     // vetor de buckets
} SubTable;

// Tabela hash principal (nível 1)
typedef struct {
    size_t size;         // n = capacidade total esperada
    SubTable subtables[10];
} HashTable;

// --------- Protótipos ---------

// Cria e inicializa uma tabela hash para `n` objetos.
HashTable *ht_create(size_t n);

// Libera todos os itens e estruturas da tabela.
void ht_destroy(HashTable *ht);

// Insere `value` sob a chave `key`.
void ht_insert(HashTable *ht, int key, void *value);

// Busca o valor associado a `key`; retorna NULL se não encontrado.
void *ht_search(HashTable *ht, int key);

#endif // HASH_TABLE_H
