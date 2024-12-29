#include <stdio.h>
#include "grafo_confiabilidade.h"


//Menus do Programa

void menu_principal(){
    printf("Menu Principal\n"); 
    printf("[1]-Montar Grafo\n"); 
    printf("[2]-Descobrir Caminho Mais Confiavel\n"); 
    printf("[3]-Sobre\n"); 
    printf("[0]-Sair\n"); 
}

void sobre(){
    printf("Trabalho desenvolvido por:\nJonathan dos Santos\nClistenes Rodger\n"); 
}


//Mensagens de Diagnóstico

void mensagem_criacao_grafo(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o Grafo já foi montado anteriormente\n"); 
    }
    if(situacao == 1){
        printf("Operação Realizada com Sucesso, Grafo foi montado\n");
    }
}

void mensagem_caminho_confiavel(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o Grafo ainda não foi montado\n"); 
    }
    if(situacao == 1){
        printf("Operação realizada com sucesso\n"); 
    }

    if(situacao == 2){
        printf("A operação falhou porque nenhum caminho entre os dois vértices foi encontrado\n"); 
    }
} 