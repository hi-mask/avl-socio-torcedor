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
        No * : endereço do nó criado e preenchido com os valores
                recebidos.
        NULL : O nó não pôde ser criado
=========================================================*/
No* criarNo(int chave, const char *nome, int plano, float valor, int status) {
    No * no = malloc(sizeof(No));
    verificarMallocNo(no);
    no->chave = chave;
    strncpy(no->nome, nome, sizeof(no->nome) - 1);
    no->nome[sizeof(no->nome) - 1] = '\0';
    no->plano = plano;
    no->valor = valor;
    no->status = status;
    no->esq = NULL;
    no->dir = NULL;
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
void verificarMallocNo(No const * const no) {
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
void mostrarSocio(No const * const n) {
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
int altura(No const * const n) {
    if (n == NULL) return 0;
    return n->altura;
}

/*=========================================================
    Função: atualizaAltura
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Recalcula a altura de um nó a partir da altura dos filhos:
        altura = 1 + max(altura do esq, altura do dir).
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
void atualizaAltura(No *n) {
    int ae, ad;
    if (n == NULL) return;
    ae = altura(n->esq);
    ad = altura(n->dir);
    n->altura = 1 + (ae > ad ? ae : ad);
}

/*=========================================================
    Função: fb
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Calcula o fator de balanceamento (FB) de um nó:
        FB = altura(esq) - altura(dir).
    Parâmetros:
        1 - n : nó a ser avaliado (pode ser NULL)
    Retorno:
        int : fator de balanceamento; 0 se n for NULL.
              Em uma AVL válida, o FB fica entre -1 e +1.
              FB >= +2 indica desbalanceamento à esquerda e
              FB <= -2, desbalanceamento à direita.
  =========================================================*/
int fb(No const * const n) {
    if (n == NULL) return 0;
    return altura(n->esq) - altura(n->dir);
}

/*=========================================================
    Função: emOrdem
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Percorre a árvore em ordem (esq, nó, dir) e
        imprime os sócios em ordem crescente de ID.
    Parâmetros:
        1 - raiz : raiz da árvore (ou subárvore) a ser percorrida
    Retorno:
        void. Se raiz for NULL, não imprime nada.
  =========================================================*/
void emOrdem(No const * const raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    mostrarSocio(raiz);
    emOrdem(raiz->dir);
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
void mostrarFB(No const * const raiz) {
    if (raiz == NULL) return;
    mostrarFB(raiz->esq);
    printf("No %d: altura=%d  FB=%d\n", raiz->chave, raiz->altura, fb(raiz));
    mostrarFB(raiz->dir);
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
void desenhar(No const * const raiz, int nivel) {
    int i;
    if (raiz == NULL) return;
    desenhar(raiz->dir, nivel + 1);
    for (i = 0; i < nivel; i++) printf("      ");
    printf("%d\n", raiz->chave);
    desenhar(raiz->esq, nivel + 1);
}

/*=========================================================
    Função: inserir
    Autor: Samuel de Godoy Larroque

    Descrição:
        Insere dados de um sócio-torcedor em um nó da árvore AVL 
    Parâmetros:
        1 - raiz   : Nó que rebeberá dados
        2 - chave  : número da carteirinha do sócio (ID único)
        3 - nome   : ponteiro para o nome do sócio
        4 - plano  : código do plano
        5 - valor  : valor da mensalidade do plano
        6 - status : situação do sócio
    Retorno:
        No * : endereço do nó criado e preenchido com os valores
                recebidos.
        NULL : O nó não pôde ser criado
=========================================================*/
No * inserir(No *raiz, int chave, const char *nome, int plano,
     float valor, int status) {

    /* --- Passo 1: inserção normal de BST --- */
    if (raiz == NULL)
        return criarNo(chave, nome, plano, valor, status);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave, nome,
             plano, valor, status);
    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave, nome,
             plano, valor, status);
    else
        return raiz;   /* duplicata — ignora */

    /* --- Passo 2: atualiza altura deste nó --- */
    atualizaAltura(raiz);

    /* --- Passo 3: verifica FB e rotaciona se necessário --- */
    int f = fb(raiz);

    /* LL: pesado à esquerda, inserção no filho esq do filho esq */
    if (f > 1 && chave < raiz->esq->chave)
        return rotacaoDireita(raiz);

    /* RR: pesado à direita, inserção no filho dir do filho dir */
    if (f < -1 && chave > raiz->dir->chave)
        return rotacaoEsquerda(raiz);

    /* LR: pesado à esquerda, inserção no filho dir do filho esq */
    if (f > 1 && chave > raiz->esq->chave)
        return rotacaoLR(raiz);

    /* RL: pesado à direita, inserção no filho esq do filho dir */
    if (f < -1 && chave < raiz->dir->chave)
        return rotacaoRL(raiz);

    return raiz;   /* sem rotação necessária */
}

/*=========================================================
    Função: buscar
    Autor: Samuel de Godoy Larroque

    Descrição:
        Busca um sócio torcedor pelo sua carteirinha (ID)
    Parâmetros:
        1 - raiz   : Nó que rebeberá dados
        2 - chave  : número da carteirinha do sócio (ID único)
    Retorno:
        No * : endereço do nó procurado
=========================================================*/
No * buscar(No *raiz, int chave) {
    if (raiz == NULL || raiz->chave == chave)
        return raiz;
    if (chave < raiz->chave)
        return buscar(raiz->esq, chave);
    return buscar(raiz->dir, chave);
}

/*=========================================================
    Função: liberar
    Autor: Samuel de Godoy Larroque

    Descrição:
        Libera a árvore inteira;
    Parâmetros:
        1 - raiz   : Nó da raiz
    Retorno:
        void.
=========================================================*/
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* =============================================================================
 * ROTAÇÃO LL — giro à DIREITA
 * =============================================================================
 *
 * Quando usar:
 *   FB do nó = +2  (pesado à esquerda)
 *   FB do filho esquerdo = +1 (inserção no filho esquerdo do filho esquerdo)
 *
 * Antes:          Depois:
 *     y              x
 *    /              / \
 *   x       →     T1   y
 *  / \                / \
 * T1  T2            T2   T3
 *
 * O filho esquerdo (x) sobe e assume o lugar de y.
 * O nó y desce e vira filho DIREITO de x.
 */
No* rotacaoDireita(No *y) {

    No *x  = y->esq;   /* x é o filho esquerdo — vai subir        */
    No *T2 = x->dir;   /* T2 é o filho direito de x — muda de pai */

    /* --- o giro acontece aqui --- */
    x->dir = y;        /* y desce: vira filho DIREITO de x        */
    y->esq = T2;       /* T2 passa a ser filho esquerdo de y      */

    /* atualiza alturas: y primeiro pois agora está ABAIXO de x */
    atualizaAltura(y);
    atualizaAltura(x);

    return x;   /* x é a nova raiz desta subárvore */
}


/* =============================================================================
 * ROTAÇÃO RR — giro à ESQUERDA
 * =============================================================================
 *
 * Quando usar:
 *   FB do nó = -2  (pesado à direita)
 *   FB do filho direito = -1 (inserção no filho direito do filho direito)
 *
 * Antes:      Depois:
 *   x              y
 *    \            / \
 *     y    →     x   T3
 *    / \          \
 *   T2  T3        T2
 *
 * O filho direito (y) sobe e assume o lugar de x.
 * O nó x desce e vira filho ESQUERDO de y.
 */
No* rotacaoEsquerda(No *x) {

    No *y  = x->dir;   /* y é o filho direito — vai subir         */
    No *T2 = y->esq;   /* T2 é o filho esquerdo de y — muda de pai */

    /* --- o giro acontece aqui --- */
    y->esq = x;        /* x desce: vira filho ESQUERDO de y       */
    x->dir = T2;       /* T2 passa a ser filho direito de x       */

    /* atualiza alturas: x primeiro pois agora está ABAIXO de y */
    atualizaAltura(x);
    atualizaAltura(y);

    return y;   /* y é a nova raiz desta subárvore */
}


/* =============================================================================
 * ROTAÇÃO LR — dupla esquerda-direita
 * =============================================================================
 *
 * Quando usar:
 *   FB do nó = +2  (pesado à esquerda)
 *   FB do filho esquerdo = -1 (inserção no filho DIREITO do filho esquerdo)
 *
 * Solução em duas etapas:
 *   1. Rotação à ESQUERDA no filho esquerdo
 *   2. Rotação à DIREITA na raiz
 */
No* rotacaoLR(No *z) {
    z->esq = rotacaoEsquerda(z->esq);   /* passo 1: gira o filho esquerdo */
    return rotacaoDireita(z);            /* passo 2: gira a raiz           */
}


/* =============================================================================
 * ROTAÇÃO RL — dupla direita-esquerda
 * =============================================================================
 *
 * Quando usar:
 *   FB do nó = -2  (pesado à direita)
 *   FB do filho direito = +1 (inserção no filho ESQUERDO do filho direito)
 *
 * Solução em duas etapas:
 *   1. Rotação à DIREITA no filho direito
 *   2. Rotação à ESQUERDA na raiz
 */
No* rotacaoRL(No *z) {
    z->dir = rotacaoDireita(z->dir);    /* passo 1: gira o filho direito  */
    return rotacaoEsquerda(z);           /* passo 2: gira a raiz           */
}

/*=========================================================
    Função: menorNo
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Desce sempre pela esquerda a partir de um nó até
        encontrar o nó sem filho esquerdo, que é o de menor
        chave daquela subárvore. Usada no caso 3 da remoção
        (nó com 2 filhos) para achar o sucessor em ordem.
    Parâmetros:
        1 - no : raiz da subárvore a ser percorrida
    Retorno:
        No * : endereço do nó de menor chave da subárvore.
        NULL : se no for NULL.
    Observação:
        A função apenas localiza o nó; não o remove nem
        altera a árvore.
  =========================================================*/
No * menorNo(No * no){
    if(no == NULL)return NULL;
    if(no->esq == NULL) return no;
    
    return menorNo(no->esq);
}

/*=========================================================
    Função: remover
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Remove da árvore AVL o sócio com a chave informada e
        rebalanceia o caminho percorrido. Trata os três casos:
        1 - folha: libera o nó e devolve NULL;
        2 - um filho: libera o nó e devolve o filho;
        3 - dois filhos: copia os dados do sucessor (menor nó
            da subárvore direita) para o nó atual e remove o
            sucessor da direita.
    Parâmetros:
        1 - no    : raiz da árvore (ou subárvore)
        2 - chave : número da carteirinha do sócio a remover
    Retorno:
        No * : nova raiz da subárvore após a remoção e o
               rebalanceamento.
        NULL : se a subárvore ficou vazia ou se no for NULL.
    Observação:
        Se a chave não existir, a árvore não muda. O retorno
        deve ser sempre recebido: raiz = remover(raiz, chave).
  =========================================================*/
No * remover(No * const no, int chave){
    if(no == NULL) return NULL;

    if(chave < no->chave){
        no->esq = remover(no->esq, chave);
    }
    else if(chave > no->chave){
        no->dir = remover(no->dir, chave);
    }
    //caso 1
    else if(no->esq == NULL && no->dir == NULL){
        free(no);
        return NULL;
    }
    //caso 2
    else if(no->esq == NULL && no->dir != NULL){
        No * pAux = no->dir;
        free(no);
        return pAux;
    }
    else if(no->esq != NULL && no->dir == NULL){
        No * pAux = no->esq;
        free(no);
        return pAux;
    }
    //caso 3
    else {
        No * sucessor = menorNo(no->dir);
        no->chave = sucessor->chave;
        no->plano = sucessor->plano;
        no->status = sucessor->status;
        no->valor = sucessor->valor;
        strncpy(no->nome, sucessor->nome, sizeof(no->nome) - 1);
        no->nome[sizeof(no->nome) - 1] = '\0';
        no->dir = remover(no->dir, sucessor->chave);
    }
    return balancear(no);
    
}

/*=========================================================
    Função: balancear
    Autor: Marcos Paulo da Silva Oliveira

    Descrição:
        Atualiza a altura de um nó, calcula seu fator de
        balanceamento e, se estiver fora do intervalo [-1, 1],
        aplica a rotação adequada (LL, LR, RR ou RL). A escolha
        é feita pelo FB do filho pesado: LL se filho esq >= 0,
        LR se filho esq < 0, RR se filho dir <= 0 e RL se
        filho dir > 0. Chamada na volta da recursão da remoção.
    Parâmetros:
        1 - no : nó (raiz da subárvore) a ser balanceado
    Retorno:
        No * : nova raiz da subárvore (o próprio no, se não
               houve rotação, ou o nó que subiu após a rotação).
        NULL : se no for NULL.
    Observação:
        O retorno deve sempre ser ligado ao pai, pois a raiz
        da subárvore pode mudar.
  =========================================================*/
No * balancear(No * const no){
    int f;
    if(no == NULL) return NULL;

    atualizaAltura(no);
    f = fb(no);

    /* pesado a esquerda */
    if(f > 1){
        if(fb(no->esq) >= 0)
            return rotacaoDireita(no);      /* LL */
        return rotacaoLR(no);               /* LR */
    }

    /* pesado a direita */
    if(f < -1){
        if(fb(no->dir) <= 0)
            return rotacaoEsquerda(no);     /* RR */
        return rotacaoRL(no);               /* RL */
    }

    return no;
}

/*=========================================================
    Função: alturaReal
    Autor: Samuel de Godoy Larroque

    Descrição:
        Calcula a altura de uma subárvore percorrendo seus
        nós, sem usar o campo altura gravado. Serve para
        conferir se as alturas gravadas estão corretas.
    Parâmetros:
        1 - no : raiz da subárvore (pode ser NULL)
    Retorno:
        int : altura real da subárvore, ou 0 se no for NULL.
  =========================================================*/
int alturaReal(No const * const no){
    int ae, ad;
    if(no == NULL) return 0;
    ae = alturaReal(no->esq);
    ad = alturaReal(no->dir);
    return 1 + (ae > ad ? ae : ad);
}

/*=========================================================
    Função: ehAVL
    Autor: Samuel de Godoy Larroque

    Descrição:
        Verifica se a árvore é uma AVL válida: em todos os nós,
        a altura gravada deve ser igual à altura real e o fator
        de balanceamento deve estar entre -1 e 1.
    Parâmetros:
        1 - no : raiz da árvore (ou subárvore) a ser verificada
    Retorno:
        int : 1 se a árvore é AVL válida, 0 caso contrário.
              Uma árvore vazia (NULL) é considerada válida.
  =========================================================*/
int ehAVL(No const * const no){
    int f;
    if(no == NULL) return 1;

    if(no->altura != alturaReal(no)) return 0;

    f = alturaReal(no->esq) - alturaReal(no->dir);
    if(f < -1 || f > 1) return 0;

    // retorna o valor lógico da sentença
    return ehAVL(no->esq) && ehAVL(no->dir);
}

/*=========================================================
    Função: contarNos
    Autor: Samuel de Godoy Larroque

    Descrição:
        Conta quantos nós existem na árvore, percorrendo-a
        recursivamente: 1 (o nó atual) + nós da subárvore
        esquerda + nós da subárvore direita. Usada para
        mostrar a quantidade de sócios após a carga e após
        cada remoção.
    Parâmetros:
        1 - raiz : raiz da árvore (ou subárvore) a ser contada
    Retorno:
        int : quantidade de nós da árvore, ou 0 se raiz for
              NULL (árvore vazia).
  =========================================================*/
int contarNos(No const * const raiz){
    if(raiz == NULL) {
        return 0;
    }
    return 1 + contarNos(raiz->esq) +
    contarNos(raiz->dir);
}