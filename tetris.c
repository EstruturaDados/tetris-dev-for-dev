#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 
#include <time.h>   

#define MAX_FILA 5
#define MAX_PILHA 3 

// 🧩 Nível Novato: Fila de Peças Futuras
// (Structs e funções da Fila permanecem idênticas)

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
        return;
    }
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % MAX_FILA; 
    f->total++;
}

Peca dequeue(Fila *f) {
    Peca p;
    if (filaVazia(f)) {
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

// Estrutura da Pilha
typedef struct {
    Peca itens[MAX_PILHA];
    int topo;
} Pilha;

// Funções da Pilha (Nível Aventureiro)

void inicializarPilha(Pilha *p) {
    p->topo = -1; 
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == MAX_PILHA - 1;
}

void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("Erro: Pilha de reserva cheia! Nao pode reservar.\n");
        return;
    }
    p->topo++;
    p->itens[p->topo] = peca;
}

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


// 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
//
// - Implemente interações avançadas entre as estruturas:
//       4 - Trocar a peça da frente da fila com o topo da pilha
//       5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
// - Para a opção 4:
//       Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
//       Troque os elementos diretamente nos arrays.
// - Para a opção 5:
//       Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
//       Use a lógica de índice circular para acessar os primeiros da fila.
// - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.

/**
 * Troca a peça da frente da fila com o topo da pilha.
 * (Nível Mestre - Opção 4)
 */
void trocarPecaFilaPilha(Fila *f, Pilha *p) {
    // Validação: Ambas as estruturas devem ter pelo menos uma peça.
    if (filaVazia(f) || pilhaVazia(p)) {
        printf("Erro: Fila e Pilha precisam ter pelo menos 1 peca para trocar.\n");
        return;
    }

    // Troca a peça da frente da fila (f->inicio) com o topo da pilha (p->topo)
    Peca temp = f->itens[f->inicio];
    f->itens[f->inicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;

    printf("Troca realizada: Frente da Fila <-> Topo da Pilha.\n");
}

/**
 * Troca as 3 primeiras peças da fila com as 3 peças da pilha.
 * (Nível Mestre - Opção 5)
 */
void trocar3PecasFilaPilha(Fila *f, Pilha *p) {
    // Validação: Pilha deve estar cheia (topo == 2) e fila deve ter 3+ peças.
    if (p->topo != 2 || f->total < 3) {
        printf("Erro: Para a troca multipla, a Pilha deve estar cheia (3 pecas) e a Fila deve ter pelo menos 3 pecas.\n");
        return;
    }

    // Troca as 3 peças da pilha (índices 0, 1, 2) 
    // com as 3 primeiras da fila (índices inicio, inicio+1, inicio+2)
    
    for (int i = 0; i < 3; i++) {
        // Calcula o índice circular para a fila
        int idx_fila = (f->inicio + i) % MAX_FILA;
        
        // O índice da pilha é simplesmente 'i' (0, 1, 2)
        int idx_pilha = i; 
        
        Peca temp = f->itens[idx_fila];
        f->itens[idx_fila] = p->itens[idx_pilha];
        p->itens[idx_pilha] = temp;
    }

    printf("Troca multipla realizada: 3 da Fila <-> 3 da Pilha.\n");
}


int main() {
    srand(time(NULL)); 
    
    Fila fila;
    Pilha pilha; 

    inicializarFila(&fila);
    inicializarPilha(&pilha); 

    // Preenche a fila inicial com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao = -1;
    while (opcao != 0) {
        printf("\n--- Tetris Stack (Nivel Mestre) ---\n");
        mostrarFila(&fila);
        mostrarPilha(&pilha); 
        printf("-------------------------------------\n");
        printf("Menu:\n");
        printf("  1 - Jogar peca (remove da frente)\n");
        printf("  2 - Reservar peca (fila -> pilha)\n");
        printf("  3 - Usar peca reservada (pilha)\n");
        printf("  4 - Trocar frente da fila com topo da pilha\n");
        printf("  5 - Trocar 3 da fila com 3 da pilha\n");
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
                    enqueue(&fila, gerarPeca()); // Repõe
                }
                break;
            }
            case 2: { // Reservar peça (Fila -> Pilha)
                if (pilhaCheia(&pilha)) {
                    printf("Erro: Pilha de reserva esta cheia!\n");
                } else if (filaVazia(&fila)) {
                    printf("Erro: Fila esta vazia, nao pode reservar!\n");
                } else {
                    Peca reservada = dequeue(&fila);
                    push(&pilha, reservada);
                    printf("Peca [%c%d] reservada.\n", reservada.tipo, reservada.id);
                    enqueue(&fila, gerarPeca()); // Repõe
                }
                break;
            }
            case 3: { // Usar peça reservada (Pop Pilha)
                if (pilhaVazia(&pilha)) {
                    printf("Erro: Pilha de reserva esta vazia!\n");
                } else {
                    Peca usada = pop(&pilha);
                    printf("Peca [%c%d] usada da reserva.\n", usada.tipo, usada.id);
                }
                break;
            }
            case 4: { // Trocar frente da fila com topo da pilha (Mestre)
                trocarPecaFilaPilha(&fila, &pilha);
                break;
            }
            case 5: { // Trocar 3 primeiros da fila com 3 da pilha (Mestre)
                trocar3PecasFilaPilha(&fila, &pilha);
                break;
            }
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}