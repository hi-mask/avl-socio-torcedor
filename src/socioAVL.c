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