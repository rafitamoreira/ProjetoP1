#ifndef OBJETOMEMBRO_H_INCLUDED
#define OBJETOMEMBRO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "funcoes_auxiliares.h"
#include "funcoes_escrever_ler_text_binario.h"

int dias_mes[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
tipoData dataRecente(tipo_devolucao *vetorDevolucao, int quantDevolucoes);
float multaMedia(int quantRequisicao, tipo_requisicao *vetorRequisicao);
int menorUtente(tipo_requisicao *vetorRequisicao, int quantRequisicoes);

unsigned long dist_dias (tipoData inicio, tipoData fim)
{
    unsigned long idias, fdias;	/* guarda qtos dias tem da data */
    /* ate o comeco do ano */
    unsigned long def_anos = 0;	/* guarda diferenca entre anos das */
    /* datas inicio e fim medida em dias */
    register int i;
    int dbissexto;

    idias = inicio.dia;
    dbissexto = bissexto (inicio.ano);
    for (i = inicio.mes - 1; i > 0; --i)
        idias += dias_mes[dbissexto][i];

    fdias = fim.dia;
    dbissexto = bissexto (fim.ano);
    for (i = fim.mes - 1; i > 0; --i)
        fdias += dias_mes[dbissexto][i];

    while (inicio.ano < fim.ano)
        def_anos += 365 + bissexto(inicio.ano++);

    return def_anos - idias + fdias;
}


int bissexto (int ano)
{
    return (ano % 4 == 0) && ((ano % 100 != 0) || (ano % 400 == 0));
}

tipoData dataRecente(tipo_devolucao *vetorDevolucao, int quantDevolucoes)
{
    int anoRecente=0,mesRecente=0,diaRecente=0,i;

    for(i=0; i<quantDevolucoes; i++)
    {

        if(anoRecente<vetorDevolucao[i].dataDevolucao.ano)
        {

            anoRecente=vetorDevolucao[i].dataDevolucao.ano;
            mesRecente=vetorDevolucao[i].dataDevolucao.mes;
            diaRecente=vetorDevolucao[i].dataDevolucao.dia;

        }
        else
        {
            if(anoRecente==vetorDevolucao[i].dataDevolucao.ano)
            {
                if(mesRecente<vetorDevolucao[i].dataDevolucao.mes)
                {

                    anoRecente=vetorDevolucao[i].dataDevolucao.ano;
                    mesRecente=vetorDevolucao[i].dataDevolucao.mes;
                    diaRecente=vetorDevolucao[i].dataDevolucao.dia;
                }
                else
                {
                    if(mesRecente==vetorDevolucao[i].dataDevolucao.mes)
                    {
                        if(diaRecente<vetorDevolucao[i].dataDevolucao.dia)
                        {
                            anoRecente=vetorDevolucao[i].dataDevolucao.ano;
                            mesRecente=vetorDevolucao[i].dataDevolucao.mes;
                            diaRecente=vetorDevolucao[i].dataDevolucao.dia;
                        }
                    }
                }
            }
        }
    }
    tipoData dataRecente;
    dataRecente.ano = anoRecente;
    dataRecente.mes = mesRecente;
    dataRecente.dia = diaRecente;


    return dataRecente;
}

int comparaDatas(tipoData data, tipoData data1)
{
    int controlo;
    unsigned int dataC;
    unsigned int data1C;
    dataC = data.ano*10000+data.mes*100+data.dia; // data requisição

    data1C = data1.ano*10000+data1.mes*100+data1.dia; // data devolução

    if(dataC > data1C)
    {
        controlo = -1;
    }
    else
    {
        if(data1C > dataC)
        {
            controlo = 1;
        }
        else
        {
            controlo = 1;
        }
    }
    return controlo;
}

int menorUtente(tipo_requisicao *vetorRequisicao, int quantRequisicoes)
{
    int menor=0, i=0,estudante=0,docente=0,tecnico=0, controlo=0;

    if(quantRequisicoes==0)
    {
        printf("\nNao existem requisicoes!");
    }
    else
    {
        for(i=0; i<quantRequisicoes; i++)
        {

            switch(vetorRequisicao[i].tipo_utente)
            {
            case 0:
                estudante++;
                break;
            case 1:
                docente++;
                break;
            case 2:
                tecnico++;
                break;
            }
        }
        if(estudante<docente && estudante<tecnico)
        {
            menor=estudante;
            printf("\nO tipo de utente com menor numero de requisicoes e o estudante, com %d requisicoes", menor);
            controlo=0;
        }
        else
        {
            if(docente<estudante && docente<tecnico)
            {
                menor=docente;
                printf("\nO tipo de utente com menor numero de requisicoes e o docente, com %d requisicoes", menor);
                controlo=1;
            }
            else
            {
                if(docente==estudante && docente==tecnico){
                    printf("\nNao existe nenhum tipo de utente com menos requisicoes do que os outros!");
                }
                menor=tecnico;
                printf("\nO tipo de utente com menor numero de requisicoes e o tecnico, com %d requisicoes", menor);
                controlo=2;
            }
        }
    }

    return controlo;
}

float multaMedia(int quantRequisicao, tipo_requisicao *vetorRequisicao)
{
    int i=0,somaMulta=0;
    float multaMedia=0.0;

    for(i=0; i<quantRequisicao; i++)
    {
        int dias = dist_dias(vetorRequisicao[i].data_requisicao, vetorRequisicao[i].data_devolucao);
        if (dias>30)
        {
            int multa = dias-30;
            if(multa!=0)
            {
                multa = multa*10;
                somaMulta = somaMulta + multa;
            }

        }
    }
    multaMedia = (float)somaMulta/(float)quantRequisicao;
    printf("\nA multa media e de %.1f$", multaMedia);
    return multaMedia;
}


tipoData lerData()
{
    tipoData nova;
    int limite;
    nova.ano=lerInteiro("Indique ano ", 2000, 2023);
    nova.mes=lerInteiro("Indique mês ", 1,12);
    switch (nova.mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        limite=31;
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        limite=30;
        break;
    case 2:
        if((nova.ano%400==0) || (nova.ano%4==0 && nova.ano%100!=0))
        {
            limite=29;
        }
        else
        {
            limite=28;
        }
    }
    nova.dia=lerInteiro("Indique dia ", 1, limite);
    return nova;
}

float lerFloat(char mensagem[MAX_STRING], float minimo, float maximo)
{
    float numero;
    int controlo;
    do
    {
        printf("%s (%.2f a %.2f) :", mensagem, minimo, maximo);
        controlo = scanf ("%f", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();
        if (controlo == 0)
        {
            printf("Devera inserir um numero decimal (float) \n");
        }
        else
        {
            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }
        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);
    return numero;
}

void lerString(char mensagem[MAX_STRING], char vetorCaracteres[MAX_STRING], int maximoCaracteres)
{
    int tamanhoString;
    do          // Repete leitura caso sejam obtidas strings vazias
    {
        printf("%s", mensagem);
        fgets(vetorCaracteres, maximoCaracteres, stdin);
        tamanhoString = strlen(vetorCaracteres);
        if (tamanhoString == 1)
        {
            printf("Nao foram introduzidos caracteres!!! . apenas carregou no ENTER \n\n");  // apenas faz sentido limpar buffer se a ficarem caracteres
        }
    }
    while (tamanhoString == 1);
    if(vetorCaracteres[tamanhoString-1] != '\n')  // ficaram caracteres no buffer....
    {
        limpaBufferStdin();  // apenas faz sentido limpar buffer se a ficarem caracteres
    }
    else
    {
        vetorCaracteres[tamanhoString-1] = '\0';    //Elimina o \n da string armazenada em vetor
    }
}

int lerInteiro(char mensagem[MAX_STRING], int minimo, int maximo)
{
    int numero, controlo;
    do
    {
        printf("%s (%d a %d) :", mensagem, minimo, maximo);
        controlo = scanf ("%d", &numero);  // scanf devolve quantidade de valores vàlidos obtidos
        limpaBufferStdin();     //limpa todos os caracteres do buffer stdin (nomeadamente o \n)
        if (controlo == 0)
        {
            printf("Devera inserir um numero inteiro \n");
        }
        else
        {
            if(numero == 1)
            {
                return 1;
            }
            if(numero<minimo || numero>maximo)
            {
                printf("Numero invalido. Insira novamente:\n");
            }

        }
    }
    while(numero<minimo || numero>maximo || controlo ==0);

    return numero;
}

void limpaBufferStdin(void)
{
    char chr;
    do
    {
        chr = getchar();
    }
    while (chr != '\n' && chr != EOF);
}




#endif
