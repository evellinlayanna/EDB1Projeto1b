INTRODUÇÃO

Este projeto visa desenvolver uma aplicação em linguagem C que utiliza a estrutura de dados Fila, implementada com lista encadeada, para simular a gestão de cargas portuárias. O objetivo é organizar e priorizar o carregamento e descarregamento de cargas com base em critérios específicos, garantindo uma gestão eficiente e ágil.

REQUISITOS DO PROJETO

O sistema deverá atender aos seguintes requisitos:

1. Utilizar a estrutura de dados Fila, com lista encadeada, para gerenciar as cargas.
2. Implementar as operações básicas:
	- Inserção de cargas.
	- Remoção de cargas com base na prioridade.
	- Busca de cargas específicas por ID.
	- Exibição das cargas da fila.
3. Permitir o carregamento inicial de dados de um arquivo .csv.
4. Oferecer ao usuário a opção de adicionar novas cargas manualmente.
5. Implementar modularização no código-fonte.

ESTRUTURA DE DADOS

Cada carga será representada por uma estrutura contendo os seguintes atributos:
	- ID (identificador único da carga).
	- Tipo de carga (ex.: container, granel sólido, granel líquido).
	- Peso (em quilogramas).
	- Prioridade (baixa, normal ou alta).
	- Descrição (detalhes da carga).

OPERAÇÕES IMPLEMENTADAS

1. Inserção de Carga

A inserção de uma carga ocorre no final da fila, mantendo a ordem de chegada. Novas cargas podem ser adicionadas pelo usuário ou lidas de um arquivo .csv. Os atributos obrigatórios devem ser validados antes da inserção.

2. Remoção de Carga com Prioridade

A remoção segue as seguintes regras:
  1. Localizar a primeira carga na fila com a prioridade Alta.
	2. Caso existam múltiplas cargas de prioridade Alta, remover a carga adicionada mais cedo 	(ordem de chegada).
	3. Se não houver cargas de prioridade Alta, remover a carga no início da fila.

Após a remoção, a fila deve ser reorganizada para manter a integridade. Exemplo:

Fila inicial:
ID: 001 | Tipo: Container | Peso: 15.3 | Prioridade: Normal
ID: 002 | Tipo: Granel sólido | Peso: 30.0 | Prioridade: Alta
ID: 003 | Tipo: Granel l´ıquido | Peso: 50.0 | Prioridade: Normal

Remoção: A carga com ID 002 (prioridade Alta) é processada.

Fila resultante:
ID: 001 | Tipo: Container | Peso: 15.3 | Prioridade: Normal
ID: 003 | Tipo: Granel líquido | Peso: 50.0 | Prioridade: Normal

3. Busca de Carga
A busca permite ao usuário localizar uma carga específica pelo seu ID. O sistema deverá exibir todos os atributos da carga encontrada.

4. Exibição de Cargas

O sistema deverá exibir todas as cargas pertencentes à fila.

5. Exemplo de um arquivo .csv

C006,Granel l´ıquido,4587.31,Normal,medicamentos
C002,Container,2568.19,Alta,fertilizantes
C020,Granel s´olido,4097.81,Normal,produtos químicos
C003,Container,2176.93,Baixa,materiais de construção

FUNCIONAMENTO GERAL

1. O sistema carrega os dados iniciais de um arquivo .csv.
2. O usuário pode visualizar as cargas na fila, adicionar novas cargas ou processar a próxima carga.
3. A cada processamento, a carga removida será exibida, e a fila será reorganizada automaticamente.
4. O sistema deve exibir mensagens claras para cada operação realizada.
