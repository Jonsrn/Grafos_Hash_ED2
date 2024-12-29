#include <limits.h>
#ifndef _GRAFOS_H
#define _GRAFOS_H

#define MAX_VERTICES 81 // Para 4 discos, existem 3^4 = 81 configurações possíveis
#define INFINITO INT_MAX


//Prototipo dos Menus

void menu_principal(); 
void sobre();

//protótipo das funções de diagnóstico

void mensagens_criacao_grafo(int situacao);
void mensagem_operacao(int situacao);


//Protótipo das Funções auxiliares
int configuracao_para_indice(int configuracao[], int n); //Função para converter uma configuração em um índice único no grafo
void indice_para_configuracao(int indice, int configuracao[], int n);// Função para converter um índice em uma configuração
int movimento_valido(int configuracao[], int n, int origem, int destino); //// Verifica se o movimento é válido (regra da Torre de Hanói)
void criar_grafo(int n, int grafo[MAX_VERTICES][MAX_VERTICES], int *grafo_criado);  //// Criação do grafo como matriz de adjacência
void dijkstra(int grafo[MAX_VERTICES][MAX_VERTICES], int inicio, int distancias[MAX_VERTICES], int anteriores[MAX_VERTICES]); //// Algoritmo de Dijkstra para encontrar o menor caminho(Ótimo)
long long tempo_atual_nano(); //Função para medir tempo em nanossegundos
void imprimir_melhor_caminho(int grafo[MAX_VERTICES][MAX_VERTICES],int config_inicial[],int config_final[], int numero_discos,int distancias[MAX_VERTICES], int anteriores[MAX_VERTICES], int grafo_criado); 
void medir_tempo_dijkstra(int grafo[MAX_VERTICES][MAX_VERTICES], int config_inicial[], int numero_discos, int distancias[MAX_VERTICES], int anteriores[MAX_VERTICES], int grafo_criado); 





#endif