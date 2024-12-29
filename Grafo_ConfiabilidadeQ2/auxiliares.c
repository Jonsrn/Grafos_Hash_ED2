#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include "grafo_confiabilidade.h"



//Função de montagem do Grafo 

void montar_grafo(graf *Grafo, int *criado_grafo){
    int situacao, numero_vertices, numero_arestas, confirmacao; 

    if(*criado_grafo == 0){
       
        do{
            printf("Digite o Número de Vértices: "); 
            scanf("%d", &numero_vertices); 
            if(numero_vertices > 0){
                confirmacao = 1;
            }else{
                confirmacao = 0; 
                printf("Digite um valor válido\n"); 
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
            } 


        }while(confirmacao == 0);

        Grafo->numero_vertices = numero_vertices; 
        
        //Inicializando Grafo, com um valor qualquer temporario
        for (int i = 0; i < numero_vertices; i++){
            for(int j = 0; j < numero_vertices; j++){
                Grafo->Arestas[i][j].confiabilidade = -1; 
            }
        }


        do{
            printf("Digite o Número de Arestas: "); 
            scanf("%d",&numero_arestas); 

            if(numero_arestas > 0){
                confirmacao = 1;
            }else{
                confirmacao = 0; 
                printf("Digite um valor válido\n"); 
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
            }
        }while(confirmacao == 0);

        for(int i = 0; i < numero_arestas; i++){
            int vertice_origem, vertice_destino; 
            float confiabilidade;
            
            printf("Aresta: %d\n", i + 1);
            
            do{
            printf("Digite o Vertice de Origem: "); 
            scanf("%d", &vertice_origem); 

            if(vertice_origem >= 0 && vertice_origem < numero_vertices){
                confirmacao = 1;
            }else{
                confirmacao = 0; 
                printf("Digite um valor válido, entre 0 e %d\n", numero_vertices - 1); 
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida               
            }         
            }while(confirmacao == 0);

            do{
                printf("Digite o Vértice de Destino: "); 
                scanf("%d", &vertice_destino); 
                if(vertice_destino >= 0 && vertice_destino < numero_vertices){
                confirmacao = 1;
            }else{
                confirmacao = 0; 
                printf("Digite um valor válido, entre 0 e %d\n", numero_vertices - 1); 
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida               
            }         
            }while(confirmacao == 0);

            do{
                printf("Digite o Grau de Confiabilidade (Entre 0.0 e 1.0): "); 
                scanf("%f", &confiabilidade); 

                if(confiabilidade <= 1 && confiabilidade >= 0){
                    confirmacao = 1;
                }else{
                    confirmacao = 0; 
                    printf("Digite um valor válido, entre 0.0 e 1.0\n"); 
                    while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
                }
            }while(confirmacao == 0);

            //Feitas todas as validações, é possivel inserir. 

            Grafo->Arestas[vertice_origem][vertice_destino].confiabilidade = confiabilidade;

        }

        (*criado_grafo) = 1; //Confirmada a montagem do grafo
        situacao = 1; 
    }else{
        //Grafo já montado 
        situacao = 0; 
    } 

    mensagem_criacao_grafo(situacao);    
}

//Função para descobrir o caminho mais confiavel; 

void descobrir_caminho_mais_confiavel(graf *Grafo, int criado_grafo){
    int situacao, vertice_inicial, vertice_final, confirmacao;
    if(criado_grafo == 1){ 
       
        do{
            printf("Digite o Vertice Inicial: "); 
            scanf("%d", &vertice_inicial);
            if(vertice_inicial >= 0 && vertice_inicial <= Grafo->numero_vertices - 1){
                confirmacao = 1;
            }else{
                confirmacao = 0; 
                printf("Digite um valor válido, de 0 a %d\n", Grafo->numero_vertices - 1); 
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
            }

        }while(confirmacao == 0);   

        do{
             printf("Digite o Vértice Final: "); 
             scanf("%d", &vertice_final); 

             if(vertice_final >= 0 && vertice_final <= Grafo->numero_vertices - 1){
                confirmacao = 1; 
             }else{
                confirmacao = 0; 
                printf("Digite um valor válido, de 0 a %d\n", Grafo->numero_vertices - 1); 
                while (getchar() != '\n'); // Limpa o buffer em caso de entrada inválida
             }

        }while(confirmacao == 0); 

        float distancia[LIMITE_VERTICES];
        int vertice_anterior[LIMITE_VERTICES]; 

        //Algoritmo de Dijkstra    
        dijkstra(Grafo, vertice_inicial, distancia, vertice_anterior); 
        
        if(distancia[vertice_final] < (float)INFINITO){
            printf("Este é o caminho mais confiavel entre %d e %d: ", vertice_inicial, vertice_final); 
            mostrar_caminho(vertice_anterior, vertice_final); 
            float confiab = expf(-distancia[vertice_final]);
            printf("\nConfiabilidade: %.5f\n", confiab); 
            situacao = 1; //sucesso
        }else{
            //Nenhum caminho confiavel foi encontrado 
            situacao = 2; 
        }

    }else{
        //O grafo ainda não foi montado
        situacao = 0; 
    }
    
    mensagem_caminho_confiavel(situacao); 

}

//Dijkstra vai ficar aqui. 

void dijkstra(graf *G, int origem, float dist[], int anterior[]) {
    bool visitado[LIMITE_VERTICES] = {false};
    int n = G->numero_vertices;

    // Inicializa distancias e anterior
    for (int i = 0; i < n; i++) {
        dist[i] = (float)INFINITO;
        anterior[i] = -1;
    }
    dist[origem] = 0.0f;

    for (int cont = 0; cont < n - 1; cont++) {
        int u = descobrir_menor_dist_vertice(dist, visitado, n);
        if (u == -1) break;

        visitado[u] = true;

        for (int v = 0; v < n; v++) {
            float r = G->Arestas[u][v].confiabilidade;
            if (!visitado[v] && r > 0.0f) {
                // custo = -log(r). Se r=1, custo=0; se r<1, custo>0
                float custo = -logf(r);

                float nova_dist = dist[u] + custo;
                if (nova_dist < dist[v]) {
                    dist[v] = nova_dist;
                    anterior[v] = u;
                }
            }
        }
    }
}

int descobrir_menor_dist_vertice(float distancia[], bool visitados[], int numero_vertices){
    float min = (float)INFINITO; 
    int indice_min = -1;

    for (int i = 0; i < numero_vertices; i++) {
        if (!visitados[i] && distancia[i] < min) {
            min = distancia[i];
            indice_min = i;
        }
    }
    return indice_min; 
}

void mostrar_caminho(int vertice_anterior[], int vertice){
   
   // Verifica se o vértice tem um vértice anterior associado
   if(vertice_anterior[vertice] != -1){

       mostrar_caminho(vertice_anterior, vertice_anterior[vertice]); 

       printf(" -> ");      
   }

   printf("%d", vertice); 

}
