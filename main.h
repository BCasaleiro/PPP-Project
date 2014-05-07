#define MAX 101

void menu(reservas lista_reservas, prereservas lista_pre);
void reserva(reservas lista_reservas, prereservas lista_pre);
void cancela(reservas lista_reservas, prereservas lista_pre);
void reservar(reservas lista_reservas, prereservas lista_pre, char op);
void cancelar(reservas lista_reservas, char op);
int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano);
int disponibilidade(reservas lista_reservas,char op, int hora,int min);
void update_reservas(reserva lista);
void update_prereservas(prereserva lista);
void clear_screen();