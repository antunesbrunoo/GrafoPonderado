#include <stdio.h>
#include <stdlib.h>
#include "FilaDinamica.h"
#define MAX 100

Fila *criaFila(){
    Fila *f =(Fila*) malloc (sizeof(Fila));
    f -> inicio = NULL;
    f -> fim = NULL;
    return f;
}

int Filavazia(Fila *f){
    if(f -> inicio == NULL){
        return 1;
    }
    return 0;
}
void push(Fila *f, int x){
    nodod *novo = (nodod*) malloc (sizeof(nodod));
    novo -> info = x;
    if( f-> fim != NULL){
        f -> fim -> prox = novo;
    }
    f -> fim = novo;
    novo -> prox = NULL;
    if (f -> inicio == NULL){
        f -> inicio = novo;
    }
}

int pop(Fila *f){

    int x = f -> inicio -> info;
    nodod *prox = f-> inicio -> prox;
    if(f->fim == f->inicio)
        f->fim=NULL;
    free(f -> inicio);
    f->inicio = prox;
    if(f-> inicio == NULL){
        f-> fim = NULL;
    }
    return x;
}
