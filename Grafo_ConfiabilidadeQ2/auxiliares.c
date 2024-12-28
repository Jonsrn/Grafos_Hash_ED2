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
        
        if(distancia[vertice_final] < INFINITO){
            printf("Este é o caminho mais confiavel entre %d e %d: ", vertice_inicial, vertice_final); 
            mostrar_caminho(vertice_anterior, vertice_final); 
            printf("\nConfiabilidade: %.5f\n", exp(distancia[vertice_final])); 
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

void dijkstra(graf *grafo, int vertice_inicial, float distancia[], int vertice_anterior[]){
   
   //
   bool visitados[LIMITE_VERTICES] = {false}; 
   int vertice_localizado; 
   float confiabilidade;

   for(int i = 0; i < grafo->numero_vertices; i++){
      distancia[i] = INFINITO; //inicializa com "infinito"
      vertice_anterior[i] = -1; //inicializa com -1      
   } 

   distancia[vertice_inicial] = 0;  //A distancia pra ele mesmo é zero

   for(int i = 0; i < grafo->numero_vertices - 1; i++){
       
       vertice_localizado = descobrir_menor_dist_vertice(distancia, visitados, grafo->numero_vertices);

       visitados[vertice_localizado] = true; //Marca o vertice como já percorrido

       for(int j = 0; j < grafo->numero_vertices; j++){

          confiabilidade = grafo->Arestas[vertice_localizado][j].confiabilidade; 
          // Verifica se o vértice não foi visitado, a confiabilidade é válida e
          // a distância até o vértice atual somada ao logaritmo da confiabilidade
          // é maior que a distância atual do vértice destino
          if(!visitados[j] && distancia[vertice_localizado] + log(confiabilidade) < distancia[j]){
              // Atualiza a distância e o vértice anterior
              distancia[j] = distancia[vertice_localizado] * confiabilidade; 
              vertice_anterior[j] = vertice_localizado; 
          }

       }
      
   }
   


}

int descobrir_menor_dist_vertice(float distancia[], bool visitados[], int numero_vertices){
    float minimo = INFINITO; 
    int indice_minimo = -1; 

    for(int i = 0; i < numero_vertices; i++){
        if(!visitados[i] && distancia[i] < minimo){
            minimo = distancia[i]; //Atualiza com um valor menor
            indice_minimo = i; 
        }
    }

    return indice_minimo; 
}

void mostrar_caminho(int vertice_anterior[], int vertice){
   
   // Verifica se o vértice tem um vértice anterior associado
   if(vertice_anterior[vertice] != -1){

       mostrar_caminho(vertice_anterior, vertice_anterior[vertice]); 

       printf(" -> ");      
   }

   printf("%d", vertice); 

}
