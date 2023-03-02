#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiros.h"


void listarmeios(Meio* inicio) {
	while (inicio != NULL) {
		printf("%d %s %.2f %.2f %.2f %s\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia, inicio->custo, inicio->geocodigo);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listaradmins(Administradores* inicio) {
	while (inicio != NULL) {
		printf("%s %s\n", inicio->nome, inicio->senha);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listarutil(Utilizadores* inicio) {
	while (inicio != NULL) {
		printf("%s %s %d %.2f\n", inicio->nome, inicio->morada, inicio->NIF, inicio->saldo);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

int checkloginadmin(Administradores* inicio, char usuario[20], char senha[20]) {
	while (inicio != NULL) {
		if (!(strcmp(inicio->nome, usuario)) && !(strcmp(inicio->senha, senha))){
			system("cls");
			printf("Seja bem vindo %s!\n", inicio->nome);
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

int main() {
	FILE* meiosb,*adminsb,*utilsb;
	Meio* meios = NULL;
	Administradores* admins = NULL;
	Utilizadores* utils = NULL;
	int run = 1, bool = 1, exec = 1,login,adminchoice, utiladminmeio,cod;
	float bat, aut, cust;
	char nickname[20], password[20], tipo[20], geocod[20];
	meiosb = fopen("meios.bin", "rb");
	meios = pegarregistomeios(meios, meiosb);
	fclose(meiosb);
	adminsb = fopen("admin.bin", "rb");
	admins = pegarregistoadmin(admins, adminsb);
	fclose(adminsb);
	utilsb = fopen("util.bin", "rb");
	utils = pegarregistoutil(utils, utilsb);
	fclose(utilsb);

	while (run>0) {
		login = 3;
		while(login <= 3 && login > 0){
		
			if(login == 3){//verificar se � igual a 3, para se o util errar a senha, n�o aparecer para escolhar de novo
				printf("Deseja fazer login como:\n1- Admin\n2- Utilizador\n0- Encerrar programa\n");
				scanf("%d", &login);
				system("cls");
			}
			else if (login == 1) {//parte dos administradores
				printf("Bem-vindo Administrador! Por favor faca login.\n");
				printf("Usuario: ");
				scanf("%s", nickname);
				printf("Senha: ");
				scanf("%s", password);
				system("cls");
				if (!(checkloginadmin(admins,nickname,password))) {//verifica��o do login
					printf("ERRO! Nome de usuario ou senha errados!");
				}
				else{
					while (exec) {
						printf("O que deseja fazer?\n1- Registar novo utilizador, administrador ou meio\n2- Remocao de um utilizador, administrador ou meio\n");
						printf("3- Alteracao da informacao de um utilizador, administrador ou meio\n4- Terminar sessao\n");
						scanf("%d", adminchoice);
						system("cls");
						// Adicionar dados �s listas
						if (adminchoice == 1) {// Adicionar dados �s listas
							printf("Utilizador, administrador ou meio? (1,2,3)\n");
							scanf("%d", utiladminmeio);
							if (utiladminmeio == 1) {//utilizador
								printf("em desenvolvimento");
							}
							else if (utiladminmeio == 2) {//administrador
								printf("em desenvolvimento");
							}
							else if (utiladminmeio == 3) {//meio
								printf("Codigo\n");
								scanf("%d",cod);
								printf("\nTipo: (trotinete/bicicleta)\n");
								while(bool){
								scanf("%s", tipo);
								if(!(strcmp(tipo, "trotinete")) || !(strcmp(tipo, "bicicleta"))){
									bool = 1;
								}
								printf("\nBateria\n");
								scanf("%f", bat);
								printf("\nAutonomia\n");
								scanf("%f", aut);
								printf("\nCusto\n");
								scanf("%f", cust);
								printf("\nGeocodigo\n");
								scanf("%s", geocod);
								meios = inserirMeio(meios, cod, tipo, bat, aut, cust, geocod);
							}
						}
						//Remover dados das listas
						else if (adminchoice == 2) {
							printf("Utilizador, administrador ou meio? (1,2,3)\n");
							scanf("%d", utiladminmeio);
							if (utiladminmeio == 1) {//utilizador
								printf("em desenvolvimento");
							}
							else if (utiladminmeio == 2) {//administrador
								printf("em desenvolvimento");
							}
							else if (utiladminmeio == 3) {//meio
								scanf("%d",cod);
								removerMeio(meio, cod);
							}
						}
						//Alterar informa��o
						else if (adminchoice == 3) {
							printf("Utilizador, administrador ou meio? (1,2,3)\n");
							scanf("%d", utiladminmeio);
							if (utiladminmeio == 1) {//utilizador
								printf("em desenvolvimento");
							}
							else if (utiladminmeio == 2) {//administrador
								printf("em desenvolvimento");
							}
							else if (utiladminmeio == 3) {//meio
								printf("em desenvolvimento");
							}
						}
						else if (adminchoice == 4) {
							login = 3;
							exec = 0;
						}
						printf("Deseja realizar outra opera��o?\n");
						scanf("%d", &exec);
					}
				}
			}
		//Parte dos utilizadores
			else if (login == 2) {
			
			}
		
		}
		printf("Deseja continuar a usar o programa? (0/1)\n");
		scanf("%d", &run);
	}
	listarmeios(meios);
	listarutil(utils);
	listaradmins(admins);


	meiosb = fopen("meios.bin", "wb");
	escreverbinmeios(meios, meiosb);
	fclose(meiosb);
	adminsb = fopen("admin.bin", "wb");
	escreverbinadmin(admins, adminsb);
	fclose(adminsb);
	utilsb = fopen("util.bin", "wb");
	escreverbinutil(utils, utilsb);
	fclose(utilsb);

	return 1;
}