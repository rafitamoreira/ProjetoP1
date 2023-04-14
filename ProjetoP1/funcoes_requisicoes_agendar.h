#ifndef FUNCOES_REQUISICOES_AGENDAR_H_INCLUDED
#define FUNCOES_REQUISICOES_AGENDAR_H_INCLUDED
#define MAX_PORTATIL 30
#define MAX_NOME 50


#include "funcoes_portatil.h"


typedef struct {
    int id_portatil;
    char designacao[MAX_DESIGNACAO], nome[MAX_NOME];
    int tipo_utente; // 1-Estudante ou 2-Docente ou 3-tecnico
    tipoData data_requisicao;
    int estado; // 1-ativa ou 2-concluida
    tipoData data_devolucao;
    int localizacao; // 0-Residencias, 1-Campus1, 2-Campus2 ou 3-Campus5
} tipo_requisicao;

typedef struct {
    char local[MAX_NOME];
    char designacao[MAX_DESIGNACAO];
    tipoData dataDevolucao;
    int multa;
} tipo_devolucao;


tipo_requisicao *
agendamentoPortatil(tipo_portatil vetorPortatil[MAX_PORTATIL], tipo_requisicao *vetorRequisicao, int quantPortatil,
                    int *portateisRequisitado, int *portateisReAtivos);

tipo_requisicao
lerDadosRequisicao(tipo_portatil vetorPortatil[MAX_PORTATIL], tipo_requisicao *vetorRequisicao,
                int portateisRequisitado, int *existe);

void mostrarRequisicao(tipo_requisicao vetorRequisicao[], int portateisRequisitado);

int procurarequisicao(tipo_requisicao vetorRequisicao[], int portateisRequisitados, char aux1[MAX_DESIGNACAO]);

int procuraDevolucao(tipo_devolucao vetorDevolucao[], int quantDevolucoes, char aux1[MAX_DESIGNACAO]);

int procuraDevolvido(tipo_devolucao vetorDevolucao[], tipo_requisicao vetorRequesicao[], int portateisRequisitado);

void renovarRequisicao(tipo_requisicao *vetorRequisicao, int portateisRequisitado);

void mostrarUnicaRequisicao(tipo_requisicao *vetorRequisicao, int portateisRequisitado);

tipo_devolucao *devolucaoPortatil(tipo_requisicao vetorRequisicao[], tipo_devolucao *vetorDevolucao,
                                  tipo_portatil vetorPortatil[MAX_PORTATIL], int *quantDevolucoes,
                                  int portateisRequisitado, int *portateisReAtivos , int quantPortateis);

#endif // FUNCOES_REQUISICOES_AGENDAR_H_INCLUDED
