#define MAX 101

void menu(reservas lista_reservas, prereservas lista_pre);
void reserva(reservas lista_reservas, prereservas lista_pre);
void reservar(reservas lista_reservas, prereservas lista_pre, char op);
int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano);
int disponibilidade(reservas lista_reservas,char op, int hora,int min);
void clear_screen();