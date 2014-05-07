#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "main.h"


int main(){
    reservas lista_reservas= create_reservas();
    prereservas lista_pre= create_pre_reservas();
    clear_screen();
    menu(lista_reservas, lista_pre);
    return 0;
}

void menu(reservas lista_reservas, prereservas lista_pre){
    int menu;
    do{
        printf("Menu:\n1- Reservar lavagem ou manutenção\n2- Cancelar reserva de lavagem ou manutenção\n3- Cancelar pré-reserva de lavagem ou manutenção\n4- Listar reservas e pré-reservas\n0- Sair\nO que fazer? ");
        scanf("%d", &menu); 
        getchar(); //eliminar o '\n' não lido pelo scanf
        switch(menu){
            case 0:
                clear_screen();
                printf("A terminar...\n");
                break;
            case 1:
                clear_screen();
                reserva(lista_reservas, lista_pre);
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

void reserva(reservas lista_reservas, prereservas lista_pre){
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
            op ='L';
            reservar(lista_reservas, lista_pre, op);
            break;
        case 2:
            clear_screen();
            printf("Reserva de Manutenção:\n");
            op = 'M';
            reservar(lista_reservas, lista_pre, op);
            break;
        default:
            clear_screen();
            printf("%d não é uma opção válida! A regressar ao menu principal...\n", menu);
    }

    
}

void reservar(reservas lista_reservas, prereservas lista_pre, char op){
    int flag=1;
    int reservado;
    int pre_reservado;
    char nome[MAX];
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    printf("Nome: ");
    fgets(nome, MAX-1, stdin);
    for (i = 0; nome[i] != 0; ++i) {
        if (nome[i] == '\n') {
            nome[i] = '\0';
        }
    }
    printf("Data (d-m-a): ");
    scanf("%d-%d-%d", &dia, &mes, &ano);
    //Verificação da disponibilidade desse dia, se nao houver 
    //reencaminhar para as pré reservas.
    if( /*Condição*/!1 ){
        pre_reservado= insert_pre_reserva(lista_pre, op, dia, mes, ano, nome);
        if(pre_reservado==0){
            clear_screen();
            printf("Pré-Reserva efectuada com sucesso!");
            return;
        } else {
            clear_screen();
            printf("Falha ao efectuar a pré-reserva!\n");
            return;
        }
    }
    //Se possivel indicar as horas disponiveis para esse dia
    do{
        printf("Hora (hh:mm): ");
        scanf("%d:%d", &hora, &min);
        if(hora>=8 && ((hora<=17 && min==0 && op=='M') || (hora==17 && min<=30 && op=='L')) && min>=0 && min<60){
            flag=0;
        } else {
            printf("%d:%d não é uma hora válida para reserva\n", hora, min);
        }
    }while(flag==1);
    reservado= insert_reserva(lista_reservas, op, dia, mes, ano, hora, min, nome);
    if(reservado==0){
        clear_screen();
        printf("Reserva efectuada com sucesso!\n");
    } else {
        clear_screen();
        printf("Falha ao efectuar a reserva!\n");
    }
}

void clear_screen(){
    system("clear");
}