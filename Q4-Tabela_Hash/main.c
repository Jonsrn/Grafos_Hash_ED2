#include <stdio.h>
#include <string.h>
#include "hash.h"



int main(){
   fcnario Funcionarios[TOTAL_FUNCIONARIOS]; //Vetor com o total de 1000 Funcionários   
   int op1, op2, op3, importado_txt;
   importado_txt = 0; //Significa que nada foi importado ainda 

   do{

    menu_principal(); 
    scanf("%d", &op1); 

    switch(op1){
        
        case 1: 
            //Importar Dataset
            importar_dataset(Funcionarios, "funcionarios.txt", &importado_txt);
            break;
            
        case 2: 
            do{
                //submenu de operações com o Hash A
                menu_operacoes_Hash_A();
                scanf("%d", &op2);

                switch(op2){
                    case 1: 
                       //Realizar o Hash A com Vetor de 101 elementos
                       operacao_hash_A(Funcionarios, VETOR_MENOR, importado_txt); 
                       break;
                    case 2: 
                       //Realizar o Hash A com Vetor de 150 elementos
                       operacao_hash_A(Funcionarios, VETOR_MAIOR, importado_txt); 
                       break; 
                    case 0: 
                       //voltar
                       break;
                    default: 
                       printf("Opção Inválida, tente novamente\n");
                       break;         
                       
                }


            }while(op2!=0);
            break;      
        case 3: 
           do{
                //submenu de operações com o Hash B
                menu_operacoes_Hash_B();
                scanf("%d", &op3);

                switch(op3){
                    case 1: 
                       //Realizar o Hash B com Vetor de 101 elementos
                       operacao_hash_B(Funcionarios, VETOR_MENOR, importado_txt);                      
                       break;
                    case 2: 
                       //Realizar o Hash B com Vetor de 150 elementos
                       operacao_hash_B(Funcionarios, VETOR_MAIOR, importado_txt);                       
                       break; 
                    case 0: 
                       //voltar
                       break;
                    default: 
                       printf("Opção Inválida, tente novamente\n");
                       break;                         
                }
            }while(op3!=0);
            break;                

        case 4: 
            //Sobre
            sobre();
            break;  

        case 0: 
            //Encerrar Programa
            break;  

        default: 
            printf("Opção Inválida, tente novamente\n");
            break;     
    }

  }while(op1!=0); 

    return 0; 
}