#ifndef PROJETO_H
#define PROJETO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Representa uma carga com seus atributos, como ID, tipo, peso, prioridade e descrição
// O campo 'proxima' conecta esta carga à próxima, formando uma lista encadeada
typedef struct Carga {
  char id[10];
  char tipo[50];
  float peso;
  char prioridade[10];
  char descricao[200];
  struct Carga *proxima;
} Carga;

// Representa a fila de cargas. Armazena o início e o final da fila
typedef struct Fila {
  Carga *inicio;
  Carga *fim;
} Fila;

// Protótipos das funções
Carga *criarCarga(char *id, char *tipo, float peso, char *prioridade, char *descricao);
Fila *inicializarFila();

int estaVazia(Fila *f);
void enfileirar(Fila *f, Carga *novaCarga);

Carga *desenfileirar(Fila *f);
Carga *visualizar(Fila *f);

void adicionarCarga(Fila *f);
void removerCarga(Fila *f);
void buscarCarga(Fila *f, char *idCarga);
void exibirCargas(Fila *f);
void carregarCargas(Fila *f, char *nomeArquivo);

#endif
