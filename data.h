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
int insert_reserva(reservas r, int dia, int mes, int ano, int hora, int min, char nome[]);
int insert_pre_reserva(preresevas pr, char op, int dia, int mes, int ano, char nome[]);