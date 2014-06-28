/*
 * Trabalho final de ED1
 * Autor: Guilherme Henrique Costa 131151291
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

// constantes
const char *SENHA_FACIL = "12345";
const char *BANCO = "Satander";

// structs
// Struct Conta Corrente
typedef struct {
  int numCC;              // 1 a 999
  char nome[41];          //
  char senha[7];          // xxxxx
  char cpf[13];           // xxxxxxxxx-xx
  char rg[11];            // xxxxxxxx-x
  char dataNasc[11];      // dd/mm/aaaa
  char dataAbertura[11];  // dd/mm/aaaa
  float depInicial;       //
  char tipoConta;         // C ou E
  float saldoAtual;       //
  char dataUltMov[11];    // dd/mm/aaaa
  char tipoUltMoc;        // D ou C
  float valorUltMov;      //
} regConta;

typedef struct No {
  regConta conta;
  int bal;
  struct No *pai;
  struct No *dir;
  struct No *esq;
} tNo;

// prototypes

regConta *leConta();
tNo *obtemConta(tNo *t, int numCC);
int proximaConta(tNo *arvContas);
void incluiConta(tNo **arvContas);
void alteraConta(int numCC, tNo **arvContas);
void depositoConta(int numCC, tNo *arvContas, float valor);
bool saqueConta(int numCC, tNo *arvContas, float valor);
float saldoAtualConta(int numCC, tNo *arvContas);
void consultaUltimaMovimentacao(int numCC, tNo *arvContas);
bool transfereValor(int numCCorig, int numCCdest, tNo *arvContas, float valor);
void excluiConta(int numCC, tNo **arvContas);

void printHead();
void printFooter();
void agora(char ret[11]);

bool validaCPF(char cpf[13]);
bool validaRG(char rg[11]);
bool validaData(char data[11]);
bool validaSenha(char senha[7]);
bool validaNumCC(int numCC);
bool validaNome(char nome[41]);
bool validaValor(float valor);

bool arvore_vazia(tNo *t);
int alturaAvl(tNo *no);
tNo *rotacaoLL(tNo *p);
tNo *rotacaoRR(tNo *p);
void inserir(tNo **pRaiz, tNo **PAI, regConta *info);
void Output(tNo *Arvore, int Nivel);

char now[11];

int main(int argc, const char * argv[]) {

  tNo *arvConta = NULL;
  int numConta = 0, numContaAux = 0, numContaDestTransf = 0, op = -1;
  char senhaConta[6];
  float valor;
  tNo *noAux, *noAuxDestTransf;
  regConta contaAux;
  while (numConta != -1) {
    system("cls");
    printHead();
    printf("Conta Corrente: ");
    scanf("%d", &numConta);
    fflush(stdin);
    switch (numConta) {
      case -1:
        printf("exit");
        break;

      case 0:
        printf("Senha (6 digitos): ");
        scanf("%[^\r\n]s", &senhaConta);
        fflush(stdin);
        if (!strcmp(senhaConta, SENHA_FACIL)) {
          op = -1;
          while (op != 0) {
            system("cls");
            printHead();
            printf("Bem-vindo funcionario!\n\n");
            printf("Escolha uma opcao:\n");
            printf("\t1) cadastrar uma conta corrente\n");
            printf("\t2) excluir uma conta corrente\n");
            printf("\t3) alterar os dados da conta corrente\n");
            printf("\t4) consultar dados da conta corrente\n");
            printf("\t5) realizar deposito em conta corrente\n");
            printf("\t6) efetivar saque em conta corrente\n");
            printf("\t7) consultar saldos\n");
            printf("\t8) realizar a transferencia entre contas correntes\n");
            printf("\t9) consultar os dados da ultima movimentacao\n");
            printf("\t0) sair\n");
            scanf("%d", &op);
            fflush(stdin);

            switch (op) {
              case 0:
                system("cls");
                printHead();
                printf("\t\t\t..::LOGOUT REALIZADO COM SUCESSO::..\n");
                printFooter();
                getch();
                break;

              case 1:
                incluiConta(&arvConta);
                getch();
                break;

              case 2:
                system("cls");
                printHead();
                printf("\t\t\t..::EXCLUIR CONTA::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                if (obtemConta(arvConta, numContaAux) != NULL) {
                  excluiConta(numContaAux, &arvConta);
                  system("cls");
                  printHead();
                  printf("\t\t\t..::CONTA CORRENTE EXCLUIDA COM SUCESSO::..\n");
                  printFooter();
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL EXCLUIR A CONTA::..\n");
                  printFooter();
                }
                getch();
                break;
              case 3:
                system("cls");
                printHead();
                printf("\t\t\t..::ALTERAR DADOS DE CONTA::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                if (obtemConta(arvConta, numContaAux) != NULL) {
                  alteraConta(numContaAux, &arvConta);
                  system("cls");
                  printHead();
                  printf("\t\t\t..::CONTA CORRENTE ALTERAR COM SUCESSO::..\n");
                  printFooter();
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL ALTERAR A CONTA::..\n");
                  printFooter();
                }
                getch();
                break;
              case 4:
                system("cls");
                printHead();
                printf("\t\t\t..::CONSULTAR DADOS DE CONTA::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                noAux = obtemConta(arvConta, numContaAux);
                if (noAux != NULL) {
                  contaAux = noAux->conta;

                  system("cls");
                  printHead();
                  printf("Conta Corrente: %d - Tipo: %s\n",contaAux.numCC, contaAux.tipoConta=='C' ? "Comum" : "Especial");
                  printf("Data atual: %s\n", now);
                  printf("Nome do cliente: %s\n", contaAux.nome);
                  printf("CPF: %s \t\t RG: %s\n", contaAux.cpf, contaAux.rg);
                  printf("--------------------------------------------------------------------------------\n");
                  //printf("Saldo anterior: R$ %.2f\n", contaAux.tipoUltMoc=='C' ? contaAux.saldoAtual-contaAux.valorUltMov : contaAux.saldoAtual+contaAux.valorUltMov);
                  //printf("--------------------------------------------------------------------------------\n");
                  //printf("Data Ult. Mov\t\t\tTipo OperaÁ„o\t\t\tValor Movim.\n");
                  //printf("%s\t\t\t\t%s\t\t\t\t\tR$ %.2f\n",contaAux.dataUltMov, contaAux.tipoUltMoc == 'C' ? "Credito" : "Debito", contaAux.valorUltMov);
                  //printf("--------------------------------------------------------------------------------\n");
                  printf("Saldo atual: R$ %.2f\n", contaAux.saldoAtual);
                  printFooter();
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL CONSULTAR CONTA::..\n");
                  printFooter();
                }
                getch();
                break;

              case 5:
                system("cls");
                printHead();
                printf("\t\t\t..::DEPOSITO EM CONTA::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                printf("Digite o valor do deposito:\n");
                scanf("%f", &valor);
                noAux = obtemConta(arvConta, numContaAux);
                if (noAux != NULL && validaValor(valor)) {
                  depositoConta(numContaAux, arvConta, valor);
                  system("cls");
                  printHead();
                  printf("\t\t\t..::DEPOSITO REALIZADO COM SUCESSO::..\n");
                  printFooter();
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR O DEPOSITO::..\n");
                  printFooter();
                }
                getch();
                break;
              case 6:
                system("cls");
                printHead();
                printf("\t\t\t..::SAQUE EM CONTA::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                printf("Digite o valor do saque:\n");
                scanf("%f", &valor);
                noAux = obtemConta(arvConta, numContaAux);
                if (noAux != NULL && validaValor(valor)) {
                  if (saqueConta(numContaAux, arvConta, valor)) {
                    system("cls");
                    printHead();
                    printf("\t\t\t..::SAQUE REALIZADO COM SUCESSO::..\n");
                    printFooter();
                  } else {
                    system("cls");
                    printHead();
                    printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR O SAQUE::..\n");
                    printFooter();
                  }
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR O SAQUE::..\n");
                  printFooter();
                }
                getch();
                break;

              case 7:
                system("cls");
                printHead();
                printf("\t\t\t..::SALDO ATUAL DA CONTA::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                noAux = obtemConta(arvConta, numContaAux);
                if (noAux != NULL) {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::SALDO ATUAL DA CONTA::..\n");
                  printf("Saldo atual: R$ %.2f\n", saldoAtualConta(numContaAux, arvConta));
                  printFooter();
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL CONSULTAR CONTA::..\n");
                  printFooter();
                }
                getch();
                break;

              case 8:
                system("cls");
                printHead();
                printf("\t\t\t..::TRANSFERENCIA ENTRE CONTAS::..\n");
                printf("Digite o numero da conta de origem:\n");
                scanf("%d", &numContaAux);
                printf("Digite o valor da transferencia:\n");
                scanf("%f", &valor);
                printf("Digite o numero da conta de destino:\n");
                scanf("%d", &numContaDestTransf);
                noAux = obtemConta(arvConta, numContaAux);
                noAuxDestTransf = obtemConta(arvConta, numContaDestTransf);
                if (noAux != NULL && noAuxDestTransf != NULL && validaValor(valor)) {
                  if (saqueConta(numContaAux, arvConta, valor)) {
                    depositoConta(numContaDestTransf, arvConta, valor);
                    system("cls");
                    printHead();
                    printf("\t\t\t..::TRANSFERENCIA REALIZADA COM SUCESSO::..\n");
                    printFooter();
                  } else {
                    system("cls");
                    printHead();
                    printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR A TRANSFERENCIA::..\n");
                    printFooter();
                  }
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR A TRANSFERENCIA::..\n");
                  printFooter();
                }
                getch();
                break;

              case 9:
                system("cls");
                printHead();
                printf("\t\t\t..::CONSULTAR DADOS DA ULTIMA MOVIMENTACAO::..\n");
                printf("Digite o numero da conta:\n");
                scanf("%d", &numContaAux);
                noAux = obtemConta(arvConta, numContaAux);
                if (noAux != NULL) {
                  consultaUltimaMovimentacao(numContaAux, arvConta);
                } else {
                  system("cls");
                  printHead();
                  printf("\t\t\t..::NAO FOI POSSIVEL CONSULTAR CONTA::..\n");
                  printFooter();
                }
                getch();
                break;
              default:
                printf("Opcao invalida!");
                getch();
                break;
            }
          }
        } else {
          printf("Senha invalida!");
          getch();
        };
        break;

      case 1 ... 999:
        printf("Senha (6 digitos): ");
        scanf("%[^\r\n]s", &senhaConta);
        fflush(stdin);
        if (arvConta) {
          noAux = obtemConta(arvConta, numConta);
          contaAux = noAux->conta;
          if (!strcmp(senhaConta, contaAux.senha)) {
            op = -1;
            while (op != 0) {
              system("cls");
              printf("\t5) realizar deposito em conta corrente\n");
              printf("\t6) efetivar saque em conta corrente\n");
              printf("\t7) consultar saldos\n");
              printf("\t8) realizar a transferencia entre contas correntes\n");
              printf("\t9) consultar os dados da ultima movimentacao\n");
              printf("\t0) sair\n");
              scanf("%d", &op);
              fflush(stdin);

              switch (op) {
                case 0:
                  system("cls");
                  printHead();
                  printf("\t\t\t..::LOGOUT REALIZADO COM SUCESSO::..\n");
                  printFooter();
                  getch();
                  break;
                case 5:
                  system("cls");
                  printHead();
                  printf("\t\t\t..::DEPOSITO EM CONTA::..\n");
                  printf("Digite o numero da conta:\n");
                  scanf("%d", &numContaAux);
                  printf("Digite o valor do deposito:\n");
                  scanf("%f", &valor);
                  noAux = obtemConta(arvConta, numContaAux);
                  if (noAux != NULL && validaValor(valor)) {
                    depositoConta(numContaAux, arvConta, valor);
                    system("cls");
                    printHead();
                    printf("\t\t\t..::DEPOSITO REALIZADO COM SUCESSO::..\n");
                    printFooter();
                  } else {
                    system("cls");
                    printHead();
                    printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR O DEPOSITO::..\n");
                    printFooter();
                  }
                  getch();
                  break;
                case 6:
                  system("cls");
                  printHead();
                  printf("\t\t\t..::SAQUE EM CONTA::..\n");
                  printf("Conta Atual: %d\n", contaAux.numCC);
                  printf("Digite o valor do saque:\n");
                  scanf("%f", &valor);
                  if (validaValor(valor)) {
                    if (saqueConta(contaAux.numCC, arvConta, valor)) {
                      system("cls");
                      printHead();
                      printf("\t\t\t..::SAQUE REALIZADO COM SUCESSO::..\n");
                      printFooter();
                    } else {
                      system("cls");
                      printHead();
                      printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR O SAQUE::..\n");
                      printFooter();
                    }
                  } else {
                    system("cls");
                    printHead();
                    printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR O SAQUE::..\n");
                    printFooter();
                  }
                  getch();
                  break;
                case 7:
                  system("cls");
                  printHead();
                  printf("\t\t\t..::SALDO ATUAL DA CONTA::..\n");
                  printf("Saldo atual: R$ %.2f\n", saldoAtualConta(contaAux.numCC, arvConta));
                  printFooter();
                  getch();
                  break;
                case 8:
                  system("cls");
                  printHead();
                  printf("\t\t\t..::TRANSFERENCIA ENTRE CONTAS::..\n");
                  printf("Digite o valor da transferencia:\n");
                  scanf("%f", &valor);
                  printf("Digite o numero da conta de destino:\n");
                  scanf("%d", &numContaDestTransf);
                  noAuxDestTransf = obtemConta(arvConta, numContaDestTransf);
                  if (noAuxDestTransf != NULL && validaValor(valor)) {
                    if (saqueConta(contaAux.numCC, arvConta, valor)) {
                      depositoConta(numContaDestTransf, arvConta, valor);
                      system("cls");
                      printHead();
                      printf("\t\t\t..::TRANSFERENCIA REALIZADA COM SUCESSO::..\n");
                      printFooter();
                    } else {
                      system("cls");
                      printHead();
                      printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR A TRANSFERENCIA::..\n");
                      printFooter();
                    }
                  } else {
                    system("cls");
                    printHead();
                    printf("\t\t\t..::NAO FOI POSSIVEL REALIZAR A TRANSFERENCIA::..\n");
                    printFooter();
                  }
                  getch();
                  break;
                case 9:
                  consultaUltimaMovimentacao(contaAux.numCC, arvConta);
                  getch();
                  break;
                default:
                  printf("Opcao invalida!");
                  getch();
                  break;
              }
            }
          } else {
            system("cls");
            printHead();
            printf("\t\t\t..::SENHA INVALIDA::..\n");
            printFooter();
            getch();
          }
        } else {
          system("cls");
          printHead();
          printf("\t\t\t..::AINDA NAO EXISTEM CONTAS NO SISTEMA::..\n");
          printFooter();
          getch();
        }
        break;
      case 1000:
        printf("\n\nArvore:\n");
        Output(arvConta, 1);
        printf("\n\n");
        getch();
        break;
      default:
        printf("Opcao invalida!");
        void printFooter();
        getch();
        break;
    }
  }
  return 0;
}

void printHead() {
  printf("\t\t\t\t\tBanco %s\n", BANCO);
  printf("Rua 24, 430 - Bela Vista - CEP: 13506-770 - Rio Claro, SP\n");
  printf("--------------------------------------------------------------------------------\n");
}

void printFooter() {
  printf("--------------------------------------------------------------------------------\n");
}

/* Retorna string com a data de agora no formato dd/mm/yyyy */
void agora(char ret[11]) {
  char buffer[11];
  int n;
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  n = sprintf(buffer, "%02d/%02d/%04d", t->tm_mday, t->tm_mon+1, t->tm_year+1900);
  strcpy(ret, buffer);
}

/* Busca a CC passada por parametro e imprime a ultima movimentacao */
void consultaUltimaMovimentacao(int numCC, tNo *arvContas) {
  agora(now);

  tNo *noAux;
  regConta contaAux;

  noAux = obtemConta(arvContas, numCC);

  contaAux = noAux->conta;

  system("cls");
  printHead();
  printf("Conta Corrente: %d - Tipo: %s\n",contaAux.numCC, contaAux.tipoConta=='C' ? "Comum" : "Especial");
  printf("Data atual: %s\n", now);
  printf("Nome do cliente: %s\n", contaAux.nome);
  printf("CPF: %s \t\t RG: %s\n", contaAux.cpf, contaAux.rg);
  printf("--------------------------------------------------------------------------------\n");
  printf("Saldo anterior: R$ %.2f\n", contaAux.tipoUltMoc=='C' ? contaAux.saldoAtual-contaAux.valorUltMov : contaAux.saldoAtual+contaAux.valorUltMov);
  printf("--------------------------------------------------------------------------------\n");
  printf("Data Ult. Mov\t\t\tTipo Operacao\t\t\tValor Movim.\n");
  printf("%s\t\t%s\t\t\t\t\tR$ %.2f\n",contaAux.dataUltMov, contaAux.tipoUltMoc == 'C' ? "Credito" : "Debito", contaAux.valorUltMov);
  printf("--------------------------------------------------------------------------------\n");
  printf("Saldo atual: R$ %.2f\n", contaAux.saldoAtual);
  printFooter();
}

/* Busca o proximo numero de conta corrente disponivel */
int proximaConta(tNo *arvContas) {
  tNo *achou;
  for (int i=1; i<1000; i++) {
    achou = obtemConta(arvContas, i);
    if (arvore_vazia(achou)) {
      return i;
    }
  }
  return -1;
}

/* Cadastra nova conta corrente */
void incluiConta(tNo **arvContas) {
  system("cls");
  printHead();
  printf("\t\t\t..::CADASTRAR NOVA CONTA CORRENTE::..\n");

  int proxCC = proximaConta(*arvContas);
  if (proxCC != -1) {
    printf("Proximo numero de Conta Corrente disponivel: %d\n", proxCC);

    regConta *novaConta = leConta();
    tNo *aux = NULL;
    if (obtemConta(*arvContas, novaConta->numCC) != NULL) {
      system("cls");
      printHead();
      printf("\t\t\t..::NAO FOI POSIVEL CRIAR A NOVA CONTA::..\n");
      printFooter();
    } else {
      inserir(arvContas, &aux, novaConta);
      system("cls");
      printHead();
      printf("\t\t\t..::NOVA CONTA CORRENTE CADASTRADA COM SUCESSO::..\n");
      printFooter();
    }
  } else {
    printf("Nao existem mais numeros disponiveis!\n\n\n");
    printFooter();
  }
}

/* Le as dados da nova conta corrente e armazena na struct.
   Retorna um ponteiro para a struct criada */
regConta *leConta() {

  regConta *aux = (regConta *) malloc(sizeof(regConta));

  while (!validaNumCC(aux->numCC)) {
    printf("Digite o numero da conta: ");
    scanf("%d", &aux->numCC);
    fflush(stdin);
    if (!validaNumCC(aux->numCC)) {
      printf("Numero invalido!\n");
    }
  }

  while (!validaNome(aux->nome)) {
    printf("Digite o nome do cliente: ");
    scanf("%[^\r\n]s", &aux->nome);
    fflush(stdin);
    if (!validaNome(aux->nome)) {
      printf("Nome invalido!\n");
    }
  }

  while (!validaSenha(aux->senha)) {
    printf("Digite a senha do cliente (6 digitos): ");
    scanf("%[^\r\n]s", &aux->senha);
    fflush(stdin);
    if (!validaSenha(aux->senha)) {
      printf("Senha invalida!\n");
    }
  }

  while (!validaCPF(aux->cpf)) {
    printf("Digite o CPF do cliente (XXXXXXXXX-XX): ");
    scanf("%[^\r\n]s", &aux->cpf);
    fflush(stdin);
    if (!validaCPF(aux->cpf)) {
      printf("CPF invalido!\n");
    }
  }

  while (!validaRG(aux->rg)) {
    printf("Digite o RG do cliente (XXXXXXXX-X): ");
    scanf("%[^\r\n]s", &aux->rg);
    fflush(stdin);
    if (!validaRG(aux->rg)) {
      printf("RG invalido!\n");
    }
  }

  while (!validaData(aux->dataNasc)) {
    printf("Digite a data de nascimento do cliente (DD/MM/AAAA): ");
    scanf("%[^\r\n]s", &aux->dataNasc);
    fflush(stdin);
    if (!validaData(aux->dataNasc)) {
      printf("Data invalida!\n");
    }
  }

  agora(now);
  printf("Data de abertura da conta: %s\n", now);
  strcpy(aux->dataAbertura, now);

  aux->depInicial = 0;
  while (!validaValor(aux->depInicial)) {
    printf("Digite o valor do deposito inicial: ");
    scanf("%f", &aux->depInicial);
    fflush(stdin);
    if (!validaValor(aux->depInicial)) {
      printf("Valor invalido!\n");
    }
  }

  aux->tipoConta = aux->depInicial > 12000 ? 'E' : 'C';

  aux->saldoAtual = aux->depInicial;
  strcpy(aux->dataUltMov, now);
  aux->tipoUltMoc = 'C';
  aux->valorUltMov = aux->depInicial;

  return aux;
}


/* Insere Struct Conta Corrente na arvore e
   faz as rotacoes para balancea-la caso necessario */
void inserir(tNo **pRaiz, tNo **PAI, regConta *info) {
  if (*pRaiz == NULL) {
    *pRaiz = (tNo *) malloc(sizeof(tNo));
    (*pRaiz)->esq = NULL;
    (*pRaiz)->dir = NULL;
    (*pRaiz)->conta = *info;
    (*pRaiz)->pai = (*PAI);
    (*pRaiz)->bal = 0;
  } else {
    if (info->numCC < (*pRaiz)->conta.numCC) {
      inserir(&(*pRaiz)->esq,& (*pRaiz), info);
      (*pRaiz)->bal = alturaAvl((*pRaiz)->esq) - alturaAvl((*pRaiz)->dir);
      if ((*pRaiz)->bal == 2)  {
        if ((*pRaiz)->esq->bal==1)
          (*pRaiz) = rotacaoLL((*pRaiz));
        else if ((*pRaiz)->esq->bal == -1) {
          (*pRaiz)->esq = rotacaoRR((*pRaiz)->esq);
          (*pRaiz) = rotacaoLL((*pRaiz));
        }
      }
    } else {
      if (info->numCC > (*pRaiz)->conta.numCC) {
        inserir(& (*pRaiz)->dir,& (*pRaiz), info);
        (*pRaiz)->bal=alturaAvl ((*pRaiz)->esq) - alturaAvl ((*pRaiz)->dir);
        if ((*pRaiz)->bal==-2) {
          if ( (*pRaiz)->dir->bal==-1)
            (*pRaiz)= rotacaoRR ((*pRaiz));
          else if ( (*pRaiz)->dir->bal==1) {
            (*pRaiz)->dir=rotacaoLL ((*pRaiz)->dir);
            (*pRaiz)= rotacaoRR ((*pRaiz));
          }
        }
      }
    }
  }
}

/* Remove Conta Corrente da arvore e
   faz as rotacoes para balancea-la caso necessario */
void excluiConta(int numCC, tNo **arvContas) {
  regConta aux;
  tNo *P;
  /* se o elemento nao esta na arvore sai da funçao*/
  if (*arvContas == NULL) return;
  if (numCC<(*arvContas)->conta.numCC) {
    /* se remove da esquerda é como inserir na direita para balancear */
    excluiConta (numCC, &((*arvContas)->esq));
    (*arvContas)->bal = alturaAvl((*arvContas)->esq) - alturaAvl((*arvContas)->dir);
    if ((*arvContas)->bal == -2) {
      if ((*arvContas)->dir->bal != 1) {
        (*arvContas) = rotacaoRR((*arvContas));
      } else if ((*arvContas)->dir->bal == 1) {
        (*arvContas)->dir = rotacaoLL((*arvContas)->dir);
        (*arvContas) = rotacaoRR((*arvContas));
      }
    }
  } else {
    if (numCC > (*arvContas)->conta.numCC) {
      excluiConta(numCC, &((*arvContas)->dir));
      (*arvContas)->bal = alturaAvl((*arvContas)->esq) - alturaAvl((*arvContas)->dir);
      if ((*arvContas)->bal == 2) {
        if ((*arvContas)->esq->bal != -1) {
          (*arvContas) = rotacaoLL((*arvContas));
        } else if ((*arvContas)->esq->bal == -1) {
          (*arvContas)->esq = rotacaoRR((*arvContas)->esq);
          (*arvContas) = rotacaoLL((*arvContas));
        }
      }
    } else {
      if (numCC == (*arvContas)->conta.numCC) {
        if (((*arvContas)->esq == NULL) && ((*arvContas)->dir == NULL)) {
          free(*arvContas);
          *arvContas = NULL;
        } else {
          if (((*arvContas)->esq == NULL && (*arvContas)->dir != NULL) || (*arvContas)->bal == -1) {
            P = (*arvContas)->dir;
            while (P->esq != NULL)
              P = P->esq;
            aux = P->conta;
            excluiConta(P->conta.numCC, &((*arvContas)));
            (*arvContas)->conta = aux;
          } else {
            P = (*arvContas)->esq;
            while (P->dir != NULL)
              P = P->dir;
            aux = P->conta;
            excluiConta (P->conta.numCC, &((*arvContas)));
            (*arvContas)->conta = aux;
          }
        }
      }
    }
  }
}

/* Altera os Dados da Conta Corrente */
void alteraConta(int numCC, tNo **arvContas) {
  int op = 0;

  tNo *noAux;

  noAux = obtemConta(*arvContas, numCC);

  while (op != 5) {
    system("cls");
    printHead();
    printf("\t\t\t..::ALTERAR DADOS::..\n");
    printf("Informe a opção a ser alterada:\n");
    printf("1 - Nome: %s\n", noAux->conta.nome);
    printf("2 - Deposito inicial: R$ %.2f - Tipo da conta: %s\n", noAux->conta.depInicial, noAux->conta.tipoConta == 'C' ? "Comum" : "Especial");
    printf("3 - Senha: %s\n", noAux->conta.senha);
    printf("4 - Finalizar\n");
    scanf("%d", &op);
    fflush(stdin);
    switch (op) {
      case 1:
        strcpy(noAux->conta.nome, "");
        //noAux->conta.nome = "";
        while (!validaNome(noAux->conta.nome)) {
          printf("Digite o novo valor para o campo NOME:\n");
          scanf("%[^\r\n]s", &noAux->conta.nome);
          fflush(stdin);
          if (!validaNome(noAux->conta.nome)) {
            printf("Nome invalido!\n");
          }
        }

        printf("\nDado alterado com sucesso!");
        getch();
        break;
      case 2:
        noAux->conta.depInicial = 0;
        while (!validaValor(noAux->conta.depInicial)) {
          printf("Digite o novo valor do deposito inicial: ");
          scanf("%f", &noAux->conta.depInicial);
          fflush(stdin);
          if (!validaValor(noAux->conta.depInicial)) {
            printf("Valor invalido!\n");
          }
        }

        noAux->conta.tipoConta = noAux->conta.depInicial>12000 ? 'E' : 'C';
        printf("\nDado alterado com sucesso!");
        getch();
        break;
      case 4:
        strcpy(noAux->conta.senha, "");
        //noAux->conta.senha = NULL;
        while (!validaSenha(noAux->conta.senha)) {
          printf("Digite a nova senha (6 digitos): ");
          scanf("%[^\r\n]s", &noAux->conta.senha);
          fflush(stdin);
          if (!validaSenha(noAux->conta.senha)) {
            printf("Senha invalida!\n");
          }
        }

        printf("\nDado alterado com sucesso!");
        getch();
        break;
      case 5:
        return;
        break;
      default:
        printf("Opcao invalida!");
        getch();
        break;
    }
  }
}

void depositoConta(int numCC, tNo *arvContas, float valor) {
  agora(now);

  tNo *noAux;

  noAux = obtemConta(arvContas, numCC);

  noAux->conta.saldoAtual += valor;
  noAux->conta.tipoUltMoc = 'C';
  noAux->conta.valorUltMov = valor;
  strcpy(noAux->conta.dataUltMov, now);
}

/**
 * Realiza saque do valor passado na conta corrente.
 * Retorna Falso caso nao seja possivel realizar o saque. 
 */
bool saqueConta(int numCC, tNo *arvContas, float valor) {
  agora(now);

  tNo *noAux;

  noAux = obtemConta(arvContas, numCC);

  if (noAux->conta.tipoConta == 'E') {
    if (valor > (noAux->conta.saldoAtual + 1500)) {
      return false;
    }
  } else if (valor > noAux->conta.saldoAtual) {
    return false;
  }

  noAux->conta.saldoAtual -= valor;
  noAux->conta.tipoUltMoc = 'D';
  noAux->conta.valorUltMov = valor;
  strcpy(noAux->conta.dataUltMov, now);
  return true;
}

/**
 * Obtém o saldo da cc informada
 */
float saldoAtualConta(int numCC, tNo *arvContas) {
  tNo *noAux;

  noAux = obtemConta(arvContas, numCC);
  return noAux->conta.saldoAtual;
}

/**
 * Desobre se a árvore está vazia
 */
bool arvore_vazia(tNo *t) {
  return (t == NULL);
}

/**
 * Obtém altura da árvore
 */
int alturaAvl(tNo *no) {
  int esq, dir;
  if (no == NULL) return -1;
  esq = alturaAvl(no->esq);
  dir = alturaAvl(no->dir);
  return esq > dir ? esq+1 : dir+1;
}

/**
 * Rotação simples para a esquerda
 */
tNo *rotacaoLL(tNo *p) {
  tNo *q;
  q = p->esq;
  //----------------> Realiza a rotação
  p->esq = q->dir;
  if (q->dir != NULL)
    q->dir->pai = p;
  q->dir = p;
  q->pai = p->pai;
  if (p->pai != NULL) {
    if (p->pai->esq == p)
      p->pai->esq = q;
    else
      p->pai->dir = q;
  }
  p->pai = q;
  //----------------> Rebalanceia
  q->bal = alturaAvl (q->esq) - alturaAvl (q->dir);
  p->bal = alturaAvl (p->esq) - alturaAvl (p->dir);
  return q;
}

/**
 * Rotação simples para a direita.
 */
tNo *rotacaoRR(tNo *p) {
  tNo *q;
  q = p->dir;
  //----------------> Realiza a rotacao
  p->dir = q->esq;
  if (q->esq != NULL)
    q->esq->pai = p;
  q->esq = p;
  q->pai = p->pai;
  if (p->pai != NULL) {
    if (p->pai->esq == p)
      p->pai->esq = q;
    else
      p->pai->dir = q;
  }
  p->pai = q;
  //----------------> Rebalanceia
  q->bal = alturaAvl(q->esq) - alturaAvl(q->dir);
  p->bal = alturaAvl(p->esq) - alturaAvl(p->dir);
  return q;
}

/**
 * Imprime a árvore
 */
void Output(tNo *Arvore, int Nivel) {
  if (Arvore) {
    Output(Arvore->dir, Nivel + 1);
    printf("\n");
    for (int i = 0; i < Nivel; i++)
      printf("      ");
    printf("(%d)%d", Arvore->bal, Arvore->conta.numCC);
    Output(Arvore->esq, Nivel + 1);
  }
}

/* Busca a Conta Corrente pelo numero e retorna o no ou NULL se nao encontrar. */
tNo *obtemConta(tNo *t, int numConta) {
  tNo *achou;
  tNo *aux = NULL;
  if (arvore_vazia(t)) return aux;
  if (t->conta.numCC == numConta) return t;
  achou = obtemConta(t->esq, numConta);
  if (arvore_vazia(achou))
    achou = obtemConta(t->dir, numConta);
  return achou;
}

/**
 * Validações dos dados da conta
 */

bool validaCPF(char cpf[13]) {
  return (strlen(cpf) == 12 && strcspn(cpf, "-") == 9) ? true : false;
}

bool validaRG(char rg[11]) {
  return (strlen(rg) == 10 && strcspn(rg, "-") == 8) ? true : false;
}

bool validaData(char data[11]) {
  return (strlen(data) == 10 && data[2] == '/' && data[5] == '/') ? true : false;
}

bool validaSenha(char senha[7]) {
  return strlen(senha) == 6 ? true : false;
}

bool validaNumCC(int numCC) {
  return (numCC >= 1 && numCC <= 999) ? true : false;
}

bool validaNome(char nome[41]) {
  return strlen(nome) >= 8 ? true : false;
}

bool validaValor(float valor) {
  return valor > 0 ? true : false;
}
