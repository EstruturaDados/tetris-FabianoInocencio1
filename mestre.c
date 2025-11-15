#include <stdio.h>
#include <stdlib.h>

#define MAX 50   // Quantidade máxima de peças no tabuleiro ou pilha

// ----------------------------------------------------
// Estrutura de cada peça
// ----------------------------------------------------
typedef struct {
    char nome;     // Nome da peça (ex: 'A', 'B', 'C')
    int codigo;    // Código numérico da peça
} PECAS;

// ----------------------------------------------------
// Estrutura da fila (Tabuleiro)
// Representa a sequência de peças em jogo
// ----------------------------------------------------
typedef struct {
    PECAS itens[MAX]; // Vetor circular que guarda as peças
    int inicio;       // Índice da primeira peça da fila
    int fim;          // Índice onde a próxima peça será inserida
    int total;        // Quantidade atual de peças na fila
} Tabuleiro;

// ----------------------------------------------------
// Estrutura da Pilha (Reserva)
// ----------------------------------------------------
typedef struct {
    PECAS itens[MAX];  // Armazena as peças empilhadas
    int topo;          // Índice do topo da pilha
} Pilha;

// ---------- Funções auxiliares ----------

// Verifica se o tabuleiro (fila) está vazio
int TabuleiroVazio(Tabuleiro *t) { return (t->total == 0); }

// Verifica se o tabuleiro está cheio
int TabuleiroCheio(Tabuleiro *t) { return (t->total == MAX); }

// Verifica se a pilha está vazia
int pilhaVazia(Pilha *p) { return (p->topo == -1); }

// Verifica se a pilha está cheia
int pilhaCheia(Pilha *p) { return (p->topo == MAX - 1); }

// ---------- Inicializações ----------

// Inicializa os controles da fila
void iniciarTabuleiro(Tabuleiro *t) {
    t->inicio = 0;
    t->fim = 0;
    t->total = 0;
}

// Inicializa o topo da pilha
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

// ---------- Operações do Tabuleiro (fila circular) ----------

// Insere uma peça no final da fila
void inserir(Tabuleiro *t, PECAS p) {
    if (TabuleiroCheio(t)) {
        printf("Tabuleiro cheio, não é possível inserir mais peças!\n");
        return;
    }

    // Inserção no índice "fim"
    t->itens[t->fim] = p;

    // Incrementa o fim com volta circular
    t->fim = (t->fim + 1) % MAX;

    // Atualiza total de itens
    t->total++;

    printf("Peça %c %d inserida no tabuleiro.\n", p.nome, p.codigo);
}

// Remove a peça da frente da fila (jogada)
void remover(Tabuleiro *t) {
    if (TabuleiroVazio(t)) {
        printf("Tabuleiro vazio, nenhuma peça para remover.\n");
        return;
    }

    // Guarda a peça que está sendo removida
    PECAS p = t->itens[t->inicio];

    // Move o início circularmente
    t->inicio = (t->inicio + 1) % MAX;

    // Diminui o total
    t->total--;

    printf("Peça %c %d jogada (removida da fila).\n", p.nome, p.codigo);
}

// ---------- Operações da Pilha ----------

// Empilha peça no topo
void push(Pilha *p, PECAS nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Não é possível inserir.\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = nova;
    printf("Peça %c %d enviada para a reserva (empilhada).\n", nova.nome, nova.codigo);
}

// Desempilha peça do topo
void pop(Pilha *p, PECAS *removida) {
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Não é possível remover.\n");
        return;
    }

    // A peça removida é a do topo
    *removida = p->itens[p->topo];
    p->topo--;

    printf("Peça %c %d usada da reserva (desempilhada).\n", removida->nome, removida->codigo);
}

// ---------- Mostrar estados ----------

// Imprime o conteúdo atual do tabuleiro (fila)
void mostrarTabuleiro(Tabuleiro *t) {
    printf("\n--- Estado do Tabuleiro ---\n");

    if (TabuleiroVazio(t)) {
        printf("(vazio)\n");
        return;
    }

    int i, idx = t->inicio;

    // Percorre apenas os elementos existentes
    for (i = 0; i < t->total; i++) {
        printf("[%c %d] ", t->itens[idx].nome, t->itens[idx].codigo);
        idx = (idx + 1) % MAX;  // avanço circular
    }

    printf("\n");
}

// Imprime o conteúdo da pilha
void mostrarPilha(Pilha *p) {
    printf("\n--- Estado da Pilha (Reserva) ---\n");

    if (pilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }

    // Imprime de cima para baixo
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].nome, p->itens[i].codigo);
    }

    printf("\n");
}

// ---------- Função Principal ----------
int main() {
    Tabuleiro t;
    Pilha p;

    iniciarTabuleiro(&t);
    inicializarPilha(&p);

    int opcao;
    PECAS nova, removida;

    // Inserindo peças iniciais de exemplo
    for (int i = 0; i < 5; i++) {
        nova.nome = 'A' + i;
        nova.codigo = i + 1;
        inserir(&t, nova);
    }

    // Loop principal de opções
    do {
        printf("\n================ MENU DE OPCOES ================\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para reserva (pilha)\n");
        printf("3 - Usar peça da reserva (pilha)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com as 3 peças da pilha\n");
        printf("0 - Sair\n");
        printf("===============================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: // Remover da fila
                remover(&t);
                break;

            case 2: // Enviar da fila para pilha
                if (!TabuleiroVazio(&t)) {
                    PECAS frente = t.itens[t.inicio];
                    push(&p, frente);
                    remover(&t);
                } else {
                    printf("Tabuleiro vazio!\n");
                }
                break;

            case 3: // Usar peça da pilha
                pop(&p, &removida);
                break;

            case 4: // Troca individual
                if (!TabuleiroVazio(&t) && !pilhaVazia(&p)) {
                    PECAS temp = t.itens[t.inicio];
                    t.itens[t.inicio] = p.itens[p.topo];
                    p.itens[p.topo] = temp;
                    printf("Peça da frente da fila trocada com o topo da pilha!\n");
                } else {
                    printf("Troca não possível. Fila ou pilha vazia.\n");
                }
                break;

            case 5: // Troca de 3 peças
                if (t.total >= 3 && p.topo >= 2) {
                    for (int i = 0; i < 3; i++) {
                        int idx = (t.inicio + i) % MAX;
                        PECAS temp = t.itens[idx];
                        t.itens[idx] = p.itens[p.topo - i];
                        p.itens[p.topo - i] = temp;
                    }
                    printf("Trocadas as 3 primeiras peças da fila com as 3 da pilha!\n");
                } else {
                    printf("Operação inválida! É preciso ter ao menos 3 peças em cada.\n");
                }
                break;

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

        // Mostrar estados atuais sempre após cada operação
        mostrarTabuleiro(&t);
        mostrarPilha(&p);

    } while (opcao != 0);

    return 0;
}