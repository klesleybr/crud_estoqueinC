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
#include "./methods/functions.c"

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	char userNome[50];
	int opc, status;
	
	listaPont estoque = NULL;
    char id[20];
    char nome[70];
    float pesoUni;
    int quantidade;
    float precoUni;
	
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
				puts("<    PROGRAMA ENCERRADO   >");
				break;
				
			case 1:
				printf("Insira o ID do produto: "); // Sem espaços...
                scanf("%s", id);
                getchar(); 

                printf("Insira o nome do produto: ");
                fgets(nome, sizeof(nome), stdin);

                printf("Insira o peso unitário do produto (kg): ");
                scanf("%f", &pesoUni);

                printf("Insira a quantidade a ser adicionada: ");
                scanf("%d", &quantidade);

                printf("Insira o preço unitário do produto: R$ ");
                scanf("%f", &precoUni);
                
                if(adicionar(&estoque, id, nome, pesoUni, quantidade, precoUni)){
                	puts("----------------------------------------------------");
                	printf("Produto adicionado com sucesso: %s", nome);
                    printf("ID do produto: %s\n", id);
				}
				else{
					printf("Erro ao adicionar o produto: %s\n", nome);
				}
                
                break;
            
            case 3:
            	exibir_estoque(estoque);
            	break;
                
			default:
				puts(">> Erro - Opção inválida!");
				break;
		}
		puts("====================================================");
		
		system("pause");
		system("cls");
	} while(opc != 0);
	
	return 0;
}

