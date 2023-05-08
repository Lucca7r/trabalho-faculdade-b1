#include <stdio.h>
#include <stdlib.h>
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

void editarTarefa(int p) {
  int definir;

  printf("\nO que vc deseja alterar da tarefa: \n");
  puts("(1) Nome da tarefa");
  puts("(2) Data de inicio");
  puts("(3) Data de término");
  puts("(4) Status da tarefa");
  scanf("%d", &definir);

  switch (definir) {
  case 1:
    printf("\nDigite o novo nome da tarefa: \n");
    getchar();
    scanf("%[^\n]", listaTarefas[p].nome);
    getchar();
    printf("\n       😄Editado com sucesso!!😄\n");
    break;

  case 2:
    printf("\nDigite a nova data de início (formato dd/mm/aaaa): ");
    scanf("%s", listaTarefas[p].dataInicio);
    printf("\n       😄Editado com sucesso!!😄\n");
    getchar();
    break;

  case 3:
    printf("\nDigite a nova data de término (formato dd/mm/aaaa): ");
    scanf("%s", listaTarefas[p].dataTermino);
    getchar();
    printf("\n       😄Editado com sucesso!!😄\n");
    break;

  case 4:
    printf("\nDigite o novo status da tarefa: ");
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ; // Limpar o buffer de entrada
    scanf("%[^\n]", listaTarefas[p].status);
    getchar();
    printf("\n       😄Editado com sucesso!!😄\n");
    break;

  default:
    printf("\nOpção invalidade!\n");
  }
}

void achaNome() {
  char nomeTarefa[100];
  int passa;
  int encontrou = 0; // Flag para indicar se a tarefa foi encontrada ou não

  printf("\nDigite o nome da tarefa que deseja editar: \n");
  scanf("%[^\n]", nomeTarefa);
  getchar();

  // Aqui ele vai compara a nome digiado com o nome de todas tarefas salvas
  for (int i = 0; i < numTarefas; i++) {
    if (strcmp(listaTarefas[i].nome, nomeTarefa) == 0) {
      passa = i;
      editarTarefa(passa);
      encontrou = 1;
      break;
    }
  }
  // caso tarefa nao encontrada
  if (!encontrou) {
    printf("\n       😐Tarefa não encontrada😐\n");
  }
}

void ligacaoAdEd(int p) {
  // Função de "ponte" para editar tarefas
  int y;
  printf("Deseja editar essa tarefa ja existente?\n");
  puts("(1) Sim");
  puts("(2) Não");
  scanf("%d", &y);
  getchar();

  if (y == 1) {
    editarTarefa(p);
  } else {
    return;
  }
}

void adicionarTarefa() {
  struct tarefa novaTarefa;
  int x, p;
  printf("\nDigite o nome da tarefa: ");
  scanf("%[^\n]", novaTarefa.nome);
  getchar(); // É usado para limpar o buffer após a leitura

  // Verificar se já existe tarefa como aquele nome
  for (int i = 0; i < numTarefas; i++) {
    if (strcmp(listaTarefas[i].nome, novaTarefa.nome) == 0) {
      printf("\n       ❌❌Já existe uma tarefa com esse nome❌❌\n\n");
      p = i;
      ligacaoAdEd(p);
      return;
    }
  }
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
    strcpy(novaTarefa.status, "Em Progresso...");

    printf("\n       😄Tarefa criada com sucesso!!😄\n");
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
  printf("--------------------------------------------\n");
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
  printf("\n--------------------------------------------\n");
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

void decidirRemover() {
  int flag = 0;
  puts("\nDeseja continua? apos excluir não é possivel recuperar!");
  puts("(1) Sim");
  puts("(2) Não");
  scanf("%d", &flag);
  getchar();
  if (flag == 1) {
    removerTarefa();
  }
}

// Vai passa por toda a lista de tarefas ate encontra a primera tarefa vazia
void quantasTarefas(int *c) {
  int cont = 0;
  for (int i = 0; i < numTarefas; i++) {
    if (listaTarefas[i].nome[0] != '\0') {
      cont++;
    }
  }
  *c = cont; // Por meio de um ponteiro vai modificar o valor para imprimir na
             // main
}

void nomeTodasT() {
  // Pecorrer o array de listaTarefas dando print apenas no nome da estrutura
  printf("\n--------------------------------------------\n");
  for (int i = 0; i < numTarefas; i++) {
    printf("%d - %s\n", i + 1, listaTarefas[i].nome);
  }
  printf("--------------------------------------------\n");
}

int comparar(const void *a, const void *b) {
  // Essa função define como o qsort vai ordena o array
  struct tarefa *tarefaA = (struct tarefa *)a;
  struct tarefa *tarefaB = (struct tarefa *)b;
  return strcmp(tarefaA->nome, tarefaB->nome);
}

void ordena() {
  // chamando a função e passandos os parametros necessarios para ordena o array
  qsort(listaTarefas, numTarefas, sizeof(struct tarefa), comparar);
  printf("\n--------------------------------------------\n");
  puts("Lista de tarefas pos ordenação: ");
  for (int i = 0; i < numTarefas; i++) {
    printf("%d - %s\n", i + 1, listaTarefas[i].nome);
  }
  printf("\n--------------------------------------------\n");
}

int main(void) {
  int x, y;
  int flag;
  printf("\n\nBem vindo ao seu gerenciamento de tarefas 📄\n");
  do {
    puts("\nGostaria de:");
    puts("(1) Adicionar ➕");
    puts("(2) Mudar Status ✅");
    puts("(3) Buscar 🔎");
    puts("(4) Editar 🔩");
    puts("(5) Remover ❌");
    puts("(6) Nome de todas as tarefas 📚");
    puts("(7) Quantidade de tarefas atualmente 🗂");
    puts("(8) Ordena lista de tarefas por nome 🔀");
    puts("(0) sair");
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
      achaNome();
      break;

    case 5:
      decidirRemover();
      break;

    case 6:
      nomeTodasT();
      break;

    case 7:
      quantasTarefas(&y);
      printf("\n       😄Atualmente tem %d tarefas!😄 ", y);
      printf("\n--------------------------------------------\n");
      break;

    case 8:
      puts("\nDeseja continua? apos a ordenação não é possivel retorna!");
      puts("(1) Sim");
      puts("(2) Não");
      scanf("%d", &flag);
      getchar();
      if (flag == 1) {
        ordena();
      }
      break;

    default:
      printf("\n❌❌Errouuu❌❌\n");
    }
  } while (x != 0);
  printf("Até mais...");
  return 0;
}