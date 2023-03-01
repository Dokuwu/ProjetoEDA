#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct registomeio {
	int codigo;
	char tipo[50];
	float bateria;
	float autonomia;
	float custo;
	char geocodigo[50];
	struct registo* seguinte;
} Meio;

typedef struct registoutil {
	char nome[100];
	char morada[100];
	int NIF;
	float saldo;
	struct registo* seguinte;
} Utilizadores;

typedef struct registoadmin {
	char nome[100];
	char senha[20];
	struct registo* seguinte;
} Administradores;

Meio* pegarregistomeios(Meio* inicio, FILE* bin);
Administradores* pegarregistoadmin(Administradores* inicio, FILE* bin);
Utilizadores* pegarregistoutil(Utilizadores* inicio, FILE* bin);

void escreverbinmeios(Meio* inicio, FILE* bin);
void escreverbinadmin(Administradores* inicio, FILE* bin);
void escreverbinutil(Utilizadores* inicio, FILE* bin);