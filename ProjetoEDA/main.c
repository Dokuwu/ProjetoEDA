#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiroslistas.h"

/* checklist:
1.sim| Definição de uma estrutura de dados dinâmica (a validar previamente com o docente), para a representação dos meios de mobilidade elétrica, clientes e gestores;
2.sim| Armazenamento/leitura dos dados em ficheiro de texto (valores de simulação) e binários (preservar dados);
3.sim| Inserção de novos dados (cliente/gestor/meio de mobilidade elétrica);
4.sim| Remoção de determinados dados (cliente/gestor/meio de mobilidade elétrica);
5. Alteração de determinados dados (cliente/gestor/meio de mobilidade elétrica);
6.sim| Registo do aluguer de um determinado meio de mobilidade elétrica;
7.sim| Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;
8.sim| Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo.
*/
void listarmeios(Meio* inicio) {
	while (inicio != NULL) {
		printf("Codigo:%d Tipo:%s Bateria:%.2f\nAutonomia:%.2f Custo:%.2f$ geocodigo: %s\n", inicio->codigo, inicio->tipo, inicio->bateria,
			inicio->autonomia, inicio->custo, inicio->geocodigo);
		printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n");
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listarmeiosgeocod(Meio* inicio, char geocod[]) {
	while (inicio != NULL) {
		if(!(strcmp(inicio->geocodigo,geocod))){
			printf("Codigo:%d Tipo:%s Bateria:%.2f\nAutonomia:%.2f Custo:%.2f$ geocodigo%s\n", inicio->codigo, inicio->tipo, inicio->bateria,
				inicio->autonomia, inicio->custo, inicio->geocodigo);
			printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n");
		}
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

int checkloginutil(Utilizadores* inicio, char nome[50], int NIF) {
	while (inicio != NULL) {
		if (!(strcmp(inicio->nome, nome)) && inicio->NIF) {
			system("cls");
			printf("Seja bem vindo %s!\n", inicio->nome);
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;
}

int main() {
	FILE* meiosb,*adminsb,*utilsb,*historicaluguel;
	Meio* meios = NULL;
	Administradores* admins = NULL;
	Utilizadores* utils = NULL;
	int run = 1, bool = 1, exec = 1, alreadylogged = 0, login, choice, utiladminmeio, cod, utilNIF;
	float bat, aut, cust, utilsaldo,adicionarsaldo;
	char nickname[20], password[20], tipo[20], geocod[50],adminnome[20],adminsenha[20],utilnome[60],utilmorada[100];
	meiosb = fopen("meios.bin", "rb");
	meios = pegarregistomeios(meios, meiosb);
	fclose(meiosb);
	adminsb = fopen("admin.bin", "rb");
	admins = pegarregistoadmin(admins, adminsb);
	fclose(adminsb);
	utilsb = fopen("util.bin", "rb");
	utils = pegarregistoutil(utils, utilsb);
	fclose(utilsb);
	BubbleSortMeios(meios);

	login = 3;
	while(login <= 3 && login > 0){
		
		if(login == 3){//verificar se é igual a 3, para se o util errar a senha, não aparecer para escolhar de novo
			printf("Deseja fazer login como:\n1- Admin\n2- Utilizador\n0- Encerrar programa\n");
			scanf("%d", &login);
			system("cls");
			alreadylogged = 0;
		}
			
		else if (login == 1) {//parte dos administradores
			if(!(alreadylogged)){
			printf("Bem-vindo Administrador! Por favor faca login.\n");
			printf("Usuario: ");
			scanf("%s", nickname);
			printf("Senha: ");
			scanf("%s", password);
			alreadylogged = 1;
			}
			system("cls");
			if (!(checkloginadmin(admins, nickname, password))) {//verificação do login
				printf("ERRO! Nome de usuario ou senha errados!");
				alreadylogged = 0;
			}
			else{
				exec = 1;
				while (exec) {
					printf("O que deseja fazer?\n1- Registar novo utilizador, administrador ou meio\n2- Remocao de um utilizador, administrador ou meio\n");
					printf("3- Alteracao da informacao de um utilizador, administrador ou meio\n4- Listar dados\n5- Terminar sessao\n");
					scanf("%d", &choice);
					system("cls");

					// Adicionar dados às listas
					if (choice == 1) {
						printf("Utilizador, administrador ou meio? (1,2,3)\n");
						scanf("%d", &utiladminmeio);
						system("cls");
						if (utiladminmeio == 1) {//utilizador
							printf("Nome\n");
							getchar();
							gets(utilnome);
							printf("\nNIF:\n");
							scanf("%d", &utilNIF);
							printf("\nMorada:\n");
							getchar();
							gets(utilmorada);
							printf("\nSaldo\n");
							scanf("%f", &utilsaldo);
							system("cls");
							if (!(existeUtil(utils, utilnome)) && utilNIF > 99999999 && utilNIF < 1000000000) {
								utils = inserirUtils(utils, utilnome, utilNIF, utilmorada, utilsaldo);
								printf("Adicionado com sucesso! ");
							}
							else {
								printf("ERRO DE DIGITACAO ENCONTRADO OU NIF JA EXISTENTE!\n");
							}
						}

						else if (utiladminmeio == 2) {//administrador
							printf("\nNome de usuario: \n");
							scanf("%s", &adminnome);
							printf("\nSenha:\n");
							scanf("%s", &adminsenha);
							system("cls");
							if (!(existeAdmin(admins, adminnome))) {
								admins = inserirAdmins(admins, adminnome, adminsenha);
								printf("Adicionado com sucesso! ");
							}
							else {
								printf("ERRO DE DIGITACAO ENCONTRADO OU USUARIO JA EXISTENTE!\n");
							}
						}

						else if (utiladminmeio == 3) {//meio
							printf("Codigo\n");
							scanf("%d",&cod);
							printf("\nTipo: (trotinete/bicicleta)\n");
							bool = 1;
							while (bool) {
								scanf("%s", tipo);
								if (!(strcmp(tipo, "trotinete")) || !(strcmp(tipo, "bicicleta")))
									bool = 0;
								else
									printf("Digitou errado, escreva de novo:\n");
							}
							printf("\nBateria\n");
							scanf("%f", &bat);
							printf("\nAutonomia\n");
							scanf("%f", &aut);
							printf("\nCusto\n");
							scanf("%f", &cust);
							printf("\nGeocodigo\n");
							scanf("%s", geocod);
							system("cls");
							if(!(existeMeio(meios, cod)) &&bat >= 0 && aut >=0 && cust >= 0){
								meios = inserirMeio(meios, cod, tipo, bat, aut, cust, geocod);
								BubbleSortMeios(meios);
								printf("Adicionado com sucesso! ");
							}
							else {
								printf("ERRO DE DIGITACAO ENCONTRADO OU CODIGO JA EXISTENTE!\n");
							}
						}
					}


					//Remover dados das listas
					else if (choice == 2) {
						printf("Utilizador, administrador ou meio? (1,2,3)\n");
						scanf("%d", &utiladminmeio);
						if (utiladminmeio == 1) {//utilizador
							printf("Digite o NIF de utilizador:");
							scanf("%d", &utilNIF);
							utils = removerUtil(utils, utilNIF);
							system("cls");
							printf("Removido com sucesso! ");
						}
						else if (utiladminmeio == 2) {//administrador
							printf("Digite o nome de usario:");
							scanf("%s", &adminnome);
							admins = removerAdmins(admins, adminnome);
							system("cls");
							printf("Removido com sucesso! ");
						}
						else if (utiladminmeio == 3) {//meio
							printf("Digite o codigo:");
							scanf("%d", &cod);
							meios = removerMeio(meios, cod);
							system("cls");
							printf("Removido com sucesso! ");
						}
					}

					//Alterar informação
					else if (choice == 3) {
						printf("Utilizador, administrador ou meio? (1,2,3)\n");
						scanf("%d", &utiladminmeio);
						if (utiladminmeio == 1) {//utilizador
							printf("Digite o NIF de quem quer mudar as informacoes: ");
							scanf("%d", &utilNIF);
							mudarUtils(utils, utilNIF);
						}
						else if (utiladminmeio == 2) {//administrador
							printf("Digite o nome do administrador de quem quer mudar as informacoes: ");
							getchar();
							gets(adminnome);
							mudarAdmins(admins, adminnome);
						}
						else if (utiladminmeio == 3) {//meio
							//mudarMeio(meios);
						}
					}


					else if (choice == 4) {
						listarmeios(meios);
						listarutil(utils);
						listaradmins(admins);
					}


					//Logout
					else if (choice == 5) {
						alreadylogged = 0;
						login = 3;
						exec = 0;
					}

					//No final de uma operação, pergunta se quer fazer mais alguma coisa, senão, envia para a escolha de login
					if(choice < 5){
						printf("Deseja realizar outra operacao? (1/0)\n");
						scanf("%d", &exec);
						if (exec <= 0){
							alreadylogged = 0;
							login = 3;
						}
					}
				}
			}
		}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Parte dos utilizadores
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		else if (login == 2) {
			if (!(alreadylogged)) {
				printf("Bem-vindo Utilizador! Por favor faca login.\n");
				printf("Usuario: ");
				getchar();
				gets(utilnome);
				printf("NIF: ");
				scanf("%d", &utilNIF);
				alreadylogged = 1;
			}
			system("cls");
			if (!(checkloginutil(utils, utilnome, utilNIF))) {//verificação do login
				printf("ERRO! Nome ou NIF errados!");
				alreadylogged = 0;
			}
			else {
				exec = 1;
				while (exec) {
					printf("O que deseja fazer?\n1- Ver e adicionar saldo\n2- Ver todos os meios\n3- Ver os meios num geocodigo\n4- Alugar meio\n5- Terminar sessao\n");
					scanf("%d", &choice);
					system("cls");

					//ver Saldo
					if (choice == 1) {
						verificarsaldo(utils, utilNIF,NULL, NULL, 0, NULL,NULL);//NULL serve para as variaveis presentes na função que não vao ser precisas
						printf("Quer adicionar saldo? (1/0)\n");
						scanf("%f", &adicionarsaldo);
						if (adicionarsaldo){
							printf("Digite o valor a adicionar:\n");
							scanf("%f", &adicionarsaldo);
							verificarsaldo(utils, utilNIF, NULL, NULL, 1, adicionarsaldo, NULL);
						}
					}

					//ver meios
					else if (choice == 2) {
						printf("Os meios existentes são:\n");
						listarmeios(meios);
					}

					else if (choice == 3) {
						printf("Escreva o geocodigo:");
						scanf("%s", geocod);
						printf("Os meios no geocodigo existentes sao:\n");
						listarmeiosgeocod(meios, geocod);
					}

					else if (choice == 4) {
						printf("Escreva o codigo do meio:");
						scanf("%d", &cod);
						verificarsaldo(utils, utilNIF, meios, cod, NULL, NULL, 1);//como o ultimo parametro está 1 ele vai passar para 
					}
					//Logout
					else if (choice == 5) {
						alreadylogged = 0;
						login = 3;
						exec = 0;
					}

					if (choice < 5) {
						printf("Deseja realizar outra operacao? (1/0)\n");
						scanf("%d", &exec);
						if (exec <= 0) {
							alreadylogged = 0;
							login = 3;
						}
					}
				}
			}
		}
	}
	/*
	listarmeios(meios);
	listarutil(utils);
	listaradmins(admins);
	*/
	printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~Obrigado por utilizar nossos servicos!-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~");
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