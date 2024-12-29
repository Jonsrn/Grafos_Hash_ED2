#ifndef _HASH_H
#define _HASH_H

#define VETOR_MENOR 101
#define VETOR_MAIOR 150
#define TOTAL_FUNCIONARIOS 1000


typedef struct Funcionario{
    char Nome[50]; 
    char Matricula[7];
    char funcao[20]; 
    float salario; 
}fcnario;


//Prototipo dos Menus
void menu_principal(); 
void menu_operacoes_Hash_A(); 
void menu_operacoes_Hash_B();  
void sobre(); 



//Prototipo das funções auxiliares

void importar_dataset(fcnario funcionarios[TOTAL_FUNCIONARIOS], const char *nome_arquivo, int *importado_txt); 

//Funções referentes ao Hash A
void operacao_hash_A(fcnario funcionarios[TOTAL_FUNCIONARIOS], int tamanho_vetor, int importado_txt); //Função principal que lida com os passos do Hash A
int rotacao2dig(const char *matricula); //Realiza a rotação à esquerda dos dois digitos
int extrair_digitos(int matricula); //Extrai os digitos desejados
int tratar_colisao_A(int chave_atual, int chave_original, int tamanho_vetor, int tentativas); //Função que lida com o tratamento das colisões
int primeiro_digito(int chave_original); //Função que coleta o primeiro digito

//Funções referentes ao Hash B

void operacao_hash_B(fcnario funcionarios[], int tamanho_vetor, int importado_txt); //Função principal que lida com os passos do Hash A








//Protótipo das Funções de Mensagem de diagnóstico
void mensagem_importacao_dataset(int situacao); 
void mensagem_Hash_A(int situacao); //Diagnóstico do Hash A
void mensagem_Hash_B(int situacao); //Diagnóstico do Hash B














#endif
