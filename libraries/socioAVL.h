#ifndef SOCIOAVL_H
#define SOCIOAVL_H
#define TAM_NOME 50

/*=========================================================
/*
    Struct do No que estará na Arvore
=========================================================*/
typedef struct No {
    int chave;            /* idSocio: numero da carteirinha */
    char nome[TAM_NOME];
    int plano;            /* 1=Bronze 2=Prata 3=Ouro 4=Diamante */
    float valor;
    int status;           /* 1=em dia  0=inadimplente */
    int altura;           /* obrigatorio na AVL */
    struct No *esq;
    struct No *dir;
} No;

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
No * criarNo(int chave, const char *nome, int plano, float valor, int status);

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
void verificarMallocNo(No const * const no);

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
const char * nomePlano(int plano);

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
void mostrarSocio(No const * const n);
 
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
int altura(No const * const n);

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
void atualizaAltura(No *n);
 
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
int fb(No const * const n);
 
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
void emOrdem(No const * const raiz);
 
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
void mostrarFB(No const * const raiz);
 
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
void desenhar(No const * const raiz, int nivel);

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
     float valor, int status);

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
No * buscar(No *raiz, int chave);

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
void liberarArvore(No *raiz);


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
No* rotacaoDireita(No *y);


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
No* rotacaoEsquerda(No *x);


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
No* rotacaoLR(No *z);


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
No* rotacaoRL(No *z);
#endif