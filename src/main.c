#include <stdio.h>
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