#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

/* Definiï¿½ï¿½o da lista */
typedef struct pdt{
	char id[20];
	char nome[70];
	float pesoUni;
	int quantidade;
	float precoUni;
} dadosProduto;
/* Cada nï¿½ da lista corresponderï¿½ a uma struct pdt e um ponteiro. */

typedef struct listaP{
	dadosProduto produto;
	struct listaP* proximo;
} listaP;
typedef listaP* listaPont;


/* Funï¿½ï¿½o de login */
void autenticacao(char* nomeUser){
	setlocale(LC_ALL, "Portuguese");
	
	char nome[50], password[20];
	int t = 3;
	
	printf("|| Informe o nome de usuï¿½rio: ");
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
		puts("~ Vocï¿½ zerou o nï¿½mero de tentativas. O programa serï¿½ encerrado. ~");
		exit(1);
	}
	else{
		puts("-----------------------------------------------------");
		strcpy(nomeUser, nome);
	 	puts(">> Login realizado COM SUCESSO.");
	 	printf("- Usuï¿½rio: %s\n", nomeUser);
	 	time_t t; time(&t);
		printf("- Dados de login: %s", ctime(&t));
		
	 	system("pause");
	 	system("cls");
	}
}

/* Funï¿½ï¿½o adicionar produtos */
int adicionar(listaPont* P, char id[], char nome[], float pesoUni, int quantidade, float precoUni) {
	listaPont novo;
    
    novo = (listaPont)malloc(sizeof(listaP));
    if (novo == NULL) return 0; // Erro de alocaï¿½ï¿½o de memï¿½ria.

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

// Função retirar produtos
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
        if (atual->produto.quantidade >= quantidade) { // Verifica se a quantidade ï¿½ suficiente
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

/* Funï¿½ï¿½o de visualizar estoque */
void exibir_estoque(listaPont P){
	if(P == NULL) puts(">> ERRO - O estoque estï¿½ vazio.");
	else{
		int i = 1;
		while(P != NULL){
			puts("----------------------------------------------------");
			printf("----------------- Dados do Produto %2d -------------\n", i);
			printf("|| ID: %s\n", P->produto.id);
			printf("|| NOME: %s\n", P->produto.nome);
			printf("|| QUANTIDADE: %d\n", P->produto.quantidade);
			printf("|| PESO UNITï¿½RIO (kg): %.4f\n", P->produto.pesoUni);
			printf("|| PREï¿½O UNITï¿½RIO: R$%.2f\n", P->produto.precoUni);
			printf("~ O produto possui um peso total de %.4f kg, o equivalente a R$ %.3f.\n", (P->produto.pesoUni)*(P->produto.quantidade), (P->produto.precoUni)*((P->produto.quantidade)));
			
			i++;
			P = P->proximo;
		}	
	}
}

/* Função deletar produtos */
int deletar(listaPont* lista, char id[], char nome[]) {
	if(*lista == NULL) return -1;
	
    listaPont aux = *lista;
    listaPont anterior = NULL;

    while (aux != NULL) {
        if (strcmp(aux->produto.id, id) == 0) {
        	strcpy(nome, aux->produto.nome);
            if (anterior == NULL) {
                *lista = aux->proximo;
            } else {
                anterior->proximo = aux->proximo;
            }
            free(aux);
            return 1;
        }
        anterior = aux;
        aux = aux->proximo;
    }
    
    if(aux == NULL) return 0;
}


