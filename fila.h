#ifndef FILA_H_INCLUDED
#define FILA_H_INCLUDED

//Cria uma lista vinculada
typedef struct Node
{
  void *data;
  struct Node *next;
} node;

//Cria a estrutura da fila
typedef struct
{
  int tamanhoDaFila;
  size_t memTamanho;
  node *head;
  node *tail;
} Fila;

void iniciaFila(Fila *q, size_t memTamanho);
int enviaParaFila(Fila *, const void *);
void tirarFila(Fila *, void *);
int tamanhoFila(Fila *);

#endif /* FILA_H_INCLUDED */