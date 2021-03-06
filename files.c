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
	FILE *f;

	fp = fopen("reservas.txt", "r");
	f = fopen("prereservas.txt", "r");

	if (fp != NULL) {
		while (fgets(input, MAX-1, fp) != NULL) {
			extrair_informacao_reservas(lista_reservas, input);
		}
		fclose(fp);
	}

	if (f != NULL) {
		while (fgets(input, MAX-1, f) != NULL) {
			extrair_informacao_prereservas(lista_pre, input);
		}	
		fclose(f);
	}	
}

void extrair_informacao_reservas(reservas lista_reservas, char input[]) {
	int i;
	int dia, mes, ano, hora, min;
	int counter = 0;
	char nome[MAX];
	
	dia = (input[2] - '0') * 10 + (input[3] - '0');

	mes = (input[5] - '0') * 10 + (input[6] - '0');

	ano = (input[8] - '0') * 1000 + (input[9] - '0') * 100 + (input[10] - '0') * 10 + (input[11] - '0');

	hora = (input[13] - '0') * 10 + (input[14] - '0');

	min = (input[16] - '0') * 10 + (input[17] - '0');

	for (i = 19; input[i] != 0; i++) {
		if(input[i]=='\n'){
			input[i]='\0';
		}
		nome[counter] = input[i];
		counter++;
	}
	printf("%d,%d,%d,%d,%d\n", dia, mes, ano, hora, min);
	insert_reserva(lista_reservas, input[0], dia, mes, ano, hora, min, nome);
}

void extrair_informacao_prereservas(prereservas lista_pre, char input[]) {
	int i;
	int dia; 
	int mes; 
	int ano;
	int hora; 
	int min;
	int dia_prereserva;
	int mes_prereserva;
	int ano_prereserva;
	int counter = 0;
	char nome[MAX];
	
	dia_prereserva = (input[2] - '0') * 10 + (input[3] - '0');
	mes_prereserva = (input[5] - '0') * 10 + (input[6] - '0');
	ano_prereserva = (input[8] - '0') * 1000 + (input[9] - '0') * 100 + (input[10] - '0') * 10 + (input[11] - '0');

	dia = (input[13] - '0') * 10 + (input[14] - '0');
	mes = (input[16] - '0') * 10 + (input[17] - '0');
	ano = (input[19] - '0') * 1000 + (input[20] - '0') * 100 + (input[21] - '0') * 10 + (input[22] - '0');
	hora = (input[24] - '0') * 10 + (input[25] - '0');
	min = (input[27] - '0') * 10 + (input[28] - '0');

	for (i = 30; input[i] != 0; i++) {
		if(input[i]=='\n'){
			input[i]='\0';
		}
		nome[counter] = input[i];
		counter++;
	}
	nome[counter] = '\0';

	insert_pre_reserva(lista_pre, input[0], dia_prereserva, mes_prereserva, ano_prereserva, nome, dia, mes, ano, hora, min);
}

void por_no_ficheiro_reservas(reservas lista) {
	FILE *fp;
	reservas aux = lista->next;

	fp = fopen("reservas.txt", "w");
	while(aux!=NULL) {
		fprintf(fp, "%c %02d %02d %04d %02d %02d %s\n", aux->op, aux->dia, aux->mes, aux->ano, aux->hora, aux->min, aux->nome);
		aux=aux->next;
	}
	fclose(fp);
}

void por_no_ficheiro_prereserva(prereservas lista) {
	FILE *fp;
	prereservas aux = lista->next;

	fp = fopen("prereservas.txt", "w");
	while(aux!=NULL) {
		fprintf(fp, "%c %02d %02d %04d %02d %02d %04d %02d %02d %s\n", aux->op, aux->dia_prereserva, aux->mes_prereserva, aux->ano_prereserva, aux->dia, aux->mes, aux->ano, aux->hora, aux->min, aux->nome);
		aux = aux -> next;
	}
	fclose(fp);
}

