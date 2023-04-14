#ifndef FUNCOESAUX_H_INCLUDED
#define FUNCOESAUX_H_INCLUDED


#define MAX_STRING 50
#define MAX_TESTES 200
#define MAX_PORTATIL 30

typedef struct
{
    int dia, mes, ano;
} tipoData;



int bissexto (int ano);
unsigned long dist_dias (tipoData inicio, tipoData fim);
int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo);
float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo);
void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres);
tipoData lerData(void);
void escreverData(tipoData data);
void limpaBufferStdin(void);
int comparaDatas(tipoData data, tipoData data1);

#endif
