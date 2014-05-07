#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

reservas create_reservas(){
    rnode* initial;
    initial=malloc(sizeof(rnode));
    if(initial!= NULL){
        initial->next= NULL;
        return initial;
    }
    printf("ERROR: returning NULL!\n");
    return NULL;
}

prereservas create_pre_reservas(){
    prnode* initial;
    initial= malloc(sizeof(prnode));
    if(initial!= NULL){
        initial->next= NULL;
        return initial;
    }
    printf("ERROR: returning NULL!\n");
    return NULL;
}

int insert_reserva(reservas r, char op, int dia, int mes, int ano, int hora, int min, char nome[]){
    rnode* ins;
    ins= malloc(sizeof(rnode));
    if(ins!=NULL){
        ins->op= op;
        ins->dia= dia;
        ins->mes= mes;
        ins->ano= ano;
        ins->hora= hora;
        ins->min= min;
        strcpy(ins->nome, nome);
        ins->next= r->next;
        r->next=ins;
        return 0;
    }
    //update
    //por_no_ficheiro(r);
    printf("ERROR: returning 1!\n");
    return 1;
}

int insert_pre_reserva(prereservas pr, char op, int dia, int mes, int ano, char nome[]){
    prnode*  ins;
    ins= malloc(sizeof(prnode));
    if(ins!=NULL){
        ins->op= op;
        ins->dia= dia;
        ins->mes= mes;
        ins->ano= ano;
        strcpy(ins->nome, nome);
        ins->next= pr->next;
        pr->next= ins;
        return 0;
    }
    printf("ERROR: returning 1!\n");
    return 1;
}

rnode* find_ant(reservas lista_reservas, char nome[]){
    reservas aux= lista_reservas;
    while(aux->next!=NULL){
        printf("%s e %s enter now\n", nome, aux->nome);
        if(strcmp(nome, aux->next->nome)==0){
            return aux;
        }
        aux=aux->next;
    }
    return NULL;
}

void delete_reserva(rnode* anterior){
    rnode* aux;
    aux=anterior->next;
    anterior->next= anterior->next->next;
    free(aux);
}

prnode* find_ant_pre(prereservas lista_reservas, char nome[]){
    prereservas aux= lista_reservas;
    while(aux->next!=NULL){
        printf("%s e %s enter now\n", nome, aux->nome);
        if(strcmp(nome, aux->next->nome)==0){
            return aux;
        }
        aux=aux->next;
    }
    return NULL;
}

void delete_pre(prnode* anterior){
    prnode* aux;
    aux=anterior->next;
    anterior->next= anterior->next->next;
    free(aux);
}

int check_reservas(reservas lista_reservas, int menu){
    reservas aux=lista_reservas->next;
    while(aux->next!=NULL){
        if(menu==1){
            if((aux->ano<aux->next->ano)||
                (aux->ano==aux->next->ano && aux->mes>aux->next->mes) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia>aux->next->dia) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia==aux->next->dia && aux->hora>aux->next->hora) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia==aux->next->dia && aux->hora==aux->next->hora && aux->min>aux->next->min))
            {
                return 1;
            }
        } else {
            if((aux->ano>aux->next->ano)||
                (aux->ano==aux->next->ano && aux->mes<aux->next->mes) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia<aux->next->dia) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia==aux->next->dia && aux->hora<aux->next->hora) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia==aux->next->dia && aux->hora==aux->next->hora && aux->min<aux->next->min))
            {
                return 1;
            }
        }
        aux=aux->next;
    }
    return 0;
}

int check_pre(prereservas lista_pre, int menu){
    prereservas aux=lista_pre->next;
    while(aux->next!=NULL){
        if(menu==1){
            if((aux->ano<aux->next->ano)||
                (aux->ano==aux->next->ano && aux->mes>aux->next->mes) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia>aux->next->dia)){
                return 1;
            }
        } else {
            if((aux->ano>aux->next->ano)||
                (aux->ano==aux->next->ano && aux->mes<aux->next->mes) ||
                (aux->ano==aux->next->ano && aux->mes==aux->next->mes && aux->dia<aux->next->dia)){
                return 1;
            }
        }
        aux=aux->next;
    }
    return 0;
}

void sort_reservas(reservas lista_reservas, int menu){
    reservas aux= lista_reservas;
    reservas exchange;
    reservas exchange2;
    //Ordenar reservas
    while(aux->next->next!=NULL){
        if(menu==1){
            if(((aux->next)->ano< (aux->next->next)->ano) || 
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes> (aux->next->next)->mes) ||
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes== (aux->next->next)->mes && (aux->next)->dia> (aux->next->next)->dia)||
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes== (aux->next->next)->mes && (aux->next)->dia== (aux->next->next)->dia && (aux->next)->hora> (aux->next->next)->hora)||
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes== (aux->next->next)->mes && (aux->next)->dia== (aux->next->next)->dia && (aux->next)->hora== (aux->next->next)->hora && (aux->next)->min> (aux->next->next)->min)){

                exchange=aux->next->next->next;
                exchange2=aux->next;
                aux->next= aux->next->next;
                (aux->next)->next=exchange2;
                (aux->next->next)->next=exchange;
            }
        } else {
            if(((aux->next)->ano> (aux->next->next)->ano) || 
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes< (aux->next->next)->mes) ||
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes== (aux->next->next)->mes && (aux->next)->dia< (aux->next->next)->dia)||
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes== (aux->next->next)->mes && (aux->next)->dia== (aux->next->next)->dia && (aux->next)->hora< (aux->next->next)->hora)||
                ((aux->next)->ano == (aux->next->next)->ano && (aux->next)->mes== (aux->next->next)->mes && (aux->next)->dia== (aux->next->next)->dia && (aux->next)->hora== (aux->next->next)->hora && (aux->next)->min< (aux->next->next)->min)){

                exchange=aux->next->next->next;
                exchange2=aux->next;
                aux->next= aux->next->next;
                (aux->next)->next=exchange2;
                (aux->next->next)->next=exchange;
            }
        }
        aux=aux->next;
    }
    if(check_reservas(lista_reservas, menu)==1){
        sort_reservas(lista_reservas, menu);
    } else {
        return;
    }

}

void sort_pre(prereservas lista_pre, int menu){
    prereservas auxpr= lista_pre;
    prereservas exchangepr;
    prereservas exchangepr2;
    //Ordenar pré-reservas
    while(auxpr->next->next!=NULL){
        if(menu==1){
            if(((auxpr->next)->ano< (auxpr->next->next)->ano) || 
                ((auxpr->next)->ano == (auxpr->next->next)->ano && (auxpr->next)->mes> (auxpr->next->next)->mes) ||
                ((auxpr->next)->ano == (auxpr->next->next)->ano && (auxpr->next)->mes== (auxpr->next->next)->mes && (auxpr->next)->dia> (auxpr->next->next)->dia))
            {
                exchangepr=auxpr->next->next->next;
                exchangepr2=auxpr->next;
                auxpr->next= auxpr->next->next;
                (auxpr->next)->next=exchangepr2;
                (auxpr->next->next)->next=exchangepr;
            }
        } else {
            if(((auxpr->next)->ano> (auxpr->next->next)->ano) || 
                ((auxpr->next)->ano == (auxpr->next->next)->ano && (auxpr->next)->mes< (auxpr->next->next)->mes) ||
                ((auxpr->next)->ano == (auxpr->next->next)->ano && (auxpr->next)->mes== (auxpr->next->next)->mes && (auxpr->next)->dia< (auxpr->next->next)->dia))
            {
                exchangepr=auxpr->next->next->next;
                exchangepr2=auxpr->next;
                auxpr->next= auxpr->next->next;
                (auxpr->next)->next=exchangepr2;
                (auxpr->next->next)->next=exchangepr;
            }
        }           
        auxpr=auxpr->next;
    }
    if(check_pre(lista_pre, menu)==1){
        sort_pre(lista_pre, menu);
    } else {
        return;
    }
}