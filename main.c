#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "data.h"
#include "files.h"
#include "main.h"


int main(){
    reservas lista_reservas= create_reservas();
    prereservas lista_pre= create_pre_reservas();
    print_informacao(lista_reservas, lista_pre);
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
                clear_screen();
                cancela(lista_reservas, lista_pre);
                break;
            case 3:
                clear_screen();
                cancela_pre(lista_pre);
                break;
            case 4:
                break;
            default:
                clear_screen();
                printf("%d não é uma opção válida!\n", menu);
        }
    }while(menu != 0);
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
            //update();
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

void cancela(reservas lista_reservas, prereservas lista_pre){
    int menu;
    char op;
    printf("Cancelar:\n1- Lavagem\n2- Manutenção\n0- Regressar ao menu principal\nO que cancelar? ");
    scanf("%d", &menu);
    getchar();
    switch(menu){
        case 0:
            clear_screen();
            break;
        case 1:
            clear_screen();
            op='L';
            cancelar(lista_reservas, op);
            break;
        case 2:
            clear_screen();
            op='M';
            cancelar(lista_reservas, op);
            break;
        default:
            clear_screen();
            printf("%d não é uma opção válida! A regressar ao menu principal...\n", menu);
    }
}

void cancela_pre(prereservas lista_pre){
    int menu;
    char op;
    printf("Cancelar:\n1- Lavagem\n2- Manutenção\n0- Regressar ao menu principal\nO que cancelar? ");
    scanf("%d", &menu);
    getchar();
    switch(menu){
        case 0:
            clear_screen();
            break;
        case 1:
            clear_screen();
            op='L';
            cancelar_pre(lista_pre, op);
            break;
        case 2:
            clear_screen();
            op='M';
            cancelar_pre(lista_pre, op);
            break;
        default:
            clear_screen();
            printf("%d não é uma opção válida! A regressar ao menu principal...\n", menu);
    }
}

void reservar(reservas lista_reservas, prereservas lista_pre, char op){
    int i;
    int menu;
    int flag=1;
    int reservado;
    int pre_reservado;
    char nome[MAX];
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    int contador = 1;
    printf("Nome: ");
    fgets(nome, MAX-1, stdin);
    for (i = 0; nome[i] != 0; ++i) {
        if (nome[i] == '\n') {
            nome[i] = '\0';
        }
    }
    do {
        printf("Data (DD-MM-AAAA): ");
        scanf("%d-%d-%d", &dia, &mes, &ano);
        if (contador >= 1 && data_valida(dia, mes, ano) == 0) {
            printf("Data incorrecta!\n");
            contador++;
        }
    }while (data_valida(dia, mes, ano) == 0);
    //Verificação da disponibilidade desse dia, se nao houver 
    //reencaminhar para as pré reservas.
    if(verifica_vaga(lista_reservas, op, dia, mes, ano)== 1){
        printf("Deseja efectuar pré-reserva? (1- Sim)");
        scanf("%d", &menu);
        getchar();
        if(menu==1){
            pre_reservado= insert_pre_reserva(lista_pre, op, dia, mes, ano, nome);
            if(pre_reservado==0){
                clear_screen();
                printf("Pré-Reserva efectuada com sucesso!");
                //update_PREreservas();
                return;
            } else {
                clear_screen();
                printf("Falha ao efectuar a pré-reserva!\n");
                return;
            }
        }
    }
    //Se possivel indicar as horas disponiveis para esse dia
    do{
        printf("Hora (hh:mm): ");
        scanf("%02d:%02d", &hora, &min);
        if(disponibilidade(lista_reservas, op, hora, min)==0){
            flag=0;
        } else {
            printf("%02d:%02d não é uma hora válida para reserva\n", hora, min);
        }
    }while(flag==1);
    reservado = insert_reserva(lista_reservas, op, dia, mes, ano, hora, min, nome);

    if(reservado==0){
        clear_screen();
        printf("Reserva efectuada com sucesso!\n");
        //update_reservas();
    } else {
        clear_screen();
        printf("Falha ao efectuar a reserva!\n");
    }
}

void cancelar(reservas lista_reservas, char op){
    char nome[MAX];
    rnode* ant;
    int i;
    if(op=='M'){
        printf("Cancelar reserva de manutenção em nome de: ");
    } else {
        printf("Cancelar reserva de lavagem em nome de: ");
    }
    fgets(nome, MAX-1, stdin);
    for (i= 0; nome[i]!= 0; ++i) {
        if (nome[i] == '\n') {
            nome[i] = '\0';
        }
    }
    ant= find_ant(lista_reservas, nome);
    if(ant==NULL){
        printf("Reserva não encontrada! A regressar ao menu principal...\n");
        return;
    }
    delete_reserva(ant);
}

void cancelar_pre(prereservas lista_pre, char op){
    char nome[MAX];
    prnode* ant;
    int i;
    if(op=='M'){
        printf("Cancelar pré-reserva de manutenção em nome de: ");
    } else {
        printf("Cancelar pré-reserva de lavagem em nome de: ");
    }
    fgets(nome, MAX-1, stdin);
    for (i= 0; nome[i]!= 0; ++i) {
        if (nome[i] == '\n') {
            nome[i] = '\0';
        }
    }
    ant= find_ant_pre(lista_pre, nome);
    if(ant==NULL){
        printf("Pré-reserva não encontrada! A regressar ao menu principal...\n");
        return;
    }
    printf("Entra no delete\n");
    delete_pre(ant);
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
        if(op==aux->op && dia== aux->dia && mes== aux->mes && ano== aux->ano){
            reservas[i][0]= aux->hora;
            reservas[i][1]= aux->min;
            i++;
        }
        aux=aux->next;
    }
    if(i>1){
        for(k=0;k<i-1;k++){
            printf("ERROR!!\n");
            phora_vaga= reservas[k+1][0]- reservas[k][0];
            pmin_vaga= reservas[k+1][1]- reservas[k][1];
            printf("Hora:%d e min:%d de diferença\n", phora_vaga, pmin_vaga);
            if(op=='M' && (phora_vaga>1 || (phora_vaga==1 && pmin_vaga>=0))){
                printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[k][0]+1, reservas[k][1], reservas[k+1][0],reservas[k+1][1]);
                flag=0;
            } else if(op=='L' &&( phora_vaga>1 || ( phora_vaga==1 && abs(pmin_vaga)>=30 ) ||  (phora_vaga==0 && pmin_vaga>=30))){
                if(reservas[k][1]+30<60){
                    printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[k][0], reservas[k][1]+30, reservas[k+1][0],reservas[k+1][1]);
                } else if(reservas[k][1]+30>60){
                    printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[k][0]+1, reservas[k][1]-30, reservas[k+1][0],reservas[k+1][1]);
                } else {
                    printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[k][0]+1, 0, reservas[k+1][0],reservas[k+1][1]);
                }
                flag=0;
            }
        }
    } else if(i==1){
        if(op=='M' && (reservas[0][0]-8>=1)){
            printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n", 8,0, reservas[0][0], reservas[0][1]);
            printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n",reservas[0][0]+1, reservas[0][1], 18, 0 );
            flag=0;
        }else if(op=='M' && reservas[0][0]==8){
            printf("Manutenção disponivel entre as %02d:%02d e as %02d:%02d\n",reservas[0][0]+1, reservas[0][1], 18, 0 );
            flag=0;
        } else if(op=='L' && (reservas[0][0]-8>=1 || (reservas[0][0]-8==0 && reservas[0][1]>=30) )){
            printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", 8,0, reservas[0][0], reservas[0][1]);
            if(reservas[0][1]+30<60){
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[0][0], reservas[0][1]+30, 18,0);
            } else if(reservas[0][1]+30>60){
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[0][0]+1, reservas[0][1]-30, 18, 0);
            } else {
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[0][0]+1, 0, 18,0);
            }
            flag=0;
        } else if(op=='L' && reservas[0][0]==8){
            if(reservas[0][1]+30<60){
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[0][0], reservas[0][1]+30, 18,0);
            } else if(reservas[0][1]+30>60){
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[0][0]+1, reservas[0][1]-30, 18, 0);
            } else {
                printf("Lavagem disponivel entre as %02d:%02d e as %02d:%02d\n", reservas[0][0]+1, 0, 18,0);
            }
        }
    } else {
        printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", 8, 0, 18, 0);
        flag=0;
    }
    return flag;
}

int disponibilidade(reservas lista_reservas, char op, int hora,int min){
    reservas aux=lista_reservas->next;
    if(hora<8 || hora>=18 || min<0 || min>=60){
        return 1;
    }
    while(aux!=NULL){
        if(op=='M' && aux->op== op){
            if(hora==aux->hora && min>aux->min && hora+1>aux->hora && hora+1<aux->hora+1 && min>aux->min){
                return 1;
            } else if(hora==17 && min>0){
                return 1;
            }
        } else if(op=='L' && aux->op== op){
            if(min+30>60){
                if(hora+1==aux->hora && min-30>aux->min || hora+1>aux->hora && hora+1<aux->hora+1 && min-30>aux->min){
                    return 1;
                }
            } else if(min+30==60){
                if(hora+1==aux->hora+1 && aux->min+30>60){
                    return 1;
                }
            } else if(min+30<60){
                if(hora==aux->hora && min+30>aux->min || hora==aux->hora && min+30<aux->min+30){
                    return 1;
                }
            }
        }
        aux=aux->next;
    }
    return 0;
}

void update_reservas(reservas lista) {   

}

void update_prereservas(prereservas lista) {


}

int data_valida(int dia, int mes, int ano) {

    int bissexto;

    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        bissexto = 1;
    }
    else
        bissexto = 0;

    if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
        if (dia > 0 && dia <= 31) {
            return 1;
        }
    }

    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
        if (dia > 0 && dia <= 30) {
            return 1;
        }
    }

    if (mes == 2 && bissexto == 1) {
        if (dia > 0 && dia <= 29) {
            return 1;
        }
        
    }

    if (mes == 2 && bissexto == 0) {
        if (dia > 0 && dia <= 28) {
            return 1;
        }

    }
}

void listar(reservas lista_reservas, prereservas lista_pre){
    int menu;
    int submenu;
    char op;
    printf("Listar:\n1- Lavagens\n2- Manutenções\n0- Regressar ao menu principal\nO que listar?");
    scanf("%d", &menu);
    getchar();
    switch(menu){
        case 0:
            clear_screen();
            break;
        case 1:
            clear_screen();
            printf("Ordenar:\n1- Mais recentes primeiro\n2- Mais antigas primeiro\n0-Regressar ao menu principal\nComo ordenar? ");
            scanf("%d", &submenu);
            getchar();
            if(submenu==1 || submenu==2){
                sort(lista_reservas, lista_pre, submenu, 1);
            } else {
                printf("%d não é uma opção válida! A regressar ao menu principal...\n", submenu);
                return;
            }
            break;
        case 2:
            clear_screen();
            printf("Ordenar:\n1- Mais recentes primeiro\n2- Mais antigas primeiro\n0-Regressar ao menu principal\nComo ordenar? ");
            scanf("%d", &submenu);
            getchar();
            if(submenu==1 || submenu==2){
                sort(lista_reservas, lista_pre, submenu, 1);
            } else {
                printf("%d não é uma opção válida! A regressar ao menu principal...\n", submenu);
                return;
            }
            break;
        default:
            clear_screen();
            printf("%d não é uma opção válida! A regressar ao menu principal...\n", menu);
    }
}

void imprimir_reservas(reservas lista_reservas){
    reservas aux= lista_reservas->next;
    printf("Reservas:\n");
    while(aux!=NULL){
        printf("Reserva em nome de: %s\n", aux->nome);
        printf("Reserva: %d/%d/%d pelas %d:%d\n\n", aux->dia, aux->mes, aux->ano, aux->hora, aux->min);
        aux=aux->next;
    }
}

void imprimir_pre(prereservas lista_pre){
    prereservas aux= lista_pre->next;
    printf("Pré-Reservas:\n");
    while(aux!=NULL){
        printf("Pré-reserva em nome de: %s\n", aux->nome);
        printf("Pré-reserva: %d/%d/%d\n\n", aux->dia, aux->mes, aux->ano);
        aux=aux->next;
    }
}

void clear_screen(){
    system("clear");
}