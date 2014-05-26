#define MAX 101
#define MAX_DATA 10

void load(reservas lista_reservas, prereservas lista_pre);
void menu(reservas lista_reservas, prereservas lista_pre);
void reserva(reservas lista_reservas, prereservas lista_pre);
void cancela(reservas lista_reservas, prereservas lista_pre);
void cancela_pre(prereservas lista_pre);
void reservar(reservas lista_reservas, prereservas lista_pre, char op);
void cancelar(reservas lista_reservas, prereservas lista_pre, char op);
void cancelar_pre(prereservas lista_pre, char op);
void concluida(reservas lista_reservas, prereservas lista_pre);
void conclusao(reservas lista_reservas, prereservas lista_pre, char op);
int encaixe(rnode* first, int hora_a, int min_a, char op);
int hora_valida(int dia, int mes, int ano, int hora, int min);
void get_time(int *hora, int *min);
void update_reservas(reservas lista);
void update_prereservas(prereservas lista);
int data_valida(int dia, int mes, int ano);
void get_date(int * dia, int * mes, int * ano);
void listar(reservas lista_reservas, prereservas lista_pre);
void imprimir_reservas(reservas lista_reservas, char op);
void imprimir_pre(prereservas lista_pre, char op);
void update_apos_cancelamento(reservas lista_reservas, prereservas lista_pre, int dia, int mes, int ano, int hora, int min, char op);
void clear_buffer();
void clear_screen();