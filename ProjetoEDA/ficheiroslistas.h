#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct registomeio {
	int codigo;
	char tipo[50];
	float bateria;
	float autonomia;
	float custo;
	char geocodigo[100];
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
//definições das funções para escrever e ler dados
Meio* pegarregistomeios(Meio* inicio, FILE* bin);
Administradores* pegarregistoadmin(Administradores* inicio, FILE* bin);
Utilizadores* pegarregistoutil(Utilizadores* inicio, FILE* bin);

void escreverbinmeios(Meio* inicio, FILE* bin);
void escreverbinadmin(Administradores* inicio, FILE* bin);
void escreverbinutil(Utilizadores* inicio, FILE* bin);

//definição das funções dos admins
//Meios
int existeMeio(Meio* inicio, int cod);
Meio* inserirMeio(Meio* inicio, int cod, char tipo[], float bat, float aut, float cust, char geocod[]);
Meio* removerMeio(Meio* inicio, int cod);

//Admin
Administradores* removerAdmins(Administradores* inicio, char nome[]);
Administradores* inserirAdmins(Administradores* inicio, char nome[], char senha[]);
int existeAdmin(Administradores* inicio, char nome[]);



//BubbleSort dos Meios em ordem decrescente
void BubbleSortMeios(Meio* inicio);