//
// Created by valeria on 09/04/18.
//

#include "print.h"

//stampa una stinga per ogni tipologia di carta
void printTypeCard(CardType num){
    switch (num){
        case ARMA:
            printf("Arma");
            break;
        case SOSPETTO:
            printf("Sospetto");
            break;
        case STANZA:
            printf("Stanza");
            break;
    }
}

//stampa il nome della carta
void printCard(Card carta){
    printTypeCard(carta.type);
    printf(" - %s" , carta.cardName);
}


//stampa i valori contenuti nella pila
void printStack(Stack pila){
    int i=0;
    Nodo *tmp = (Nodo *) malloc(sizeof(Nodo));
    tmp = pila.top;
    while(tmp!=NULL){
        printf("\n%d - " , i+1);
        printCard(tmp->info);
        tmp=tmp->next;
        i++;
    }
}


void printHand(Player giocatori){

    printf("\n\n[***VISIBILE SOLO A %s***]" , giocatori.playerName);
    printf("\nCarte in mano:");
    printStack(giocatori.hand);
    if(giocatori.outOfHand.count!=0){
        printf("\n\nCarte a terra:");
        printStack(giocatori.outOfHand);
    }
    printf("\n\n[***VISIBILE SOLO A %s***]" , giocatori.playerName);

}