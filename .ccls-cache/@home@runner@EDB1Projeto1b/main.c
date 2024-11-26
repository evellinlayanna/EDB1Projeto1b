#include "projeto.h"

int main() {
  Fila *filaCargas = inicializarFila();
  carregarCargas(
      filaCargas,
      "cargas.csv"); // Substitua "cargas.csv" pelo nome do seu arquivo

  int escolha;
  char idCarga[10];

  do {
    printf("\nSistema de Gerenciamento de Cargas\n");
    printf("1. Adicionar Carga\n");
    printf("2. Remover Carga\n");
    printf("3. Buscar Carga\n");
    printf("4. Exibir Cargas\n");
    printf("5. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
    case 1:
      adicionarCarga(filaCargas);
      break;
    case 2:
      removerCarga(filaCargas);
      break;
    case 3:
      printf("Informe o ID da carga para buscar: ");
      scanf("%s", idCarga);
      buscarCarga(filaCargas, idCarga);
      break;
    case 4:
      exibirCargas(filaCargas);
      break;
    case 5:
      printf("Saindo...\n");
      break;
    default:
      printf("Opção inválida!\n");
    }
  } while (escolha != 5);

  return 0;
}
