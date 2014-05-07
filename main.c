#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    int i;
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
    if(verifica_vaga(lista_reservas, op, dia, mes, ano)== 1){
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
        scanf("%02d:%02d", &hora, &min);
        if(hora>=8 && hora <=18 && min>=0 && min<60){
            printf("passa aqui!\n");
            flag=0;
        } else {
            printf("%02d:%02d não é uma hora válida para reserva\n", hora, min);
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

int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano){
    reservas aux= lista_reservas->next;
    int flag=1;
    int reservas[20][2];
    int i=0;
    int k;
    int phora_vaga;
    int pmin_vaga;
    //Mete todas as reservas para o dia
    while(aux!=NULL){
        if(op== aux->op && dia== aux->dia && mes== aux->mes && ano== aux->ano){
            reservas[i][0]= aux->hora;
            reservas[i][1]= aux->min;
            i++;
        }
        aux=aux->next;
    }
    if(i>1){
        for(k=0;k<i-1;k++){
            phora_vaga= reservas[k+1][0]- reservas[k][0];
            pmin_vaga= reservas[k+1][0]- reservas[k][1];
            if(op=='M' && (phora_vaga>1 || (phora_vaga==1 && pmin_vaga>=0))){
                printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[k][0], reservas[k][1], reservas[k+1][0],reservas[k+1][1]);
                flag=0;
            } else if(op=='L' &&( phora_vaga>1 || ( phora_vaga==1 && abs(pmin_vaga)>=30 ) ||  (phora_vaga==0 && pmin_vaga>=30))){
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[k][0], reservas[k][1], reservas[k+1][0],reservas[k+1][1]);
                flag=0;
            }
        }
    } else if(i==1){
        if(op=='M' && (8-reservas[0][0]>=1)){
            printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n", 8,0, reservas[0][0], reservas[0][1]);
            printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n",reservas[0][0], reservas[0][1], 18, 0 );
            flag=0;
        } else if(op=='L' && (reservas[0][0]-8>=1 || (reservas[0][0]-8==0 && reservas[0][1]>=30) )){
            printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", 8,0, reservas[0][0], reservas[0][1]);
            printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n",reservas[0][0], reservas[0][1], 18, 0 );
            flag=0;
        }
    } else {
        printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", 8, 0, 18, 0);
        flag=0;
    }
    return flag;
}

void clear_screen(){
    system("clear");
}