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

    //por_no_ficheiro(op, dia, mes, ano, nome)
    printf("ERROR: returning 1!\n");
    return 1;

}

