#include <stdio.h>
#include <string.h>
#include <time.h>

// Definir a estrutura da tarefas
struct tarefa {
  char nome[100];
  char dataInicio[11];
  char dataTermino[11];
  char status[20];
};

struct tarefa listaTarefas[100];
int numTarefas = 0; // Numero de tarefas atual

void adicionarTarefa() {
  struct tarefa novaTarefa;
  int x;
  printf("\nDigite o nome da tarefa: ");
  scanf("%[^\n]", novaTarefa.nome);
  getchar(); // É usado para limpar o buffer após a leitura

  // Exibir opção de inserir data inicial
  printf("\nDeseja adicionar a data de hoje ou quer inserir manualmente?\n");
  puts("\n(1) para de hoje\n(2) para manualmente: ");
  scanf("%d", &x);
  getchar(); //é usado para limpar o buffer após a leitura

  if (x == 1) {
    time_t t = time(NULL);         // Data atual em segundos
    struct tm tm = *localtime(&t); // Converte para formato atual
    sprintf(novaTarefa.dataInicio, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1,
            tm.tm_year + 1900); // Armazena a data formatada

    novaTarefa.dataTermino[0] = '\0'; // inicializa como vazio
    novaTarefa.status[0] = '\0';      // Inicializa como vazio

    printf("\n       😄Tarefa criada com sucesso!!😄");
  }
  
  // Neste bloco usuaria digitara manualmente
  else if (x == 2) {
    printf("\nDigite a nova data de início (formato dd/mm/aaaa): ");
    scanf("%s", novaTarefa.dataInicio);
    novaTarefa.dataTermino[0] = '\0';
    novaTarefa.status[0] = '\0';

    printf("\n       😄Atividade criada com sucesso!!😄");
  }
  // Ter o controle de tarefas adicionadas na estrutura
  listaTarefas[numTarefas] = novaTarefa;
  numTarefas++;
}

void editarTarefa() {
  char nomeTarefa[100];
  int encontrou = 0; // Flag para indicar se a tarefa foi encontrada ou não

  printf("\nDigite o nome da tarefa que deseja editar: \n");
  scanf("%[^\n]", nomeTarefa);
  getchar();

  for (int i = 0; i < numTarefas; i++) {
    // Aqui ele vai compara a nome digiado com o nome de todas tarefas salvas
    if (strcmp(listaTarefas[i].nome, nomeTarefa) == 0) {
      printf("\nDigite o novo nome da tarefa: ");
      scanf("%[^\n]", listaTarefas[i].nome);
      getchar();

      printf("\nDigite a nova data de início (formato dd/mm/aaaa): ");
      scanf("%s", listaTarefas[i].dataInicio);

      printf("\nDigite a nova data de término (formato dd/mm/aaaa): ");
      scanf("%s", listaTarefas[i].dataTermino);

      printf("\nDigite o novo status da tarefa: ");
      scanf("%s", listaTarefas[i].status);

      printf("\n       😄Atualizado com sucesso!!😄");

      encontrou = 1;
      break;
    }
  } // caso tarefa nao encontrada
  if (!encontrou) {
    printf("\n       😐Tarefa não encontrada😐\n");
  }
}

void buscarTarefa() {
  char nomeTarefa[100];
  int encontrou = 0; // Flag para indicar se a tarefa foi encontrada ou não

  // Buscar nome na lista de tarefas
  printf("\nDigite o nome da tarefa que deseja buscar: ");
  scanf("%[^\n]", nomeTarefa);
  getchar();

  for (int i = 0; i < numTarefas; i++) {
    if (strcmp(listaTarefas[i].nome, nomeTarefa) == 0) {
      printf("\nTarefa encontrada com sucesso:\n\n");
      printf("Nome: %s\n", listaTarefas[i].nome);
      printf("Data de inicio: %s\n", listaTarefas[i].dataInicio);
      printf("Data de término: %s\n", listaTarefas[i].dataTermino);
      printf("Status: %s\n", listaTarefas[i].status);

      // Seta a flag como verdadeira
      encontrou = 1;
      break;
    }
  }
  // Caso tarefa nao encontrada
  if (!encontrou) {
    printf("\n       😐Tarefa não encontrada😐\n");
  }
}

void mudarStatus() {
  char nomeTarefa[100];
  int posicao = -1;
  int update = 0;

  // Solicitar nome da tarefa
  printf("Digite o nome da tarefa que seja mudar o status: ");
  scanf("%[^\n]", nomeTarefa);
  getchar();

  // Buscar nome na lista de tarefas
  for (int i = 0; i < numTarefas; i++) {
    if (strcmp(listaTarefas[i].nome, nomeTarefa) == 0) {
      posicao = i;
      break;
    }
  }

  // Exibe as opções de atualização do status
  printf("\n(1) Atualizar status para concluido automatico \n");
  printf("\n(2) Atualizar status manualmente \n");
  scanf("%d", &update);
  getchar();

  // Verifica se a opção de atualização é válida
  if (update != 1 && update != 2) {
    printf("\n       😐Decisão invalidade!😐");
  }

  // Atualiza o status para "Concluído" automaticamente
  if (update == 1) {

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(listaTarefas[posicao].dataTermino, "%02d/%02d/%d", tm.tm_mday,
            tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(listaTarefas[posicao].status, "Concluido");

    printf("\n       😄Atualizado com sucesso!!😄");
  }

  // Atualiza o status manualmente
  else if (update == 2) {

    printf("\nDigite a nova data de término (formato dd/mm/aaaa): ");
    scanf("%s", listaTarefas[posicao].dataTermino);

    printf("\nDigite o novo status da tarefa: ");
    scanf("%s", listaTarefas[posicao].status);

    printf("\n       😄Atualizado com sucesso!!😄");
  }
  return;
}

void removerTarefa() {
  char nomeTarefa[100];
  int posicao = -1;
  printf("\nDigite o nome da terafa que deseja excluir: ");
  scanf("%s", nomeTarefa);
  getchar(); //é usado para limpar o buffer após a leitura

  for (int i = 0; i < numTarefas; i++) {
    if (strcmp(listaTarefas[i].nome, nomeTarefa) == 0) {
      posicao = i;
      break;
    }
  }
  if (posicao == -1) {
    printf("\n       😐Tarefa não encontrada\n");
  } else {
    for (int i = posicao; i < numTarefas - 1; i++) {
      listaTarefas[i] = listaTarefas[i + 1];
    }
    (numTarefas)--;
    printf("\n       😄Tarefa excluida com sucesso😄\n");
  }
}

void quantasTarefas(int *c) {
  int cont = 0;

  for (int i = 0; i < numTarefas; i++) {
    if (listaTarefas[i].nome[0] != '\0') {
      cont++;
    }
  }
  *c = cont;
}

int main(void) {
  int x, y;

  do {
    printf("\n\nBem vindo ao seu gerenciamento de tarefas 📄\n");
    puts("\nGostaria de:");
    puts("(1)Adicionar➕");
    puts("(2)Mudar Status✅");
    puts("(3)Buscar🔎");
    puts("(4)Editar🔩");
    puts("(5)Remover ❌");
    puts("(6)Quantidade de tarefas atualmente🗂");
    scanf("%d", &x);
    getchar(); //é usado para limpar o buffer após a leitura

    switch (x) {
    case 1:
      adicionarTarefa();
      break;

    case 2:
      mudarStatus();
      break;

    case 3:
      buscarTarefa();
      break;

    case 4:
      editarTarefa();
      break;

    case 5:
      removerTarefa();
      break;

    case 6:
      quantasTarefas(&y);
      printf("\n       😄Atualmente tem %d tarefas!😄", y);
      break;

    default:
      printf("\n❌❌Errouuu tentou novamente❌❌\n");
    }
  } while (x != 0);
  return 0;
}