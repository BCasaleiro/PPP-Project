#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int main(){
    return 0;
}

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

pre_reservas create_pre_reservas(){
    prnode* initial;
    initial= malloc(sizeof(prnode));
    if(initial!= NULL){
        initial->next= NULL;
        return initial;
    }
    printf("ERROR: returning NULL!\n");
    return NULL;
}

int insert_reserva(reservas r, int dia, int mes, int ano, int hora, int min, char nome[]){
    rnode* ins;
    ins= malloc(sizeof(rnode));
    if(ins!=NULL){
        ins->dia= dia;
        ins->mes= mes;
        ins->ano= ano;
        ins->hora= hora;
        ins->min= min;
        strcmp(ins->nome, nome);
        ins->next= r->next;
        r->next=ins;
        return 0;
    }
    printf("ERROR: returning 1!\n");
    return 1;
}