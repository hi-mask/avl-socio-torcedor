#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socioAVL.h"
#include "tratamentoArquivos.h"

int main(void){
    No * raizAVL = NULL;
    No * raizBST = NULL;
    zerarContadores();
    raizAVL = carregarArquivoNaAVL(raizAVL, "socios.txt");
    raizBST = carregarArquivoNaBST(raizBST, "socios.txt");

    do{
        int opcao = -1;

        printf("\n================== MENU ==================\n");
        printf("1. Realizar Busca\n");
        printf("2. Inserir\n");
        printf("3. Remover\n");
        printf("4. Listar Tudo\n");
        printf("5. Listar por Faixa\n");
        printf("6. Estatisticas\n");
        printf("7. Comparar AVL x BST\n");
   
        printf("0. Encerrar o Programa\n\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao){
            case 1: {
              int chave = -1;
              int comparacoesAVL = 0;

              printf("\nDigite o ID do socio: ");
              scanf("%d", &chave);
              getchar();

              No *resultadoAVL = buscar(raizAVL, chave, &comparacoesAVL);

              if (resultadoAVL != NULL) {
                     printf("\nSocio encontrado na AVL:\n");
                     mostrarSocio(resultadoAVL);
                     printf("Comparacoes: %d\n", comparacoesAVL);
              } else {
                     printf("\nSocio nao encontrado na AVL.\n");
                     printf("Comparacoes: %d\n", comparacoesAVL);
              }
            break;
            }

            case 2: {
              int chave = -1, plano = -1, status = -1;
              float valor = -1;
              char nome[sizeof(((No *)0)->nome)];
              int comparacoesAVL = 0;
              int comparacoesBST = 0;

              printf("\nDigite o ID do socio: ");
              scanf("%d", &chave);
              getchar();

              // Verifica se a chave ja existe nas arvores
              if (buscar(raizAVL, chave, &comparacoesAVL) != NULL ||
                     buscarBST(raizBST, chave, &comparacoesBST) != NULL) {

                     printf("\nJa existe um socio com esse ID!\n");
                     break;
              }

              printf("Digite o nome do socio: ");
              fgets(nome, sizeof(nome), stdin);
              nome[strcspn(nome, "\n")] = '\0';

              printf("Digite um dos planos abaixo:\n");
              printf("1. Bronze\n2. Prata\n3. Ouro\n4. Diamante\n\n");
              printf("Opcao: ");
              scanf("%d", &plano);
              getchar();

              printf("Digite o valor: ");
              scanf("%f", &valor);
              getchar();
  
              raizAVL = inserir(raizAVL, chave, nome, plano, valor, 1);
              raizBST = inserirBST(raizBST, chave, nome, plano, valor, 1);

              salvarAVLNoArquivo(raizAVL, "socios.txt");
              printf("\nSocio inserido com sucesso!\n");

            break;
            }

            case 3: {
              int chave = -1;
              int comparacoesAVL = 0;
              int comparacoesBST = 0;
              int prosseguir = -1;
              printf("\nDigite o ID do socio que deseja remover: ");
              scanf("%d", &chave);
              getchar();
              No *socioAVL = buscar(raizAVL, chave, &comparacoesAVL);
              No *socioBST = buscarBST(raizBST, chave, &comparacoesBST);

              if (socioAVL == NULL && socioBST == NULL) {
                     printf("\nSocio nao encontrado!\n");
                     break;
              }

              if (socioAVL == NULL || socioBST == NULL) {
                     printf("\nErro: as arvores possuem registros diferentes!\n");
                     break;
              }

              printf("\nSocio encontrado nas duas arvores!\n\n");
              printf("Deseja continuar?\n1. Sim\n0. Nao\n");
              printf("Opcao: ");
              scanf("%d", &prosseguir);
              if(!prosseguir){
                break;
              }
              raizAVL = remover(raizAVL, chave);
              raizBST = removerBST(raizBST, chave);
              salvarAVLNoArquivo(raizAVL, "socios.txt");
              printf("\nSocio removido de ambas arvores com sucesso!\n");
            break;
            }

            case 4:{
              int opcaoExibicao = -1;
              printf("\nEscolha uma opcao\n");
              printf("1. Socios da AVL\n0. Socios da BST\n");
              printf("Opcao: ");
              scanf("%d", &opcaoExibicao);
              getchar();
              if(!opcaoExibicao){
                printf("\n========== SOCIOS DA BST ==========\n");
                emOrdem(raizBST);
              }
              else{
              printf("\n========== SOCIOS DA AVL ==========\n");
              emOrdem(raizAVL);
              }
            break;
            }

            case 5:
              int inicio = 0, fim = 0;

              printf("\nDigite o inicio da faixa: ");
              scanf("%d", &inicio);
              getchar();

              printf("Digite o final da faixa: ");
              scanf("%d", &fim);
              getchar();
              if (inicio > fim) {
                     printf("\nFaixa invalida!\n");
                     break;
              }

              printf("\n==================== SOCIOS NA FAIXA [%d | %d] ====================\n",
                 inicio, fim);
              listarFaixa(raizAVL, inicio, fim);

            break;

            case 6:
              int quantidade = contarSociosArquivo("socios.txt");
              if(quantidade == -1){
                printf("Erro ao consultar o arquivo!\n");
                break;
              }
              printf("Registros carregados: %d\n", quantidade);
              printf("BST Simples -> altura: %d\n", alturaBST(raizBST));
              printf("AVL         -> altura: %d Raiz: %d\n",
              altura(raizAVL), raizAVL->chave);
              printf("\n========== ROTACOES AVL ==========\n");
              mostrarContadores();
            break;

            case 7: {
              int chave = -1;
              int comparacoesAVL = 0;
              int comparacoesBST = 0;

              printf("\nDigite o ID do socio: ");
              scanf("%d", &chave);

              No *resultadoAVL = buscar(raizAVL, chave, &comparacoesAVL);
              No *resultadoBST = buscarBST(raizBST, chave, &comparacoesBST);

              printf("\n========== COMPARACAO AVL x BST ==========\n");

              printf("AVL: %d comparacoes\n", comparacoesAVL);
              printf("BST: %d comparacoes\n", comparacoesBST);

              printf("==========================================\n");

              break;
            }

            case 0:
            liberarArvore(raizBST);
            liberarArvore(raizAVL);
            printf("\nEncerrando...\n");
            exit(0);

            default:
            printf("\nOpcao invalida!\n");

        }
    }while(1);
}
