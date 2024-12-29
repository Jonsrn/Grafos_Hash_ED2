#include <stdio.h>
#include "grafos.h"

//Menus do programa

void menu_principal(){
    printf("Menu Principal- Torre de Hanoi\n"); 
    printf("[1]-Montar Grafo\n"); 
    printf("[2]-Imprimir Grafo\n"); 
    printf("[3]-Medir tempo (Ford-Moore-Bellman)\n");
    printf("[4]-Sobre\n"); 
    printf("[0]-Sair\n"); 
}


void sobre(){
    printf("Trabalho feito por:\nJonathan dos Santos\nClistenes Rodger\n"); 
}

//Mensagem de Diagnóstico

void mensagens_criacao_grafo(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o grafo já foi criado anteriormente\n");
    }
    if(situacao == 1){
        printf("A operação foi realizada com sucesso\n"); 
    }
}


void mensagem_operacao(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o grafo ainda não foi montado\n");
    }
    if(situacao == 1){
        printf("A operação foi realizada com sucesso\n"); 
    }
}