#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_SIZE 5

typedef struct {
    int id;
    char type;
} Piece;

typedef struct {
    Piece data[QUEUE_SIZE];
    int front;
    int back;
    int count;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->back = -1;
    q->count = 0;
}

int isFull(Queue *q) {
    return q->count == QUEUE_SIZE;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

Piece generatePiece() {
    static int nextId = 1;
    char types[] = {'I', 'O', 'T', 'L'};
    int r = rand() % 4;

    Piece p;
    p.id = nextId++;
    p.type = types[r];
    return p;
}

void enqueue(Queue *q) {
    if (isFull(q)) {
        printf("\nA fila está cheia! Não é possível inserir.\n");
        return;
    }

    Piece newPiece = generatePiece();

    q->back = (q->back + 1) % QUEUE_SIZE;
    q->data[q->back] = newPiece;
    q->count++;

    printf("\nPeça inserida: ID=%d, Tipo=%c\n", newPiece.id, newPiece.type);
}

void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("\nA fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Piece p = q->data[q->front];
    printf("\nPeça jogada: ID=%d, Tipo=%c\n", p.id, p.type);

    q->front = (q->front + 1) % QUEUE_SIZE;
    q->count--;
}

void showQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\n--- Estado atual da Fila ---\n");

    int index = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("[%d] ID=%d | Tipo=%c\n", i + 1, q->data[index].id, q->data[index].type);
        index = (index + 1) % QUEUE_SIZE;
    }
}

int main() {
    srand(time(NULL));

    Queue queue;
    initQueue(&queue);

    int option;

    for (int i = 0; i < QUEUE_SIZE; i++)
        enqueue(&queue);

    do {
        printf("\n========== MENU ==========\n");
        printf("1 - Jogar peça \n");
        printf("2 - Inserir nova peça \n");
        printf("3 - Exibir fila\n");
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                dequeue(&queue);
                showQueue(&queue);
                break;

            case 2:
                enqueue(&queue);
                showQueue(&queue);
                break;

            case 3:
                showQueue(&queue);
                break;

            case 0:
                printf("\nSaindo...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (option != 0);

    return 0;
}