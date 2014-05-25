#define MAX_RESERVAS 20

int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano);
int agrupar_reservas(reservas lista_reservas,int reservas[MAX_RESERVAS][2] ,char op, int dia, int mes, int ano);
int agrupar_vagas(int reservas[MAX_RESERVAS][2], int vagas[MAX_RESERVAS][2][2], int n_reservas,char op);
int mostra_vagas(int vagas[MAX_RESERVAS][2][2], int n_vagas, char op);
int disponibilidade(reservas lista_reservas, char op, int hora,int min, int dia, int mes, int ano);