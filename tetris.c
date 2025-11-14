#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3 // Definido para uso futuro no Nível Aventureiro

// 🧩 Nível Novato: Fila de Peças Futuras
//
// - Crie uma struct Peca com os campos: tipo (char) e id (int).
// - Implemente uma fila circular com capacidade para 5 peças.
// - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
// - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
// - Exiba a fila após cada ação com uma função mostrarFila().
// - Use um menu com opções como:
//       1 - Jogar peça (remover da frente)
//       0 - Sair
// - A cada remoção, insira uma nova peça ao final da fila.

// Estrutura da Peça
typedef struct {
    char tipo; // 'I', 'O', 'T', 'L'
    int id;
} Peca;

// Estrutura da Fila Circular
typedef struct {
    Peca itens[MAX_FILA];
    int inicio;
    int fim;
    int total;
} Fila;

// Variável global para controlar os IDs sequenciais das peças
int proximoId = 0;

/**
 * Gera uma nova peça com tipo aleatório e ID sequencial.
 */
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};
    p.tipo = tipos[rand() % 4]; // Sorteia um dos 4 tipos
    p.id = proximoId++;
    return p;
}

// Funções da Fila (Nível Novato)

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX_FILA;
}

/**
 * Adiciona um elemento ao final da fila (enqueue).
 */
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Aviso: Fila cheia! Nao foi possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA; // Lógica circular
    f->total++;
}

/**
 * Remove um elemento do início da fila (dequeue).
 */
Peca dequeue(Fila *f) {
    Peca p;
    if (filaVazia(f)) {
        printf("Aviso: Fila vazia! Retornando peca nula.\n");
        p.tipo = ' '; // Valor sentinela
        p.id = -1;
        return p;
    }
    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA; // Lógica circular
    f->total--;
    return p;
}

/**
 * Exibe o conteúdo da fila de forma ordenada (Início -> Fim).
 */
void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila de pecas: [Vazia]\n");
        return;
    }
    printf("Fila de pecas (Frente -> Fim):\n");
    
    int i = 0;
    int idx = f->inicio; // Índice para percorrer a fila circularmente
    
    while (i < f->total) {
        printf("[%c%d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
        i++;
    }
    printf("\n");
}


// Estruturas e funções do Nível Aventureiro (Pilha)


// Estruturas e funções do Nível Mestre (Integração)


int main() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    Fila fila;
    inicializarFila(&fila);

    // Preenche a fila inicial com 5 peças (requisito do desafio)
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- Tetris Stack (Nivel Novato) ---\n");
        mostrarFila(&fila);
        printf("-------------------------------------\n");
        printf("Menu:\n");
        printf("  1 - Jogar peca (remove da frente)\n");
        printf("  0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        // Limpa o buffer de entrada para evitar loops infinitos com char
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa entrada inválida
            opcao = -1; // Força opção inválida
        }

        switch (opcao) {
            case 1: { // Jogar peça
                if (filaVazia(&fila)) {
                    printf("Fila esta vazia, nao pode jogar.\n");
                } else {
                    Peca jogada = dequeue(&fila);
                    printf("Peca jogada: [%c%d]\n", jogada.tipo, jogada.id);

                    // Adiciona uma nova peça para manter a fila cheia
                    Peca nova = gerarPeca();
                    enqueue(&fila, nova);
                    printf("Nova peca adicionada a fila: [%c%d]\n", nova.tipo, nova.id);
                }
                break;
            }
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }
    
    // Nível Aventureiro: Adição da Pilha de Reserva

    // Nível Mestre: Integração Estratégica entre Fila e Pilha

    return 0;
}