#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Cria e inicia uma nova fila vazia
// Cada fila tem dois ponteiros: um para o início e outro para o fim
Fila *criarFila() {
  Fila *fila = (Fila *)malloc(sizeof(Fila));
  if (!fila) {
    printf("Erro ao alocar memória para a fila.\n");
    exit(1);
  }
  // Iniciando o ponteiro para o início e fim da fila como NULL
  fila->inicio = NULL;
  fila->fim = NULL;
  return fila;
}

// Função que cria um novo nó com as informações fornecidas
// Aloca memória, preenche os dados e retorna o nó pronto para uso
No *criarNo(Carga carga) {
  No *novoNo = (No *)malloc(sizeof(No));
  if (!novoNo) {
    printf("Erro ao alocar memória para o nó.\n");
    exit(1);
  }
  novoNo->carga = carga;  // Armazena a carga no nó
  novoNo->proximo = NULL; // Inicia o ponteiro "proximo" como NULL
  return novoNo;
}

// Adiciona um novo nó à fila
void enfileirar(Fila *fila, Carga carga) {
  // Cria um nó com a carga fornecida
  No *novoNo = criarNo(carga);
  if (!fila->inicio) {     // Fila vazia
    fila->inicio = novoNo; // O novo nó é o início e o fim da fila
    fila->fim = novoNo;
  } else {
    fila->fim->proximo = novoNo; // Conecta o último nó com o novo nó
    fila->fim = novoNo;          // Atualiza o fim da lista para o novo nó
  }
}

// Remove o primeiro nó da fila e retorna a carga removida
Carga desenfileirar(Fila *fila) {
  if (!fila->inicio) {
    printf("Erro: Fila vazia.\n");
    exit(1);
  }
  No *noRemovido = fila->inicio;      // Guarda o nó a ser removido
  Carga carga = noRemovido->carga;    // Armazena a carga removida
  fila->inicio = noRemovido->proximo; // Atualiza o início da fila
  if (!fila->inicio) {                // Se a fila ficou vazia
    fila->fim = NULL;
  }
  free(noRemovido); // Libera a memória do nó removido
  return carga;
}

// Exibe todos os nós da fila
void exibirFila(Fila *fila) {
  if (!fila->inicio) {
    printf("A fila está vazia.\n");
    return;
  }
  // Começa pelo início da fila com o primiero nó
  No *atual = fila->inicio;
  printf("Fila de cargas:\n\n");
  while (atual) {
    printf("ID: %s | Tipo: %s | Peso: %.2f | Prioridade: %s | Descrição: %s\n",
           atual->carga.id, atual->carga.tipo, atual->carga.peso,
           atual->carga.prioridade, atual->carga.descricao);
    atual = atual->proximo; // Move a fila para o proximo nó
  }
}

// Busca uma carga pelo ID
void buscarPorID(Fila *fila, const char *id) {
  No *atual = fila->inicio;
  while (atual) {
    if (strcmp(atual->carga.id, id) == 0) {
      printf("\nCarga encontrada!\n\n");
      printf("ID: %s\nTipo: %s\nPeso: %.2f\nPrioridade: %s\nDescrição: %s\n",
             atual->carga.id, atual->carga.tipo, atual->carga.peso,
             atual->carga.prioridade, atual->carga.descricao);
      return; // Se encontrou a carga, retorna
    }
    atual = atual->proximo; // Se não, passa para o próximo nó
  }
  printf("\nCarga com ID %s não encontrada.\n", id);
}

// Remove a carga com maior prioridade (ou a primeira da fila, se não houver
// "Alta")
void removerPorPrioridade(Fila *fila) {
  if (!fila->inicio) {
    printf("A fila está vazia.\n");
    return;
  }

  No *anterior = NULL, *atual = fila->inicio, *prioritario = NULL,
     *prevPrioritario = NULL;

  while (atual) {
    if (strcmp(atual->carga.prioridade, "Alta") == 0) {
      prioritario = atual; // Define o no com prioridade "Alta" como prioritário
      prevPrioritario = anterior; // Define o nó anterior ao prioritário
      break;                      // Se encontra o nó prioritário, sai do loop
    }
    anterior = atual; // Vai apara o próximo nó
    atual = atual->proximo;
  }

  if (!prioritario) {           // Nenhum com prioridade "Alta" encontrado
    prioritario = fila->inicio; // Remove o primeiro nó da fila
  }

  if (prevPrioritario) { // Se o nó prioritário não for o primeiro da fila
    prevPrioritario->proximo =
        prioritario->proximo; // Remove o nó prioritário da fila
  } else {
    fila->inicio =
        prioritario->proximo; // Se o nó prioritário é o primeiro da fila
  }

  if (prioritario == fila->fim) { // Caso o nó removido seja o último
    fila->fim = prevPrioritario;
  }

  printf("Carga ID: %s e Tipo: %s removida! \n", prioritario->carga.id,
         prioritario->carga.tipo);
  free(prioritario); // Libera a memória do nó removido
}

// Carrega cargas de um arquivo .csv e adiciona a fila
void carregarCargasDeArquivo(Fila *fila, const char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (!arquivo) {
    printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
    return;
  }

  char linha[256];
  while (fgets(linha, sizeof(linha), arquivo)) {
    Carga carga;
    sscanf(linha, "%[^,],%[^,],%f,%[^,],%[^\n]", carga.id, carga.tipo,
           &carga.peso, carga.prioridade, carga.descricao);
    enfileirar(fila, carga); // Adiciona a carga a fila
  }

  fclose(arquivo);
  printf("Cargas carregadas do arquivo %s.\n", nomeArquivo);
}
