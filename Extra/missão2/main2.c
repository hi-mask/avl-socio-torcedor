#include <stdio.h>
#include "socioAVL2.h"

#define LIMITE 15

int main(void) {

    No * raizAVL = NULL;
    No * raizBST = NULL;

    printf("Carga de %d registros em ordem crescente\n\n", LIMITE);

    for(int i = 0; i < LIMITE; i++){
        raizAVL = inserir(raizAVL, 1000 + i, "Marcos", 1 , 21.90 + 10*i, 1);
        raizBST = inserirBST(raizBST, 1000 + i, "Samuel", 1 , 31.40 + 5*i, 0);
    }

    printf("\n\t ALTURAS\n");
    printf("BST simples -> altura: %d\n", alturaBST(raizBST));
    printf("AVL -> altura: %d", altura(raizAVL));
    if (raizAVL != NULL)
        printf("\nraizAVL: %d\n", raizAVL->chave);
    else
        printf("\nraizAVL: -\n");

    printf("\n\nFator de balanceamento:\n");
    mostrarFB(raizAVL);

    printf("\n\t Registros\n");
    printf("\nRegistros em ordem crescente da BST:\n");
    emOrdem(raizBST);
    printf("\nRegistros em ordem crescente da AVL:\n");
        emOrdem(raizAVL);

    liberarArvore(raizBST);
    liberarArvore(raizAVL);

    return 0;
}