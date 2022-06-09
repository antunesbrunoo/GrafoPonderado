#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "FilaEstatica.h"
#define inf 0x7fffffff


typedef struct Nodo {

    int info;
    int peso;
    struct Nodo *prox;

} nodo;

nodo *insere(nodo *lista, int x, int peso){

    nodo *novo=(nodo*)malloc(sizeof(nodo));
    novo->info=x;
    novo->peso=peso;
    novo->prox=lista;
    return novo;

}

void imprimevizinhos(nodo *lista){

    nodo *aux=lista;
    if (aux==NULL){printf("(nenhum)");}
    while (aux!=NULL){
        printf("%d ", aux->info);
        aux=aux->prox;
    }
    printf("\n");
}

int imprimepeso(nodo *lista, int B){

    nodo *aux=NULL;
    aux = lista;
    while(aux!=NULL){
        if((aux->info)==B){
            printf("%d\n", aux->peso);
            return aux->peso;
        }
        aux=aux->prox;
    }
    return inf;
}

void imprimematriz(nodo* lista[], int N){

    int i=0, j;

    for (j=0; j < N; j++){
            nodo *aux = NULL;
        for(i=1; i <= N; i++){
            aux = lista[j];
            if ( aux == NULL){
                printf("- ");
            }else{
                int z=inf;
                while (aux!= NULL){
                    if(aux->info == i){
                        z = aux->peso;
                    }
                    aux = aux->prox;
                }
                if(z==inf){
                    printf("- ");
                }else{
                    printf("%d ", z);
                }
            }
        }
        printf("\n");
    }

}

void libera(nodo *lista){
    if (lista == NULL) return;
    libera(lista -> prox);
    free(lista);
}

int popular(nodo *lista){

    nodo *aux=lista;
    int cont=0;
        while (aux!=NULL){
            cont++;
            aux=aux->prox;
        }
    return cont;
}

void buscaprofundidade2(nodo *lista[], int *v, int com, int *total, int peso){

    nodo *aux=NULL;
    aux=lista[com];
    if(aux==NULL){
        return;
    }
    else{
        v[com]=1;
        while(aux!=NULL){
            if(v[(aux->info-1)]==0){
                printf("%d ", aux->info);
                buscaprofundidade2(lista, v, (aux->info-1), total, peso);
            }
            peso = *total;
            peso += aux->peso;
            *total = peso;
            aux=aux->prox;
        }
        return;
    }
}

void buscaprofundidade(nodo *lista[], int *v, int N, int *total){

    int i=0, comp=0, peso=0;
    for(i=0;i<N;i++){
        v[i]=0;
    }
    for (i=0;i<N;i++){
            if(v[i]==0){
                printf("[");
                printf("%d ", i+1);
                buscaprofundidade2(lista, v, i, &total, 0);
                printf("]");
                peso = total;
                peso = peso/2;
                printf("peso total %d", peso);
                total=0;
                printf("\n");
                comp++;
            }
    }
    printf("o numero de componentes conexas %d\n", comp);


}

void removearesta(nodo *lista[], int A, int B){

    nodo *aux = NULL, *ant = NULL, *aux2 = NULL;
    aux = lista[A-1];
    do{
        if((aux->info) == B){
            if (ant == NULL){
                aux=aux->prox;
                free(lista[A-1]);
                lista[A-1]=aux;
            }
            else if ((aux -> prox) != NULL){
                ant->prox = aux->prox;
                aux=aux2;
            }
            else if((aux -> prox) == NULL){
                ant->prox = NULL;
                aux=aux2;
            }
        }
        else{
            ant = aux;
            aux = aux -> prox;
        }
    }while (aux != NULL);
    free(aux2);
}

void bfs(nodo *lista[],int N, int A, int B){

    Fila *F = criaFila();
    nodo *aux = NULL;
    int distancia[MAX] = {}, pai[MAX] = {}, v[MAX] = {}, x = 0, vazio, i=0, ord[MAX]={}, peso=0;
    distancia[A] = 0;
    pai[A] = inf;
    push(F, A);
    v[A] = 1;

    while(vazio!=1){
        x = pop(F);
        aux = lista[x-1];
        while(aux!=NULL){
            if(v[(aux->info)]==0){
                push(F, aux->info);
                v[aux->info] = 1;
                distancia[aux->info] = distancia[x]+1;
                pai[aux->info] = x;
            }
        aux=aux->prox;
        }
        vazio = Filavazia(F);
    }
    if (v[B]!=1){
            printf("sem caminho\n");
            return;
    }
    ord[0]=B;
    x=pai[B];
    peso += imprimepeso(lista[x-1], B);
    for(i=1; x!=inf; i++){
        ord[i]=x;
        peso += imprimepeso(lista[x-1], pai[x]);
        x = pai[x];
    }
    for(x=i-1; x>=0; x--){
        printf("%d ", ord[x]);
    }
    printf("\nnumero de arestas %d\n", i-1);
    printf("peso: %d\n", peso-inf);

}

int main()
{
    int A, B, peso, N, maior=0, result, vertpopu, *total=0;
    char func[10]={};

    setlocale(LC_ALL, "portuguese");

    scanf("%d", &N);
    nodo **lista=(nodo**)malloc(sizeof(nodo)*N);
    for(int i=0;i<N;i++){
        lista[i]=NULL;
    }

    do {
        scanf("%s", &func);
        if (strcmp(func, "+")==0){
            scanf("%d %d %d", &A, &B, &peso);
            lista[A-1]=insere(lista[A-1], B, peso);
            lista[B-1]=insere(lista[B-1], A, peso);
        }

        if(strcmp(func, "w")==0){
            scanf("%d %d", &A, &B);
            peso = imprimepeso(lista[A-1], B);
            if(peso==inf){
                    printf("aresta inexistente\n");
            }
            else {
                    printf("%d\n", peso);
            }
        }
        if(strcmp(func,"vizinhos")==0){
            scanf("%d", &A);
            imprimevizinhos(lista[A-1]);
        }
        if(strcmp(func,"popular")==0){
            for(int i=0; i<N;i++){
                result= popular(lista[i]);
                if (result>maior){
                    maior=result;
                    vertpopu=(i+1);
                }
            }
            printf("o mais popular e %d com grau %d\n", vertpopu, maior);
            maior=0;
        }
        if(strcmp(func,"matriz")==0){
            imprimematriz(lista, N);
        }
        if(strcmp(func, "dfs")==0){
            int v[N];
            buscaprofundidade(lista, v, N, total);
        }
        if(strcmp(func, "bfs")==0){
            scanf("%d %d", &A, &B);
            bfs(lista, N, A, B);
        }
        if(strcmp(func, "-")== 0){
            scanf("%d %d", &A, &B);
            removearesta(lista, A, B);
            removearesta(lista, B, A);
        }

    }while ((strcmp(func, "F")));

    for(int i=N-1;i>=0;i--){
        libera(lista[i]);
    }
    system("pause");
    return 0;
}
