#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct registo {
	int codigo;
	char tipo[50];
	float bateria;
	float autonomia;
	struct registo* seguinte;
} Meio;

Meio* pegarregistromeios(Meio* inicio, FILE* txt);

void escrevertxtmeios(Meio* inicio, FILE* txt);

void listarMeios(Meio* inicio);
