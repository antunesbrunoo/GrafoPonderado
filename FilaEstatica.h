#ifndef FILAESTATICA_H_INCLUDED
#define FILAESTATICA_H_INCLUDED
#define MAX 100

typedef struct{
    int v[MAX+1];
    int inicio, fim;
}Fila;

/*Função para criar a Fila*/
Fila *criaFila();

/*Função que verifica se a fila está vazia*/
int Filavazia(Fila *f);

/*Insere um elemento na fila*/
void push(Fila *f, int x);

/*Remove elemento da fila*/
int pop(Fila *f);

#endif // FILAESTATICA_H_INCLUDED
