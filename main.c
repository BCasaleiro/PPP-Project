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
    load(lista_reservas, lista_pre);
    clear_screen();
    menu(lista_reservas, lista_pre);
    return 0;
}

void load(reservas lista_reservas, prereservas lista_pre){
    print_informacao(lista_reservas, lista_pre);
    int reservas_lavagem=0;
    int reservas_manutencao=0;
    count_reservas(lista_reservas, &reservas_lavagem, &reservas_manutencao);
    if(reservas_lavagem+reservas_manutencao>1){
        sort_reservas(lista_reservas, 1);
    }
}

void menu(reservas lista_reservas, prereservas lista_pre){
    int menu=9;
    do{
        printf("Menu:\n1- Reservar lavagem ou manutenção\n2- Cancelar reserva de lavagem ou manutenção\n3- Cancelar pré-reserva de lavagem ou manutenção\n4- Listar reservas e pré-reservas\n5- Lavagem ou Manutenção Concluida\n0- Sair\nO que fazer? ");
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
            case 5:
                clear_screen();
                concluida(lista_reservas, lista_pre);
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

void concluida(reservas lista_reservas, prereservas lista_pre){
    int menu=9;
    char op;
    printf("Operação concluida:\n1- Lavagem\n2- Manutenção\n0- Regressar ao menu principal\nO que foi concluido? ");
    scanf("%d", &menu);
    getchar(); //eliminar o '\n' não lido pelo scanf
    switch(menu){
        case 0:
            clear_screen();
            break;
        case 1:
            clear_screen();
            op='L';
            conclusao(lista_reservas, lista_pre, op);
            break;
        case 2:
            clear_screen();
            op='M';
            conclusao(lista_reservas, lista_pre, op);
            break;
        default:
            clear_screen();
            printf("Não é uma opção válida! A regressar ao menu principal...\n");
    }
}

void conclusao(reservas lista_reservas, prereservas lista_pre, char op){
    reservas aux=lista_reservas;
    int menu=9;
    int dia_a;
    int mes_a;
    int ano_a;
    int hora_a;
    int min_a;
    int reservas_lavagem;
    int reservas_manutencao;
    get_date(&dia_a, &mes_a, &ano_a);
    get_time(&hora_a, &min_a);
    count_reservas(lista_reservas, &reservas_lavagem, &reservas_manutencao);
    if(reservas_lavagem==0 && op=='L'){
        printf("Não existem reservas de lavagem! A regressar ao menu principal...\n");
        return;
    } else if(reservas_manutencao==0 && op=='M'){
        printf("Não existem reservas de manutenção! A regressar ao menu principal...\n");
        return;
    }
    //Achar o anterior a primeira reserva
    while(aux->next!=NULL){
        if(aux->next->op==op){
            break;
        }
        aux=aux->next;
    }
    if(aux->next->dia!=dia_a || aux->next->mes!=mes_a || aux->next->ano!=ano_a){
        printf("Não é possivel uma operação demorar mais que um dia ou concluir uma operação futura!\n");
        return;
    } else if(aux->next->hora>hora_a || (aux->next->hora==hora_a && aux->next->min>min_a)){
        printf("Não é possivel concluir uma operação futura!\n");
        return;
    } else {
        printf("Tem a certeza que a operação foi concluida?(1-Sim) \n");
        scanf("%d", &menu);
        getchar();
        if(menu==1){
            delete_reserva(aux);
            if(encaixe(aux, hora_a, min_a, op)==0){
                update_apos_cancelamento(lista_reservas, lista_pre, hora_a, min_a, op);
            }
        } else {
            clear_screen();
            printf("A retornar ao menu principal...\n");
            return;
        }
    }
}

int encaixe(rnode* first, int hora_a, int min_a, char op){
    int dif_hora;
    int dif_min;
    if(op=='L'){
        if(hora_a+30>=60){
            dif_hora=first->next->hora - (hora_a+1);
            dif_min=first->next->min - (min_a-30);
            if(dif_hora>=1){
                return 0;
            } else if(dif_hora==0 && dif_min>=30){
                return 0;
            }
        } else {
            dif_hora=first->next->hora - hora_a;
            dif_min=first->next->min - (min_a-30);
            if(dif_hora>1){
                return 0;
            } else if(dif_hora==0 && dif_min>=30){
                return 0;
            } else if(dif_hora==1 && dif_min>=-30){
                return 0;
            }
        }
    } else if(op=='M'){
        dif_hora=first->next->hora - (hora_a+1);
        dif_min=first->next->min - min_a;
        if(dif_hora==1 && dif_min>=0){
            return 0;
        } else if(dif_hora>1){
            return 0;
        }
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
    clear_buffer();
    for (i = 0; nome[i] != 0; ++i) {
        if (nome[i] == '\n') {
            nome[i] = '\0';
        }
    }
    do {
        printf("Data (DD-MM-AAAA): ");
        if (scanf("%d-%d-%d", &dia, &mes, &ano)!=3){
            printf("A data introduzida não está no formato DD-MM-AAAA\n");
            clear_buffer();
        } else {
            if (data_valida(dia, mes, ano) == 0) {
                printf("Data incorrecta!\n");
            } else {
                flag=0;
            }
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
        if(scanf("%d:%d", &hora, &min)!=2){
            printf("A hora introduzida não está no formato hh:mm\n");
            clear_buffer();
        } else {
            if(disponibilidade(lista_reservas, op, hora, min, dia, mes, ano)==0){
                flag=0;
            } else {
                printf("%02d:%02d não é uma hora válida para reserva\n", hora, min);
            }
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
    clear_buffer();
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
    clear_buffer();
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

void clear_buffer(){
    while(getchar()!='\n');
}

void clear_screen(){
    system("clear");
}
