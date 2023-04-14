#ifndef FUNCOES_ESCREVER_LER_TEXT_BINARIO_H_INCLUDED
#define FUNCOES_ESCREVER_LER_TEXT_BINARIO_H_INCLUDED


#include "funcoes_auxiliares.h"
#include "funcoes_portatil.h"
#include "funcoes_requisicoes_agendar.h"


int lerFicheiroBP(tipo_portatil vetorPortatil[MAX_PORTATIL]);
void gravaFicheiroBP(tipo_portatil vetorPortatil[] , int quantPortatil);
tipo_requisicao *lerRequisicaoBP(tipo_requisicao *vetorRequisicao , int *portateisRequisitado , int *portateisReAtivos);
void escreveFichBinTets(tipo_requisicao *vetorRequisicao, int quant);
void devolucaoLOG(tipo_devolucao *vetorDevolucao,  int *quantDevolucoes,tipo_requisicao *vetorRequisicao , int quantRequisicoes , tipo_portatil vetorPortatil[] ,int quantPortatil);//Escrever em log as devolucoes
void gravaFicheiroAvaria(tipo_avaria *vetorAvaria, int quantAvaria);
tipo_avaria *leFicheiroAvaria(tipo_avaria *vetorAvaria, int *quantAvaria);



#endif // FUNCOES_ESCREVER_LER_TEXT_BINARIO_H_INCLUDED
