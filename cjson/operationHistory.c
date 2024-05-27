#include "operationHistory.h"

cJSON *listaHistoricoToJson(pontHistorico listaHistorico) {
  cJSON *historicoArray = cJSON_CreateArray();
  if (historicoArray == NULL) {
    return NULL;
  }

  pontHistorico atual = listaHistorico;
  while (atual != NULL) {
    cJSON *objHistoricoJson = cJSON_CreateObject();
    if (objHistoricoJson == NULL) {
      cJSON_Delete(historicoArray);
      return NULL;
    }

    cJSON_AddItemToObject(objHistoricoJson, "acao", cJSON_CreateString(atual->elementoHist->acao));
    cJSON_AddItemToObject(objHistoricoJson, "nome", cJSON_CreateString(atual->elementoHist->nome));
    cJSON_AddItemToObject(objHistoricoJson, "pesoUni", cJSON_CreateNumber(atual->elementoHist->pesoUni));
    cJSON_AddItemToObject(objHistoricoJson, "precoUni", cJSON_CreateNumber(atual->elementoHist->precoUni));
    cJSON_AddItemToObject(objHistoricoJson, "quantidade", cJSON_CreateNumber(atual->elementoHist->quantidade));

    cJSON_AddItemToArray(historicoArray, objHistoricoJson);
    atual = atual->proximoElemento;
  }
  cJSON *historicoJson = cJSON_CreateObject();
  cJSON_AddItemToObject(historicoJson, "historico", historicoArray);

  return historicoJson;
}

void registrarOperacao(pontHistorico *listaHistorico, const char *acao, const char *nome, float pesoUni, int quantidade, float precoUni) {
  elementoHistorico *novaOperacao = (elementoHistorico *)malloc(sizeof(elementoHistorico));
  if (novaOperacao == NULL) {
    puts("Nao foi possivel alocar memoria para a nova operacao!\n");
    return;
  }

  strcpy(novaOperacao->acao, acao);
  strcpy(novaOperacao->nome, nome);
  novaOperacao->pesoUni = pesoUni;
  novaOperacao->quantidade = quantidade;
  novaOperacao->precoUni = precoUni;

  pontHistorico novoElemento = (pontHistorico)malloc(sizeof(struct listaHistorico));
  if (novoElemento == NULL) {
    puts("Nao foi possivel alocar memoria para o novo elemento do historico!\n");
    free(novaOperacao);
    return;
  }

    novoElemento->elementoHist = novaOperacao;
    novoElemento->proximoElemento = *listaHistorico;
    *listaHistorico = novoElemento;
}

void imprimirHistorico(pontHistorico listaHistorico) {

      cJSON *historicoJson = listaHistoricoToJson(listaHistorico);

    if (historicoJson != NULL) {
      char *historicoJsonStr = cJSON_Print(historicoJson);

      if (historicoJsonStr != NULL) {
        printf("%s", historicoJsonStr);
    
        FILE *file = fopen("history.json", "w");
        if (file != NULL) {
          fprintf(file, "%s\n", historicoJsonStr);
          fclose(file);
          printf("Json Salvo!");
          return;
        }
        free(historicoJsonStr);
        fprintf(stderr, "Erro ao abrir arquivo para escrita!\n");
      }
      cJSON_Delete(historicoJson);
      return;
    }

}