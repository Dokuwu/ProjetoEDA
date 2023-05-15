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
	char geocodigo[100];
	struct registoutil* seguinte;
} Utilizadores;

typedef struct registoadmin {
	//cada gestor um codigo unico
	int codigo;
	char nome[100];
	char senha[20];
	struct registoadmin* seguinte;
} Administradores;

//~~~~~~~~~~~~~~~~ FASE 2 ESTRUTURA ~~~~~~~~~~~~~~~~~~

typedef struct registoadjacentes {
	char geocodigo[100];
	float peso;
	struct Adjacentes* seguinte;
} Adjacentes;


typedef struct registovertices {
	char geocodigo[100];
	Adjacentes* adjacente;
	Meio* meios;
	Utilizadores* utils;
	struct registovertices* seguinte;
} Grafo;


typedef struct pilhageocodigo {
	char geocodigo[100];
	struct pilhageocodigo* seguinte;
} Pilha;


typedef struct guardarpilhas {
	Pilha* pilha;
	float peso;
	struct guardarpilhas* seguinte;
} Listapilhas;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



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
void mudarMeios(Meio* inicio, int cod, Grafo* grafo);

//Admin
int existeAdmin(Administradores* inicio, int cod);
Administradores* removerAdmins(Administradores* inicio, int cod);
Administradores* inserirAdmins(Administradores* inicio,int cod, char nome[], char senha[]);
void mudarAdmins(Administradores* inicio, int cod);

//Utilizadores
int existeUtil(Utilizadores* inicio, int NIF);
Utilizadores* inserirUtils(Utilizadores* inicio, char nome[], int NIF, char morada[], float saldo);
Utilizadores* removerUtil(Utilizadores* inicio, int NIF);
void mudarUtils(Utilizadores* inicio, int NIF, Grafo* grafo);

//BubbleSort dos Meios em ordem decrescente
void BubbleSortMeios(Meio* inicio);

//Gerenciamento de saldo do utilizador
void mostrarsaldo(Utilizadores* util, int utilNIF);
void adicionarsaldo(Utilizadores* util, int utilNIF, float valorcarregado);
void aluguelmeio(Utilizadores* util, int utilNIF, Meio* iniciomeio, int cod);
void guardarhistorico(Utilizadores* util, Meio* meio);

//Listar coisas

void listarmeios(Meio* inicio);
void listarmeiosgeocod(Meio* inicio, char geocod[]);
void listaradmins(Administradores* inicio);
void listarutil(Utilizadores* inicio);


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//										FASE 2 GRAFOS
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Listar coisas FASE 2
void listargrafo(Grafo* inicio);
void listarutilmeiogeocod(Grafo* inicio, Utilizadores* utilzadores, int NIF);
void listarmeiostipo(Meio* inicio, char* tipo);

//parte da criação do grafo
Grafo* pegarregistografo(Grafo* inicio, FILE* bin);
void escrevergrafo(Grafo* inicio, FILE* bin);
void fixarmeiosvertices(Meio* iniciomeio, Grafo* iniciografo);
void fixarutilsvertices(Utilizadores* inicioutils, Grafo* iniciografo);
int verificargeocodigo(Grafo* grafo, char* geocodigo);
Grafo* criarvertice(Grafo* inicio, char* geocodigo);
int adicionaradjacentes(Grafo* grafo, char*geocodigo, char* geocodigoadj, float peso);

//parte dos meios no vertice
void removermeiovertice(Grafo* grafo,Meio* meio, int cod);
void mudarcodmeiovertice(Grafo* grafo,Meio* meio, int codnovo);
void mudartipomeiovertice(Grafo* grafo, Meio* meio, char* tipo );
void mudarbatvertice(Grafo* grafo, Meio* meio, float valor);
void mudarautvertice(Grafo* grafo, Meio* meio, float valor);
void mudarcustvertice(Grafo* grafo, Meio* meio, float valor);

//parte dos utilizadores
void mudargeocodutil(Utilizadores* inicio,int NIF, char* geocod);
void removerutilvertice(Grafo* grafo, Utilizadores* util, int NIF);
void mudarnomeutilvertice(Grafo* grafo, Utilizadores* util,char* nome);
void mudarmoradavertice(Grafo* grafo, Utilizadores* util, char* morada);
void mudarNIFvertice(Grafo* grafo, Utilizadores* util, int NIF);


//~~~~~~~Caminhos nos grafo~~~~~~~//

// funções gerais
int visitado(Pilha* sequencia, char* geocodigo);
Pilha* colocarsequencia(Pilha* sequencia, char* geocodigo);
Grafo* pegarorigem(Grafo* grafo, char* origem);
Pilha* copiarpilha(Pilha* sequencianova, Pilha* sequencia);




/// listar meios por raio
void listarMeiosPeso(Grafo* grafo,int NIF, Utilizadores* inicio, char* tipo, float PesoLimite);
void listarMeiosAuxpeso(Grafo* grafo, char* origem, char* tipo, Pilha* sequencia, float pesoTotal, float PesoLimite);
/// listar caminho em Listapilhas
void listarcaminho(Listapilhas* pilhas);

//caixeiroviajante
void listarCaminhobateria(Grafo* grafo, char* origem, char* tipo);
int nbatvertices(Grafo* grafo, char* destino, char* tipo);
Pilha* pegarverticesbateria(Grafo* grafo, char* tipo);
Listapilhas* listarcaminhorapidoaux(Grafo* grafo, char* origem, char* destino, Pilha* sequencia, float pesoTotal, Listapilhas* listacaminhos);
Listapilhas* verificarmenor(Listapilhas* caminhos);
Listapilhas* guardarcaminho(Pilha* caminho, Listapilhas* listacaminho, float peso);
Listapilhas* limparpilha(Listapilhas* listapilhas);