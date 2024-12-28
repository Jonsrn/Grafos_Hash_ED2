#include <stdio.h> 
#include "grafo_confiabilidade.h"

int main(){

    int op1, criado_grafo; 
    criado_grafo = 0; //Grafo ainda não montado
    graf Grafo; 
    

    do{
        menu_principal(); 
        scanf("%d", &op1); 

        switch(op1){
            case 1: 
               //Montar Grafo
               montar_grafo(&Grafo, &criado_grafo); 
               break;
            case 2: 
               //Descobrir Caminho mais confiável entre dois vértices
               descobrir_caminho_mais_confiavel(&Grafo, criado_grafo);
               break; 
            case 3: 
               //Sobre
               sobre();
               break; 
            case 0: 
               //sair
               break; 
            default: 
               printf("Entrada inválida, tente novamente\n"); 
               break;                          
        }

    }while(op1!=0);

    return 0; 
}