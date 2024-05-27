/* A proposta é fazer um controle de estoque de um armazem que abriga produtos diversos
para revenda. Até o momento, pensamos em implementar as opções:

		- Adicionar produto
		- Retirar produto
		- Excluir produto
		- Histórico de açoes
		
Isso será feito utilizando-se da TAD lista dinâmica encadeada.
*/

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include "functions.h"

int main(void) {
	setlocale(LC_ALL, "Portuguese");
	
	char userNome[50];
	int opc, status;

	pontHistorico listaHistorico = NULL;
	
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

										registrarOperacao(&listaHistorico, "Adicionado", nome, pesoUni, quantidade, precoUni);
				}
				else{
					printf("Erro ao adicionar o produto: %s\n", nome);
				}
                break;
            
            case 2:
            	printf("Insira o ID do produto a ser retirado: ");
	    		scanf("%s", id);
	    		getchar();
	
	    		printf("Insira a quantidade a ser retirada: ");
	   			scanf("%d", &quantidade);
				
				status = retirar(&estoque, id, quantidade, nome);
	    		if (status == 1) { // Produto retirado com sucesso
	        		printf(">> Foram retirados %d pacotes do produto %s com sucesso.\n", quantidade, nome);
							registrarOperacao(&listaHistorico, "Retirado", nome, pesoUni, quantidade, precoUni);
	   			} else if(status == 0) { // Erro ao retirar o produto (não encontrado)
	        		puts(">> ERRO - Produto não encontrado.");
	   			} else if(status == -1){ // Erro ao retirar o produto (quantidade excedente)
	   				puts(">> ERRO - A quantidade desejada excede o estoque.");
				}else{
					puts(">> ERRO - O estoque estã vazio.");
				}
            	break;
            
            case 3:
            	exibir_estoque(estoque);
            	break;
			case 4:
				imprimirHistorico(listaHistorico);
				break;
			case 5:
                printf("Digite o ID do produto a ser removido: ");
                scanf("%s", id);
                getchar();
                
                status = deletar(&estoque, id);
                if(status){
                	printf(">> O produto %s (%s) foi removido com sucesso.\n", nome, id);
									registrarOperacao(&listaHistorico, "Removido", nome, pesoUni, quantidade, precoUni);
				}
				else if(status == 0){
					puts(">> ERRO - Produto não encontrado.");	
				}
				else{
					puts(">> ERRO - O estoque estã vazio.");
				}		
                break;
        
            default:
                puts(">> Erro - Opção Inválida.");
                break;
		}
		puts("====================================================");
		
		system("pause");
		system("cls");
	} while(opc != 0);
	
	return 0;
}
