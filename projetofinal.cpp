/* Este programa constrói e mostra uma árvore balanceada (AVL) a partir de uma seqüência de dados de entrada. Ele também realiza buscas na árvore criada e elimina nós da árvore */
/* Autor: Marcus Vinicius Maltempi */
#include <stdlib.h> 
#include <stdio.h> 
#include <cstring> //Utilizado para strcopy
#include <time.h> //Funcoes de data

#define V 1 
#define F 0 
enum balanco {
	menor=-1, igual, maior
}
;
struct no {
	struct regCCorrente *cCorrente;
	struct no *esq;
	struct no *dir;
	enum balanco bal;
}
;


struct regCCorrente {
int nrCCorrente;
char nome[40];
char senha[6];
char cpf[12];
char rg[10];
char dtNascimento[10];
char dtAbertura[10];
float vlDepositoInicial;
char tpConta;
float vlSaldo;
char dtUltimaMovimentacao[10];
char tpMovimentacao;
float vlUltimaMovimentacao;
}
;



struct regCCorrente* leCCorrente();
struct regCCorrente *obtemCCorrente(struct no *atual, int numContaCorrente);
int proximaCCorrente(struct no *atual);
void incluiCCorrente(struct no **raiz);
void depositoCCorrente(int numContaCorrente, struct no *raiz, float valorDeposito);
int saqueCCorrente(int numContaCorrente, struct no *raiz, float valorSaque);
void saldoAtualCCorrente(int numContaCorrente, struct no *raiz);
void consultaUltimaMovimentacao(int numContaCorrente, struct no *raiz);
void transfereValor(int numContaCorrenteOrigem, int numContaCorrenteDestino, float valorTransferencia, struct no *raiz);

void excluiCCorrente(struct no **atual, int elem, int *h);

//Metodo auxiliar chamado por incluiCCorrente
void insereContaCorrente(struct no **atual, int elem, int *h);

//aux
int buscarProximaCCorrente(struct no *r);


void retira(struct no **atual, int elem, int *h);
void antecessor(struct no **aux, struct no **atual, int *h);
void balancoE(struct no **p, int *h);
void balancoD(struct no **p, int *h);

int logadoFuncionario = -1;


int main(void) {
 
 	char senha[6];
	int escolha, escolha2;	
	struct no *arvCCorrente;
	int h=V;
	arvCCorrente = NULL;
	
	//1 == logado como funcionario

	
	do
	{	
		printf("Informe o numero da conta corrente:\n\n");
		scanf("%d",&escolha);
		printf("Entre com sua senha:\n\n");	
		scanf("%s",&senha);
		//Funcionario
		if(escolha == 0)
		{
			if(strcmp(senha, "123456") == 0)
			{
				logadoFuncionario = 1;
			}
			else
			{
				printf("Senha invalida!:\n\n");	
			}
		}
		else
		{
			struct regCCorrente *aux = 	obtemCCorrente(arvCCorrente, escolha);
			
			if(aux == NULL)
			{
			    printf("ContaCorrente nao encontrada:\n\n");		
			}
			else
			{
				if(strcmp(senha, aux->senha) == 0)
				{
					logadoFuncionario = 0;
				}
			}
		}
		
		if(logadoFuncionario != -1)
		{
		
			do
			{
			 printf("Menu\n\n");
			 printf("1. cadastrar uma conta corrente;\n");
			 printf("2. excluir uma conta corrente;\n");
			 printf("3. alterar os dados da conta corrente;\n");
			 printf("4. consultar dados da conta corrente;\n");
			 printf("5. realizar depósito em conta corrente;\n");
			 printf("6. efetivar saque em conta corrente;\n");
			 printf("7. consultar saldos;\n");
			 printf("8. realizar a transferência entre contas correntes;\n");     
			 printf("9. consultar os dados da última movimentação.\n");     
			 scanf("%d",&escolha2);
		   
			 switch (escolha2)
			 {
			     case 1: incluiCCorrente(&arvCCorrente);
			          break;
			     case 2: 
			          break;
			     case 3: 
			         break;
			     case 4: 
			         break;
			     case 5: 
			         break;
			     case 6: 
			         break;
			     case 7: 
			         break;			 			 			 	         
			     case 8: 
			         break;	
			     case 9: 
			         break;	
			     default: printf("Escolha uma entre as opcoes a cima!\n");
			     	 break;
			 } 
		  
			} while (escolha2 != -1);
	}
	
} while (escolha != -1);	
	

	return 0;
}
void insereContaCorrente(struct no **atual, struct regCCorrente *elem, int *h) {
	struct no *p1, *p2;
	if(*atual==NULL) {
		*atual = (struct no *) malloc(sizeof(struct no));
		if(!(*atual)) {
			printf("sem memória\n");
			exit(0);
		} else {
			/* cria o no  */
			*h = V;
			(*atual)->cCorrente = elem;
			(*atual)->esq = NULL;
			(*atual)->dir = NULL;
			(*atual)->bal = igual;
			return;
		}
	} else   
	/* escolhe a subarvore */
	if((*atual)->cCorrente->nrCCorrente > elem->nrCCorrente) {
		insereContaCorrente(&(*atual)->esq, elem, h);
		if(*h==V)   
		/* subarvore esquerda cresceu */
		switch((*atual)->bal) {
			case maior: 
			     (*atual)->bal = igual;
			*h = F;
			break;
			case igual: 
			     (*atual)->bal = menor;
			break;
			case menor:  
			/* rebalanceamento */
			p1 = (*atual)->esq;
			if(p1->bal == menor) {
				/* rotacao LL */
				(*atual)->esq = p1->dir;
				p1->dir = *atual;
				(*atual)->bal = igual;
				*atual = p1;
			} else {
				/* rotacao LR */
				p2 = p1->dir;
				p1->dir = p2->esq;
				p2->esq = p1;
				(*atual)->esq = p2->dir;
				p2->dir = *atual;
				if(p2->bal == menor) (*atual)->bal = maior; else (*atual)->bal = igual;
				if(p2->bal == maior) p1->bal = menor; else p1->bal = igual;
				*atual = p2;
			}
			(*atual)->bal = igual;
			*h = F;
		}
	} else 
	      if((*atual)->cCorrente->nrCCorrente < elem->nrCCorrente) {
		insereContaCorrente(&(*atual)->dir, elem, h);
		if(*h==V)   
		/* subarvore direita cresceu */
		switch((*atual)->bal) {
			case menor: 
			       (*atual)->bal = igual;
			*h = F;
			break;
			case igual: 
			       (*atual)->bal = maior;
			break;
			case maior:  
			/* rebalanceamento */
			p1 = (*atual)->dir;
			if(p1->bal == maior) {
				/* rotacao RR */
				(*atual)->dir = p1->esq;
				p1->esq = *atual;
				(*atual)->bal = igual;
				*atual = p1;
			} else {
				/* rotacao RL */
				p2 = p1->esq;
				p1->esq = p2->dir;
				p2->dir = p1;
				(*atual)->dir = p2->esq;
				p2->esq = *atual;
				if(p2->bal == maior) (*atual)->bal = menor; else (*atual)->bal = igual;
				if(p2->bal == menor) p1->bal = maior; else p1->bal = igual;
				*atual = p2;
			}
			(*atual)->bal = igual;
			*h = F;
		}
	}
}
struct regCCorrente *obtemCCorrente(struct no *atual, int numCCorrente) {
	if(atual==NULL || atual->cCorrente->nrCCorrente==numCCorrente) return atual->cCorrente; else 
	    if(numCCorrente<atual->cCorrente->nrCCorrente) return obtemCCorrente(atual->esq, numCCorrente); else return obtemCCorrente(atual->dir, numCCorrente);
}
void retira(struct no **atual, int elem, int *h) {
	struct no *aux;
	if(*atual==NULL) printf("Elemento nao esta na arvore!\n"); else 
	    if((*atual)->cCorrente->nrCCorrente > elem) {
		/* procura a esquerda */
		retira(&(*atual)->esq, elem, h);
		if(*h==V) balancoE(atual, h);
	} else 
	      if((*atual)->cCorrente->nrCCorrente < elem) {
		/* procura a direita */
		retira(&(*atual)->dir, elem, h);
		if(*h==V) balancoD(atual, h);
	} else {
		/* achou: deleta *atual */
		aux = *atual;
		if(aux->dir==NULL) {
			*atual=aux->esq;
			*h=V;
		} else 
		   if(aux->esq==NULL) {
			*atual=aux->dir;
			*h=V;
		} else {
			antecessor(&aux, &(*atual)->esq, h);
			if(*h==V) balancoE(atual, h);
		}
		free(aux);
	}
}
void antecessor(struct no **aux, struct no **atual, int *h) {
	if((*atual)->dir!=NULL) {
		antecessor(aux, &(*atual)->dir, h);
		if(*h==V) balancoD(atual, h);
	} else {
		(*aux)->cCorrente->nrCCorrente = (*atual)->cCorrente->nrCCorrente;
		*aux = *atual;
		*atual = (*atual)->esq;
		*h = V;
	}
}
void balancoE(struct no **p, int *h) {
	struct no *p1, *p2;
	enum balanco b1, b2;
	/* subarvore esquerda diminuiu */
	switch((*p)->bal) {
		case menor: 
		      (*p)->bal = igual;
		break;
		case igual: 
		      (*p)->bal = maior;
		*h = F;
		break;
		case maior: 
		/*rearranjo */
		p1 = (*p)->dir;
		b1 = p1->bal;
		if(b1 >= igual) {
			/* rotacao RR simples */
			(*p)->dir = p1->esq;
			p1->esq = *p;
			if(b1 == igual) {
				(*p)->bal = maior;
				p1->bal = menor;
				*h = F;
			} else {
				(*p)->bal = igual;
				p1->bal = igual;
			}
			*p = p1;
		} else {
			/* rotacao RL dupla */
			p2 = p1->esq;
			b2 = p2->bal;
			p1->esq = p2->dir;
			p2->dir = p1;
			(*p)->dir = p2->esq;
			p2->esq = *p;
			if(b2 == maior) (*p)->bal = menor; else (*p)->bal = igual;
			if(b2 == menor) p1->bal = maior; else p1->bal = igual;
			*p = p2;
			p2->bal = igual;
		}
	}
}
void balancoD(struct no **p, int *h) {
	struct no *p1, *p2;
	enum balanco b1, b2;
	/* subarvore direita diminuiu */
	switch((*p)->bal) {
		case maior: 
		      (*p)->bal = igual;
		break;
		case igual: 
		      (*p)->bal = menor;
		*h = F;
		break;
		case menor: 
		/*rearranjo */
		p1 = (*p)->esq;
		b1 = p1->bal;
		if(b1 <= igual) {
			/* rotacao LL simples */
			(*p)->esq = p1->dir;
			p1->dir = *p;
			if(b1 == igual) {
				(*p)->bal = menor;
				p1->bal = maior;
				*h = F;
			} else {
				(*p)->bal = igual;
				p1->bal = igual;
			}
			*p = p1;
		} else {
			/* rotacao LR dupla */
			p2 = p1->dir;
			b2 = p2->bal;
			p1->dir = p2->esq;
			p2->esq = p1;
			(*p)->esq = p2->dir;
			p2->dir = *p;
			if(b2 == menor) (*p)->bal = maior; else (*p)->bal = igual;
			if(b2 == maior) p1->bal = menor; else p1->bal = igual;
			*p = p2;
			p2->bal = igual;
		}
	}
}



/////////////////////

struct regCCorrente* leCCorrente()
{
	struct regCCorrente* contaCorrente;
	char aux[41];	

	contaCorrente = (struct regCCorrente *) malloc(sizeof(struct regCCorrente));
	
	printf("CPF: ");
	scanf("%s",&aux);
	strcpy(contaCorrente->cpf, aux);	
	
	printf("rg: ");
	scanf("%s",&aux);
	strcpy(contaCorrente->rg, aux);	

	printf("nome: ");
	scanf("%s",&aux);
	strcpy(contaCorrente->nome, aux);
	
	printf("senha: ");
	scanf("%s",&aux);
	strcpy(contaCorrente->senha, aux);				
		
	printf("nascimento: ");
	scanf("%s",&aux);
	strcpy(contaCorrente->dtNascimento, aux);	
	
	printf("Deposito inicial: ");
	scanf("%f", &(contaCorrente->vlDepositoInicial));
	
	contaCorrente->vlSaldo = contaCorrente->vlDepositoInicial;
	
	contaCorrente->vlUltimaMovimentacao = contaCorrente->vlDepositoInicial;
	
	if(contaCorrente->vlDepositoInicial > 12000)
		contaCorrente->tpConta = 'E';
	else
		contaCorrente->tpConta = 'C';
		
	contaCorrente->tpMovimentacao = 'C';
	
	time_t now;
    time(&now);

    struct tm* now_tm;
    now_tm = localtime(&now);

    char out[11];
    strftime (out, 11, "%d-%m-%Y", now_tm);

	strcpy(contaCorrente->dtAbertura, out);	
	
	strcpy(contaCorrente->dtUltimaMovimentacao, contaCorrente->dtAbertura);	
		
	//contaCorrente->nrCCorrente;	
	
	return contaCorrente;

}

int proximaCCorrente(struct no *r)
{
	int retorno = buscarProximaCCorrente(r);
	
	if(retorno == 0)
	{
		retorno = 1;
	}
	else
	{
		retorno = retorno + 1;
	}
	
	if(retorno >= 999)
	{
		printf("Nao é possivel inserir mais contas!:\n\n");
		return -1;
	}
	
	return retorno;
}

int buscarProximaCCorrente(struct no *r)
{
	
	if(!r) return 0;
	
	int retorno = 0;
	
	int aux1, aux2;
	
	aux1 = buscarProximaCCorrente(r->dir);
	aux2 = buscarProximaCCorrente(r->esq);
	
	retorno = aux1;
	
	
	if(r->cCorrente->nrCCorrente > retorno)
	{
		retorno = r->cCorrente->nrCCorrente;
	}
	
	if(aux2 > retorno)
	{
		aux2 = retorno;
	}
	
	
		return retorno;
}

void incluiCCorrente(struct no **raiz)
{
	int proxCCorrente = proximaCCorrente(*raiz);
	printf("%d", proxCCorrente);
	if(proxCCorrente == -1)
	{
		printf("Impossível cadastrar mais clientes");
		return;
	}
	
	struct regCCorrente* novaCCorrente;
	
	novaCCorrente = leCCorrente();
	novaCCorrente->nrCCorrente = proxCCorrente;

	int h=V;

    insereContaCorrente(raiz, novaCCorrente, &h);
}

void depositoCCorrente(int numContaCorrente, struct no *raiz, float valorDeposito)
{
	struct regCCorrente * cCorrente = obtemCCorrente(raiz, numContaCorrente);
	
	if(cCorrente == NULL)
	{
		printf("Nao foi encontrada nenhuma conta corrente");
		return;
	}
		time_t now;
        time(&now);

        struct tm* now_tm;
        now_tm = localtime(&now);

        char out[11];
        strftime (out, 11, "%d-%m-%Y", now_tm);

	    strcpy(cCorrente->dtUltimaMovimentacao, out);
		
		cCorrente->vlUltimaMovimentacao = valorDeposito;
		cCorrente->vlSaldo = cCorrente->vlSaldo + valorDeposito;
		cCorrente->tpMovimentacao = 'C';
}

int saqueCCorrente(int numContaCorrente, struct no *raiz, float valorSaque)
{
	struct regCCorrente * cCorrente = obtemCCorrente(raiz, numContaCorrente);
	
	if(cCorrente == NULL)
	{
		printf("Nao foi encontrada nenhuma conta corrente");
		return 0;
	}
	
	if(cCorrente->tpConta == 'C')
	{
		if(cCorrente->vlSaldo < valorSaque)
		{
		    printf("Saldo insuficiente!");
		    return 0;
		}
	}
	else
	{
		if(cCorrente->tpConta == 'E')
		{
		    if((cCorrente->vlSaldo + 1500)< valorSaque)
		    {
		    	printf("Saldo insuficiente!");
		        return 0;
		    }
		}
	}
	
		time_t now;
        time(&now);

        struct tm* now_tm;
        now_tm = localtime(&now);

        char out[11];
        strftime (out, 11, "%d-%m-%Y", now_tm);

	    strcpy(cCorrente->dtUltimaMovimentacao, out);
		
		cCorrente->vlUltimaMovimentacao = valorSaque;
		cCorrente->vlSaldo = cCorrente->vlSaldo - valorSaque;
		cCorrente->tpMovimentacao = 'D';
		
		return 1;
}

void saldoAtualCCorrente(int numContaCorrente, struct no *raiz)
{
	struct regCCorrente * cCorrente = obtemCCorrente(raiz, numContaCorrente);
	
	if(cCorrente == NULL)
	{
		printf("Nao foi encontrada nenhuma conta corrente");
		return;
	}
	
	printf("O saldo da conta %d é de R$: %f", numContaCorrente, cCorrente->vlSaldo);
}

void consultaUltimaMovimentacao(int numContaCorrente, struct no *raiz)
{
	struct regCCorrente * cCorrente = obtemCCorrente(raiz, numContaCorrente);
	
	if(cCorrente == NULL)
	{
		printf("Nao foi encontrada nenhuma conta corrente");
		return;
	}
	
	printf("Data da ultima movimentacao: %s", cCorrente->dtUltimaMovimentacao);
	printf("Valor da ultima movimentacao %f:", cCorrente->vlSaldo);
	printf("Tipo movimentacao: %c", cCorrente->tpMovimentacao);
}



void transfereValor(int numContaCorrenteOrigem, int numContaCorrenteDestino, float valorTransferencia, struct no *raiz)
{
	struct regCCorrente * cCorrenteOrigem = obtemCCorrente(raiz, numContaCorrenteOrigem);
	struct regCCorrente * cCorrenteDestino = obtemCCorrente(raiz, numContaCorrenteDestino);
	
	if(cCorrenteOrigem == NULL)
	{
		printf("Nao foi encontrada conta corrente origem!");
		return;
	}
	
	if(cCorrenteDestino == NULL)
	{
        printf("Nao foi encontrada conta corrente destino!");
		return;
	}
	
	int aux = saqueCCorrente(numContaCorrenteOrigem, raiz, valorTransferencia);
	
	if(aux == 1)
	{
		depositoCCorrente(numContaCorrenteDestino, raiz, valorTransferencia);
	}
}

void excluiCCorrente(struct no **atual, int elem, int *h)
{
	struct no *aux;
	if(*atual==NULL) printf("Elemento nao esta na arvore!\n"); else 
	    if((*atual)->cCorrente->nrCCorrente > elem) {
		/* procura a esquerda */
		retira(&(*atual)->esq, elem, h);
		if(*h==V) balancoE(atual, h);
	} else 
	      if((*atual)->cCorrente->nrCCorrente < elem) {
		/* procura a direita */
		retira(&(*atual)->dir, elem, h);
		if(*h==V) balancoD(atual, h);
	} else {
		/* achou: deleta *atual */
		aux = *atual;
		if(aux->dir==NULL) {
			*atual=aux->esq;
			*h=V;
		} else 
		   if(aux->esq==NULL) {
			*atual=aux->dir;
			*h=V;
		} else {
			antecessor(&aux, &(*atual)->esq, h);
			if(*h==V) balancoE(atual, h);
		}
		free(aux);
	}	
}
