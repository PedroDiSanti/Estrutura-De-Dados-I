#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
    char item;
    struct no *prox;
};

typedef struct{
    struct no *com;
}Lista;

void iniciaLista(Lista *l){
    l -> com = NULL;
}

void mostraLista(Lista *l){
    struct no *aux;
    aux = l -> com;
    printf("[");
    while(aux){
        if(aux -> prox == NULL){
            printf("%c ]",aux ->item);
        }else{
            printf("%c , ",aux ->item);
        }
        aux = aux -> prox;
    }    
}

void insereLista(Lista *l,char v){
    struct no *aux,*ant,*p;
    ant = NULL;
    aux = l -> com;
    while(aux != NULL && aux -> item < v){
        ant = aux;
        aux = aux -> prox;
    }
    p = (struct no*)malloc(sizeof(struct no));
    if(p == NULL){
        printf("Memoria Cheia!");
        exit(0);
    }
    p ->item = v;
    if(ant == NULL){
        l -> com = p;
        p -> prox = aux;
    }else{
        ant -> prox = p;
        p -> prox = aux;        
    }    
}

void removerLista(Lista *l,char v){
    struct no *aux,*ant,*p;
    ant = NULL;
    aux = l -> com;
    while(aux != NULL && aux -> item != v){
        ant = aux;
        aux = aux -> prox;
    }
    if(aux -> item == v && ant == NULL){
        free(aux);
        l -> com = ant;
    }else if(aux -> item == v){
        ant -> prox = aux -> prox;
        free(aux);
    }else{
        printf("Elemento não encontrado!");
    }     
}

void destruirLista(Lista *l){
    struct no *aux;
    while(l -> com){
        aux = l -> com;
        l -> com = l -> com -> prox;
        free(aux);
    }
}

int main(int argc, char** argv) {
    
    Lista l;
    iniciaLista(&l);
    insereLista(&l,'a');
    insereLista(&l,'f');
    insereLista(&l,'b');
    insereLista(&l,'c');
    removerLista(&l,'b');
    mostraLista(&l);
    destruirLista(&l);
    
    return (EXIT_SUCCESS);
}