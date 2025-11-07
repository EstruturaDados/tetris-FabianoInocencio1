#include <stdio.h>   // Biblioteca padrão de entrada e saída (printf, scanf, etc.)
#include <string.h>  // Para manipulação de strings (não é usada aqui, mas pode ser útil)
#include <stdlib.h>  // Para funções como malloc, rand, srand, etc.
#include <time.h>    // Para usar o tempo como semente do gerador de números aleatórios

// Estrutura que representa uma peça do jogo
typedef struct {
    char nome;   // Letra identificadora da peça (I, O, L, T)
    int codigo;  // Código numérico da peça
} PECAS;

// Define o tamanho máximo do tabuleiro (número de peças)
#define MAX 5

// Estrutura que representa o tabuleiro (implementado como fila circular)
typedef struct {
    PECAS itens[MAX]; // Vetor que armazena as peças
    int inicio;       // Índice do início da fila
    int fim;          // Índice do fim da fila
    int total;        // Quantidade total de peças no tabuleiro
} Tabuleiro;

// Função que inicializa o tabuleiro vazio
void iniciarTabuleiro(Tabuleiro *t) {
    t->inicio = 0;
    t->fim = 0;
    t->total = 0;
}

// Gera uma nova peça aleatória com base no código recebido
PECAS gerarPecas(int codigo) {
    PECAS p;
    char tipo[] = {'I', 'O', 'L', 'T'}; // Tipos possíveis de peças
    p.nome = tipo[rand() % 4];          // Escolhe um tipo aleatório
    p.codigo = codigo;                  // Define o código da peça
    return p;
}

// Verifica se o tabuleiro está cheio
int TabuleiroCheio(Tabuleiro *t) {
    return t->total == MAX;
}

// Verifica se o tabuleiro está vazio
int TabuleiroVazio(Tabuleiro *t) {
    return t->total == 0;
}

// Insere uma nova peça no tabuleiro (fim da fila)
void inserir(Tabuleiro *t, PECAS p) {
    if (TabuleiroCheio(t)) {
        printf("Tabuleiro cheio, não é possível inserir!\n");
        return;
    }
    t->itens[t->fim] = p;              // Coloca a peça na posição 'fim'
    t->fim = (t->fim + 1) % MAX;       // Atualiza o índice circularmente
    t->total++;                        // Incrementa o total de peças
    printf("Peça %c %d jogada\n", p.nome, p.codigo);
}

// Remove uma peça do tabuleiro (início da fila)
PECAS remover(Tabuleiro *t) {
    PECAS p = {'-', -1}; // Valor padrão caso esteja vazio

    if (TabuleiroVazio(t)) {
        printf("Tabuleiro vazio, nenhuma peça para jogar\n");
        return p;
    }

    // Pega a peça atual do início antes de atualizar
    p = t->itens[t->inicio];
    t->inicio = (t->inicio + 1) % MAX; // Atualiza o índice circularmente
    t->total--;                        // Decrementa o total de peças
    return p;
}

// Mostra o estado atual do tabuleiro
void mostrarTabuleiro(Tabuleiro *t) {
    printf("Tabuleiro: ");
    for (int i = 0, idx = t->inicio; i < t->total; i++, idx = (idx + 1) % MAX) {
        printf("[%c, %d] ", t->itens[idx].nome, t->itens[idx].codigo);
    }
    printf("\n");
}

// Função principal
int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Tabuleiro t;
    iniciarTabuleiro(&t); // Começa com o tabuleiro vazio

    printf("==== Inserir 5 peças ====\n");
    int id = 1;
    for (int i = 0; i < MAX; i++) {
        inserir(&t, gerarPecas(id++)); // Gera e insere 5 peças aleatórias
    }

    printf("==== Peça Removida ====\n");
    PECAS removida = remover(&t); // Remove a primeira peça inserida (fila)
    printf("Peça removida %c, %d\n", removida.nome, removida.codigo);

    printf("\n==== Tabuleiro após remover ====\n");
    mostrarTabuleiro(&t); // Mostra o estado final do tabuleiro

    return 0;
}