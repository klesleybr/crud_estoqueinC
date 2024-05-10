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
#include <string.h>
#include <malloc.h>
#include "./methods/login.c"

typedef struct pdt {
    char id[20];
    char nome[70];
    float pesoUni;
    int quantidade;
    float precoUni;
} dadosProduto;
/* Cada nó da lista corresponderá a uma struct pdt e um ponteiro. */

typedef struct listaP {
    dadosProduto produto;
    struct listaP* proximo;
} listaP;

typedef listaP* listaPont;

int adicionar(listaPont* P, char id[], char nome[], float pesoUni, int quantidade, float precoUni) {
    
	listaPont novo, auxiliar;
	novo = *P;

    novo = (listaPont)malloc(sizeof(listaP));
    
    if (novo == NULL) return 0;

    strcpy(novo->produto.id, id);
    strcpy(novo->produto.nome, nome);
    novo->produto.pesoUni = pesoUni;
    novo->produto.quantidade = quantidade;
    novo->produto.precoUni = precoUni;
    novo->proximo = NULL;

        while (novo != NULL){
            auxiliar = novo;
        	novo = novo->proximo;
    }
    auxiliar->proximo = novo;

	return 1;
}

int main(void) {
    setlocale(LC_ALL, "Portuguese");

    listaPont estoque = NULL;
    int opc;
    char id[20];
    char nome[70];
    float pesoUni;
    int quantidade;
    float precoUni;

    puts("========================================================================");
    puts("      BEM-VINDO AO SISTEMA DE CONTROLE DE ESTOQUE Almeida Storage!      ");
    puts("========================================================================");

    do {
        puts("============ CONTROLE DE ESTOQUE (MENU) ============");
        puts("[1] - Adicionar produto");
        puts("[2] - Retirar produto");
        puts("[3] - Ver estoque atual");
        puts("[4] - Ver histórico de operações");
        puts("[5] - Excluir produto");
        puts("[6] - Alterar usuário");
        puts("[0] - Sair");
        puts("====================================================");
        printf("|| Escolha uma opção (0-6): ");
        scanf("%d", &opc);

        switch (opc){
            case 0:
                puts("VOCÊ SAIU DO SISTEMA DE CONTROLE DE ESTOQUE.");
                break;
            case 1: 
				printf("Insira o ID do produto: ");
                scanf("%s", id);
                getchar(); /*A função getchar em C é utilizada para realizar a entrada de um único caractere e não precisa usar %c ou &, como fazemos na scanf()*/

                printf("Insira o nome do produto: ");
                fgets(nome, sizeof(nome), stdin);

                printf("Insira o peso unitário do produto (kg): ");
                scanf("%f", &pesoUni);

                printf("Insira a quantidade que você deseja: ");
                scanf("%d", &quantidade);

                printf("Insira o preço unitário do produto: R$ ");
                scanf("%f", &precoUni);
                
                puts("=========================================");

                if (adicionar(&estoque, id, nome, pesoUni, quantidade, precoUni)) {
                    printf("Produto adicionado com sucesso: %s", nome);
                    printf("ID do produto: %s\n", id);
                } else {
                    printf("Erro ao adicionar o produto: %s\n", nome);
                }
                break;
	}

        system("pause");
        system("cls");
	} while (opc != 0);
    
	listaPont novo = estoque;
    while (novo != NULL) {
        listaPont proximo = novo->proximo;
        free(novo);
        novo = proximo;
    }

    return 0;
}
