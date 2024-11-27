#include "projeto.h"
#include <stdio.h>

int main() {

  // Cria uma fila vazia para armazenar as cargas
  Fila *fila = criarFila();

  // Carrega cargas de um arquivo CSV para a fila
  carregarCargasDeArquivo(fila, "cargas.csv");

  int escolha;
  do {
    printf("\n========= MENU ==========\n\n");
    printf("Gestão de Cargas Portuárias\n");
    printf("1. Adicionar Carga\n");
    printf("2. Remover Carga por Prioridade\n");
    printf("3. Buscar Carga por ID\n");
    printf("4. Exibir Cargas\n");
    printf("5. Sair\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);
    printf("\n");

    if (escolha == 1) {
      Carga novaCarga;
      printf("ID: ");
      scanf("%s", novaCarga.id);
      printf("Tipo: ");
      scanf(" %[^\n]", novaCarga.tipo);
      printf("Peso: ");
      scanf("%f", &novaCarga.peso);
      printf("Prioridade (Alta, Normal, Baixa): ");
      scanf(" %[^\n]", novaCarga.prioridade);
      printf("Descrição: ");
      scanf(" %[^\n]", novaCarga.descricao);
      enfileirar(fila, novaCarga);
    } else if (escolha == 2) {
      removerPorPrioridade(fila);
    } else if (escolha == 3) {
      char id[10];
      printf("ID da carga: ");
      scanf("%s", id);
      buscarPorID(fila, id);
    } else if (escolha == 4) {
      exibirFila(fila);
    }
  } while (escolha != 5);

  printf("Programa encerrado.\n");
  return 0;
}
