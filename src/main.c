#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/socioAVL.h"
#include "../libraries/tratamentoArquivos.h"

int main(void){
    No * raizAVL = NULL;
    No * raizBST = NULL;
    raizAVL = carregarArquivoNaAVL(raizAVL, "../data/socios.txt");
    raizBST = carregarArquivoNaBST(raizBST, "../data/socios.txt");

    printf("Registros carregados: 1000\n");
    printf("BST Simples -> altura: %d\n", alturaBST(raizBST));
    printf("AVL         -> altura: %d Raiz: %d\n",
        altura(raizAVL), raizAVL->chave);
    mostrarContadores();

}