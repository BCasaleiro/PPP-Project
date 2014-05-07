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
rnode* find_ant(reservas lista_reservas, char nome[]);
void delete_reserva(rnode* anterior);
prnode* find_ant_pre(prereservas lista_reservas, char nome[]);
void delete_pre(prnode* anterior);
int check_reservas(reservas lista_reservas);
int check_pre(prereservas lista_pre);
void sort(reservas lista_reservas, prereservas lista_pre, int menu);