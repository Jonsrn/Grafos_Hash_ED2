#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "hash.h"



//Primeira função, importar do txt os 1000 funcionários e preencher o primeiro vetor



void importar_dataset(fcnario funcionarios[TOTAL_FUNCIONARIOS], const char *nome_arquivo, int *importado_txt) {
    int situacao; 
    if(*importado_txt == 0){
    
        FILE *arquivo = fopen(nome_arquivo, "r");
        if (arquivo != NULL) {
            
            char linha[200];
            int i = 0;

            // Ignorar a primeira linha (cabeçalho)
            fgets(linha, sizeof(linha), arquivo);

            while (fgets(linha, sizeof(linha), arquivo) != NULL && i < TOTAL_FUNCIONARIOS) {
                // Dividir a linha nos campos
                char *matricula = strtok(linha, ",");
                char *nome = strtok(NULL, ",");
                char *funcao = strtok(NULL, ",");
                char *salario_str = strtok(NULL, ",");

                // Remover espaços adicionais
                if (nome) nome += (*nome == ' ');
                if (funcao) funcao += (*funcao == ' ');

                // Preencher a estrutura
                strcpy(funcionarios[i].Matricula, matricula);
                strcpy(funcionarios[i].Nome, nome);
                strcpy(funcionarios[i].funcao, funcao);
                funcionarios[i].salario = atof(salario_str);

                i++;
            }

        fclose(arquivo);
        (*importado_txt) = 1; 
        situacao = 1; //sucesso
       }else{
        //Problema na leitura do arquivo
        situacao = 2; 

      }
   }else{
      //Dataset já importado 
      situacao = 0; 
   }

   mensagem_importacao_dataset(situacao);   

}


//Funções referentes ao Hash A


void operacao_hash_A(fcnario funcionarios[TOTAL_FUNCIONARIOS], int tamanho_vetor, int importado_txt) {
    int situacao; 
    if(importado_txt == 1){
        int qtd_colisoes = 0;
        fcnario hash_funcionarios[tamanho_vetor];
        int slots_ocupados = 0;
        long long t1, t2;

        // Inicializar o vetor hash
        for (int i = 0; i < tamanho_vetor; i++) {
            strcpy(hash_funcionarios[i].Matricula, ""); // Indica posição vazia
        }

        // Marca tempo inicial
        t1 = tempo_atual_nano();

        for (int i = 0; i < TOTAL_FUNCIONARIOS; i++) {
            // Rotação de 2 dígitos para a esquerda
            int nova_chave = rotacao2dig(funcionarios[i].Matricula);

            // Extrair o 2º, 4º e 6º dígito
            nova_chave = extrair_digitos(nova_chave);

            // Obter o resto da divisão pelo tamanho do vetor
            nova_chave = (nova_chave % tamanho_vetor);

            // Se todos os slots já estão ocupados, substituir diretamente

            if (slots_ocupados == tamanho_vetor) {
                hash_funcionarios[nova_chave] = funcionarios[i];
                
            }else{

                // Tentar inserir ou tratar colisões
                int posicao_final = nova_chave;
                int tentativas = 0;
                
                // Enquanto a posição NÃO estiver vazia
                while (strcmp(hash_funcionarios[posicao_final].Matricula, "") != 0) {
                    qtd_colisoes++; 
                    posicao_final = tratar_colisao_A(posicao_final, atoi(funcionarios[i].Matricula), tamanho_vetor);
                    tentativas++;

                    // Evita loop infinito: se exceder o tamanho do vetor, paramos
                    if (tentativas > tamanho_vetor) {
                        break; 
                    }
                }

                // Se ainda está vazio, insere; senão, significa que o while quebrou por saturação
                if (strcmp(hash_funcionarios[posicao_final].Matricula, "") == 0) {
                    hash_funcionarios[posicao_final] = funcionarios[i];
                    slots_ocupados++;
                } else {
                    
                    hash_funcionarios[nova_chave] = funcionarios[i];
                
                }
            }
        }

        // Marca tempo final
        t2 = tempo_atual_nano(); 

        // Exibir o número de colisões
        printf("Total de colisões do Hash A, com vetor de %d posições: %d\n", tamanho_vetor, qtd_colisoes); 

        //Exibir o tempo decorrido
        printf("Tempo para executar o Hash A, com um vetor de %d posições : %lld ns\n", tamanho_vetor, (t2 - t1));

        situacao = 1; //sucesso
    } else {
        // O Dataset ainda não foi importado
        situacao = 0; 
    }    

    mensagem_Hash_A(situacao);
}





// Função para rotacionar 2 dígitos para a esquerda


int rotacao2dig(const char *matricula) {
    char rotacionada[7];
    int len = strlen(matricula);

    // Colocar os dois últimos caracteres no início
    rotacionada[0] = matricula[len - 2];
    rotacionada[1] = matricula[len - 1];

    // Copiar o restante dos caracteres para frente
    for (int i = 0; i < len - 2; i++) {
        rotacionada[i + 2] = matricula[i];
    }

    // Adicionar o terminador de string
    rotacionada[len] = '\0';

    // Converter para inteiro e retornar
    return atoi(rotacionada);
}



// Função para extrair o 2º, 4º e 6º dígito
int extrair_digitos(int matricula) {
    char str[7];
    snprintf(str, sizeof(str), "%06d", matricula); // Garantir 6 dígitos
    return (str[1] - '0') * 100 + (str[3] - '0') * 10 + (str[5] - '0');
}

// Função para tratar colisões
int tratar_colisao_A(int chave_atual, int chave_original, int tamanho_vetor) { 
    // Obtém o primeiro dígito da chave original usando sua função 
    int primeiro_digito_valor = primeiro_digito(chave_original); // Calcula a nova posição 
    int nova_posicao = (chave_atual + primeiro_digito_valor) % tamanho_vetor; 
    return nova_posicao;
}
// Função para obter o primeiro dígito
int primeiro_digito(int chave_original) {
    while (chave_original >= 10) {
        chave_original /= 10;
    }
    return chave_original;
}






//Funções Referentes ao Hash B

int hash_b(char matricula[]) {
    // Soma os dois números gerados a partir de posições específicas da matrícula
    return (atoi((char[]){matricula[0], matricula[2], matricula[5], '\0'}) + 
            atoi((char[]){matricula[1], matricula[3], matricula[4], '\0'}));
}

int foldShift(char *palavra){
	return (atoi((char[]){palavra[0],palavra[2],palavra[5]}) + 
		atoi((char[]){palavra[1],palavra[3],palavra[4]}));	
}

// Função para tratar colisões, somando 7 à chave
int tratar_colisao_B(int chave, int tamanho_vetor) {
    chave = (chave + 7) % tamanho_vetor;
    return chave;
}

// Função principal para a operação de hashing
void operacao_hash_B(fcnario funcionarios[], int tamanho_vetor, int importado_txt) {
    int situacao; 
    if(importado_txt == 1){    
        long long t1, t2; 

        // Vetor que guardará o índice do funcionário armazenado em cada posição.
        // Se a posição estiver vazia, ela fica com -1.
        int Tabela_Hash[tamanho_vetor];
        memset(Tabela_Hash, -1, sizeof(Tabela_Hash)); // Inicializa com -1

        int qtd_colisoes = 0;     // Contador de colisões (todas as tentativas mal-sucedidas)
        int slots_ocupados = 0;    // Quantidade de slots preenchidos

        // Marca tempo inicial
        t1 = tempo_atual_nano();

        for (int i = 0; i < TOTAL_FUNCIONARIOS; i++) {
            // 1) Calcula a "chave bruta" via Hash B (fole shift)
            int chave = hash_b(funcionarios[i].Matricula);
            // 2) Calcula o índice inicial
            int index = chave % tamanho_vetor;
            int index_inicial = index;  

            if (slots_ocupados == tamanho_vetor) {                
                Tabela_Hash[index_inicial] = i;
                //Se o vetor tá lotado, ao invés de pingar todo o vetor e voltar ao inicio já insere diretamente. 
                
            }else{

                //vamos tentar inserir
                while (Tabela_Hash[index] != -1) {
                    // Cada vez que achamos a posição ocupada, incrementa colisões
                    qtd_colisoes++;
                    // Passo de colisão: soma 7 e faz módulo
                    index = tratar_colisao_B(index, tamanho_vetor); 

                    // Se demos a volta inteira e voltamos ao index_inicial,
                    // significa que não há slot livre (tabela realmente cheia).
                    if (index == index_inicial) {
                        // Substitui a posição inicial (ou a que desejar)
                        Tabela_Hash[index_inicial] = i;
                        break; // encerra o while
                    }
                }

                //Se a posição está livre (não -1), insere
                if (Tabela_Hash[index] == -1) {
                    Tabela_Hash[index] = i; 
                    slots_ocupados++;
                }
            }
        }
        // Marca tempo final
        t2 = tempo_atual_nano(); 

        // Exibe o número total de colisões
        printf("Total de colisões do Hash B, com vetor de %d posições: %d\n", tamanho_vetor,  qtd_colisoes);

        printf("\nTempo para executar o Hash B, com um vetor de %d posições : %lld ns\n", tamanho_vetor, (t2 - t1));
        situacao = 1; //sucesso
    }else{
        //dataset ainda não montado
        situacao = 0; 
    }    

    mensagem_Hash_B(situacao);
}



// Função para medir tempo em nanossegundos
long long tempo_atual_nano() {
    LARGE_INTEGER frequencia, contador;
    QueryPerformanceFrequency(&frequencia);
    QueryPerformanceCounter(&contador);
    return (contador.QuadPart * 1000000000LL) / frequencia.QuadPart;
}




