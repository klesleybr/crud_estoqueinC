#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/* Defini��o da lista */
typedef struct pdt{
	char id[20];
	char nome[70];
	float pesoUni;
	int quantidade;
	float precoUni;
} dadosProduto;
/* Cada n� da lista corresponder� a uma struct pdt e um ponteiro. */

typedef struct listaP{
	dadosProduto produto;
	struct listaP* proximo;
} listaP;
typedef listaP* listaPont;


/* Fun��o de login */
void autenticacao(char* nomeUser){
	setlocale(LC_ALL, "Portuguese");
	
	char nome[50], password[20];
	int t = 3;
	
	printf("|| Informe o nome de usu�rio: ");
	gets(nome);
	do{
		printf("|| Informe a senha de acesso: ");
		gets(password);
		if(strcmp(password, "arm2024storage") != 0){
			t--;
			if(t == 0) break;
			printf("(!) Restam %d tentativas.\n", t);
		}
	} while(strcmp(password, "arm2024storage") != 0 && t!=0);
	
	if(t == 0){
		system("cls");
		puts("~ Voc� zerou o n�mero de tentativas. O programa ser� encerrado. ~");
		exit(1);
	}
	else{
		puts("-----------------------------------------------------");
		strcpy(nomeUser, nome);
	 	puts(">> Login realizado COM SUCESSO.");
	 	printf("- Usu�rio: %s\n", nomeUser);
	 	time_t t; time(&t);
		printf("- Dados de login: %s", ctime(&t));
		
	 	system("pause");
	 	system("cls");
	}
}

/* Fun��o adicionar produtos */
int adicionar(listaPont* P, char id[], char nome[], float pesoUni, int quantidade, float precoUni) {
	listaPont novo;
    
    novo = (listaPont)malloc(sizeof(listaP));
    if (novo == NULL) return 0; // Erro de aloca��o de mem�ria.

    strcpy(novo->produto.id, id);
    strcpy(novo->produto.nome, nome);
    novo->produto.pesoUni = pesoUni;
    novo->produto.quantidade = quantidade;
    novo->produto.precoUni = precoUni;
    novo->proximo = NULL;
    
    if(*P == NULL){
        *P = novo;
        return 1;
    }
    
    listaPont copia, auxiliar;
    copia = *P;
    while (copia != NULL){
        auxiliar = copia;
        copia = copia->proximo;
    }
    auxiliar->proximo = novo;
    return 1;
}
/* Função deletar produtos */
void deletar(listaPont* lista, char id[]) {
    listaPont aux = *lista;
    listaPont anterior = NULL;

    while (aux != NULL) {
        if (strcmp(aux->produto.id, id) == 0) {
            if (anterior == NULL) {
                *lista = aux->proximo;
            } else {
                anterior->proximo = aux->proximo;
            }
            free(aux);
            return;
        }
        anterior = aux;
        aux = aux->proximo;
    }
}

// Fun��o retirar produtos
int retirar(listaPont* P, char id[], int quantidade, char nome[]) {
	if(*P == NULL) return -2;
	
	listaPont atual = *P;
	listaPont anterior = NULL;
	
	// Percorre a lista procurando o produto com o ID 
	while (atual != NULL && strcmp(atual->produto.id, id) != 0) {
	    anterior = atual;
	    atual = atual->proximo;
	}
	
	// Se encontrou o produto, remove a quantidade
    if (atual != NULL) {
        if (atual->produto.quantidade >= quantidade) { // Verifica se a quantidade � suficiente
	        atual->produto.quantidade -= quantidade;
	        strcpy(nome, atual->produto.nome);
	        return 1; 
	    } else {
	        return -1; 
	    }
	} else {
	        return 0; 
	    }
}

/* Fun��o de visualizar estoque */
void exibir_estoque(listaPont P){
	if(P == NULL) puts(">> ERRO - O estoque est� vazio.");
	else{
		int i = 1;
		while(P != NULL){
			puts("----------------------------------------------------");
			printf("----------------- Dados do Produto %2d -------------\n", i);
			printf("|| ID: %s\n", P->produto.id);
			printf("|| NOME: %s\n", P->produto.nome);
			printf("|| QUANTIDADE: %d\n", P->produto.quantidade);
			printf("|| PESO UNIT�RIO (kg): %.4f\n", P->produto.pesoUni);
			printf("|| PRE�O UNIT�RIO: R$%.2f\n", P->produto.precoUni);
			printf("~ O produto possui um peso total de %.4f kg, o equivalente a R$ %.3f.\n", (P->produto.pesoUni)*(P->produto.quantidade), (P->produto.precoUni)*((P->produto.quantidade)));
			
			i++;
			P = P->proximo;
		}	
	}
}


