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
5.sim| Alteração de determinados dados (cliente/gestor/meio de mobilidade elétrica);
6.sim| Registo do aluguer de um determinado meio de mobilidade elétrica;
7.sim| Listagem dos meios de mobilidade elétrica por ordem decrescente de autonomia;
8.sim| Listagem dos meios de mobilidade elétrica existentes numa localização com determinado geocódigo.
*/

void listarmeios(Meio* inicio) {//funcao para mostrar os meios
	while (inicio != NULL) {
		printf("Codigo:%d Tipo:%s Bateria:%.2f", inicio->codigo, inicio->tipo, inicio->bateria);
		if (inicio->alugado == 1)//se estiver alugado mostra que sim senão mostra que nao
			printf(" Alugado: Sim");
		else
			printf(" Alugado: Nao");
		printf("\nAutonomia: %.2f Custo : %.2f$ geocodigo : %s\n", inicio->autonomia, inicio->custo, inicio->geocodigo);
		printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n");
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listarmeiosgeocod(Meio* inicio, char geocod[]) {//lista os meios pelo geocodigo
	while (inicio != NULL) {
		if(!(strcmp(inicio->geocodigo,geocod))){//Verifica se o geocodigo é o mesmo
			printf("Codigo:%d | Tipo:%s | Bateria:%.2f |", inicio->codigo, inicio->tipo, inicio->bateria);
			if (inicio->alugado == 1)//se estiver alugado mostra que sim senão mostra que nao
				printf(" Alugado: Sim");
			else
				printf(" Alugado: Nao");
			printf("\nAutonomia: %.2f | Custo : %.2f$ | geocodigo : %s\n", inicio->autonomia, inicio->custo, inicio->geocodigo);
			printf("-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-\n");
		}
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}


void listaradmins(Administradores* inicio) {
	while (inicio != NULL) {
		printf("Codigo: %d | Nome: %s | Senha: %s\n",inicio->codigo, inicio->nome, inicio->senha);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

void listarutil(Utilizadores* inicio) {
	while (inicio != NULL) {
		printf("Nome: %s | Morada: %s | NIF: %d | Saldo: %.2f\n", inicio->nome, inicio->morada, inicio->NIF, inicio->saldo);
		inicio = inicio->seguinte;
	}
	printf("\n\n\n");
}

int checkloginadmin(Administradores* inicio, int codigo, char senha[20]) {//verifica a parte de login para admin
	while (inicio != NULL) {
		if ((inicio->codigo == codigo && !(strcmp(inicio->senha, senha)))) {//se a senha e o codigo for o mesmo avança para a frente
			system("cls");
			printf("Seja bem vindo %s!\n", inicio->nome);
			return 1;
		}
		inicio = inicio->seguinte;
	}
	return 0;//senão, retorna 0 e pede para fazer login
}

int checkloginutil(Utilizadores* inicio, char nome[50], int NIF) {//mesma ideia para o checkloginadmin
	while (inicio != NULL) {
		if ((!(strcmp(inicio->nome, nome)) && inicio->NIF == NIF)) {
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
	int run = 1, bool = 1, exec = 1, alreadylogged = 0, login, choice, utiladminmeio, cod, utilNIF, logcodadmin , admincod;
	float bat, aut, cust, utilsaldo,adicionarsaldo;
	char nickname[20], password[20], tipo[20], geocod[50],adminnome[20],adminsenha[20],utilnome[60],utilmorada[100];
	//parte de leitura dos ficheiros com os dados dos meios,utilizadores e admins
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
	while(login <= 3 && login > 0){//inicio do programa, no qual pergunta se quer fazer login como admin ou util, se login for 0, acaba o programa
		
		if(login == 3){//se login for 3, ele volta para o inicio do programa
			printf("Deseja fazer login como:\n1- Admin\n2- Utilizador\n0- Encerrar programa\n");
			scanf("%d", &login);
			system("cls");
			alreadylogged = 0;//alreadylogged serve na parte de login de util ou admin, por isso a necessidade de começar como 0 depois de escolher
		}
			

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				//Parte dos admins
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


		else if (login == 1) {
			if(!(alreadylogged)){//enquanto alreadylogged for igual a 0, ele pede sempre para escrever o codigo e senha
			printf("Bem-vindo Administrador! Por favor faca login.\n");
			printf("Codigo: ");
			scanf("%d", &logcodadmin);
			printf("Senha: ");
			scanf("%s", password);
			alreadylogged = 1;
			}
			system("cls");
			if (!(checkloginadmin(admins, logcodadmin, password))) {//verificação do login, se estiver errado retorna erro e o alreadylogged volta a 0 fazendo assim pedir o codigo e senha de novo
				printf("ERRO! Codigo ou senha errados!");
				alreadylogged = 0;
			}
			else{
				exec = 1;
				while (exec) {//exec serve para a parte de funções dos utilizadores e administradores
					printf("O que deseja fazer?\n1- Registar novo utilizador, administrador ou meio\n2- Remocao de um utilizador, administrador ou meio\n");
					printf("3- Alteracao da informacao de um utilizador, administrador ou meio\n4- Listar dados\n5- Terminar sessao\n");
					scanf("%d", &choice);
					system("cls");//Questiona o admin o que quer fazer

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
							//verifica se os dados estão corretos
							//se não existe o NIF e se este está com 9 digitos
							if (!(existeUtil(utils, utilNIF)) && utilNIF > 99999999 && utilNIF < 1000000000) {
								utils = inserirUtils(utils, utilnome, utilNIF, utilmorada, utilsaldo);
								printf("Adicionado com sucesso! ");
							}
							else {
								printf("ERRO DE DIGITACAO ENCONTRADO OU NIF JA EXISTENTE!\n");
							}
						}

						else if (utiladminmeio == 2) {//administrador
							printf("Codigo:\n");
							scanf("%d", &admincod);
							printf("\nNome de usuario: \n");
							getchar();
							gets(adminnome);
							printf("\nSenha:\n");
							scanf("%s", &adminsenha);
							system("cls");
							if (!(existeAdmin(admins, admincod))) {//Se não existir o codigo adiciona
								admins = inserirAdmins(admins, admincod, adminnome, adminsenha);
								printf("Adicionado com sucesso! ");
							}
							else {
								printf("ERRO DE DIGITACAO ENCONTRADO OU CODIGO JA EXISTENTE!\n");
							}
						}

						else if (utiladminmeio == 3) {//meio
							printf("Codigo\n");
							scanf("%d",&cod);
							printf("\nTipo: (trotinete/bicicleta)\n");
							bool = 1;
							while (bool) {
								scanf("%s", tipo);//impede erros de escrita, ajudando assim se necessitar que pesquisar pelo nome, não haver problemas
								if ( (!(strcmp(tipo, "trotinete")) || !(strcmp(tipo, "bicicleta"))))
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
							//verifica se já existe um meio com esse codigo e se todos os numeros são maiores ou igual a 0
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
							printf("Digite o codigo de usuario:");
							scanf("%d", &cod);
							admins = removerAdmins(admins, cod);
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
							printf("Digite o codigo do administrador de quem quer mudar as informacoes: ");
							scanf("%d", &admincod);
							mudarAdmins(admins, admincod);
						}
						else if (utiladminmeio == 3) {//meio
							printf("Digite o codigo do meio de que quer mudar as informacoes: ");
							scanf("%d", &cod);
							mudarMeios(meios,cod);
						}
					}


					else if (choice == 4) {//Lista toda a informação
						listarmeios(meios);
						listarutil(utils);
						listaradmins(admins);
					}


					//Logout
					else if (choice == 5) {
						alreadylogged = 0;//serve para obrigar a fazer login, se escolher 
						login = 3;//login a 3 para perguntar se quer fazer login como admin ou util
						exec = 0;//exec a 0 para terminar o loop while
					}

					//No final de uma operação, pergunta se quer fazer mais alguma coisa, senão, envia para a escolha de login
					if(choice < 5){
						printf("Deseja realizar outra operacao? (1/0)\n");
						scanf("%d", &exec);
						if (exec <= 0){//se digitar 0, acaba a sessão, e volta ao inicio da função
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
			if (!(alreadylogged)) {//mesma ideia da parte dos admins
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
				while (exec) {//mesma ideia dos admins
					printf("O que deseja fazer?\n1- Ver e adicionar saldo\n2- Ver todos os meios\n3- Ver os meios num geocodigo\n4- Alugar meio\n5- Terminar sessao\n");
					scanf("%d", &choice);
					system("cls");

					//ver Saldo
					if (choice == 1) {
						verificarsaldo(utils, utilNIF,NULL, NULL, 0, 0,NULL);//NULL serve para as variaveis presentes na função que não vao ser precisas e o primeiro 0 serve para dizer que não é para adicionar saldo
						printf("Quer adicionar saldo? (1/0)\n");
						scanf("%f", &adicionarsaldo);
						if (adicionarsaldo){
							printf("Digite o valor a adicionar:\n");
							scanf("%f", &adicionarsaldo);
							verificarsaldo(utils, utilNIF, NULL, NULL, 1, adicionarsaldo, NULL);
						}
					}

					//ver meios
					else if (choice == 2) {//lista todos os meios
						printf("Os meios existentes são:\n");
						listarmeios(meios);
					}

					else if (choice == 3) {//lista os meios pertencentes a um geocodigo
						printf("Escreva o geocodigo:");
						scanf("%s", geocod);
						printf("Os meios no geocodigo existentes sao:\n");
						listarmeiosgeocod(meios, geocod);
					}

					else if (choice == 4) {//parte para alugar meio
						printf("Escreva o codigo do meio:");
						scanf("%d", &cod);
						verificarsaldo(utils, utilNIF, meios, cod, NULL, 0, 1);//como o ultimo parametro está 1 ele vai saber que é pra verificar o saldo se é maior que o custo
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


	//FIM DO PROGRAMA

	printf("\n-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~Obrigado por utilizar nossos servicos!-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~\n");

	//parte no qual guarda todas as informação que foram adicionada, removidas ou alteradas ao longo do codigo
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