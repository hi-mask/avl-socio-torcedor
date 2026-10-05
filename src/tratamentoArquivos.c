#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/tratamentoArquivos.h"
#include "../libraries/socioAVL.h"
#define TAM_STRING 250

/*=========================================================
    Função: verificarAberturaArquivo
    Autor: Nome do Integrante

    Descrição:
        Verifica se o arquivo foi aberto corretamente.
        Se o ponteiro for NULL, exibe uma mensagem de erro.

    Parâmetros:
        1 - arquivo : ponteiro devolvido pelo fopen

    Retorno:
        1 : erro ao abrir o arquivo
        0 : arquivo aberto com sucesso

  =========================================================*/
int verificarAberturaArquivo(FILE *arquivo){
    if(arquivo == NULL){
        printf("Problema ao abrir o arquivo!\n");
        return 1;
    }
    return 0;
}

/*=========================================================
    Função: verificarCampo
    Autor: Samuel de Godoy Larroque
 
    Descrição:
        Verifica se um campo da linha do arquivo foi encontrado.
        O strtok devolve NULL quando a linha tem menos campos
        do que o esperado (linha vazia ou incompleta).
 
    Parâmetros:
        1 - campo : ponteiro devolvido pelo strtok
 
    Retorno:
        1 : campo ausente (a linha deve ser ignorada)
        0 : campo encontrado
 
  =========================================================*/
int verificarCampo(const char * campo){
    if(campo == NULL)
        return 1;
    return 0;
}

/*=========================================================
    Função: carregarArquivoNaAVL
    Autor: Samuel de Godoy Larroque
 
    Descrição:
        Lê o arquivo de sócios (uma linha por sócio, campos
        separados por ';') e insere cada sócio na árvore AVL.
        A primeira linha do arquivo é o cabeçalho e é descartada.
        Linhas vazias ou incompletas são ignoradas.
 
        Formato da linha: ID;Nome;Plano;Valor;Status
 
    Parâmetros:
        1 - raiz        : raiz atual da árvore (NULL se vazia)
        2 - nomeArquivo : nome do arquivo a ser lido
 
    Retorno:
        No * : nova raiz da árvore. A raiz pode mudar a cada
                inserção por causa das rotações; por isso o
                retorno deve ser atribuído à raiz do chamador.
                Se o arquivo não abrir, devolve a raiz recebida.
 
  =========================================================*/
No * carregarArquivoNaAVL(No *raiz, const char nomeArquivo[]){
    FILE *arquivo;
    char string[TAM_STRING];
    char *campo;
    char *nome;
    int chave, plano, status;
    float valor;
 
    arquivo = fopen(nomeArquivo, "r");
 
    if(verificarAberturaArquivo(arquivo))
        return raiz;
 
    /* descarta a linha de cabecalho: ID;Nome;Plano;Valor;Status */
    if(fgets(string, sizeof(string), arquivo) == NULL){
        fclose(arquivo);
        return raiz;
    }
 
    while(fgets(string, sizeof(string), arquivo) != NULL){
 
        string[strcspn(string, "\r\n")] = '\0';
 
        campo = strtok(string, ";");
        if(verificarCampo(campo))
            continue;
        chave = atoi(campo);
 
        campo = strtok(NULL, ";");
        if(verificarCampo(campo))
            continue;
        nome = campo;
 
        campo = strtok(NULL, ";");
        if(verificarCampo(campo))
            continue;
        plano = atoi(campo);
 
        campo = strtok(NULL, ";");
        if(verificarCampo(campo))
            continue;
        valor = (float) atof(campo);
 
        campo = strtok(NULL, ";");
        if(verificarCampo(campo))
            continue;
        status = atoi(campo);
 
        raiz = inserir(raiz, chave, nome, plano, valor, status);
    }
 
    fclose(arquivo);
    return raiz;
}

/*=========================================================
    Função: gravarEmOrdem
    Autor: Samuel de Godoy Larroque
 
    Descrição:
        Percorre a árvore em ordem (esquerdo, nó, direito) e
        grava uma linha no arquivo para cada sócio. Assim o
        arquivo fica em ordem crescente de ID.
 
    Parâmetros:
        1 - arquivo : arquivo já aberto para escrita
        2 - raiz    : raiz da árvore (ou subárvore) a ser gravada
 
    Retorno:
        void. Se raiz for NULL, não grava nada.
 
  =========================================================*/
void gravarEmOrdem(FILE *arquivo, No const * const raiz){
    if(raiz == NULL) return;
    gravarEmOrdem(arquivo, raiz->esq);
    fprintf(arquivo, "%d;%s;%d;%.2f;%d\n",
            raiz->chave,
            raiz->nome,
            raiz->plano,
            raiz->valor,
            raiz->status);
    gravarEmOrdem(arquivo, raiz->dir);
}

/*=========================================================
    Função: salvarAVLNoArquivo
    Autor: Samuel de Godoy Larroque
 
    Descrição:
        Salva todos os sócios da árvore em um arquivo, no mesmo
        formato lido por carregarArquivoNaAVL (com a linha de
        cabeçalho), em ordem crescente de ID.
 
    Parâmetros:
        1 - raiz        : raiz da árvore a ser salva
        2 - nomeArquivo : nome do arquivo de destino
 
    Retorno:
        void. Se o arquivo não abrir, nada é gravado.
 
  =========================================================*/
void salvarAVLNoArquivo(No const * const raiz, const char nomeArquivo[]){
    FILE *arquivo = fopen(nomeArquivo, "w");
 
    if(verificarAberturaArquivo(arquivo))
        return;
 
    fprintf(arquivo, "ID;Nome;Plano;Valor;Status\n");
    gravarEmOrdem(arquivo, raiz);
 
    fclose(arquivo);
}