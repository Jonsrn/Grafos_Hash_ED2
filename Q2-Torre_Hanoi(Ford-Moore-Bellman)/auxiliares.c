#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <windows.h>
#include "grafos.h"


// Função para converter uma configuração em um índice único no grafo
int configuracao_para_indice(int configuracao[], int n) {
    int indice = 0;
    for (int i = 0; i < n; i++) {
        indice = indice * 3 + (configuracao[i] - 1); // Configurações variam de 1 a 3
    }
    return indice;
}

// Função para converter um índice em uma configuração
void indice_para_configuracao(int indice, int configuracao[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        configuracao[i] = (indice % 3) + 1;
        indice /= 3;
    }
}

// Verifica se o movimento é válido (regra da Torre de Hanói)
int movimento_valido(int configuracao[], int n, int origem, int destino) {
    int topo_origem = -1, topo_destino = -1;

    // Encontrar o disco no topo do pino "origem" e "destino"
    for (int i = 0; i < n; i++) {
        if (configuracao[i] == origem) {
            topo_origem = i;
            break;
        }
    }
    for (int i = 0; i < n; i++) {
        if (configuracao[i] == destino) {
            topo_destino = i;
            break;
        }
    }

    // Movimento é válido se "origem" tem disco e "destino" está vazio ou disco de "destino" é maior
    return (topo_origem != -1 && (topo_destino == -1 || topo_origem < topo_destino));
}

// Criação do grafo como matriz de adjacência
void criar_grafo(int n, int grafo[MAX_VERTICES][MAX_VERTICES], int *grafo_criado) {
    int situacao; 
    if(*grafo_criado == 0){    
        int configuracao[n], nova_configuracao[n];

        // Inicializar a matriz de adjacência com 0
        for (int i = 0; i < MAX_VERTICES; i++) {
            for (int j = 0; j < MAX_VERTICES; j++) {
                grafo[i][j] = 0;
            }
        }

        // Iterar por todas as configurações possíveis
        for (int i = 0; i < pow(3, n); i++) {
            indice_para_configuracao(i, configuracao, n);

            // Tentar mover cada disco de um pino para outro
            for (int origem = 1; origem <= 3; origem++) {
                for (int destino = 1; destino <= 3; destino++) {
                    if (origem != destino && movimento_valido(configuracao, n, origem, destino)) {
                        memcpy(nova_configuracao, configuracao, sizeof(configuracao));

                        // Mover o disco do pino "origem" para "destino"
                        for (int d = 0; d < n; d++) {
                            if (nova_configuracao[d] == origem) {
                                nova_configuracao[d] = destino;
                                break;
                            }
                        }

                        int indice_origem = configuracao_para_indice(configuracao, n);
                        int indice_destino = configuracao_para_indice(nova_configuracao, n);
                        grafo[indice_origem][indice_destino] = 1; // Conectar os vértices
                    }
                }
            }
        }
        (*grafo_criado) = 1; 
        situacao = 1; //sucesso
    }else{
        //O grafo já foi montado
        situacao = 0;
    }
    mensagens_criacao_grafo(situacao);     
}

// Algoritmo de ford_moore_bellman para encontrar o menor caminho
void ford_moore_bellman(int grafo[MAX_VERTICES][MAX_VERTICES], int inicio, int distancias[MAX_VERTICES], int anteriores[MAX_VERTICES]){
    // 1) Inicializar distâncias e predecessores
    for (int i = 0; i < MAX_VERTICES; i++) {
        distancias[i] = INFINITO;
        anteriores[i] = -1;
    }
    distancias[inicio] = 0;

  
    // cada aresta tem peso 1
    for (int k = 0; k < MAX_VERTICES - 1; k++) {
        // Percorre todos os possíveis vértices de origem (u)
        for (int u = 0; u < MAX_VERTICES; u++) {
            // Se u não for alcançável, não adianta tentar relaxar
            if (distancias[u] == INFINITO) continue;

            // Verifica todos os possíveis vértices de destino (v)
            if (u != -1) {
                for (int v = 0; v < MAX_VERTICES; v++) {
                    // Se existe aresta de u para v
                    if (grafo[u][v]) {
                        // Peso = 1
                        int alt = distancias[u] + 1;
                        if (alt < distancias[v]) {
                            distancias[v] = alt;
                            anteriores[v] = u;
                        }
                    }
                }
            }
        }
    }
}

// Função para medir tempo em nanossegundos
long long tempo_atual_nano() {
    LARGE_INTEGER frequencia, contador;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&contador);
    return (contador.QuadPart * 1000000000LL) / frequencia.QuadPart;
}

void imprimir_melhor_caminho(int grafo[MAX_VERTICES][MAX_VERTICES],int config_inicial[], int config_final[], int numero_discos,int distancias[MAX_VERTICES], int anteriores[MAX_VERTICES], int grafo_criado){
    int situacao;
    if(grafo_criado == 1){
    
        int inicio = configuracao_para_indice(config_inicial, numero_discos);
        int fim = configuracao_para_indice(config_final, numero_discos);

        // Roda o ford_moore_bellman
        ford_moore_bellman(grafo, inicio, distancias, anteriores);

        // Exemplo simples: imprimir o caminho em índices (do fim para o início)
        printf("\nMenor caminho (índices de vértice): ");
        int atual = fim;
        while (atual != -1) {
            printf("%d ", atual);
            atual = anteriores[atual];
        }
        printf("\nDistância mínima: %d\n", distancias[fim]);

        // Agora imprimir em formato de configuração (do início para o fim)
        printf("\nCaminho em formato de configurações:\n");
        int caminho_temp[MAX_VERTICES];
        int count = 0;
        atual = fim;
        while (atual != -1) {
            caminho_temp[count++] = atual;
            atual = anteriores[atual];
        }
        // Imprime invertendo (para ficar do início ao fim)
        for (int i = count - 1; i >= 0; i--) {
            int config[4]; // se numero_discos=4, aqui poderia ser config[numero_discos]
            indice_para_configuracao(caminho_temp[i], config, numero_discos);
            printf("[");
            for (int d = 0; d < numero_discos; d++) {
                printf("%d", config[d]);
                if (d < numero_discos - 1) printf(",");
            }
            printf("] ");
        }
        printf("\n");
        situacao = 1; //sucesso
    }else{
        //Grafo não criado
        situacao = 0;
    }

    mensagem_operacao(situacao);     
}

void medir_tempo_ford_moore_bellman(int grafo[MAX_VERTICES][MAX_VERTICES], int config_inicial[], int numero_discos, int distancias[MAX_VERTICES], int anteriores[MAX_VERTICES], int grafo_criado){
    int situacao;
    if(grafo_criado == 1){
        long long t1, t2;

        int inicio = configuracao_para_indice(config_inicial, numero_discos);
        // Marca tempo inicial
        t1 = tempo_atual_nano();

        // Executa ford_moore_bellman
        ford_moore_bellman(grafo, inicio, distancias, anteriores);

        // Marca tempo final
        t2 = tempo_atual_nano();

        // Imprime o tempo em nanossegundos
        printf("\nTempo para executar Ford-Moore-Bellman: %lld ns\n", (t2 - t1));
        situacao = 1; //sucesso
    }else{
        //Grafo não criado
        situacao = 0;
    }   
    mensagem_operacao(situacao);  
}