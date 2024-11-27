#ifndef PROJETO_H
#define PROJETO_H

// Estrutura para armazenar os dados de uma carga
typedef struct Carga {
  char id[10];
  char tipo[50];
  float peso;
  char prioridade[10];
  char descricao[200];
} Carga;

// Estrutura para representar um nó na fila
typedef struct No {
  Carga carga;        // Dados da carga armazenados no nó
  struct No *proximo; // Ponteiro para o próximo nó
} No;

// Estrutura para representar a fila
typedef struct Fila {
  No *inicio; // Ponteiro para o primeiro nó
  No *fim;    // Ponteiro para o último nó
} Fila;

// Funções para manipular nós e filas
Fila *criarFila();
No *criarNo(Carga carga);
void enfileirar(Fila *fila, Carga carga);
Carga desenfileirar(Fila *fila);
void exibirFila(Fila *fila);
void buscarPorID(Fila *fila, const char *id);
void removerPorPrioridade(Fila *fila);
void carregarCargasDeArquivo(Fila *fila, const char *nomeArquivo);

#endif
