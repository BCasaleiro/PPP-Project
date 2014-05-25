#define MAX 101

typedef struct rnode* reservas;
typedef struct rnode {
    char op;
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    char nome[MAX];
    reservas next;
} rnode;

typedef struct prnode* prereservas;
typedef struct prnode{
    char op;
    int dia;
    int mes;
    int ano;
    char nome[MAX];
    prereservas next;
}prnode;

reservas create_reservas();
prereservas create_pre_reservas();
int insert_reserva(reservas r, char op, int dia, int mes, int ano, int hora, int min, char nome[]);
int insert_pre_reserva(prereservas pr, char op, int dia, int mes, int ano, char nome[]);
rnode* find_ant(reservas lista_reservas, char nome[], char op);
void delete_reserva(rnode* anterior);
prnode* find_ant_pre(prereservas lista_reservas, char nome[], char op);
void delete_pre(prnode* anterior);
int check_reservas(reservas lista_reservas, int menu);
int check_pre(prereservas lista_pre, int menu);
void sort_reservas(reservas lista_reservas, int menu);
void sort_pre(prereservas lista_pre, int menu);
int troca_reservas(int menu, reservas aux);
int troca_pre(int menu, prereservas aux);
void count_reservas(reservas lista_reservas, int* lav, int* man);
void count_pre(prereservas lista_pre, int* lav, int* man);