#ifndef OPHISTORY_H
#define OPHISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <cJSON.h>
#include <string.h>

typedef struct elementoHistorico {
  char acao[50];
  char nome[70];
  float pesoUni;
	int quantidade;
	float precoUni;
} elementoHistorico;

typedef struct listaHistorico {
  elementoHistorico *elementoHist;
  struct listaHistorico *proximoElemento;
} listaHistorico;

typedef listaHistorico *pontHistorico;

cJSON *listaHistoricoToJson(pontHistorico listaHistorico);
void registrarOperacao(pontHistorico *listaHistorico, const char *acao, const char *nome, float pesoUni, int quantidade, float precoUni);

#endif
