/* A proposta é fazer um controle de estoque de um armazém que abriga produtos diversos
para revenda. Até o momento, pensamos em implementar as opções:

		- Adicionar produto
		- Retirar produto
		- Modificar informação
		- Excluir produto
		- Histórico de ações
		
Isso será feito utilizando-se da TAD lista dinâmica encadeada.
*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include "./methods/login.c"

typedef struct pdt{
	char id[20];
	char nome[70];
	float pesoUni;
	int quantidade;
	float precoUni;
	float precoTotal;
} dadosProduto;
/* Cada nó da lista corresponderá a uma struct pdt e um ponteiro. */

typedef struct listaP{
	dadosProduto produto;
	struct listaP* proximo;
} listaP;
typedef listaP* listaPont;

int inserir(listaPont* P, int pos, dadosProduto produto){
	
	listaP* novo;
	
	if(*P == NULL){
		if(pos != 1) return 0;
	
	novo = (listaP*)malloc(sizeof(listaP));
	
	if(novo = NULL) return 0;
	
	novo->produto = produto;
	novo->proximo = NULL;
	*P = novo;	
}

return 1;
}

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	char userNome[50];
	int opc, status;
	
	puts("========================================================================");
	puts("      BEM-VINDO AO SISTEMA DE CONTROLE DE ESTOQUE Almeida Storage!      ");
	puts("========================================================================");
	autenticacao(userNome);
	
	do{
		puts("============ CONTROLE DE ESTOQUE (menu) ============");
		puts("[1] - Adicionar produto");
		puts("[2] - Retirar produto");
		puts("[3] - Ver estoque atual");
		puts("[4] - Ver histórico de operações");
		puts("[5] - Excluir produto");
		puts("[6] - Alterar usuário");
		puts("[0] - Sair");
		puts("====================================================");
		printf("|| Escolha uma opção: ");
		scanf("%d", &opc);

		switch(opc){
		
			case 0:
				puts("VOCÊ SAIU DO SISTEMA DE CONTROLE DE ESTOQUE.");
			break;
			case 1:
				printf("Digite o que você deseja adicionar: ");
				scanf("%d", &inserir);
			break;
		}
		
		system("pause");
		system("cls");
	} while(opc != 0);
	
	return 0;
}

