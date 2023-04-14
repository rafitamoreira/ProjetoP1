#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "funcoes_auxiliares.h"
#include "funcoes_portatil.h"

void adicionarPortatil (tipo_portatil vetorPortatil[], int *quantPortatil) // acrescenta Portatil
{
    int aux, existe;

    do
    {
        printf("Se pretender sair clique 1");
        aux = lerInteiro("\nIndique o ID do pc",ID_MIN,ID_MAX);
        existe = procuraPortatil (vetorPortatil, *quantPortatil, aux);
        if (existe != -1)
        {
            printf("ERRO:\n Ja existe um Portatil com esse id\n");
        }

    }
    while(existe!=-1);
    if(aux == 1)
    {
        return;
    }
    vetorPortatil[*quantPortatil].id=aux;

    vetorPortatil[*quantPortatil].processador=lerInteiro("\nIndique o Processador (1-I3, 2-I5, 3-I7) ", 1,3);
    vetorPortatil[*quantPortatil].localizacao=lerInteiro("\nIndique o local: (0-Residências, 1-Campus1, 2-Campus2 , 3-Campus5) ", 0,3);
    vetorPortatil[*quantPortatil].estado=lerInteiro("\nIndique o estado: (1-disponivel, 2-requisitado , 3-avariado) ", 1,3);
    vetorPortatil[*quantPortatil].ram=lerInteiro("\nIndique a quantidade ram: ", 1,32);
    printf("Insira a data de aquisição\n");
    vetorPortatil[*quantPortatil].data_portatil = lerData();
    vetorPortatil[*quantPortatil].valor=lerInteiro("\nIndique o valor do equipamento: ",0,1000);
    (*quantPortatil)++;
    system("cls");
}


int procuraPortatil(tipo_portatil vetorPortatil[], int quantPortatil, int tempID)
{
    int i, posicao=-1;

    for(i=0; i<quantPortatil; i++)
    {
        if (vetorPortatil[i].id == tempID)
        {
            posicao = i;
            i = quantPortatil;
        }
    }

    return posicao;
}

int procuraAvaria(tipo_avaria vetorAvaria[], int quantAvaria, char aux1[MAX_DESIGNACAO])
{
    int i, pos=-1;
    for(i=0; i<quantAvaria; i++)
    {
        if(strcmp(vetorAvaria[i].designacao,aux1)==0)
        {
            pos=i;
            i=quantAvaria;
        }
    }
    return pos;
}


int lerDadosPortatil()
{
    int num;

    num = lerInteiro("\nID do portatil a registar :", ID_MIN, ID_MAX);

    return num;
}

void mostrarDados(tipo_portatil vetorPortatil[], int quantPortatil) // Mostrar dados do Portatil
{
    int i;

    if (quantPortatil==0)
    {
        printf("\nATENCAO: Nao existem portateis inscritos\n\n");
    }
    else
    {
        for (i=0; i < quantPortatil; i++)
        {
            system("cls");
            printf("\n portatil (%d/%d)", i+1, quantPortatil);
            printf("\n\nPortatil %d\n", i+1);
            printf("Nr: %d\n", vetorPortatil[i].id);
            putchar('\n');
            switch (vetorPortatil[i].processador)
            {
            case 1:
                printf("Processador: I3");
                break;
            case 2:
                printf("Processador: I5");
                break;
            case 3:
                printf("Processador: I7");
                break;
            }
            printf("\nram: %d\n", vetorPortatil[i].ram);
            putchar('\n');
            switch (vetorPortatil[i].localizacao)
            {
            case 0:
                printf("Localizacao: Residencia");
                break;
            case 1:
                printf("Localizacao: Campus1");
                break;
            case 2:
                printf("Localizacao: Campus2");
                break;
            case 3:
                printf("Localizacao: Campus5");
                break;
            }
            putchar('\n');
            switch (vetorPortatil[i].estado)
            {
            case 1:
                printf("Estado: disponivel\n");
                break;
            case 2:
                printf("Estado: requisitado\n");
                break;
            case 3:
                printf("Estado: indisponivel\n");
                break;
            }
            printf("Ano:%d Mes:%d Dia:%d", vetorPortatil[i].data_portatil.ano,vetorPortatil[i].data_portatil.mes,vetorPortatil[i].data_portatil.dia);
            char teste;
            scanf("%c", &teste);
        }
    }
}

void mudarLoc (tipo_portatil vetorPortatil[],int quantPortatil)//Alterar a localizacao de um Portatil
{
    int aux, existe;
    do
    {
        aux=lerInteiro("\nIndique o id do portatil", ID_MIN,ID_MAX);
        existe=procuraPortatil(vetorPortatil, quantPortatil, aux);
        if(existe!=-1)
        {

            vetorPortatil[existe].localizacao = lerInteiro("\nIndique o local: (0-Residencias, 1-Campus1, 2-Campus2 , 3-Campus5) ", 0,3);

        }
        else
        {
            printf ("\nERRO:O id do portatil nao existe!");
        }

    }
    while(existe==-1);
}


tipo_avaria* registarAR(tipo_portatil vetorPortatil[],tipo_avaria *vetorAvaria,int quantPortatil, int *quantAvaria)
{
    int aux, existe, existe1=-1, opcao;
    char aux1[MAX_DESIGNACAO];
    do
    {
        aux=lerInteiro("\nIndique o id do portatil", ID_MIN,ID_MAX);
        existe=procuraPortatil(vetorPortatil, quantPortatil, aux);

        if(existe!=-1)
        {
            switch (vetorPortatil[existe].estado)
            {
            case 1:
                printf("\nEstado atual: Disponível");
                opcao=lerInteiro("\nRegistar Avaria - 2  Cancelar - 3",2,3);
                break;
            case 2:
                printf("\nEstado atual: Requisitado");
                opcao=lerInteiro("\nRegistar Avaria - 2  Cancelar - 3",2,3);
                break;
            case 3:
                printf("\nEstado atual: Avariado");
                opcao=lerInteiro("\rReparar Avaria - 2  Cancelar - 3",2,3);
                if(opcao==2)
                {
                    printf("%d", existe1);
                    do
                    {
                        lerString("\nInsira a designação: ", aux1, MAX_DESIGNACAO);
                        existe1=procuraAvaria(vetorAvaria, *quantAvaria, aux1);
                    }
                    while(existe1==-1);

                    if (vetorAvaria[existe1].avaria==2)
                    {
                        printf("\nImpossivel reparar é avaria permanente");
                    }
                    else
                    {
                        vetorPortatil[existe].estado=1;
                    }
                }
                printf("\nEstado atualizado");
                break;
            }
            putchar('\n');
            if(opcao == 2)
            {
                tipo_avaria *vetorAvariaBackup;

                vetorAvariaBackup = vetorAvaria;

                vetorAvaria = realloc(vetorAvaria,(*quantAvaria+1)*sizeof(tipo_avaria));

                if (vetorAvaria == NULL)
                {

                    printf("\nERRO! Impossivel reservar memoria.");
                    vetorAvaria = vetorAvariaBackup;

                }
                else
                {
                    do
                    {
                        lerString("\nInsira a designação: ", aux1, MAX_DESIGNACAO);
                        existe1=procuraAvaria(vetorAvaria, *quantAvaria, aux1);
                    }
                    while(existe1!=-1);
                    strcpy(vetorAvaria[*quantAvaria].designacao,aux1);
                    vetorPortatil[existe].estado = 3;
                    (*quantAvaria)++;

                }
                if (vetorAvaria[existe1].avaria == 2)
                {
                    printf("Não dá para ser reparado");
                }
                else
                {
                    opcao = lerInteiro("\nAvaria temporaria - 1  Avaria Permanente - 2  Cancelar - 3", 1,3);
                    switch (opcao)
                    {
                    case 1:
                        vetorAvaria[*quantAvaria].avaria=1;
                        vetorPortatil[existe].estado = 3;
                        vetorAvaria[*quantAvaria].data_avaria = lerData();
                        break;
                    case 2:
                        vetorAvaria[*quantAvaria].avaria=2;
                        break;
                    default:
                        existe=1;
                        break;
                    }

                }
            }
        }

    }
    while(existe==-1);


    return vetorAvaria;
}

void mostrarAvaria (tipo_avaria *vetorAvaria, int quantAvaria)
{
    if(quantAvaria<=0)
    {

        printf("\nNão há avarias");
        return;
    }
    else
    {
        for (int i = 0 ; i<quantAvaria ; i++)
        {
            printf("%s" ,vetorAvaria[i].designacao);
            printf("%d" ,vetorAvaria[i].duracao);
            printf("%s" ,vetorAvaria[i].designacao);
        }

    }
}







