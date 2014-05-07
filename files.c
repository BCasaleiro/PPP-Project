#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

#define MAX 101

void print_informacao(void);
void extrair_informacao_reservas(char input[]);
void extrair_informacao_prereservas(char input[]);
void por_no_ficheiro_reservas(reservas lista);
void por_no_ficheiro_prereserva(prereservas lista);
void por_na_prereserva(prereservas lista);

int main() {

	print_informacao();

	return 0;
}

void print_informacao(void) {

	int contador = 0, linhas = 0;
	char c;
	char input[MAX];

	FILE *fp;
	fp = fopen("reservas.txt", "r");


	while (fgets(input, 50, fp) != NULL) {
		extrair_informacao_reservas(input);
		contador++;
	}

	fclose(fp);
}

void extrair_informacao_reservas(char input[]) {

	int i;
	int dia, mes, ano, hora, min;
	int counter = 0;
	char nome[MAX];
	
	dia = (input[2] - '0') * 10 + (input[3] - '0');

	mes = (input[5] - '0') * 10 + (input[6] - '0');

	ano = (input[8] - '0') * 10 + (input[9] - '0');

	hora = (input[11] - '0') * 10 + (input[12] - '0');

	min = (input[14] - '0') * 10 + (input[15] - '0');

	for (i = 17; input[i + 2] != 0; i++) {
		nome[counter] = input[i];
		counter++;
	}
	
	nome[counter] = '\0';

}


void por_no_ficheiro_reservas(reservas lista) {

	FILE *fp;

	fp = fopen("reservas.txt", "a");

	fprintf(fp, "%c %02d %02d %02d %02d %02d %s", lista->op, lista->dia, lista->mes, lista->ano, lista->hora, lista->min, lista->nome);

	fclose(fp);

}

void por_no_ficheiro_prereserva(prereservas lista) {

	FILE *fp;

	fp = fopen("prereservas.txt", "a");

	fprintf(fp, "%c %02d %02d %02d %s\n", lista->op, lista->dia, lista->mes, lista->ano, lista->nome);

	fclose(fp);

}

