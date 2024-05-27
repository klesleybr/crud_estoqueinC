#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>
#include "operationHistory.h"

typedef struct pdt {
    char id[20];
    char nome[70];
    float pesoUni;
    int quantidade;
    float precoUni;
} dadosProduto;

typedef struct listaP {
    dadosProduto produto;
    struct listaP* proximo;
} listaP;
typedef listaP* listaPont;

void autenticacao(char* nomeUser);
int adicionar(listaPont* P, char id[], char nome[], float pesoUni, int quantidade, float precoUni);
void exibir_estoque(listaPont P);

#endif