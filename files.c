#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "files.h"



void print_informacao(reservas lista_reservas, prereservas lista_pre) {


	int contador = 0, linhas = 0;
	char c;
	char input[MAX];

	FILE *fp;
	fp = fopen("reservas.txt", "r");


	while (fgets(input, 50, fp) != NULL) {
		extrair_informacao_reservas(lista_reservas, input);
		contador++;
	}

	fclose(fp);

	
	FILE *f;
	f = fopen("reservas.txt", "r");

	while (fgets(input, 50, f) != NULL) {
		extrair_informacao_prereservas(lista_pre, input);
		contador++;
	}

	fclose(fp);


}

void extrair_informacao_reservas(reservas lista_reservas, char input[]) {

	int i;
	int dia, mes, ano, hora, min;
	int counter = 0;
	char nome[MAX];
	
	dia = (input[2] - '0') * 10 + (input[3] - '0');

	mes = (input[5] - '0') * 10 + (input[6] - '0');

	ano = (input[8] - '0') * 1000 + (input[9] - '0') * 100 + (input[10] - '0') * 10 + (input[11] - '0');

	hora = (input[14] - '0') * 10 + (input[15] - '0');

	min = (input[17] - '0') * 10 + (input[18] - '0');

	for (i = 20; input[i + 2] != 0; i++) {
		nome[counter] = input[i];
		counter++;
	}
	nome[counter] = '\0';

}

void extrair_informacao_prereservas(prereservas lista_pre, char input[]) {

	int i;
	int dia, mes, ano, hora, min;
	int counter = 0;
	char nome[MAX];
	
	dia = (input[2] - '0') * 10 + (input[3] - '0');

	mes = (input[5] - '0') * 10 + (input[6] - '0');

	ano = (input[8] - '0') * 1000 + (input[9] - '0') * 100 + (input[10] - '0') * 10 + (input[11] - '0');

	for (i = 13; input[i + 2] != 0; i++) {
		nome[counter] = input[i];
		counter++;
	}
	nome[counter] = '\0';

}


void por_no_ficheiro_reservas(reservas lista) {

	FILE *fp;
	reservas aux = lista->next;

	fp = fopen("reservas.txt", "w");
	while(aux!=NULL) {
		fprintf(fp, "%c %02d %02d %04d %02d %02d %s", lista->op, lista->dia, lista->mes, lista->ano, lista->hora, lista->min, lista->nome);
		aux=aux->next;
	}
	fclose(fp);

}

void por_no_ficheiro_prereserva(prereservas lista) {

	FILE *fp;
	prereservas aux = lista->next;

	fp = fopen("prereservas.txt", "a");

	while(aux!=NULL) {
		fprintf(fp, "%c %02d %02d %04d %s\n", lista->op, lista->dia, lista->mes, lista->ano, lista->nome);
		aux = aux -> next;
	}

	fclose(fp);

}

