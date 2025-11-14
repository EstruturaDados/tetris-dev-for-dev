#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>   

#define MAX_FILA 5
#define MAX_PILHA 3 

// 🧩 Nível Novato: Fila de Peças Futuras
// (Structs e funções da Fila permanecem idênticas ao Nível Novato)

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
    p.tipo = tipos[rand() % 4]; 
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

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        //printf("Aviso: Fila cheia! Nao foi possivel inserir.\n");
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA; 
    f->total++;
}

Peca dequeue(Fila *f) {
    Peca p;
    if (filaVazia(f)) {
        //printf("Aviso: Fila vazia! Retornando peca nula.\n");
        p.tipo = ' '; 
        p.id = -1;
        return p;
    }
    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_FILA; 
    f->total--;
    return p;
}

void mostrarFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila de pecas: [Vazia]\n");
        return;
    }
    printf("Fila de pecas (Frente -> Fim):\n");
    
    int i = 0;
    int idx = f->inicio; 
    
    while (i < f->total) {
        printf("[%c%d] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX_FILA;
        i++;
    }
    printf("\n");
}


// 🧠 Nível Aventureiro: Adição da Pilha de Reserva
//
// - Implemente uma pilha linear com capacidade para 3 peças.
// - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
// - Permita enviar uma peça da fila para a pilha (reserva).
// - Crie um menu com opção:
//       2 - Enviar peça da fila para a reserva (pilha)
//       3 - Usar peça da reserva (remover do topo da pilha)
// - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
// - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).

// Estrutura da Pilha
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// Funções da Pilha (Nível Aventureiro)

void inicializarPilha(Pilha *p) {
    p->topo = -1; // Convenção para pilha vazia
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

/**
 * Adiciona um elemento ao topo da pilha (push).
 */
void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("Erro: Pilha de reserva cheia! Nao pode reservar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = peca;
}

/**
 * Remove um elemento do topo da pilha (pop).
 */
Peca pop(Pilha *p) {
    Peca peca;
    if (pilhaVazia(p)) {
        printf("Erro: Pilha de reserva vazia! Nao pode usar.\n");
        peca.tipo = ' ';
        peca.id = -1;
        return peca;
    }
    peca = p->itens[p->topo];
    p->topo--;
    return peca;
}

/**
 * Exibe o conteúdo da pilha (Topo -> Base).
 */
void mostrarPilha(Pilha *p) {
    if (pilhaVazia(p)) {
        printf("Pilha de reserva: [Vazia]\n");
        return;
    }
    printf("Pilha de reserva (Topo -> Base):\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c%d] ", p->itens[i].tipo, p->itens[i].id);
    }
    printf("\n");
}


// Estruturas e funções do Nível Mestre (Integração)


int main() {
    srand(time(NULL)); 
    
    Fila fila;
    Pilha pilha; // Nível Aventureiro

    inicializarFila(&fila);
    inicializarPilha(&pilha); // Nível Aventureiro

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- Tetris Stack (Nivel Aventureiro) ---\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha); // Nível Aventureiro
        printf("-----------------------------------------\n");
        printf("Menu:\n");
        printf("  1 - Jogar peca (remove da frente)\n");
        printf("  2 - Reservar peca (fila -> pilha)\n");
        printf("  3 - Usar peca reservada (pilha)\n");
        printf("  0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n');
            opcao = -1; 
        }

        switch (opcao) {
            case 1: { // Jogar peça
                if (filaVazia(&fila)) {
                    printf("Fila esta vazia, nao pode jogar.\n");
                } else {
                    Peca jogada = dequeue(&fila);
                    printf("Peca jogada: [%c%d]\n", jogada.tipo, jogada.id);
                    
                    // Repõe a peça na fila para manter 5
                    enqueue(&fila, gerarPeca());
                }
                break;
            }
            case 2: { // Reservar peça (Fila -> Pilha)
                if (pilhaCheia(&pilha)) {
                    printf("Erro: Pilha de reserva esta cheia!\n");
                } else if (filaVazia(&fila)) {
                    printf("Erro: Fila esta vazia, nao pode reservar!\n");
                } else {
                    // Tira da fila e coloca na pilha
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("Peca [%c%d] reservada.\n", reservada.tipo, reservada.id);
                    
                    // Repõe a peça na fila para manter 5
                    enqueue(&fila, gerarPeca());
                }
                break;
            }
            case 3: { // Usar peça reservada (Pop Pilha)
                if (pilhaVazia(&pilha)) {
                    printf("Erro: Pilha de reserva esta vazia!\n");
                } else {
                    Peca usada = pop(&pilha);
                    printf("Peca [%c%d] usada da reserva.\n", usada.tipo, usada.id);
                    // Peça usada não volta para a fila
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
    
    // Nível Mestre: Integração Estratégica entre Fila e Pilha

    return 0;
}