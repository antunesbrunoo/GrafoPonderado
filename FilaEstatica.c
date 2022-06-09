#include <stdio.h>
#include <stdlib.h>
#include "FilaEstatica.h"
#define MAX 100

Fila *criaFila(){
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f -> inicio = 0;
    f -> fim = 0;
    return f;
}

int Filavazia(Fila *f){
    if(f -> inicio == f -> fim){
        return 1;
    }
    return 0;
}

void push(Fila *f, int x){
    f -> v[f -> fim] = x;
    f -> fim = (f -> fim+1) % MAX;
}

int pop(Fila *f){
    int x = f -> v[f -> inicio];
    f -> inicio = (f -> inicio+1) % MAX;
    return x;
}
