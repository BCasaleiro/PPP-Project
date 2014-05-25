#define MAX 101

void menu(reservas lista_reservas, prereservas lista_pre);
void reserva(reservas lista_reservas, prereservas lista_pre);
void cancela(reservas lista_reservas, prereservas lista_pre);
void cancela_pre(prereservas lista_pre);
void reservar(reservas lista_reservas, prereservas lista_pre, char op);
void cancelar(reservas lista_reservas, prereservas lista_pre, char op);
void cancelar_pre(prereservas lista_pre, char op);
int disponibilidade(reservas lista_reservas, char op, int hora,int min, int dia, int mes, int ano);
int hora_valida(int dia, int mes, int ano, int hora, int min);
void get_time(int *hora, int *min);
void update_reservas(reservas lista);
void update_prereservas(prereservas lista);
int data_valida(int dia, int mes, int ano);
void get_date(int * dia, int * mes, int * ano);
void listar(reservas lista_reservas, prereservas lista_pre);
void imprimir_reservas(reservas lista_reservas, char op);
void imprimir_pre(prereservas lista_pre, char op);
void count_reservas(reservas lista_reservas, int* lav, int* man);
void count_pre(prereservas lista_pre, int* lav, int* man);
void update_apos_cancelamento(reservas lista_reservas, prereservas lista_pre, int hora, int min, char op);
void clear_screen();