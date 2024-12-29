#include <stdio.h>
#include "hash.h"



//Menus do Programa
void menu_principal(){
    printf("Menu Principal\n"); 
    printf("[1]-Montar Dataset\n"); 
    printf("[2]-Operações com Hash Item A\n");
    printf("[3]-Operações com Hash Item B\n");
    printf("[4]-Sobre\n");
    printf("[0]-Sair\n");
}

void menu_operacoes_Hash_A(){
    printf("Menu de Operações do Hash A\n");
    printf("[1]-Realizar o Hash com Vetor de 101 elementos\n"); 
    printf("[2]-Realizar o Hash com vetor de 150 elementos\n"); 
    printf("[0]-Sair\n");
}

void menu_operacoes_Hash_B(){
    printf("Menu de Operações do Hash B\n");
    printf("[1]-Realizar o Hash com Vetor de 101 elementos\n"); 
    printf("[2]-Realizar o Hash com vetor de 150 elementos\n"); 
    printf("[0]-Sair\n");
}

void sobre(){
    printf("Trabalho realizado por:\nJonathan dos Santos\nClistenes Rodger\n");
}   


//Mensagens de Diagnóstico

void mensagem_importacao_dataset(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o Dataset do TXT já foi importado\n");
    }
    if(situacao == 1){
        printf("Operação realizada com sucesso\n");
    }
    if(situacao == 2){
        printf("A operação falhou porque houve um problema na leitura do arquivo\n");
    }
}

void mensagem_Hash_A(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o Dataset do TXT ainda não foi importado\n");
    }
    if(situacao == 1){
        printf("Operação realizada com sucesso\n"); 
    }
}

void mensagem_Hash_B(int situacao){
    if(situacao == 0){
        printf("A operação falhou porque o Dataset do TXT ainda não foi importado\n");
    }
    if(situacao == 1){
        printf("Operação realizada com sucesso\n"); 
    }
}

