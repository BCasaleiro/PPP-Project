#define MAX_RESERVAS 20

int verifica_vaga(reservas lista_reservas, char op, int dia, int mes, int ano);
int agrupar_reservas(reservas lista_reservas,int reservas[MAX_RESERVAS][2] ,char op, int dia, int mes, int ano);
int agrupar_vagas(int reservas[MAX_RESERVAS][2], int vagas[MAX_RESERVAS][2], int n_reservas,char op);