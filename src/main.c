#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libraries/socioAVL.h"

int main(void){
    No * raiz = NULL;
    char nome[40];
    int i;

    for(i = 1001; i <= 1015; i++){
        sprintf(nome, "Socio %d", i);
        raiz = inserir(raiz, i, nome, (i % 4) + 1,
                       100.0f + (i % 4) * 50.0f, i % 2);
    }
    printf("Carga de 15 registros -> altura: %d raiz: %d nos: %d\n",
           altura(raiz), raiz->chave, contarNos(raiz));

    raiz = remover(raiz, 1001);
    printf("Removeu 1001 (folha) -> altura: %d raiz: %d nos: %d AVL valida: %s\n",
           altura(raiz), raiz->chave, contarNos(raiz),
           ehAVL(raiz) ? "SIM" : "NAO");

    raiz = remover(raiz, 1002);
    printf("Removeu 1002 (1 filho) -> altura: %d raiz: %d nos: %d AVL valida: %s\n",
           altura(raiz), raiz->chave, contarNos(raiz),
           ehAVL(raiz) ? "SIM" : "NAO");

    raiz = remover(raiz, 1008);
    printf("Removeu 1008 (2 filhos)-> altura: %d raiz: %d nos: %d AVL valida: %s\n",
           altura(raiz), raiz->chave, contarNos(raiz),
           ehAVL(raiz) ? "SIM" : "NAO");

    raiz = remover(raiz, 1999);
    printf("Chave 1999 nao encontrada -> nos: %d AVL valida: %s\n",
           contarNos(raiz), ehAVL(raiz) ? "SIM" : "NAO");

    raiz = remover(raiz, 1013);
    printf("Removeu 1013 -> altura: %d raiz: %d nos: %d AVL valida: %s\n",
           altura(raiz), raiz->chave, contarNos(raiz),
           ehAVL(raiz) ? "SIM" : "NAO");

    raiz = remover(raiz, 1015);
    printf("Removeu 1015 -> altura: %d raiz: %d nos: %d AVL valida: %s\n",
           altura(raiz), raiz->chave, contarNos(raiz),
           ehAVL(raiz) ? "SIM" : "NAO");

    raiz = remover(raiz, 1014);
    printf("Removeu 1014 -> altura: %d raiz: %d nos: %d AVL valida: %s\n",
           altura(raiz), raiz->chave, contarNos(raiz),
           ehAVL(raiz) ? "SIM" : "NAO");

    printf("\nemOrdem:\n");
    emOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    return 0;
}
// PERGUNTA DO FINAL DO PDF

/*Uma remoção de registro, em nosso tema, é dada principalmente
 quando um sócio-torcedor cancela o seu plano ou pede o desligamento
do clube por algum motivo. Se não fizer o rebalanceamento, a árvore
iria se aproximar cada vez mais de uma lista, perdendo sua eficiência
de aceso*/
#include "../libraries/socioAVL.h"
#define LIMITE 3
int main (void) {
  
    No * raiz = NULL;
    for(int i = 0; i < LIMITE; i++){
    raiz = inserir(raiz, i+1000, "Marcos", 1, 21.90, 0);
    }
    desenhar(raiz, 0);
    liberarArvore(raiz);
    return 0;
}
