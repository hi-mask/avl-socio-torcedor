#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socioAVL.h"

/*=========================================================
    Função: criarNo
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Cria um nó da árvore AVL com os dados de um sócio-torcedor.
        O nó nasce como folha: altura 1 e filhos NULL.
    Parâmetros:
        1 - chave  : número da carteirinha do sócio (ID único)
        2 - nome   : ponteiro para o nome do sócio
        3 - plano  : código do plano
        4 - valor  : valor da mensalidade do plano
        5 - status : situação do sócio
    Retorno:
        TNo * : endereço do nó criado e preenchido com os valores
                recebidos.
        NULL : O nó não pôde ser criado
=========================================================*/
TNo* criarNo(int chave, const char *nome, int plano, float valor, int status) {
    TNo * no = malloc(sizeof(TNo));
    verificarMallocNo(no);
    no->chave = chave;
    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0';
    no->plano = plano;
    no->valor = valor;
    no->status = status;
    no->esquerdo = NULL;
    no->direito = NULL;
    no->altura = 1;
    return no;
}

/*=========================================================
    Função: verificarMallocNo
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Verifica se a alocação de um nó foi bem-sucedida.
        Se o ponteiro for NULL, exibe uma mensagem de erro e
        encerra o programa.
    Parâmetros:
        1 - no : ponteiro devolvido pelo malloc, a ser verificado
    Retorno:
        void. Em caso de falha, o programa termina com exit(1).
  =========================================================*/
void verificarMallocNo(TNo const * const no) {
    if(no == NULL) {
        printf("Problema ao alocar o No!\n");
        exit(1);
    }
}

/*=========================================================
    Função: nomePlano
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Converte o código numérico do plano no nome do plano,
        para exibição.
    Parâmetros:
        1 - plano : código do plano (1=Bronze, 2=Prata, 3=Ouro,
                    4=Diamante)
    Retorno:
        const char * : texto do plano ("Bronze", "Prata", "Ouro" ou
                       "Diamante"); "Desconhecido" se o código for
                       inválido.
    Observação:
        O texto retornado é uma constante: não deve ser alterado
        nem liberado com free.
  =========================================================*/
const char * nomePlano(int plano) {
    switch (plano) {
        case 1: return "Bronze";
        case 2: return "Prata";
        case 3: return "Ouro";
        case 4: return "Diamante";
        default: return "Desconhecido";
    }
}

/*=========================================================
    Função: mostrarSocio
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Imprime em uma linha todos os dados de um sócio: ID, nome,
        plano, mensalidade e situação de pagamento.
    Parâmetros:
        1 - n : nó que contém os dados do sócio
    Retorno:
        void. Se n for NULL, não imprime nada.
  =========================================================*/
void mostrarSocio(TNo const * const n) {
    if (n == NULL) return;
    printf("ID %d | %s | Plano %s | R$ %.2f | %s\n",
           n->chave, n->nome, nomePlano(n->plano), n->valor,
           n->status ? "Em dia" : "Inadimplente");
}

/*=========================================================
    Função: altura
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Devolve a altura armazenada em um nó. Uma árvore vazia
        tem altura 0 e uma folha tem altura 1.
    Parâmetros:
        1 - n : nó a ser consultado (pode ser NULL)
    Retorno:
        int : altura do nó, ou 0 se n for NULL.
  =========================================================*/
int altura(TNo const * const n) {
    if (n == NULL) return 0;
    return n->altura;
}

/*=========================================================
    Função: atualizaAltura
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Recalcula a altura de um nó a partir da altura dos filhos:
        altura = 1 + max(altura do esquerdo, altura do direito).
    Parâmetros:
        1 - n : nó cuja altura será recalculada
    Retorno:
        void. O campo altura de n é atualizado. Se n for NULL,
        nada é feito.
    Observação:
        Deve ser chamada de baixo para cima (folha primeiro, raiz
        por último), pois depende das alturas dos filhos já
        atualizadas.
  =========================================================*/
void atualizaAltura(TNo *n) {
    int ae, ad;
    if (n == NULL) return;
    ae = altura(n->esquerdo);
    ad = altura(n->direito);
    n->altura = 1 + (ae > ad ? ae : ad);
}

/*=========================================================
    Função: fb
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Calcula o fator de balanceamento (FB) de um nó:
        FB = altura(esquerdo) - altura(direito).
    Parâmetros:
        1 - n : nó a ser avaliado (pode ser NULL)
    Retorno:
        int : fator de balanceamento; 0 se n for NULL.
              Em uma AVL válida, o FB fica entre -1 e +1.
              FB >= +2 indica desbalanceamento à esquerda e
              FB <= -2, desbalanceamento à direita.
  =========================================================*/
int fb(TNo const * const n) {
    if (n == NULL) return 0;
    return altura(n->esquerdo) - altura(n->direito);
}

/*=========================================================
    Função: emOrdem
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Percorre a árvore em ordem (esquerdo, nó, direito) e
        imprime os sócios em ordem crescente de ID.
    Parâmetros:
        1 - raiz : raiz da árvore (ou subárvore) a ser percorrida
    Retorno:
        void. Se raiz for NULL, não imprime nada.
  =========================================================*/
void emOrdem(TNo const * const raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esquerdo);
    mostrarSocio(raiz);
    emOrdem(raiz->direito);
}

/*=========================================================
    Função: mostrarFB
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Percorre a árvore em ordem e imprime, para cada nó, o ID,
        a altura e o fator de balanceamento. Usada para conferir
        se a árvore está balanceada.
    Parâmetros:
        1 - raiz : raiz da árvore (ou subárvore) a ser percorrida
    Retorno:
        void. Se raiz for NULL, não imprime nada.
  =========================================================*/
void mostrarFB(TNo const * const raiz) {
    if (raiz == NULL) return;
    mostrarFB(raiz->esquerdo);
    printf("No %d: altura=%d  FB=%d\n", raiz->chave, raiz->altura, fb(raiz));
    mostrarFB(raiz->direito);
}

/*=========================================================
    Função: desenhar
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Desenha a árvore "deitada" no console: a raiz fica à
        esquerda, a subárvore direita acima e a esquerda abaixo.
        Cada nível é recuado em 6 espaços.
    Parâmetros:
        1 - raiz  : raiz da árvore (ou subárvore) a ser desenhada
        2 - nivel : nível atual de recuo; use 0 na primeira chamada
    Retorno:
        void. Se raiz for NULL, não imprime nada.
  =========================================================*/
void desenhar(TNo const * const raiz, int nivel) {
    int i;
    if (raiz == NULL) return;
    desenhar(raiz->direito, nivel + 1);
    for (i = 0; i < nivel; i++) printf("      ");
    printf("%d\n", raiz->chave);
    desenhar(raiz->esquerdo, nivel + 1);
}