#ifndef FUNCOES_PORTATIL_H_INCLUDED
#define FUNCOES_PORTATIL_H_INCLUDED


#include "funcoes_auxiliares.h"


#define ID_MIN 1111
#define ID_MAX 9999
#define TAMANHO_ID 4
#define DOIS 2
#define MAX_DESIGNACAO 4



typedef struct{
    int id,ram, estado,valor,processador,localizacao; // localizacao = 0-Residencias, 1-Campus1, 2-Campus2 e 3-Campus5 // processador (1-i3, 2-i5, 3-i7) // estado (1-disponivel, 2-requisitado, 3-avariado)
    char designacao[MAX_DESIGNACAO];
    tipoData data_portatil;
}tipo_portatil;

typedef struct{
tipo_portatil dadosPortatil;
int avaria , duracao ; // avaria temporaria(1), avaria permanente(2)
tipoData data_avaria;
char designacao[MAX_DESIGNACAO];
}tipo_avaria;





void adicionarPortatil(tipo_portatil vetorPortatil[], int *quantPortatil);
int procuraPortatil(tipo_portatil vetorPortatil[], int quantPortatil, int tempID);
int lerDadosPortatil();
void mostrarDados(tipo_portatil vetorPortatil[], int quantPortatil); // Mostrar dados do portatil
void mudarLoc(tipo_portatil vetorPortatil[],int quantPortatil); // Mudar a localização de um Portatil
tipo_avaria* registarAR(tipo_portatil vetorPortatil[],tipo_avaria *vetorAvaria,int quantPortatil, int *quantAvaria); // Registar avaria / Reparação
int procuraAvaria(tipo_avaria vetorAvaria[], int quantAvaria, char aux1[MAX_DESIGNACAO]);
void mostrarAvaria (tipo_avaria *vetorAvaria , int quantAvaria);



#endif // FUNCOES_PORTATIL_H_INCLUDED
