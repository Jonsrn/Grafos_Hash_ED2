#include <stdbool.h>
#ifndef _GRAFO_CONFIABILIDADE_H
#define _GRAFO_CONFIABILIDADE_H

#define LIMITE_VERTICES 100
#define INFINITO INT_MAX


//Prototipo das estruturas

typedef struct Aresta{
    int vertice; 
    float confiabilidade; //tem que ficar entre 0 e 1
}aresta;

typedef struct Grafo{
   aresta Arestas[LIMITE_VERTICES][LIMITE_VERTICES]; 
   int numero_vertices; 
}graf;


//prototipo dos menus

void menu_principal(); 
void sobre();

//Prototipo das mensagens de diagnóstico

void mensagem_criacao_grafo(int situacao);
void mensagem_caminho_confiavel(int situacao); 


//Protótipo das funções auxiliares

void montar_grafo(graf *Grafo, int *criado_grafo); //Função que lida com a montagem do Grafo
void descobrir_caminho_mais_confiavel(graf *Grafo, int criado_grafo); //Função auxiliar para descobrir o caminho mais confiavel;
int descobrir_menor_dist_vertice(float distancia[], bool visitados[], int numero_vertices); //Função pra descobrir a menor distancia
void dijkstra(graf *grafo, int vertice_inicial, float distancia[], int vertice_anterior[]); //Função de Dijkstra
void mostrar_caminho(int vertice_anterior[], int vertice); //Função pra exbir na tela o caminho 



#endif