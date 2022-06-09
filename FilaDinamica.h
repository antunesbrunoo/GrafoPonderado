#ifndef FILADINAMICA_H_INCLUDED
#define FILADINAMICA_H_INCLUDED
#define MAX 100

typedef struct Nodod{

    int info;
    struct NodoD *prox;

}nodod;

typedef struct{
    nodod *inicio;
    nodod *fim;
}Fila;

/*Fun��o para criar a fila*/
Fila *criaFila();

/*Verifica se a fila est� varia*/
int Filavazia(Fila *f);

/*Fun��o Insere elemento na fila*/
void push(Fila *f, int x);

/* Fun��o Remove elemento da fila*/
int pop(Fila *f);

#endif // FILADINAMICA_H_INCLUDED
