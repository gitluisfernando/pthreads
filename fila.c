#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

void iniciaFila(Fila *q, size_t memTamanho)
{
    q->tamanhoDaFila = 0;
    q->memTamanho = memTamanho;
    q->head = q->tail = NULL;
}

int enviaParaFila(Fila *q, const void *data)
{
    node *newNode = (node *)malloc(sizeof(node));

    if (newNode == NULL)
    {
        return -1;
    }

    newNode->data = malloc(q->memTamanho);

    if (newNode->data == NULL)
    {
        free(newNode);
        return -1;
    }

    newNode->next = NULL;

    memcpy(newNode->data, data, q->memTamanho);

    if (q->tamanhoDaFila == 0)
    {
        q->head = q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }

    q->tamanhoDaFila++;
    return 0;
}

void tirarFila(Fila *q, void *data)
{
    if (q->tamanhoDaFila > 0)
    {
        node *temp = q->head;
        memcpy(data, temp->data, q->memTamanho);

        if (q->tamanhoDaFila > 1)
        {
            q->head = q->head->next;
        }
        else
        {
            q->head = NULL;
            q->tail = NULL;
        }

        q->tamanhoDaFila--;
        free(temp->data);
        free(temp);
    }
}

int tamanhoFila(Fila *q)
{
    return q->tamanhoDaFila;
}