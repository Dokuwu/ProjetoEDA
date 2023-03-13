#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

typedef struct registomeio {
	int codigo;
	char tipo[50];
	int alugado;//1 se sim 0 se não
	float bateria;
	float autonomia;
	float custo;
	char geocodigo[100];
	//guardar se está alugada
	struct registomeio* seguinte;
} Meio;

typedef struct registoutil {
	char nome[100];
	char morada[200];
	int NIF;
	float saldo;
	struct registoutil* seguinte;
} Utilizadores;

typedef struct registoadmin {
	//cada gestor um codigo unico
	int codigo;
	char nome[100];
	char senha[20];
	struct registoadmin* seguinte;
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
void mudarMeios(Meio* inicio, int cod);

//Admin
int existeAdmin(Administradores* inicio, int cod);
Administradores* removerAdmins(Administradores* inicio, int cod);
Administradores* inserirAdmins(Administradores* inicio,int cod, char nome[], char senha[]);
void mudarAdmins(Administradores* inicio, int cod);

//Utilizadores
int existeUtil(Utilizadores* inicio, int NIF);
Utilizadores* inserirUtils(Utilizadores* inicio, char nome[], int NIF, char morada[], float saldo);
Utilizadores* removerUtil(Utilizadores* inicio, int NIF);
void mudarUtils(Utilizadores* inicio, int NIF);

//BubbleSort dos Meios em ordem decrescente
void BubbleSortMeios(Meio* inicio);

//Gerenciamento de saldo do utilizador
void verificarsaldo(Utilizadores* inicioutil, int utilNIF, Meio* iniciomeio, int cod, int valoradd, float carregarvalor, int verificarsemaior);
void mexersaldo(Utilizadores * util, Meio * meio, int sinal, float valorcarregado);
void guardarhistorico(Utilizadores* util, Meio* meio);