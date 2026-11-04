#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/socioAVL.h"
#include "../libraries/tratamentoArquivos.h"

int main(void){
    No * raizAVL = NULL;
    No * raizBST = NULL;
    raizAVL = carregarArquivoNaAVL(raizAVL, "dados.txt");
    raizBST = carregarArquivoNaBST(raizBST, "dados.txt");

       printf("Altura da AVL: %d\n", altura(raizAVL));

       printf("Altura da BST: %d\n", alturaBST(raizBST));
}