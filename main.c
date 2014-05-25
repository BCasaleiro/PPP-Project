#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"
#include "files.h"
#include "vagas.h"
#include "main.h"


int main(){
    reservas lista_reservas= create_reservas();
    prereservas lista_pre= create_pre_reservas();
    print_informacao(lista_reservas, lista_pre);
    int reservas_lavagem=0;
    int reservas_manutencao=0;
    count_reservas(lista_reservas, &reservas_lavagem, &reservas_manutencao);
    if(reservas_lavagem+reservas_manutencao>1){
        sort_reservas(lista_reservas, 1);
    }
    clear_screen();
    menu(lista_reservas, lista_pre);
    return 0;
}

void menu(reservas lista_reservas, prereservas lista_pre){
    int menu=9;
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
                update_reservas(lista_reservas);
                break;
            case 3:
                clear_screen();
                cancela_pre(lista_pre);
                update_prereservas(lista_pre);
                break;
            case 4:
                clear_screen();
                listar(lista_reservas, lista_pre);
                break;
            default:
                clear_screen();
                printf("Não é uma opção válida!\n");
        }
    }while(menu != 0);
}

void reserva(reservas lista_reservas, prereservas lista_pre){
    int menu = 9;
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
            printf("Não é uma opção válida! A regressar ao menu principal...\n");
    }   
}

void cancela(reservas lista_reservas, prereservas lista_pre){
    int menu = 9;
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
            cancelar(lista_reservas, lista_pre, op);
            break;
        case 2:
            clear_screen();
            op='M';
            cancelar(lista_reservas, lista_pre, op);
            break;
        default:
            clear_screen();
            printf("Não é uma opção válida! A regressar ao menu principal...\n");
    }
}

void cancela_pre(prereservas lista_pre){
    int menu = 9;
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
            printf("Não é uma opção válida! A regressar ao menu principal...\n");
    }
}

void reservar(reservas lista_reservas, prereservas lista_pre, char op){
    int i;
    int menu = 9;
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
    do {
        printf("Data (DD-MM-AAAA): ");
        scanf("%d-%d-%d", &dia, &mes, &ano);
        if (data_valida(dia, mes, ano) == 0) {
            printf("Data incorrecta!\n");
        } else {
            flag=0;
        }
    }while (flag == 1);
    flag=1;
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
                update_prereservas(lista_pre);
                return;
            } else {
                clear_screen();
                printf("Falha ao efectuar a pré-reserva!\n");
                return;
            }
        } else {
            clear_screen();
            printf("Pré-reserva não efectuada! A voltar ao menu inicial...\n");
            return;
        }
    }
    //Indica as horas disponiveis para esse dia
    do{
        printf("Hora (hh:mm): ");
        scanf("%02d:%02d", &hora, &min);
        if(disponibilidade(lista_reservas, op, hora, min, dia, mes, ano)==0){
            flag=0;
        } else {
            printf("%02d:%02d não é uma hora válida para reserva\n", hora, min);
        }
    }while(flag==1);
    reservado = insert_reserva(lista_reservas, op, dia, mes, ano, hora, min, nome);

    if(reservado==0){
        clear_screen();
        printf("Reserva efectuada com sucesso!\n");
        update_reservas(lista_reservas);
    } else {
        clear_screen();
        printf("Falha ao efectuar a reserva!\n");
    }
}

void cancelar(reservas lista_reservas, prereservas lista_pre, char op){
    char nome[MAX];
    rnode* ant;
    int i;
    int hora;
    int min;
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
    ant= find_ant(lista_reservas, nome, op);
    if(ant==NULL){
        printf("Reserva não encontrada! A regressar ao menu principal...\n");
        return;
    }
    hora= ant->next->hora;
    min=ant->next->min;
    delete_reserva(ant);
    update_apos_cancelamento(lista_reservas, lista_pre, hora, min, op);

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
    ant= find_ant_pre(lista_pre, nome, op);
    if(ant==NULL){
        printf("Pré-reserva não encontrada! A regressar ao menu principal...\n");
        return;
    }
    delete_pre(ant);
}

/*
int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano){
    reservas aux= lista_reservas->next;
    reservas aux1;
    int phora;
    int pmin;
    int n_vagas=0;
    if(aux!=NULL){
        phora= aux->hora - 8;
        pmin= aux->min;
        aux1=aux;
        while(aux!=NULL){
            if(op=='L' && op==aux->op){
                if((aux->dia==dia && aux->mes==mes && aux->ano==ano) && ((aux->min+30>=60 && phora==1 && pmin>=aux->min-30) || phora>1 || (phora==0 && pmin>=30))){
                    printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", 8, 0, aux->hora, aux->min);
                    n_vagas++;
                    break;
                }
            } else if(op=='M' && op==aux->op){
                if((aux->dia==dia && aux->mes==mes && aux->ano==ano) && phora>=1){
                    printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", 8, 0, aux->hora, aux->min);
                    n_vagas++;
                }
            }
            aux=aux->next;
        }
        aux=aux1;
        while(aux->next!=NULL){
            if(aux->min+30>=60){
                phora= aux->next->hora - (aux->hora+1);
                pmin= aux->next->min - (aux->min-30);
            } else {
                phora= aux->next->hora - aux->hora;
                pmin= aux->next->min - (aux->min+30);
            }
            if(op=='L' && op==aux->op){
                if((aux->dia==dia && aux->mes==mes && aux->ano==ano) && ((aux->min+30>=60 && phora==1 && pmin>=aux->min-30) || phora>=1 || (phora==0 && pmin>=30)) && pmin>=0){
                    if(aux->min+30>=60){
                        printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", aux->hora+1, aux->min-30, aux->next->hora, aux->next->min);
                    } else if(aux->min+30<60){
                        printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", aux->hora, aux->min+30, aux->next->hora, aux->next->min);    
                    }
                    n_vagas++;
                }
            } else if(op=='M' && op==aux->op){
                if((aux->dia==dia && aux->mes==mes && aux->ano==ano) && (phora>=1 && pmin==0)){
                    printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", aux->hora+1, aux->min, aux->next->hora, aux->next->min);
                    n_vagas++;
                }
            }
            aux=aux->next;
        }
        while(aux->next!=NULL){
            phora= 17 - aux->hora+1;
            if(aux->op=='M'){
                printf("%d e phora:%d\n", aux->hora, phora);
            }
            if(op=='L' && op==aux->op){
                pmin= aux->min;
                if((aux->dia==dia && aux->mes==mes && aux->ano==ano) && ((aux->min+30>=60 && phora==1 && pmin>=aux->min-30) || phora>1 ||(phora==0 && pmin>=30))){
                    if(aux->min<=30){
                        printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", aux->hora+1, aux->min-30, 17, 30);
                    }
                    printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", aux->hora, aux->min, 17, 30);
                    n_vagas++;
                }

            } else if(op=='M' && op==aux->op){
            printf("no final: %s, %d:%d\n", aux->nome, aux->hora, aux->min); //aqui esta para apagar
            if((aux->dia==dia && aux->mes==mes && aux->ano==ano) && phora>=1){
                printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", aux->hora+1, aux->min, 17, 0);
                n_vagas++;
            }
            aux=aux->next;
        }
    }
    }
    printf("vagas: %d\n", n_vagas);
    return vagas(lista_reservas, op, n_vagas, dia, mes, ano);
}

int vagas(reservas lista_reservas, char op, int n, int dia, int mes, int ano){
    reservas aux=lista_reservas->next;
    if(n>0){
        return 0;
    } else if(n==0){
        while(aux!=NULL){
            if(aux->dia==dia && aux->mes==mes && aux->ano==ano && op==aux->op){
                return 1;
            }
            aux=aux->next;
        }
        return 0;
    }
}
*/

int disponibilidade(reservas lista_reservas, char op, int hora,int min, int dia, int mes, int ano){
    reservas aux=lista_reservas->next;
    if(hora_valida(dia, mes, ano, hora, min)==1){
        return 1;
    }
    while(aux!=NULL){
        if(aux->dia==dia && aux->mes==mes && aux->ano==ano){
            if(op=='M' && aux->op==op){
                if((hora==aux->hora && min>=aux->min) || (hora+1==aux->hora && min>=aux->min) || (aux->hora+1==hora && min<=aux->min)){
                    return 1;
                } else if(hora==17 && min>0){
                    return 1;
                }
            } else if(op=='L' && aux->op== op){
                if(hora==17  && min>30){
                    return 1;
                }
                if(min+30>60){
                    if((hora==aux->hora && min>=aux->min && min<=aux->min+30) || (hora+1==aux->hora &&  min-30>=aux->min && min-30<=aux->min+30) || (aux->min+30>60 && hora==aux->hora && min>=aux->min && min-30 <=aux->min-30)){
                        return 1;
                    }
                } else if(min+30==60){
                    if((hora==aux->hora && min>=aux->min && min<= aux->min+30) || (hora==aux->hora && min+30>=aux->min && min+30<= aux->min+30) || (aux->min+30>60 && hora+1==aux->hora+1 && min<=aux->min-30)){
                        return 1;
                    }
                } else if(min+30<60){
                    if((hora==aux->hora && min+30>=aux->min && min+30<=aux->min+30) || (hora==aux->hora && min>=aux->min && min<=aux->min+30) || (aux->min+30>60 && hora==aux->hora+1 && min<=aux->min-30)){
                        return 1;
                    }
                }
            }
        }
        aux=aux->next;
    }
    return 0;
}

int hora_valida(int dia, int mes, int ano, int hora, int min){
    int dia_a;
    int mes_a;
    int ano_a;
    int hora_a;
    int min_a;
    get_time(&hora_a, &min_a);
    get_date(&dia, &mes, &ano);
    if(hora<8 || hora>=18 || min<0 || min>=60){
        return 1;
    } else if(ano==ano_a && mes==mes_a && dia==dia_a && hora_a<hora){
        return 1;
    }else if(ano==ano_a && mes==mes_a && dia==dia_a && hora_a==hora && min_a<min){
        return 1;
    }
    return 0;
}

void get_time(int *hora, int *min){
    struct tm *current;
    time_t timenow;
    time(&timenow);
    current= localtime(&timenow);
    *hora= current->tm_hour;
    *min= current->tm_min; 
}

void update_reservas(reservas lista) {
    int reservas_lavagem=0;
    int reservas_manutencao=0;
    count_reservas(lista, &reservas_lavagem, &reservas_manutencao);
    if(reservas_lavagem+reservas_manutencao>1){
        sort_reservas(lista, 1);
    }
    if(reservas_lavagem+reservas_manutencao>0){
        por_no_ficheiro_reservas(lista);
    }
}

void update_prereservas(prereservas lista) {
    int pre_lavagem=0;
    int pre_manutencao=0;
    count_pre(lista, &pre_lavagem, &pre_manutencao);
    por_no_ficheiro_prereserva(lista);
}

int data_valida(int dia, int mes, int ano) {
    int bissexto;
    int dia_a;
    int mes_a;
    int ano_a;
    get_date(&dia_a, &mes_a, &ano_a);

    if(ano_a>ano){
        printf("Não é possivel fazer reservas para um data do passado\n");
        return 0;
    } else if(ano==ano_a && mes<mes_a){
        printf("Não é possivel fazer reservas para um data do passado\n");
        return 0;
    } else if(ano==ano_a && mes==mes_a && dia<dia_a){
        printf("Não é possivel fazer reservas para um data do passado\n");
        return 0;
    }

    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)) {
        bissexto = 1;
    } else {
        bissexto = 0;
    }

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
    return 0;
}

void get_date(int * dia, int * mes, int * ano) {
    struct tm *current;
    time_t timenow;
    time(&timenow);
    current= localtime(&timenow);
    *mes= current->tm_mon+1;
    *dia= current->tm_mday;
    *ano= current->tm_year+1900;
}

void listar(reservas lista_reservas, prereservas lista_pre){
    int menu;
    int submenu;
    char op;
    int reservas_lavagem=0;
    int reservas_manutencao=0;
    int pre_lavagem=0;
    int pre_manutencao=0;
    count_reservas(lista_reservas, &reservas_lavagem, &reservas_manutencao);
    if(reservas_lavagem+reservas_manutencao==0){
        printf("Nenhuma reserva para listar\n");
        return;
    }
    count_pre(lista_pre, &pre_lavagem, &pre_manutencao);
    printf("Listar:\n1- Lavagens\n2- Manutenções\n0- Regressar ao menu principal\nO que listar?");
    scanf("%d", &menu);
    getchar();
    switch(menu){
        case 0:
            clear_screen();
            break;
        case 1:
            clear_screen();
            if(reservas_lavagem==1){
                op='L';
                imprimir_reservas(lista_reservas, op);
                return;
            } else {
                op='L';
                clear_screen();
                printf("Ordenar:\n1- Mais recentes primeiro\n2- Mais antigas primeiro\n0-Regressar ao menu principal\nComo ordenar? ");
                scanf("%d", &submenu);
                getchar();
                if(submenu==1 || submenu==2){
                    sort_reservas(lista_reservas, submenu);
                    if(pre_lavagem>0){
                        sort_pre(lista_pre, submenu);
                    }
                    clear_screen();
                    imprimir_reservas(lista_reservas, op);
                    imprimir_pre(lista_pre, op);
                } else {
                    printf("%d não é uma opção válida! A regressar ao menu principal...\n", submenu);
                    return;
                }
            }
            break;
        case 2:
            clear_screen();
            if(reservas_manutencao==1){
                op='M';
                imprimir_reservas(lista_reservas, op);
                return;
            } else {
                clear_screen();
                op='M';
                printf("Ordenar:\n1- Mais recentes primeiro\n2- Mais antigas primeiro\n0-Regressar ao menu principal\nComo ordenar? ");
                scanf("%d", &submenu);
                getchar();
                if(submenu==1 || submenu==2){
                    sort_reservas(lista_reservas, submenu);
                    if(pre_manutencao>1){
                        sort_pre(lista_pre, submenu);
                    }
                    imprimir_reservas(lista_reservas, op);
                    imprimir_pre(lista_pre, op);
                } else {
                    printf("%d não é uma opção válida! A regressar ao menu principal...\n", submenu);
                    return;
                }
            }
            break;
        default:
            clear_screen();
            printf("%d não é uma opção válida! A regressar ao menu principal...\n", menu);
    }
}

void imprimir_reservas(reservas lista_reservas, char op){
    reservas aux= lista_reservas->next;
    printf("Reservas:\n");
    while(aux!=NULL){
        if(aux->op==op){
            printf("Reserva em nome de: %s\n", aux->nome);
            printf("Reserva: %02d/%02d/%04d pelas %02d:%02d\n\n", aux->dia, aux->mes, aux->ano, aux->hora, aux->min);
        }
        aux=aux->next;
    }
}

void imprimir_pre(prereservas lista_pre, char op){
    prereservas aux= lista_pre->next;
    printf("Pré-Reservas:\n");
    while(aux!=NULL){
        if(aux->op==op){
            printf("Pré-reserva em nome de: %s\n", aux->nome);
            printf("Pré-reserva: %02d/%02d/%04d\n\n", aux->dia, aux->mes, aux->ano);
        }
        aux=aux->next;
    }
}

void count_reservas(reservas lista_reservas, int* lav, int* man){
    reservas aux= lista_reservas->next;
    while(aux!=NULL){
        if(aux->op=='M'){
            (*man)++;
        } else if(aux->op=='L'){
            (*lav)++;
        }
        aux=aux->next;
    }
}

void count_pre(prereservas lista_pre, int* lav, int* man){
    prereservas aux= lista_pre->next;
    while(aux!=NULL){
        if(aux->op=='M'){
            (*man)++;
        } else if(aux->op=='L'){
            (*lav)++;
        }
        aux=aux->next;
    }
}

void update_apos_cancelamento(reservas lista_reservas, prereservas lista_pre, int hora, int min, char op){
    prereservas go= lista_pre->next;
    prnode* aux;
    prnode* ant;
    int pre_lavagem=0;
    int pre_manutencao=0;
    count_pre(lista_pre, &pre_lavagem, &pre_manutencao);
    if(op=='L' && pre_lavagem>0){
        while(go!=NULL){
            if(go->op==op){
                aux=go;
            }
            go=go->next;
        }
        insert_reserva(lista_reservas, op, aux->dia, aux->mes, aux->ano, hora, min, aux->nome);
        ant= find_ant_pre(lista_pre, aux->nome, op);
        delete_pre(ant);
        update_reservas(lista_reservas);
        update_prereservas(lista_pre);
    } else if(op='M' && pre_manutencao>0){
        while(go!=NULL){
            if(go->op==op){
                aux=go;
            }
            go=go->next;
        }
        insert_reserva(lista_reservas, op, aux->dia, aux->mes, aux->ano, hora, min, aux->nome);
        ant= find_ant_pre(lista_pre, aux->nome, op);
        delete_pre(ant);
        update_reservas(lista_reservas);
        update_prereservas(lista_pre);
    } 
}

void clear_screen(){
    system("clear");
}
