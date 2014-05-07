#define MAX 101

void menu(reservas lista_reservas, prereservas lista_pre);
void reserva(reservas lista_reservas, prereservas lista_pre);
void cancela(reservas lista_reservas, prereservas lista_pre);
void cancela_pre(prereservas lista_pre);
void reservar(reservas lista_reservas, prereservas lista_pre, char op);
void cancelar(reservas lista_reservas, char op);
void cancelar_pre(prereservas lista_pre, char op);
int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano);
int disponibilidade(reservas lista_reservas,char op, int hora,int min);
void update_reservas(reservas lista);
void update_prereservas(prereservas lista);
int data_valida(int dia, int mes, int ano);
void listar(reservas lista_reservas, prereservas lista_pre);

void clear_screen();