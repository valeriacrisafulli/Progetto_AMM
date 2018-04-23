//
// Created by valeria on 09/04/18.
//

#include "stack.h"

//generazione casuale di un numero con massimo e minimo inclusi
int randNumber(int MIN , int MAX){
    return MIN + rand()%(MAX-MIN+1); ;
}

Card copyCard(Card dest , Card orig){
    dest.type=orig.type;
    strcpy(dest.cardName , orig.cardName);
    return dest;
}

//scambio di valori fra due nodi
void swapElements(Nodo* dest , Nodo* orig){
    Nodo *aux=(Nodo*)malloc(sizeof(Nodo));
    aux->info=copyCard(aux->info , orig->info);
    orig->info=copyCard(orig->info , dest->info);
    dest->info=copyCard(dest->info , aux->info);
    free(aux);
}


//inizializza la pila: il puntatore a nodo vale NULL e l'intero count vale zero
Stack initializeStack(Stack* pila){
    pila->top=NULL;
    pila->count=0;
    return *pila;
}

//verifica se la pila è vuota
_Bool isEmpty(Stack* pila){
    if(pila->count==0){
        return true;
    }else{
        return false;
    }
}

//verifica se la pila è piena
_Bool isFull(Stack* pila , int dim){
    if(pila->count==dim){
        return true;
    }else{
        return false;
    }
}

//inserisce nuovi elementi in cima alla pila
void pushStack (Stack* pila , Card val , int dim){
    Nodo* new_node=NULL;
    if(isFull(pila , dim)){
        printf("\nErrore overflow");
    }else{
        new_node=(Nodo*)malloc(sizeof(Nodo));
        if(new_node==NULL){
            exit(-1);
        }
        new_node->info=copyCard(new_node->info , val);
        new_node->next=NULL;
        if(isEmpty(pila)){
            pila->top=new_node;
        }else{
            new_node->next=pila->top;
            pila->top=new_node;
        }
    }
    pila->count++;
}

//elimina la testa dalla pila e restituisce il valore eliminato
Card popStack(Stack* pila){
    Card val;
    Nodo* tmp=(Nodo*)malloc(sizeof(Nodo));
    if(isEmpty(pila)){
        printf("Errore underflow");
    }else{
        tmp=pila->top;
        val=copyCard(val , tmp->info);
        pila->top=pila->top->next;
        pila->count--;
        free(tmp);
    }
    return val;
}




//fonde due pile insieme e salva la pila nuova nel primo elemento chiamato
void mergeStack(Stack* new_pila , Stack* pila) {
    Card aux;
    int dim=new_pila->count+pila->count;
    while(pila->top!=NULL){
        aux=popStack(pila);
        pushStack(new_pila , aux , dim);
    }
}

//mischia gli elementi all'interno della pila
void shuffleStack(Stack* pila){
    int i , num;
    Nodo* tmp=(Nodo*)malloc(sizeof(Nodo));
    for(i=0 ; i<MILLE; i++){
        num=randNumber(ZERO+1 , pila->count);
        tmp=pila->top;
        while(tmp->next!= NULL && num!=0){
            tmp=tmp->next;
            num--;
        }
        swapElements(pila->top , tmp);
    }
}

//Elimina il nodo in testa alla seconda pila per salvare il valore in esso contenuto nella testa della prima pila
void createSolution(Stack *incognite, Stack *pila) {
    Card aux;
    aux=popStack(pila);
    pushStack(incognite , aux , incognite->count+1);
}

