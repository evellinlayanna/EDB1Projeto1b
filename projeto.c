#include "projeto.h"

// Função para criar um novo nó de carga
Carga *criarCarga(char *id, char *tipo, float peso, char *prioridade, char *descricao) {
  Carga *novaCarga = (Carga *)malloc(sizeof(Carga));
  if (novaCarga == NULL) {
    printf("Falha na alocação de memória!\n");
    exit(1);
  }
  strcpy(novaCarga->id, id);
  strcpy(novaCarga->tipo, tipo);
  novaCarga->peso = peso;
  strcpy(novaCarga->prioridade, prioridade);
  strcpy(novaCarga->descricao, descricao);
  novaCarga->proxima = NULL;
  return novaCarga;
}

// Função para inicializar a fila
Fila *inicializarFila() {
  Fila *f = (Fila *)malloc(sizeof(Fila));
  if (f == NULL) {
    printf("Falha na alocação de memória!\n");
    exit(1);
  }
  f->inicio = NULL;
  f->fim = NULL;
  return f;
}

// Função para verificar se a fila está vazia
int estaVazia(Fila *f) { return (f->inicio == NULL); }

// Função para enfileirar uma carga
void enfileirar(Fila *f, Carga *novaCarga) {
  if (estaVazia(f)) {
    f->inicio = novaCarga;
    f->fim = novaCarga;
  } else {
    f->fim->proxima = novaCarga;
    f->fim = novaCarga;
  }
}

// Função para desenfileirar uma carga
Carga *desenfileirar(Fila *f) {
  if (estaVazia(f)) {
    printf("A fila está vazia!\n");
    return NULL;
  }
  Carga *temp = f->inicio;
  f->inicio = f->inicio->proxima;
  if (f->inicio == NULL) {
    f->fim = NULL;
  }
  return temp;
}

// Função para visualizar a carga no início da fila
Carga *visualizar(Fila *f) {
  if (estaVazia(f)) {
    printf("A fila está vazia!\n");
    return NULL;
  }
  return f->inicio;
}

// Função para adicionar uma nova carga
void adicionarCarga(Fila *f) {
  char id[10], tipo[50], prioridade[10], descricao[200];
  float peso;

  printf("Informe o ID da carga: ");
  scanf("%s", id);
  printf("Informe o tipo da carga: ");
  scanf(" %[^\n]", tipo);
  printf("Informe o peso da carga: ");
  scanf("%f", &peso);
  printf("Informe a prioridade da carga (Alta, Normal, Baixa): ");
  scanf(" %[^\n]", prioridade);
  printf("Informe a descrição da carga: ");
  scanf(" %[^\n]", descricao);

  Carga *novaCarga = criarCarga(id, tipo, peso, prioridade, descricao);
  enfileirar(f, novaCarga);
  printf("Carga adicionada com sucesso!\n");
}

// Função para remover uma carga com base na prioridade
void removerCarga(Fila *f) {
  if (estaVazia(f)) {
    printf("A fila está vazia!\n");
    return;
  }
  Carga *cargaAltaPrioridade = NULL;

  // Encontrar a primeira carga com prioridade "Alta"
  Carga *atual = f->inicio;
  while (atual != NULL) {
    if (strcmp(atual->prioridade, "Alta") == 0) {
      cargaAltaPrioridade = atual;
      break;
    }
    atual = atual->proxima;
  }

  // Se nenhuma carga com prioridade "Alta", remove a primeira carga
  if (cargaAltaPrioridade == NULL) {
    Carga *cargaRemovida = desenfileirar(f);
    printf("Carga removida: ID - %s, Tipo - %s\n", cargaRemovida->id,
           cargaRemovida->tipo);
    free(cargaRemovida);
  } else {
    // Remove a carga com prioridade "Alta"
    if (cargaAltaPrioridade == f->inicio) {
      f->inicio = f->inicio->proxima;
    } else {
      atual = f->inicio;
      while (atual->proxima != cargaAltaPrioridade) {
        atual = atual->proxima;
      }
      atual->proxima = cargaAltaPrioridade->proxima;
    }
    printf("Carga removida: ID - %s, Tipo - %s\n", cargaAltaPrioridade->id,
           cargaAltaPrioridade->tipo);
    free(cargaAltaPrioridade);
  }
}

// Função para buscar uma carga pelo ID
void buscarCarga(Fila *f, char *idCarga) {
  if (estaVazia(f)) {
    printf("A fila está vazia!\n");
    return;
  }
  Carga *atual = f->inicio;
  while (atual != NULL) {
    if (strcmp(atual->id, idCarga) == 0) {
      printf("Carga encontrada:\n");
      printf("ID: %s\n", atual->id);
      printf("Tipo: %s\n", atual->tipo);
      printf("Peso: %.2f kg\n", atual->peso);
      printf("Prioridade: %s\n", atual->prioridade);
      printf("Descrição: %s\n", atual->descricao);
      return;
    }
    atual = atual->proxima;
  }
  printf("Carga com ID %s não encontrada!\n", idCarga);
}

// Função para exibir todas as cargas na fila
void exibirCargas(Fila *f) {
  if (estaVazia(f)) {
    printf("A fila está vazia!\n");
    return;
  }
  printf("Fila de Cargas:\n");
  Carga *atual = f->inicio;
  while (atual != NULL) {
    printf("ID: %s, Tipo: %s, Peso: %.2f kg, Prioridade: %s, Descrição: %s\n",
           atual->id, atual->tipo, atual->peso, atual->prioridade,
           atual->descricao);
    atual = atual->proxima;
  }
}

// Função para carregar dados de carga de um arquivo CSV
void carregarCargas(Fila *f, char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo %s!\n", nomeArquivo);
    return;
  }

  char linha[256];
  char id[10], tipo[50], prioridade[10], descricao[200];
  float peso;

  while (fgets(linha, sizeof(linha), arquivo) != NULL) {
    sscanf(linha, "%[^,],%[^,],%f,%[^,],%[^\n]", id, tipo, &peso, prioridade,
           descricao);
    Carga *novaCarga = criarCarga(id, tipo, peso, prioridade, descricao);
    enfileirar(f, novaCarga);
  }

  fclose(arquivo);
  printf("Dados de carga carregados de %s!\n", nomeArquivo);
}
