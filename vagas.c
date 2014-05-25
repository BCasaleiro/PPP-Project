#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "vagas.h"

int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano){
    int lreservas[MAX_RESERVAS][2];
    int vagas[MAX_RESERVAS][2];
    int n_reservas;
    int n_vagas;
    n_reservas= agrupar_reservas(lista_reservas, lreservas, op, dia, mes, ano);
    printf("Numero de reservas para %d/%d/%d: %d\n",dia, mes, ano, n_reservas);
    if(n_reservas>0){
        n_vagas=agrupar_vagas(lreservas, vagas, n_reservas, op);
        printf("Numero de vagas para %d/%d/%d: %d\n", dia, mes, ano, n_vagas);
    } else {
        return 0;
    }
    if(n_vagas>0){
        return 0;
    } else if(n_vagas==0 && n_reservas>0){
        return 1;
    } else {
        return 0;
    }
}

int agrupar_reservas(reservas lista_reservas,int lreservas[MAX_RESERVAS][2] ,char op, int dia, int mes, int ano){
    reservas aux= lista_reservas->next;
    int count=0;
    while(aux!=NULL){
        if(op==aux->op){
            if(aux->dia==dia && aux->mes==mes && aux->ano){
                lreservas[count][0]=aux->hora;
                lreservas[count][1]=aux->min;
                count++;
            }
        }
        aux=aux->next;
    }
    return count;
}

int agrupar_vagas(int lreservas[MAX_RESERVAS][2], int vagas[MAX_RESERVAS][2], int n_reservas,char op){
    int i;
    int k=0;
    int dif_hora;
    int dif_min;
    if(op=='M'){
        for(i=0;i<n_reservas-1;i++){
            dif_hora=lreservas[i+1][0]-(lreservas[i][0]+1);
            dif_min=lreservas[i+1][1]-lreservas[i][1];
            if(dif_hora==1 && dif_min>=0){
                printf("Horas:%d:%d a %d:%d --> Granda diferença: %d:%d\n",lreservas[i][0]+1, lreservas[i][1], lreservas[i+1][0], lreservas[i+1][1],dif_hora, dif_min);
                vagas[k][0]=lreservas[i][0]+1;
                vagas[k][1]=lreservas[i][1];
                k++;
            } else if(dif_hora>1){
                printf("Horas:%d:%d a %d:%d --> Granda diferença: %d:%d\n",lreservas[i][0]+1, lreservas[i][1], lreservas[i+1][0], lreservas[i+1][1],dif_hora, dif_min);
                vagas[k][0]=lreservas[i][0]+1;
                vagas[k][1]=lreservas[i][1];
                k++;
            }
        }
    } else if(op=='L'){
        for(i=0;i<n_reservas-1;i++){
            if(lreservas[i][1]+30>=60){
                dif_hora=lreservas[i+1][0]-(lreservas[i][0]+1);
                dif_min=lreservas[i+1][1]-(lreservas[i][1]-30);
                if(dif_hora>=1){
                    vagas[k][0]=lreservas[i][0]+1;
                    vagas[k][1]=lreservas[i][1]-30;
                    k++;
                } else if(dif_hora==0 && dif_min>=30){
                    vagas[k][0]=lreservas[i][0]+1;
                    vagas[k][1]=lreservas[i][1]-30;
                    k++;
                }
                
            } else {
                dif_hora=lreservas[i+1][0]- lreservas[i][0];
                dif_min=lreservas[i+1][1] - (lreservas[i][1]+30);
                if(dif_hora>1){
                    vagas[k][0]=lreservas[i][0];
                    vagas[k][1]=lreservas[i][1]+30;
                    k++;
                } else if(dif_hora==0 && dif_min>=30){
                    vagas[k][0]=lreservas[i][0];
                    vagas[k][1]=lreservas[i][1]+30;
                    k++;
                } else if(dif_hora==1 && dif_min>=-30){
                    vagas[k][0]=lreservas[i][0];
                    vagas[k][1]=lreservas[i][1]+30;
                    k++;
                }
            }
        }
    }
    return k;
}

int mostra_vagas(int vagas[MAX_RESERVAS][2], int n_vagas){
    int i;
    for(i=0;i<n_vagas;i++){
        //mostrar vagas
    }
}