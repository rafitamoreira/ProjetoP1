#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "funcoes_escrever_ler_text_binario.h"

int lerFicheiroBP(tipo_portatil vetorPortatil[MAX_PORTATIL])//Ler em binario os portateis
{
    FILE *ficheiro;
    int numPortateis = 0;
    ficheiro = fopen("dados.dat", "rb");
    if (ficheiro == NULL) {
        printf("Nao existe o Ficheiro Portateis(Adicione portateis para criar o ficheiro)");
    } else {
        fread(&numPortateis, sizeof(int), 1, ficheiro);
        fread(vetorPortatil, sizeof(tipo_portatil), numPortateis, ficheiro);
        fclose(ficheiro);
    }
    return numPortateis;
}

void gravaFicheiroBP(tipo_portatil vetorPortatil[MAX_PORTATIL], int quantPortatil) {
    FILE *f;
    int saved;
    f = fopen("dados.dat", "wb");
    if (f != NULL) {
        saved = fwrite(&quantPortatil, sizeof(int), 1, f);
        if (saved != 1) {
            printf("ERRO: erro na quantidade de portateis");
        } else {
            saved = fwrite(vetorPortatil, sizeof(tipo_portatil), quantPortatil, f);
            if (saved != quantPortatil) {
                printf("ERRO NA ESCRITA DO VETOR");
            }
        }
        fclose(f);
    } else {
        printf("ERRO A ABRIR FICHEIRO");
    }
}

void escreveFichBinTets(tipo_requisicao *vetorRequisicao, int quant)//Guardar em binario as Requisicoes
{
    FILE *ficheiro;
    ficheiro = fopen("requisicao.dat", "wb");
    if (ficheiro == NULL) {
        printf("Impossivel abrir ficheiro");
    } else {
        fwrite(&quant, sizeof(int), 1, ficheiro);
        fwrite(vetorRequisicao, sizeof(tipo_requisicao), quant, ficheiro);
    }
    fclose(ficheiro);
}


tipo_requisicao *lerRequisicaoBP(tipo_requisicao *vetorRequisicao, int *portateisRequisitado, int *portateisReAtivos) {
    FILE *ficheiro;
    int i, totalRequisicao;

    ficheiro = fopen("requisicao.dat", "rb");

    if (ficheiro == NULL) {
        printf("\nAdicione Requisicoes para criar o ficheiro");
    } else {
        fread(&totalRequisicao, sizeof(int), 1, ficheiro);
        vetorRequisicao = realloc(vetorRequisicao, totalRequisicao * sizeof(tipo_requisicao));
        if (vetorRequisicao == NULL && totalRequisicao != 0) {
            printf("Erro ao reservar memoria");
            totalRequisicao = 0;
        } else {
            fread(vetorRequisicao, sizeof(tipo_requisicao), totalRequisicao, ficheiro);
            for (i = 0; i < totalRequisicao; i++) {
                if (vetorRequisicao[i].estado == 1) {
                    (*portateisReAtivos)++;
                    (*portateisRequisitado)++;

                } else {
                    (*portateisRequisitado)++;
                }
            }
            fclose(ficheiro);
        }
    }
    return vetorRequisicao;
}

void gravaFicheiroAvaria(tipo_avaria *vetorAvaria, int quantAvaria) {
    FILE *fp1, *fp2;

    fp1 = fopen("avarias.txt", "wb");
    fp2 = fopen("quantidade.txt", "wb");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return;
    }

    fwrite(vetorAvaria, sizeof(tipo_avaria), quantAvaria, fp1);
    fwrite(&quantAvaria, sizeof(int), 1, fp2);

    fclose(fp1);
    fclose(fp2);
}

tipo_avaria *leFicheiroAvaria(tipo_avaria *vetorAvaria, int *quantAvaria) {
    FILE *fp1, *fp2;

    fp1 = fopen("avarias.txt", "rb");
    fp2 = fopen("quantidade.txt", "rb");

    if (fp1 == NULL || fp2 == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
    }

    fread(quantAvaria, sizeof(int), 1, fp2);

    fread(vetorAvaria, sizeof(tipo_avaria), *quantAvaria, fp1);

    vetorAvaria = realloc(vetorAvaria, (*quantAvaria) * sizeof(tipo_requisicao));


    fclose(fp1);
    fclose(fp2);

    return vetorAvaria;
}



void devolucaoLOG(tipo_devolucao *vetorDevolucao,  int *quantDevolucoes,tipo_requisicao *vetorRequisicao , int quantRequisicoes , tipo_portatil vetorPortatil[] ,int quantPortatil)//Escrever em log as devolucoes
{
    FILE *fichRequisicao;

    fichRequisicao = fopen("devolucaoLOG.txt", "a");
    if (fichRequisicao == NULL) {
        printf("Erro a abrir ficheiro");
    } else {



        int pos = procurarequisicao(vetorRequisicao,quantRequisicoes,vetorDevolucao[*quantDevolucoes].designacao);
        int pos1 = procuraPortatil (vetorPortatil, quantPortatil,vetorRequisicao[pos].id_portatil );

        vetorRequisicao[pos].nome[0] = toupper(vetorRequisicao[pos].nome[0]);
        fprintf(fichRequisicao,"Nome: %s\n",vetorRequisicao[pos].nome);
        fprintf(fichRequisicao,"ID: %d\n",vetorPortatil[pos1].id);
        switch(vetorPortatil[pos1].processador){
        case 1:
            fprintf(fichRequisicao,"Processador: I3 \n");
            break;
        case 2:
            fprintf(fichRequisicao,"Processador: I5 \n");
            break;
        case 3:
            fprintf(fichRequisicao,"Processador: I7 \n");
            break;
        }
        fprintf(fichRequisicao,"Ram: %dGB\n",vetorPortatil[pos1].ram);
        fprintf(fichRequisicao,"Codigo da Reserva: %s\n",vetorRequisicao[pos].designacao);
        printf("%d",vetorRequisicao[pos].tipo_utente);
        switch(vetorRequisicao[pos].tipo_utente){
        case 1:
            fprintf(fichRequisicao,"Tipo de Utente: Estudante\n");
            break;
        case 2:
            fprintf(fichRequisicao,"Tipo de Utente: Docente\n");
            break;
        case 3:
            fprintf(fichRequisicao,"Tipo de Utente: Tecnico\n");
            break;
        }
        switch(vetorRequisicao[pos].estado){
        case 1:
            fprintf(fichRequisicao,"Estado de Requisicao: Ativo\n");
            break;
        case 2:
            fprintf(fichRequisicao,"Estado de Requisicao: Concluido\n");
            break;
        }

        fprintf(fichRequisicao,"Data requisicao: %d/%d/%d\n",vetorRequisicao[pos].data_requisicao.dia,vetorRequisicao[pos].data_requisicao.mes,
                                                                        vetorRequisicao[pos].data_requisicao.ano);
        fprintf(fichRequisicao,"Data: %d/%d/%d\n",vetorRequisicao[pos].data_devolucao.dia,vetorRequisicao[pos].data_devolucao.mes,
                                                                        vetorRequisicao[pos].data_devolucao.ano);
        fprintf(fichRequisicao,"Local: %s\n",vetorDevolucao[*quantDevolucoes].local);
        fprintf(fichRequisicao,"Valor da multa: %d€\n",vetorDevolucao[*quantDevolucoes].multa);
        fprintf(fichRequisicao,"--------------------------------\n");
    }
    fclose(fichRequisicao);
}
