#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ficheiroslistas.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//						Criação e guardar o grafo
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Grafo* pegarregistografo(Grafo* inicio, FILE* bin) {
	char linha[200];
	char* token;
	int i = 0;
	Grafo* vertices = NULL;

	while ((fgets(linha, 200, bin) != NULL)) {
		if (i == 0) {// i serve para verificar se é a primeira linha, pois esta linha é a que tem o geocodigo dos vertices

			int len = strlen(linha); // para remover o \n no final da linha, pega o tamanho da string
			if (linha[len - 1] == '\n') {
				linha[len - 1] = '\0';
				if(linha[len - 2] == '\r')
					linha[len - 2] = '\0';
			}

			token = strtok(linha, ";");
			while (token != NULL) {
				Grafo* novo = malloc(sizeof(struct registovertices));
				strcpy(novo->geocodigo, token);
				novo->adjacente = NULL;
				novo->meios = NULL;
				novo->utils = NULL;
				token = strtok(NULL, ";");
				novo->seguinte = inicio;
				inicio = novo;
			}

			vertices = inicio;
			i = 1;
		}
		else {

			int len = strlen(linha); // para remover o \n no final da linha
			if (linha[len - 1] == '\n') {
				linha[len - 1] = '\0';
				if (linha[len - 2] == '\r')
					linha[len - 2] = '\0';
			}

			token = strtok(linha, ";");
			while (!(strcmp(vertices->geocodigo, token)) != 1) {
				vertices = vertices->seguinte;
			}

			token = strtok(NULL, ";");
			while (token != NULL) {
				Adjacentes* novo = malloc(sizeof(struct registoadjacentes));
				strcpy(novo->geocodigo, token);
				token = strtok(NULL, ";");
				novo->peso = atof(token); //atof serve para converter string para float
				novo->seguinte = vertices->adjacente;
				vertices->adjacente = novo;
				token = strtok(NULL, ";");
			}

			vertices = inicio;
		}
	}

	return inicio;

}

void escrevergrafo(Grafo* inicio, FILE* bin) {
	int i = 0; // escrever na primeira linha o nome dos vertices
	Grafo* aux = inicio;
	if (bin != NULL) {
		while (inicio != NULL) {
			if (inicio->seguinte != NULL) {
				fprintf(bin, "%s;", inicio->geocodigo);
			}
			else {
				fprintf(bin, "%s\n", inicio->geocodigo);
			}
			inicio = inicio->seguinte;
		}
		inicio = aux;
		while (inicio != NULL) {
			if (inicio->adjacente != NULL) {
				fprintf(bin,"%s;", inicio->geocodigo);
				while (inicio->adjacente != NULL) {
					if (inicio->adjacente->seguinte != NULL) {
						fprintf(bin, "%s;%.2f;", inicio->adjacente->geocodigo, inicio->adjacente->peso);
					}
					else {
						fprintf(bin, "%s;%.2f\n", inicio->adjacente->geocodigo, inicio->adjacente->peso);
					}
					inicio->adjacente = inicio->adjacente->seguinte;
				}
			}
			inicio = inicio->seguinte;

		}
	}
	else
		printf("Erro na execucao do ficheiro");
}

int verificargeocodigo(Grafo* grafo, char* geocodigo) {
	while (grafo != NULL) {
		if (!(strcmp(grafo->geocodigo, geocodigo))) return 1;
		grafo = grafo->seguinte;
	}
	return 0;
}

Grafo* criarvertice(Grafo* inicio, char* geocodigo) {
	Grafo* novo = malloc(sizeof(struct registovertices));
	strcpy(novo->geocodigo, geocodigo);
	novo->adjacente = NULL;
	novo->meios = NULL;
	novo->utils = NULL;
	novo->seguinte = inicio;
	inicio = novo;
	return inicio;
}

int adicionaradjacentes(Grafo* grafo, char* geocodigo, char* geocodigoadj, float peso) {
	int bool;
	bool = verificargeocodigo(grafo, geocodigoadj);
	if (!(bool)) return 1; // se o vertice nao existir, acaba a função

	while ((grafo != NULL) && strcmp(grafo->geocodigo, geocodigo)) {
		grafo = grafo->seguinte;
	}
	Adjacentes* verificador = grafo->adjacente;// verificador para ver se já é adjacente
	while (((verificador != NULL) && strcmp(verificador->geocodigo, geocodigoadj))){
		verificador = verificador->seguinte;
	}
	if (verificador != NULL) return 1;

	Adjacentes* novo = malloc(sizeof(struct registoadjacentes));
	strcpy(novo->geocodigo, geocodigoadj);
	novo->peso = peso;
	novo->seguinte = grafo->adjacente;
	grafo->adjacente = novo;
	return 0;

}

// Meios

void fixarmeiosvertices(Meio* iniciomeio, Grafo* iniciografo) {
	Grafo* vertices = iniciografo;
	Meio* meioanterior;
	while (vertices != NULL) { // para libertar as listas anteriormentes criadas, depois de alguma alteração do geocodigo de um meio
		while (vertices->meios != NULL) {
			meioanterior = vertices->meios;
			vertices->meios = vertices->meios->seguinte;
			free(meioanterior);
		}
		vertices = vertices->seguinte;
	}
	vertices = iniciografo;
	while (iniciomeio != NULL) {
		while (strcmp(vertices->geocodigo, iniciomeio->geocodigo)) {
			vertices = vertices->seguinte;
		}
		if (vertices != NULL) {
			Meio* novomeio = malloc(sizeof(struct registomeio));
			novomeio->custo = iniciomeio->custo;
			novomeio->codigo = iniciomeio->codigo;
			novomeio->bateria = iniciomeio->bateria;
			novomeio->autonomia = iniciomeio->autonomia;
			novomeio->alugado = iniciomeio->alugado;
			strcpy(novomeio->tipo, iniciomeio->tipo);
			strcpy(novomeio->geocodigo, iniciomeio->geocodigo);
			novomeio->seguinte = vertices->meios;
			vertices->meios = novomeio;
		}
		vertices = iniciografo;
		iniciomeio = iniciomeio->seguinte;
	}

}


void removermeiovertice(Grafo* grafo,Meio* meio, int cod) {
	Meio* anterior, * atual, * aux;
	while ((meio != NULL) && (meio->codigo != cod))//ir até o codigo ser igual
	{
		meio = meio->seguinte;
	}
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) {//ir até o geocodigo corresponder
		grafo = grafo->seguinte;
	}
	//nao necessita verificação se grafo é null pois temos sempre a certeza que existe um vertice com esse geocodigo
	atual = grafo->meios;
	anterior = grafo->meios;
	aux = grafo->meios;
	if (atual->codigo == cod) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		grafo->meios = aux;
	}
	else
	{

		while ((atual != NULL) && (atual->codigo != cod))//ir avançando na lista, até ser igual.
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(grafo->meios);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			grafo->meios = aux;
		}
	}

}

void mudarcodmeiovertice(Grafo* grafo, Meio* meio, int codnovo) {
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	grafo->meios->codigo = codnovo;
	grafo->meios = aux;
}

void mudartipomeiovertice(Grafo* grafo, Meio* meio, char* tipo){
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	strcpy(grafo->meios->tipo, tipo);
	grafo->meios = aux;
}

void mudarbatvertice(Grafo* grafo, Meio* meio, float valor) {
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	grafo->meios->bateria = valor;
	grafo->meios = aux;
}


void mudarautvertice(Grafo* grafo, Meio* meio, float valor) {
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	grafo->meios->autonomia = valor;
	grafo->meios = aux;
}


void mudarcustvertice(Grafo* grafo, Meio* meio, float valor) {
	Meio* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, meio->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->meios;
	while ((grafo->meios != NULL) && (grafo->meios->codigo != meio->codigo)) grafo->meios = grafo->meios->seguinte;
	grafo->meios->custo = valor;
	grafo->meios = aux;
}

//utilizadores


void mudargeocodutil(Utilizadores* inicio,int NIF, char* geocod) {
	while ((inicio != NULL) && (inicio->NIF != NIF)) inicio = inicio->seguinte;
	strcpy(inicio->geocodigo, geocod);
}


void fixarutilsvertices(Utilizadores* inicioutils, Grafo* iniciografo) {
	Grafo* vertices = iniciografo;
	Utilizadores* utilanterior;
	while (vertices != NULL) { // para libertar as listas anteriormentes criadas, depois de alguma alteração do geocodigo de um meio
		while (vertices->utils != NULL) {
			utilanterior = vertices->utils;
			vertices->utils = vertices->utils->seguinte;
			free(utilanterior);
		}
		vertices = vertices->seguinte;
	}
	vertices = iniciografo;
	while (inicioutils != NULL) {
		while (strcmp(vertices->geocodigo, inicioutils->geocodigo)) {
			vertices = vertices->seguinte;
		}
		if (vertices != NULL) {
			Utilizadores* novoutil = malloc(sizeof(struct registoutil));
			novoutil->NIF = inicioutils->NIF;
			novoutil->saldo = inicioutils->saldo;
			strcpy(novoutil->nome, inicioutils->nome);
			strcpy(novoutil->morada, inicioutils->morada);
			strcpy(novoutil->geocodigo, inicioutils->geocodigo);
			novoutil->seguinte = vertices->utils;
			vertices->utils = novoutil;
		}
		vertices = iniciografo;
		inicioutils = inicioutils->seguinte;
	}
}

void removerutilvertice(Grafo* grafo, Utilizadores* util, int NIF) {
	Utilizadores* anterior, * atual, * aux;
	while ((util != NULL) && (util->NIF != NIF))//ir até o codigo ser igual
	{
		util = util->seguinte;
	}
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, util->geocodigo))) {//ir até o geocodigo corresponder
		grafo = grafo->seguinte;
	}
	//nao necessita verificação se grafo é null pois temos sempre a certeza que existe um vertice com esse geocodigo
	atual = grafo->utils;
	anterior = grafo->utils;
	aux = grafo->utils;
	if (atual->NIF == NIF) // remoção do 1º registo
	{
		aux = atual->seguinte;
		free(atual);
		grafo->utils = aux;
	}
	else
	{

		while ((atual != NULL) && (atual->NIF != NIF))//ir avançando na lista, até ser igual.
		{
			anterior = atual;
			atual = atual->seguinte;
		}
		if (atual == NULL) return(grafo->utils);
		else
		{
			anterior->seguinte = atual->seguinte;
			free(atual);
			grafo->utils = aux;
		}
	}

}


void mudarnomeutilvertice(Grafo * grafo, Utilizadores * util, char* nome){
	Utilizadores* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, util->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->utils;
	while ((grafo->utils != NULL) && (grafo->utils->NIF != util->NIF)) grafo->utils = grafo->utils->seguinte;
	strcpy(grafo->utils->nome, nome);
	grafo->utils = aux;

}

void mudarmoradavertice(Grafo* grafo, Utilizadores* util, char* morada) {
	Utilizadores* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, util->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->utils;
	while ((grafo->utils != NULL) && (grafo->utils->NIF != util->NIF)) grafo->utils = grafo->utils->seguinte;
	strcpy(grafo->utils->morada, morada);
	grafo->utils = aux;
}

void mudarNIFvertice(Grafo* grafo, Utilizadores* util, int NIF) {
	Utilizadores* aux;
	while ((grafo != NULL) && (strcmp(grafo->geocodigo, util->geocodigo))) grafo = grafo->seguinte;
	aux = grafo->utils;
	while ((grafo->utils != NULL) && (grafo->utils->NIF != util->NIF)) grafo->utils = grafo->utils->seguinte;
	grafo->utils->NIF = NIF;
	grafo->utils = aux;
}

/// comandos gerais de caminhos ///

Grafo* pegarorigem(Grafo* grafo, char* origem) { // pega a origem na lista dos grafos
	while (strcmp(grafo->geocodigo, origem)) {
		grafo = grafo->seguinte;
	}
	return grafo;
}

int visitado(Pilha* sequencia, char* geocodigo) { // verifica numa lista se um determinado geocodigo já foi visitado, se sim, retorna 1, se não, retorna 0
	int i;
	while (sequencia != NULL) {
		if (!strcmp(sequencia->geocodigo, geocodigo)) {
			return(1);
		}
		sequencia = sequencia->seguinte;
	}
	return(0);
}

Pilha* colocarsequencia(Pilha* sequencia, char* geocodigo) { // guarda no final de uma lista (caminho) um geocodigo
	Pilha* sequenciaincio = sequencia;
	if (sequencia == NULL) {
		Pilha* sequencianovo = malloc(sizeof(struct pilhageocodigo));
		sequencianovo->seguinte = NULL;
		strcpy(sequencianovo->geocodigo, geocodigo);
		sequencia = sequencianovo;
		return sequencia;
	}
	else {
		while (sequencia->seguinte != NULL) {
			sequencia = sequencia->seguinte;
		}
		Pilha* sequencianovo = malloc(sizeof(struct pilhageocodigo));
		strcpy(sequencianovo->geocodigo, geocodigo);
		sequencianovo->seguinte = NULL;
		sequencia->seguinte = sequencianovo;
	}

	return sequenciaincio;
}

Pilha* copiarpilha(Pilha* sequencianova, Pilha* sequencia) { // copia uma lista para outra
	Pilha* aux = NULL;
	if (sequencia != NULL) {
		while (sequencia != NULL) {
			Pilha* sequencianovo = malloc(sizeof(struct pilhageocodigo));
			strcpy(sequencianovo->geocodigo, sequencia->geocodigo);
			sequencianovo->seguinte = NULL;
			if (sequencianova == NULL) {
				sequencianova = sequencianovo;
				aux = sequencianova;
				sequencia = sequencia->seguinte;
			}
			else {
				while (sequencianova->seguinte != NULL) {
					sequencianova = sequencianova->seguinte;
				}
				sequencianova->seguinte = sequencianovo;
				sequencianova = aux;
				sequencia = sequencia->seguinte;
			}
		}
	}
	return sequencianova;
}

/// listagem dos meios por raio ///


//função para calcular todos os caminhos possiveis de um vertice e listar os meios que estao pelo caminho
void listarMeiosPeso(Grafo* grafo, int NIF, Utilizadores* inicio, char* tipo, float PesoLimite) {
	Pilha* sequencia = NULL;
	while (inicio->NIF != NIF) inicio = inicio->seguinte;
	listarMeiosAuxpeso(grafo, inicio->geocodigo, tipo, sequencia, 0, PesoLimite);

}

void listarMeiosAuxpeso(Grafo* grafo, char* origem, char* tipo, Pilha* sequencia, float pesoTotal, float PesoLimite) {
	Grafo* inicio = grafo;
	Adjacentes* auxadj;
	grafo = pegarorigem(grafo, origem); // pega o vertice de onde está 
	if (PesoLimite < pesoTotal) {
		return; // retorna para o vertice anterior se o peso do caminho for maior que o limite
	}
	else {
		if (!visitado(sequencia, origem)) { // verifica se já passamos por esse vertice
			sequencia = colocarsequencia(sequencia, grafo->geocodigo); // se nao passamos coloca na sequencia (caminho)
			printf("Geocodigo local:%s\n", grafo->geocodigo);//mostra a origem
			listarmeiostipo(grafo->meios, tipo);//lista os vertices nessa origem
		}

		auxadj = grafo->adjacente; // loop para avançar para os vertices adjacentes
		while (auxadj != NULL) {
			grafo = inicio;
			listarMeiosAuxpeso(grafo, auxadj->geocodigo, tipo, sequencia, pesoTotal + auxadj->peso, PesoLimite);
			auxadj = auxadj->seguinte;
		}
	}
}


// Caixeiro Viajante //
//função principal para a solução do caixeiro viajante, apresenta os caminhos necessarios a ser feitos para 
void listarCaminhobateria(Grafo* grafo, char* origembase, char* tipo) {
	float peso = 0, auxpeso = 0;
	int caminhaopeso = 0;
	Pilha* verticesbat = NULL;
	Listapilhas* listapilhas = NULL, * idamenor = NULL;
	char* origem = origembase, * destino;
	verticesbat = pegarverticesbateria(grafo, tipo);

	if (verticesbat == NULL) {//nao existe meios desse tipo com menos de 50% de bateria
		printf("Nao existe vertices com bateria abaixo de 50");
		return;
	}
	else {
		destino = verticesbat->geocodigo;
		while (verticesbat != NULL) {

			listapilhas = listarcaminhorapidoaux(grafo, origem, destino, NULL, 0.0, listapilhas);// pega todos os caminhos possiveis da origem até o destino

			idamenor = verificarmenor(listapilhas);//pega o caminho com menor peso
			//verificamos se existe um caminho da origem ao destino
			if (idamenor == NULL) {//se for NULL significa que nao existe caminho da origem ao destino, tentamos ir para a base
				printf("Não foi possivel encontrar um caminho possivel de %s a %s!\n", origem, destino);
				if (origem != origembase) { // se já estiver na base nao precisa procurar o caminho da base até a base
					listapilhas = listarcaminhorapidoaux(grafo, origem, origembase, NULL, 0.0, listapilhas);
					idamenor = verificarmenor(listapilhas);
					if (idamenor == NULL) {/// significa que nao é possivel voltar para atras
						printf("Não foi possivel encontrar um caminho possivel de %s ate a base(%s)!\n", origem, origembase);
					}
					else {///se foi para a base, procura o caminho da base ao destino
						caminhaopeso = 0;
						listapilhas = listarcaminhorapidoaux(grafo, origembase, destino, NULL, 0.0, listapilhas);
						idamenor = verificarmenor(listapilhas);
						if (idamenor == NULL) {//se nao foi possivel encontrar um caminho da base até o destino, mostra a mensagem
							printf("Nao foi possivel encontrar uma caminho da base(%s) ate %s!\n", origembase, destino);
						}
					}
				}
			}
			//depois de verificar se existe caminhos partimos para a parte do caminhao
			if (idamenor != NULL) {// verificamos se e diferente de NULL para que realize a parte da capacidade do caminhao se houver caminho

				listarcaminho(idamenor);
				printf("Peso: %.2f\n", idamenor->peso);
				peso += idamenor->peso;
				caminhaopeso += nbatvertices(grafo, destino, tipo);//pega a quantidade de meios no vertice
				if (caminhaopeso > 5) {// se estiver cheio
					printf("\nCaminhao cheio!\n");

					listapilhas = limparpilha(listapilhas);//limpa-se a lista de pilhas para que nao fique salvo qualquer valor que possa prejudicar a procura do menor caminho do seguinte

					listapilhas = listarcaminhorapidoaux(grafo, destino, origembase, NULL, 0.0, listapilhas);//pega o caminho até a base
					idamenor = verificarmenor(listapilhas);

					if (idamenor != NULL) {// verifica se existe
						listarcaminho(idamenor);
						printf("Peso: %.2f\n", idamenor->peso);
						auxpeso = idamenor->peso;//auxilicar para pegar o peso até base

						listapilhas = limparpilha(listapilhas);

						listapilhas = listarcaminhorapidoaux(grafo, origembase, destino, NULL, 0.0, listapilhas);//pega o caminho até a base
						idamenor = verificarmenor(listapilhas);

						if (idamenor != NULL) {// verifica se existe caminho da base ao destino
							listarcaminho(idamenor);
							printf("Peso: %.2f\n", idamenor->peso);
							if (caminhaopeso % 5 == 0) {// se o numero de meios for divisivel por cinco, ele vai parar na base
								printf("Precisa realizar um ciclo entre %s e %s %d vezes e acabara em %s\n\n", destino, origembase, (caminhaopeso / 5), origembase);
								for (int i = 0; i <= (caminhaopeso / 5) - 1; i++) peso += idamenor->peso;//menos 1 pois nao faz o caminho de volta
								for (int i = 0; i <= (caminhaopeso / 5); i++) peso += auxpeso;
								caminhaopeso = 0;
							}
							else {//se nao for, vai entregar, e ao voltar, vai ficar com o resto da divisão de numero de vertices.
								printf("\n\nPrecisa realizar um ciclo entre %s e %s %d vezes e acabara em %s\n\n", destino, origembase, (caminhaopeso / 5), destino);
								for (int i = 0; i <= (caminhaopeso / 5); i++) peso += idamenor->peso;
								for (int i = 0; i <= (caminhaopeso / 5); i++) peso += auxpeso;
								caminhaopeso = (caminhaopeso % 5);
							}
						}
						else {
							printf("E possivel ir para a base(%s) mas nao e possivel voltar ao destino (%s)", origembase, destino);
						}
					}
					else {
						printf("O caminhao esta cheio e nao tem como voltar para a base!\n");
					}
				}
			}
			// parte para definir a origem e destino do proximo loop
			if (idamenor != NULL) {// se foi possivel encontrar um caminho

				listapilhas = limparpilha(listapilhas);

				if (caminhaopeso == 0) origem = origembase;// verificar se foi para a base com 0 de peso de caminhao
				else origem = verticesbat->geocodigo;
				verticesbat = verticesbat->seguinte;
				destino = verticesbat->geocodigo;
			}
			else {
				origem = origembase;
				verticesbat = verticesbat->seguinte;
				destino = verticesbat->geocodigo;
			}
		}

		if (strcmp(origem,origembase)) {// quando acaba a lista de vertices, precisamos criar o caminho de volta para a base
			listapilhas = listarcaminhorapidoaux(grafo, origem, origembase, NULL, 0.0, listapilhas);// pega todos os caminhos possiveis da origem até á base
			idamenor = verificarmenor(listapilhas);//pega o caminho com menor peso
			//verificamos se existe um caminho da origem ao destino
			if (idamenor == NULL) {//se for NULL significa que nao existe caminho da origem ao destino, tentamos ir para a base
				printf("Não foi possivel encontrar um caminho possivel de %s a %s!\n", origem, origembase);
			}
			else{ 
				listarcaminho(idamenor);
				printf("Peso: %.2f\n", idamenor->peso);
				peso += idamenor->peso; 
				listapilhas = limparpilha(listapilhas);
			}

		}
		printf("\nPeso total:%.2f\n", peso);
	}
}

/////////////////////////// Calculo do caminho mais rapido //////////////////////////////////////////////////


Listapilhas* listarcaminhorapidoaux(Grafo* grafo, char* origem, char* destino, Pilha* sequencia, float pesoTotal, Listapilhas* listacaminhos) {//pega todos os caminhos possiveis de um ponto ao outro
	Grafo* inicio = grafo;
	Adjacentes* aux;
	Pilha* sequencianova = NULL;
	Pilha* auxfree1 = NULL;
	Pilha* auxfree2 = NULL;
	grafo = pegarorigem(grafo, origem);
	sequencianova = copiarpilha(sequencianova, sequencia);
	sequencianova = colocarsequencia(sequencianova, grafo->geocodigo);
	if (!(strcmp(grafo->geocodigo, destino))) {
		listacaminhos = guardarcaminho(sequencianova, listacaminhos, pesoTotal);
		return listacaminhos;
	}
	else {
		aux = grafo->adjacente;
		while (aux != NULL) {
			if (!visitado(sequencianova, aux->geocodigo)) {
				grafo = inicio;
				listacaminhos = listarcaminhorapidoaux(grafo, aux->geocodigo, destino, sequencianova, pesoTotal + aux->peso, listacaminhos);
			}
			aux = aux->seguinte;
		}
	}

	while (sequencianova != NULL) {
		auxfree1 = sequencianova;
		auxfree2 = sequencianova->seguinte;
		free(auxfree1);
		sequencianova = auxfree2;
	}

	return listacaminhos;
}
//funcao para guardar caminhos encontrados pela funcao listarcaminhorapidoaux
Listapilhas* guardarcaminho(Pilha* caminho, Listapilhas* listacaminho, float peso) {
	Listapilhas* novo = malloc(sizeof(struct guardarpilhas));//alocação de memoria para um novo meio

	if (novo != NULL)
	{
		novo->pilha = caminho;
		novo->peso = peso;
		novo->seguinte = listacaminho;
		return novo;
	}
	return listacaminho;
}

//numa lista do tipo Listapilhas, procura o elemento com menor peso
Listapilhas* verificarmenor(Listapilhas* caminhos) {
	Listapilhas* aux = caminhos;
	if (caminhos == NULL) {
		return NULL;
	}
	float pesomenor = caminhos->peso;
	while (caminhos != NULL) {
		if (pesomenor > caminhos->peso) {
			aux = caminhos;
			pesomenor == caminhos->peso;
		}
		caminhos = caminhos->seguinte;
	}
	return aux;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////

int nbatvertices(Grafo* grafo, char* destino, char* tipo) {
	int n = 0;
	Pilha* sequencia = NULL;
	Meio* auxmeios;
	while (grafo != NULL && strcmp(grafo->geocodigo, destino)) {
		grafo = grafo->seguinte;
	}

	auxmeios = grafo->meios;
	while (auxmeios != NULL)
	{
		if (auxmeios->bateria < 50 && !(strcmp(auxmeios->tipo, tipo))) {
			n++;
		}
		auxmeios = auxmeios->seguinte;
	}
	return n;
}

Pilha* pegarverticesbateria(Grafo* grafo, char* tipo) {
	int booliano;
	Pilha* sequencia = NULL;
	Meio* auxmeios;
	while (grafo != NULL) {
		auxmeios = grafo->meios;
		booliano = 1;
		while (auxmeios != NULL && booliano)
		{
			if (auxmeios->bateria < 50 && !(strcmp(auxmeios->tipo, tipo))) {
				sequencia = colocarsequencia(sequencia, grafo->geocodigo);
				booliano = 0;
			}
			auxmeios = auxmeios->seguinte;
		}
		grafo = grafo->seguinte;
	}
	return sequencia;
}

//funcao para limpar os conteudos guardados na lista de pilhas
Listapilhas* limparpilha(Listapilhas* listapilhas) {
	Pilha* auxfree1 = NULL, * auxfree2 = NULL;
	Listapilhas* auxfreepilha1 = NULL, * auxfreepilha2 = NULL;
	while (listapilhas != NULL) {// limpar lista de pilhas para nao ocorrer problemas
		while (listapilhas->pilha != NULL) {
			auxfree1 = listapilhas->pilha;
			auxfree2 = listapilhas->pilha->seguinte;
			free(auxfree1);
			listapilhas->pilha = auxfree2;
		}
		auxfreepilha1 = listapilhas;
		auxfreepilha2 = listapilhas->seguinte;
		free(auxfreepilha1);
		listapilhas = auxfreepilha2;
	}
	return listapilhas;
}