# Cadastro de Sócios-Torcedores com Árvore AVL

Índice de sócios-torcedores de um clube de futebol, implementado em **C** com uma **Árvore AVL** (árvore binária de busca auto-balanceada). O projeto mostra, com dados do próprio sistema, por que a AVL vence a BST simples quando as chaves chegam em ordem crescente.

> Trabalho 1 da N2 de **Estrutura de Dados II** — PUC Goiás — Prof. Dr. Rovilson Mezencio.

---

## Sobre o projeto

Em um clube, o número da carteirinha do sócio é gerado em sequência (1001, 1002, 1003...). Inserir essas chaves em ordem numa BST simples transforma a árvore em uma lista encadeada, e a busca na catraca do estádio passa a custar O(n). A AVL se rebalanceia a cada inserção e remoção, mantendo a altura em torno de log<sub>2</sub>(n).

O sistema usa a AVL como índice e também para listar sócios em ordem e por faixa de ID.

## O sócio (nó da árvore)

| Campo | Tipo em C | Descrição |
|---|---|---|
| `chave` | `int` | ID do sócio (número da carteirinha), único |
| `nome` | `char[50]` | Nome do sócio |
| `plano` | `int` | 1 = Bronze, 2 = Prata, 3 = Ouro, 4 = Diamante |
| `valor` | `float` | Mensalidade do plano |
| `status` | `int` | 1 = em dia, 0 = inadimplente |
| `altura` | `int` | Altura do nó (controle da AVL) |
| `esq` / `dir` | `No *` | Filhos |

```c
typedef struct No {
    int chave;            /* idSocio: numero da carteirinha */
    char nome[50];
    int plano;            /* 1=Bronze 2=Prata 3=Ouro 4=Diamante */
    float valor;
    int status;           /* 1=em dia  0=inadimplente */
    int altura;           /* obrigatorio na AVL */
    struct No *esq;
    struct No *dir;
} No;
```

## Funcionalidades

- [ ] Inserir sócio com balanceamento automático (rotações LL, RR, LR e RL)
- [ ] Buscar sócio por ID, mostrando todos os campos
- [ ] Remover sócio (cancelamento de plano) com rebalanceamento
- [ ] Listar todos os sócios em ordem crescente de ID
- [ ] Listar sócios por faixa de ID (ex.: lote de uma campanha de adesão)
- [ ] Listar sócios de um plano
- [ ] Listar sócios inadimplentes
- [ ] Calcular a arrecadação mensal por plano
- [ ] Carga de 1000+ registros a partir de arquivo `.txt`
- [ ] Menu interativo no console
- [ ] Contador de rotações (LL, RR, LR, RL)
- [ ] Relatório de métricas BST × AVL (altura e número de comparações)

## Estrutura do repositório

```
.
├── src/
│   ├── socioAVL.h        # struct No e protótipos
│   ├── socioAVL.c        # AVL: inserção, rotações, busca, remoção, listagens
│   └── main.c            # menu e testes
├── data/
│   └── socios.txt        # carga de dados (1000+ registros)
├── entregas/             # versões em arquivo único enviadas ao Teams
│   ├── T1_E2_<grupo>.c
│   ├── T1_E3_<grupo>.c
│   └── T1_E4_<grupo>.c
├── docs/                 # proposta e EAP (E1) e roteiro do trabalho
└── README.md
```

## Como compilar e executar

Requer um compilador C (o projeto é compatível com o **Dev-C++**).

**Com GCC:**

```bash
gcc src/main.c src/socioAVL.c -o socios
./socios          # no Windows: socios.exe
```

Execute o programa a partir da raiz do repositório, para que ele encontre `data/socios.txt`.

**Com Dev-C++:** abra os arquivos de `src/` em um projeto e compile (F11). Para as entregas, use o arquivo único em `entregas/`.

## Formato do arquivo de carga

Um sócio por linha, campos separados por `;`:

```
ID;Nome;Plano;Valor;Status
1001;Maria Souza;3;99.90;1
1002;Joao Pereira;1;29.90;0
1003;Ana Lima;4;199.90;1
```

## Métricas BST × AVL

> A preencher após a Entrega 4, com a carga de 1000 registros em ordem crescente.

| Medida | BST simples | AVL |
|---|---|---|
| Altura da árvore | | |
| Comparações para buscar a chave 1 | | |
| Comparações para buscar a chave 250 | | |
| Comparações para buscar a chave 500 | | |
| Comparações para buscar a chave 750 | | |
| Comparações para buscar a chave 1000 | | |

**Rotações realizadas na carga (AVL):** LL = `?`, RR = `?`, LR = `?`, RL = `?`

## Organização do trabalho (EAP)

| Pacote | Responsável |
|---|---|
| 1. Dados do tema | Marcos Paulo da Silva Oliveira |
| 2. Núcleo AVL | Todos |
| 3. Funcionalidades | Todos |
| 4. Métricas e relatório | Todos |
| 5. Apresentação | Todos |

## Equipe

| Nome | GitHub |
|---|---|
| Marcos Paulo da Silva Oliveira | [@hi-mask](https://github.com/hi-mask) |
| Samuel de Godoy Larroque | [@usuario2](https://github.com/usuario2) |

## Convenções do código

- Linguagem C compatível com Dev-C++: variáveis declaradas no topo das funções e sem acentos nos `printf`.
- Toda função leva um comentário `/* autor: Nome */`.
- Nomes em português e camelCase (`criarNo`, `atualizaAltura`, `balancear`).

## Licença e uso acadêmico

Projeto desenvolvido para fins acadêmicos na disciplina de Estrutura de Dados II (PUC Goiás).
