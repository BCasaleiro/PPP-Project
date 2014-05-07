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