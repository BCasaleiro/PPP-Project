#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "vagas.h"

int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano){
    int lreservas[MAX_RESERVAS][2];
    int vagas[MAX_RESERVAS][2][2];
    int n_reservas;
    int n_vagas;
    n_reservas= agrupar_reservas(lista_reservas, lreservas, op, dia, mes, ano);
    if(n_reservas>0){
        n_vagas=agrupar_vagas(lreservas, vagas, n_reservas, op);
        mostra_vagas(vagas, n_vagas, op);
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

int agrupar_vagas(int lreservas[MAX_RESERVAS][2], int vagas[MAX_RESERVAS][2][2], int n_reservas,char op){
    int i;
    int k=0;
    int dif_hora;
    int dif_min;
    if(op=='M'){
        //Primeira vaga do dia
        dif_hora=lreservas[0][0]-8;
        if(dif_hora>=1){
            vagas[k][0][0]=8;
            vagas[k][0][1]=0;
            vagas[k][1][0]=lreservas[0][0];
            vagas[k][1][1]=lreservas[0][1];
            k++;
        }
        //Vagas
        for(i=0;i<n_reservas-1;i++){
            dif_hora=lreservas[i+1][0]-(lreservas[i][0]+1);
            dif_min=lreservas[i+1][1]-lreservas[i][1];
            if(dif_hora==1 && dif_min>=0){
                vagas[k][0][0]=lreservas[i][0]+1;
                vagas[k][0][1]=lreservas[i][1];
                vagas[k][1][0]=lreservas[i+1][0];
                vagas[k][1][1]=lreservas[i+1][1];
                k++;
            } else if(dif_hora>1){
                vagas[k][0][0]=lreservas[i][0]+1;
                vagas[k][0][1]=lreservas[i][1];
                vagas[k][1][0]=lreservas[i+1][0];
                vagas[k][1][1]=lreservas[i+1][1];
                k++;
            }
        }
        //Ultima vaga do dia
        dif_hora= 17-(lreservas[n_reservas-1][0]+1);
        dif_min=lreservas[n_reservas-1][1];
        if(dif_hora>=1){
            vagas[k][0][0]=lreservas[n_reservas-1][0]+1;
            vagas[k][0][1]=lreservas[n_reservas-1][1];
            vagas[k][1][0]=17;
            vagas[k][1][1]=0;
            k++;
        } else if(dif_hora==0 && dif_min==0){
            vagas[k][0][0]=lreservas[n_reservas-1][0]+1;
            vagas[k][0][1]=lreservas[n_reservas-1][1];
            vagas[k][1][0]=17;
            vagas[k][1][1]=0;
            k++;
        }
    } else if(op=='L'){
        //Primeira vaga do dia
        dif_hora=lreservas[0][0]-8;
        dif_min=lreservas[0][1];
        if(dif_hora>=1){
            vagas[k][0][0]=8;
            vagas[k][0][1]=0;
            vagas[k][1][0]=lreservas[0][0];
            vagas[k][1][1]=lreservas[0][1];
            k++;
        } else if(dif_hora==0 && dif_min>=30){
            vagas[k][0][0]=8;
            vagas[k][0][1]=0;
            vagas[k][1][0]=lreservas[0][0];
            vagas[k][1][1]=lreservas[0][1];
            k++;
        }
        //Vagas
        for(i=0;i<n_reservas-1;i++){
            if(lreservas[i][1]+30>=60){
                dif_hora=lreservas[i+1][0]-(lreservas[i][0]+1);
                dif_min=lreservas[i+1][1]-(lreservas[i][1]-30);
                if(dif_hora>=1){
                    vagas[k][0][0]=lreservas[i][0]+1;
                    vagas[k][0][1]=lreservas[i][1]-30;
                    vagas[k][1][0]=lreservas[i+1][0];
                    vagas[k][1][1]=lreservas[i+1][1];
                    k++;
                } else if(dif_hora==0 && dif_min>=30){
                    vagas[k][0][0]=lreservas[i][0]+1;
                    vagas[k][0][1]=lreservas[i][1]-30;
                    vagas[k][1][0]=lreservas[i+1][0];
                    vagas[k][1][1]=lreservas[i+1][1];
                    k++;
                }
                
            } else {
                dif_hora=lreservas[i+1][0]- lreservas[i][0];
                dif_min=lreservas[i+1][1] - (lreservas[i][1]+30);
                if(dif_hora>1){
                    vagas[k][0][0]=lreservas[i][0];
                    vagas[k][0][1]=lreservas[i][1]+30;
                    vagas[k][1][0]=lreservas[i+1][0];
                    vagas[k][1][1]=lreservas[i+1][1];
                    k++;
                } else if(dif_hora==0 && dif_min>=30){
                    vagas[k][0][0]=lreservas[i][0];
                    vagas[k][0][1]=lreservas[i][1]+30;
                    vagas[k][1][0]=lreservas[i+1][0];
                    vagas[k][1][1]=lreservas[i+1][1];
                    k++;
                } else if(dif_hora==1 && dif_min>=-30){
                    vagas[k][0][0]=lreservas[i][0];
                    vagas[k][0][1]=lreservas[i][1]+30;
                    vagas[k][1][0]=lreservas[i+1][0];
                    vagas[k][1][1]=lreservas[i+1][1];
                    k++;
                }
            }
        }
        //Ultima vaga do dia
        if(lreservas[n_reservas-1][1]+30>=60){
            dif_hora=17-(lreservas[n_reservas-1][0]+1);
            dif_min=30-(lreservas[n_reservas-1][1]-30);
            if(dif_hora>=1){
                vagas[k][0][0]=lreservas[n_reservas-1][0]+1;
                vagas[k][0][1]=lreservas[n_reservas-1][1]-30;
                vagas[k][1][0]=17;
                vagas[k][1][1]=30;
                k++;
            } else if(dif_hora==0 && dif_min>=30){
                vagas[k][0][0]=lreservas[n_reservas-1][0]+1;
                vagas[k][0][1]=lreservas[n_reservas-1][1]-30;
                vagas[k][1][0]=17;
                vagas[k][1][1]=30;
                k++;
            }
        } else {
            dif_hora=17-lreservas[n_reservas-1][0];
            dif_min=30-(lreservas[n_reservas-1][1]+30);
            if(dif_hora>1){
                vagas[k][0][0]=lreservas[n_reservas-1][0];
                vagas[k][0][1]=lreservas[n_reservas-1][1]+30;
                vagas[k][1][0]=17;
                vagas[k][1][1]=30;
                k++;
            } else if(dif_hora==0 && dif_min>=30){
                vagas[k][0][0]=lreservas[n_reservas-1][0];
                vagas[k][0][1]=lreservas[n_reservas-1][1]+30;
                vagas[k][1][0]=17;
                vagas[k][1][1]=30;
                k++;
            } else if(dif_hora==1 && dif_min>=-30){
                vagas[k][0][0]=lreservas[i][0];
                vagas[k][0][1]=lreservas[i][1]+30;
                vagas[k][1][0]=17;
                vagas[k][1][1]=30;
                k++;
            }
        }
    }
    return k;
}

int mostra_vagas(int vagas[MAX_RESERVAS][2][2], int n_vagas, char op){
    int i;
    if(n_vagas==0){
        if(op=='M'){
            printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n",8,0,17,0);
        } else if(op=='L'){
            printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n",8,0,17,30);
        }
    }
    for(i=0;i<n_vagas;i++){
        printf("Reserva disponivel entre as %02d:%02d e as %02d:%02d\n", vagas[i][0][0], vagas[i][0][1], vagas[i][1][0], vagas[i][1][1]);
    }
}

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