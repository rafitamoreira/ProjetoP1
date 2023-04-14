#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#include "funcoes_portatil.h"
#include "funcoes_escrever_ler_text_binario.h"
#include "funcoes_requisicoes_agendar.h"
#include "funcoes_auxiliares.h"


#define INDEX 52


char menu(int quantPortatil, int portateisDisponivel, int portateisRequisitado, int portateisReAtivos);

void percProcessador(tipo_portatil vetorPortatil[MAX_PORTATIL], int quantPortatil);
int menorUtente(tipo_requisicao *vetorRequisicao, int quantRequisicoes);
float multaMedia(int quantRequisicao, tipo_requisicao *vetorRequisicao);
tipoData dataRecente(tipo_devolucao *vetorDevolucao, int quantDevolucoes);

char menuPortatil();

char menuRequisicao();

int main()
{
    setlocale(LC_ALL, "");
    int quantPortatil = 0, quantAvaria = 0, portateisDisponivel = 0, portateisRequisitado = 0, portateisReAtivos = 0, quantDevolucoes = 0;
    tipo_portatil vetorPortatil[MAX_PORTATIL];
    tipo_requisicao *vetorRequisicao=NULL;
    tipo_avaria *vetorAvaria = NULL;
    tipo_devolucao *vetorDevolucao = NULL;
    char opcao;
    quantPortatil = lerFicheiroBP(vetorPortatil);
    vetorRequisicao = lerRequisicaoBP(vetorRequisicao, &portateisRequisitado, &portateisReAtivos);
    vetorAvaria = leFicheiroAvaria(vetorAvaria,&quantAvaria);


    do
    {
        portateisDisponivel = quantPortatil - portateisReAtivos;
        opcao = menu(quantPortatil, portateisDisponivel, portateisRequisitado, portateisReAtivos);
        int requisicaoTotal = portateisRequisitado;
        escreveFichBinTets(vetorRequisicao, requisicaoTotal);
        gravaFicheiroBP(vetorPortatil, quantPortatil);
        gravaFicheiroAvaria(vetorAvaria,quantAvaria);
        system("cls");
        char opTeste;
        switch (opcao)
        {

        case 'A':
            do
            {
                opTeste = menuPortatil();
                system("cls");
                switch (opTeste)
                {
                case 'A':
                    if (quantPortatil < MAX_PORTATIL)
                    {
                        adicionarPortatil(vetorPortatil, &quantPortatil);
                    }
                    break;
                case 'B':

                    if (quantPortatil < 0)
                    {
                        printf("\nNão existem portateis");
                    }
                    else
                    {
                        mostrarDados(vetorPortatil, quantPortatil);
                    }
                    break;
                case 'C':
                    mudarLoc(vetorPortatil, quantPortatil);
                    break;
                case 'E':
                    vetorAvaria = registarAR(vetorPortatil, vetorAvaria, quantPortatil, &quantAvaria);
                    break;
                case 'G':
                    if (portateisReAtivos == 0)
                    {
                        printf("\nNão existe portateis requisitados ativos");
                    }
                    else
                    {
                        vetorDevolucao = devolucaoPortatil(vetorRequisicao, vetorDevolucao, vetorPortatil,
                                                           &quantDevolucoes, portateisRequisitado,
                                                           &portateisReAtivos, quantPortatil);
                    }
                    break;

                case 'H':
                     mostrarAvaria (vetorAvaria, quantAvaria);
                    break;
                }

            }
            while (opTeste != 'F');

            break;

        case 'B':
            do
            {
                opTeste = menuRequisicao();
                system("cls");
                switch (opTeste)
                {
                case 'A':
                    if (quantPortatil > 0)
                    {
                        vetorRequisicao = agendamentoPortatil(vetorPortatil, vetorRequisicao, quantPortatil,
                                                              &portateisRequisitado, &portateisReAtivos);
                    }
                    else
                    {
                        printf("\nERRO:Nao existe portateis para requisitar");
                    }
                    break;
                case 'B':
                    if (quantPortatil > 0)
                    {
                        mostrarRequisicao(vetorRequisicao, portateisRequisitado);
                    }
                    else
                    {
                        printf("\nERRO:Nao existe portateis para requisitar");
                    }
                    break;
                case 'C':
                    if (portateisRequisitado > 0)
                    {
                        renovarRequisicao(vetorRequisicao, portateisRequisitado);
                    }
                    else
                    {
                        printf("\nERRO:Nao existe portateis requisitados");
                    }
                    break;

                case 'E':
                    mostrarUnicaRequisicao(vetorRequisicao, portateisRequisitado);
                    break;
                }

            }
            while (opTeste != 'F');
            break;
        case 'C':
            if(quantPortatil>0){
            menorUtente(vetorRequisicao, portateisRequisitado);
            //tipoData dataRecente = dataRecente(*vetorDevolucao,quantDevolucoes);
            multaMedia(portateisRequisitado, vetorRequisicao);
            percProcessador(vetorPortatil, quantPortatil);
            }else{
            printf("Ainda não existem dados suficientes para calcular as estatísticas");
            }


            break;


        }
    }
    while (opcao != 'F');

    free(vetorRequisicao);
    free(vetorAvaria);
    free(vetorDevolucao);

    return 0;

}

char menu(int quantPortatil, int portateisDisponivel, int portateisRequisitado, int portateisReAtivos)//Menu
{
    char op;
    printf("\n\n********** Contadores **********************");
    printf("\n\nQuantidade de Portateis: %2d", quantPortatil);
    printf("\nQuantidade de portateis disponiveis:    %2d", portateisDisponivel);
    printf("\nQuantidade de requisicões efetuadas:   %2d", portateisRequisitado);
    printf("\nQuantidade de portateis requisitados ativos:   %2d", portateisReAtivos);
    printf("\n\n********** MENU PRINCIPAL ******************");
    printf("\nA - Menu Portateis\nB - Menu Requisições\nC - Mostrar Estatisticas");
    printf("\n\n\n\nF - Fim");
    printf("\n\nOpcao--> ");
    scanf("%c", &op);
    printf("\n************************************************\n");
    limpaBufferStdin();
    op = toupper(op);
    return op;
}

char menuPortatil()
{
    char opTeste;
    printf("\n\n********** Computadores **********************");
    printf("\nA - Acrescentar Portateis\nB - Mostrar Portateis\nC - Mudar localizacao portatil\nE - Registar avaria/Reparar\nG - Devolver Portatil\nH - Mostrar Avarias\nF - Sair");
    printf("\n************************************************\n");
    printf("Digite a sua opcão: ");
    scanf("%c", &opTeste);
    limpaBufferStdin();
    opTeste = toupper(opTeste);
    return opTeste;
}

char menuRequisicao()
{
    char opTeste;
    printf("\n\n********** Requisições **********************");
    printf("\nA - Agendar Requisicao de portatil\nB - Mostrar Requisições\nC - Renovar Requisicao\nE - Mostrar uma Requisição\nF - Sair");
    printf("\n************************************************\n");
    printf("Digite a sua opção: ");
    scanf(" %c", &opTeste);
    limpaBufferStdin();
    opTeste = toupper(opTeste);
    return opTeste;

}

void percProcessador(tipo_portatil vetorPortatil[], int quantPortatil)
{
    int i, i3 = 0, i5 = 0, i7 = 0;

    for (i = 0; i < quantPortatil; i++)
    {

        switch (vetorPortatil[i].processador)
        {
        case 1 :
            i3++;
            break;
        case 2 :
            i5++;
            break;
        default:
            i7++;
            break;
        }
    }
    float percProcessadorI3 = i3 * 100 / quantPortatil;
    float percProcessadorI5 = i5 * 100 / quantPortatil;
    float percProcessadorI7 = i7 * 100 / quantPortatil;
    printf("\n---------------------------");
    printf("\n Processador I3 : %.2f%%\n",percProcessadorI3);
    printf("\n Processador I5 : %.2f%%\n",percProcessadorI5);
    printf("\n Processador I7 : %.2f%%",percProcessadorI7);
}



