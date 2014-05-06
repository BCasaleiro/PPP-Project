#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

void print_informacao(void);
void imprimir(char input[]);

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
		imprimir(input);
		contador++;
	}

	fclose(fp);
}

void imprimir(char input[]) {

	int i;
	int dia, mes, ano, hora, minutos;
	int counter = 0;
	char nome[MAX];
	char trabalho[MAX];
	char manu[] = "Manutencao";
	char lava[] = "Lavagem";
	
	
	dia = (input[2] - '0') * 10 + (input[3] - '0');

	mes = (input[5] - '0') * 10 + (input[6] - '0');

	ano = (input[8] - '0') * 10 + (input[9] - '0');

	hora = (input[11] - '0') * 10 + (input[12] - '0');

	minutos = (input[14] - '0') * 10 + (input[15] - '0');

	for (i = 17; input[i] != '\n'; ++i) {
		nome[counter] = input[i];
		counter++;
	}

	if (input[0] == 'M')
		//lista_manutençao(dia, mes, ano, hora, minutos, nome)
	else 
		//lista_lavagem(dia, mes, ano, hora, minutos, nome)

	//printf("Têm agendado uma %s para as %d:%d do dia %d/%d/%d em nome de %s.\n", trabalho, hora, minutos, dia, mes, ano, nome);
}
