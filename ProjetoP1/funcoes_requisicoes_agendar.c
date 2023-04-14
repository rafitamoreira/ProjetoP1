#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "funcoes_requisicoes_agendar.h"
#include "funcoes_escrever_ler_text_binario.h"
#include "funcoes_portatil.h"
#include "funcoes_auxiliares.h"


tipo_requisicao
lerDadosRequisicao(tipo_portatil vetorPortatil[MAX_PORTATIL], tipo_requisicao *vetorRequisicao,
                   int portateisRequisitado, int *existe)
{
    int controlo = 0, procura = 0;
    char aux[MAX_DESIGNACAO];
    vetorRequisicao[portateisRequisitado].id_portatil = vetorPortatil[*existe].id;
    do
    {
        lerString("\nDigite a designacão da requisição: ", aux, MAX_DESIGNACAO);

        procura = procurarequisicao(vetorRequisicao, portateisRequisitado, aux);
        if (procura == -1)
        {
            strcpy(vetorRequisicao[portateisRequisitado].designacao, aux);
        }
        else
        {
            printf("A designação já existe");
        }
    }
    while (procura != -1);

    vetorRequisicao[portateisRequisitado].tipo_utente = lerInteiro(
                "\nIndique o tipo de Utente  (1-Estudante, 2-Docente, 3-Tecnico administrativo) ", 1, 3) - 1;
    lerString("Insira o nome: ", vetorRequisicao[portateisRequisitado].nome, MAX_NOME);

    do
    {
        printf("\nInsira a data de requisicao: ");
        vetorRequisicao[portateisRequisitado].data_requisicao = lerData();
        printf("\nInsira a data de devolucao: ");
        vetorRequisicao[portateisRequisitado].data_devolucao = lerData();

        controlo = comparaDatas(vetorRequisicao[portateisRequisitado].data_requisicao,
                                vetorRequisicao[portateisRequisitado].data_devolucao);

    }
    while (controlo == -1);
    vetorRequisicao[portateisRequisitado].localizacao = lerInteiro(
                "\nIndique o local: (0-Residencias, 1-Campus1, 2-Campus2 , 3-Campus5) ", 0, 3);
    vetorRequisicao[portateisRequisitado].estado = 1;
    vetorPortatil[*existe].estado = 2;

    return *vetorRequisicao;
}


tipo_requisicao *
agendamentoPortatil(tipo_portatil vetorPortatil[MAX_PORTATIL], tipo_requisicao *vetorRequisicao, int quantPortatil,
                    int *portateisRequisitado, int *portateisReAtivos)
{

    int aux, existe;
    tipo_requisicao *vetorRequisicaoBackup;

    vetorRequisicaoBackup = vetorRequisicao;


    printf("\nAGENDAMENTO DE PORTATIL\n");

    if (quantPortatil == 0)
    {

        printf("\nNao existem membros registados.");

    }
    else
    {
        aux = lerInteiro("Indique o id do portatil", ID_MIN, ID_MAX);
        existe = procuraPortatil(vetorPortatil, quantPortatil, aux);
        if (vetorPortatil[existe].estado != 1 || existe == -1)
        {
            printf("Portatil está indisponivel");
            return 0;
        }


        vetorRequisicao = realloc(vetorRequisicao, (quantPortatil + 1) * sizeof(tipo_requisicao));

        if (vetorRequisicao == NULL)
        {

            printf("\nERRO! Impossivel reservar memoria.");
            vetorRequisicao = vetorRequisicaoBackup;

        }
        else
        {

            vetorRequisicao[quantPortatil] = lerDadosRequisicao(vetorPortatil, vetorRequisicao,
                                             *portateisRequisitado, &existe);

            (*portateisRequisitado)++;
            (*portateisReAtivos)++;

            printf("\nAgendamento com sucesso.");
        }

    }

    return vetorRequisicao;
}


int procurarequisicao(tipo_requisicao vetorRequisicao[], int portateisRequisitados, char aux1[MAX_DESIGNACAO])
{
    int i, pos = -1;
    for (i = 0; i < portateisRequisitados; i++)
    {
        if (strcmp(vetorRequisicao[i].designacao, aux1) == 0)
        {
            pos = i;
            i = portateisRequisitados;
        }
    }
    return pos;
}

int procuraDevolucao(tipo_devolucao vetorDevolucao[], int quantDevolucoes, char aux1[MAX_DESIGNACAO])
{
    int i, pos = -1;
    for (i = 0; i < quantDevolucoes; i++)
    {
        if (strcmp(vetorDevolucao[i].designacao, aux1) == 0)
        {
            pos = i;
            i = quantDevolucoes;
        }
    }
    return pos;
}

int procuraDevolvido(tipo_devolucao vetorDevolucao[], tipo_requisicao vetorRequesicao[], int portateisRequisitado)
{
    int i, pos = -1;
    for (i = 0; i < portateisRequisitado; i++)
    {
        if (strcmp(vetorDevolucao[i].designacao, vetorRequesicao[i].designacao) == 0 &&
                vetorRequesicao[i].estado == 2)
        {
            pos = i;
            i = portateisRequisitado;
        }
    }
    return pos;
}


void mostrarRequisicao(tipo_requisicao *vetorRequisicao, int portateisRequisitado)
{
    printf("\n Mostrar dados da requisição:\n");
    for (int i = 0; i < portateisRequisitado; i++)
    {
        printf("\n------------------------------------------------\n ID: %d", vetorRequisicao[i].id_portatil);
        printf("\n Designação: %s", vetorRequisicao[i].designacao);
        printf("\n Nome:  %s", vetorRequisicao[i].nome);
        printf("\n Tipo de utente: ");
        //putchar('\n');
        switch (vetorRequisicao[i].tipo_utente)
        {
        case 0:
            printf("Estudante");
            break;
        case 1:
            printf("Docente");
            break;
        default:
            printf("Técnico Administrativo");
            break;
        }
        printf("\n A duração foi de %lu dias\n",
               dist_dias(vetorRequisicao[i].data_requisicao, vetorRequisicao[i].data_devolucao));
        int dias = dist_dias(vetorRequisicao[i].data_requisicao, vetorRequisicao[i].data_devolucao);
        if (dias > 30)
        {
            int multa = dias - 30;
            multa = multa * 10;
            printf(" Multa de pagamento: %d$\n", multa);
        }
        switch (vetorRequisicao[i].localizacao)
        {
        case 0:
            printf(" Localizacao: Residencia");
            break;
        case 1:
            printf(" Localizacao: Campus1");
            break;
        case 2:
            printf(" Localizacao: Campus2");
            break;
        case 3:
            printf(" Localizacao: Campus5");
            break;
        }
    }
}

void renovarRequisicao(tipo_requisicao *vetorRequisicao, int portateisRequisitados)
{
    int existe, dias;
    tipo_requisicao *requisicao;
    requisicao = vetorRequisicao;
    char aux[MAX_DESIGNACAO];
    if (requisicao == NULL)
    {
        printf("Erro - Impossivel renovar Requisicao");
        vetorRequisicao = requisicao;
    }
    else
    {
        do
        {
            lerString("\nDigite a designacão da requisição: ", aux, MAX_DESIGNACAO);
            existe = procurarequisicao(vetorRequisicao, portateisRequisitados, aux);
            if (existe != -1)
            {
                dias = (dist_dias(vetorRequisicao[existe].data_requisicao, vetorRequisicao[existe].data_devolucao));
                if (dias <= 7)
                {
                    printf("\nInsira a nova data de requisicao: ");
                    vetorRequisicao[existe].data_requisicao = lerData();
                    printf("\nInsira a nova data de devolucao: ");
                    vetorRequisicao[existe].data_devolucao = lerData();
                }
                else
                {
                    printf("Passou o prazo de renovar");
                }
            }
        }
        while (existe == -1);

    }
}


void mostrarUnicaRequisicao(tipo_requisicao *vetorRequisicao, int portateisRequisitado)
{
    int existe;
    tipo_requisicao *requisicao;
    requisicao = vetorRequisicao;
    char aux[MAX_DESIGNACAO];
    if (requisicao == NULL)
    {
        printf("Erro - Impossivel mostrar Requisicao");
        vetorRequisicao = requisicao;
    }
    else
    {
        do
        {
            lerString("\nDigite a designacão da requisição: ", aux, MAX_DESIGNACAO);
            existe = procurarequisicao(vetorRequisicao, portateisRequisitado, aux);
            if (existe != -1)
            {
                printf("A designação é %s", vetorRequisicao[existe].designacao);
                switch (vetorRequisicao[existe].estado)
                {
                case 1:
                    printf("\nEstado: ATIVA");
                    break;
                case 2:
                    printf("\nEstado: Concluída");
                    break;
                }
                printf("\nA diferença de dias é de %lu",
                       dist_dias(vetorRequisicao[existe].data_requisicao, vetorRequisicao[existe].data_devolucao));
            }
            else
                printf("\nDesignacao errada");
        }
        while (existe == -1);

    }

}


tipo_devolucao *devolucaoPortatil(tipo_requisicao vetorRequisicao[], tipo_devolucao *vetorDevolucao,
                                  tipo_portatil vetorPortatil[MAX_PORTATIL], int *quantDevolucoes,
                                  int portateisRequisitado, int *portateisReAtivos , int quantPortateis)
{
    int existe,local;
    long multa;
    int controlo = 0;
    tipo_requisicao *requisicao;
    requisicao = vetorRequisicao;
    char aux[MAX_DESIGNACAO];
    if (requisicao == NULL)
    {
        printf("Erro - Impossivel mostrar Requisicao");
    }
    else
    {
        do
        {
            lerString("\nDigite a designacão da requisição: ", aux, MAX_DESIGNACAO);
            existe = procurarequisicao(vetorRequisicao, portateisRequisitado, aux);
        }
        while (existe == -1);
        do
        {
            vetorDevolucao = realloc(vetorDevolucao, ((*quantDevolucoes) + 1) * sizeof(tipo_devolucao));
            strcpy(vetorDevolucao[*quantDevolucoes].designacao,vetorRequisicao[existe].designacao);
           int id = vetorRequisicao[existe].id_portatil;
            int portatil = procuraPortatil(vetorPortatil,quantPortateis , id);
            vetorPortatil[portatil].estado=1;
            printf("\nInsira a data de devolução : ");
            printf("A data de devolução da requisição é | Ano:%d Mes:%d Dia:%d\n" , vetorRequisicao[existe].data_devolucao.ano,vetorRequisicao[existe].data_devolucao.mes,
                                                                        vetorRequisicao[existe].data_devolucao.dia);
            vetorDevolucao[*quantDevolucoes].dataDevolucao = lerData();
            int diferenca = comparaDatas(vetorRequisicao[existe].data_devolucao, vetorDevolucao[*quantDevolucoes].dataDevolucao);
            if(diferenca==-1)
            {
               printf("\nERRO:Não pode inserir uma data anterior a data devolução da requisição!");
               return 0;
            }
        }
        while (controlo == -1);

        local = lerInteiro("\nLocalização da entrega do portatil: 0-Residências, 1-Campus1, 2-Campus2 , 3-Campus5", 0,
                           3);
        switch (local)
        {
        case 0:
            strcpy(vetorDevolucao[*quantDevolucoes].local, "Residências");
            printf(" A localização é: %s\n", vetorDevolucao[*quantDevolucoes].local);
            break;
        case 1:
            strcpy(vetorDevolucao[*quantDevolucoes].local, "Campus1");
            printf(" A localização é: %s\n", vetorDevolucao[*quantDevolucoes].local);
            break;
        case 2:
            strcpy(vetorDevolucao[*quantDevolucoes].local, "Campus2");
            printf(" A localização é: %s\n", vetorDevolucao[*quantDevolucoes].local);
            break;
        case 3:
            strcpy(vetorDevolucao[*quantDevolucoes].local, "Campus5");
            printf(" A localização é: %s\n", vetorDevolucao[*quantDevolucoes].local);
            break;
        }
        unsigned long dias = dist_dias(vetorRequisicao[existe].data_devolucao, vetorDevolucao[*quantDevolucoes].dataDevolucao);
        printf("\nDias: %lu", dias);

        if (dias > 30)
        {
            multa = dias - 30;
            vetorDevolucao[*quantDevolucoes].multa = multa * 10;
            printf("\nMulta de %lu dias, Total a pagar é %d €", multa, vetorDevolucao[*quantDevolucoes].multa);
        }
        else
        {
            vetorDevolucao[*quantDevolucoes].multa = 0;
            printf("\nNão tem multa");
        }

        (portateisReAtivos)--;
        devolucaoLOG(vetorDevolucao, quantDevolucoes,vetorRequisicao ,portateisRequisitado ,vetorPortatil ,quantPortateis);
        vetorRequisicao[existe].estado = 2;
    }



    return vetorDevolucao;

}

















