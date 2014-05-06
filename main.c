#include <stdio.h>
#include <stdlib.h>

void menu();
void clear_screen();

int main(){
    menu();
    return 0;
}

void menu(){
    int menu;
    do{
        printf("Menu:\n1- Reservar lavagem ou manutenção\n2- Cancelar reserva de lavagem ou manutenção\n3- Cancelar pré-reserva de lavagem ou manutenção\n4-  Listar reservas e pré-reservas\n0- Sair\n O que fazer? \n");
        scanf("%d", &menu);
        switch(menu){
            case 0:
                break;
            case 1:
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

void clear_screen(){
    system("clear");
}