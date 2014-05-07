#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 101

void print_informacao(void);
void extrair_informacao(char input[]);
void por_no_ficheiro(char op, int dia, int mes, int ano, int hora, int min, char nome[]);
void por_na_prereserva(char op, int dia, int mes, int ano, char nome[]);

int main() {

	print_informacao();

	return 0;
}

void print_informacao(void) {

	int contador = 0;
	char input[MAX];

	FILE *fp;
	fp = fopen("teste.txt", "r");

	while (contador < 2) {
		fgets(input, 50, fp);
		extrair_informacao(input);
		contador++;
	}

	fclose(fp);
}

void extrair_informacao(char input[]) {

	int i;
	int dia, mes, ano, hora, min;
	int counter = 0;
	char nome[MAX];
	char trabalho[MAX];
	
	
	dia = (input[2] - '0') * 10 + (input[3] - '0');

	mes = (input[5] - '0') * 10 + (input[6] - '0');

	ano = (input[8] - '0') * 10 + (input[9] - '0');

	hora = (input[11] - '0') * 10 + (input[12] - '0');

	min = (input[14] - '0') * 10 + (input[15] - '0');

	for (i = 17; input[i] != 0; ++i) {
		nome[counter] = input[i];
		counter++;
	}

	// "return" do dia mes ano hora min e nome guardado por linha"

	/*if (input[0] == 'M')
		lista_manutençao(dia, mes, ano, hora, min, nome)
	else 
		lista_lavagem(dia, mes, ano, hora, min, nome)*/

}


void por_no_ficheiro(reservas lista) {

	FILE *fp;

	fp = fopen("teste.txt", "a");

	fprintf(fp, "%c %02d %02d %02d %02d %02d %s", lista->op, lista->dia, lista->mes, lista->ano, lista->hora, lista->min, lista->nome);

	fclose(fp);

}

void por_na_prereserva(reservas lista) {

	FILE *fp;

	fp = fopen("teste.txt", "a");

	fprintf(fp, "%c %02d %02d %02d %s", lista->op, lista->dia, lista->mes, lista->ano, lista->nome);

	fclose(fp);

}

