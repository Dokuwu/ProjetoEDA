#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiros.h"

Meio* pegarregistromeios(Meio* inicio, FILE* txt) {
	char linha[150];
	while (fgets(linha, 150, txt) != NULL) {
		Meio* novo = malloc(sizeof(struct registo));
		sscanf(linha, "%d;%[^;];%f;%f", &novo->codigo, novo->tipo, &novo->bateria, &novo->autonomia);
		novo->seguinte = inicio;
		inicio = novo;
	}
	return inicio;
}


void escrevertxtmeios(Meio* inicio, FILE* txt) {

	if (txt != NULL) {
		while (inicio != NULL) {
			fprintf(txt, "%d;%s;%.2f;%.2f\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia);
			inicio = inicio->seguinte;
		}
	}
	else
		printf("Erro na execucao do ficheiro");
}