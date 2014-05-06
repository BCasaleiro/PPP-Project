#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(){
    reservas lista_reservas;
    prereservas lista_pre;
    menu(lista_reservas, lista_pre);
    return 0;
}

void menu(reservas lista_reservas, prereservas lista_pre){
    int menu;
    do{
        printf("Menu:\n1- Reservar lavagem ou manutenção\n2- Cancelar reserva de lavagem ou manutenção\n3- Cancelar pré-reserva de lavagem ou manutenção\n4-  Listar reservas e pré-reservas\n0- Sair\nO que fazer? ");
        scanf("%d", &menu); 
        getchar(); //eliminar o '\n' não lido pelo scanf
        switch(menu){
            case 0:
                clear_screen();
                printf("A terminar...\n");
                break;
            case 1:
                clear_screen();
                reservas();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            default:
                clear_screen();
                printf("%d não é uma opção valida!\n", menu);
        }
    }while(menu!=0);
}

void reservas(reservas lista_reservas, prereservas lista_pre){
    int menu;
    char op;
    printf("Reservar:\n1- Lavagem\n2- Manutenção\n0- Regressar ao menu principal\nO que reservar? ");
    scanf("%d", &menu);
    getchar(); //eliminar o '\n' não lido pelo scanf
    switch(menu){
        case 0:
            clear_screen();
            break;
        case 1:
            clear_screen();
            printf("Reserva de Lavagem:\n");
            char op='L';
            reservar(op);
            break;
        case 2:
            break;
        default:
            clear_screen();
            printf("%d não é uma opção válida! A regressar ao menu principal...\n", menu);
    }
}

void reservar(reservas lista_reservas, prereservas lista_pre, char op){
    int reservado;
    char nome[MAX];
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    printf("Nome: ");
    fgets(nome, MAX-1, stdin);
    printf("Data (d-m-a): ");
    scanf("%d-%d-%d", &dia, &mes, &ano);
    //Verificação da disponibilidade desse dia, se nao houver 
    //reencaminhar para as pré reservas.
    //Se possivel indicar as horas disponiveis para esse dia
    printf("Hora (hh:mm): ");
    scanf("%d:%d", &hora, &min);
    reservado= insert_reserva(lista_reservas, op, dia, mes, ano, hora, min, nome);
    if(reservado==0){
        clear_screen();
        printf("Reserva efectuada com sucesso!");
    } else {
        clear_screen();
        printf("Falha ao efectuar a reserva!\n");
    }
}

void pre_reservar(prereservas lista_pre, char op){

}

void clear_screen(){
    system("clear");
}