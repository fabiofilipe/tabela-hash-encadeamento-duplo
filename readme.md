# Prática: Tabela Hash com Encadeamento Separado Duplo

**Disciplina:** Estrutura de Dados  
**Professor:** Gilberto Farias  
**Entrega:** 17/04/2025

## Descrição

Implementação de uma tabela hash em dois níveis de endereçamento:

1. **Nível 1**: vetor de 10 ponteiros para tabelas de segundo nível.  
2. **Nível 2**: cada tabela contém `n/10` listas encadeadas (buckets).

Para inserir ou buscar um objeto:
- Aplica-se `hash1(key)` → escolhe a sub-tabela (0–9).
- Em seguida `hash2(key)` → escolhe o bucket dentro dessa sub-tabela.

## Arquivos

- `hash_table.h` – declarações de tipos e protótipos.  
- `hash_table.c` – implementa funções hash, inserção e busca.  
- `main.c`        – exemplo de uso e testes simples.  
- `Makefile`      – regras para compilar.

## Como compilar

```bash
make
./tabela_hash
