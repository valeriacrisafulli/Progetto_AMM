//
// Created by valeria on 09/04/18.
//
#include "print.h"

//generazione casuale di un numero con massimo e minimo inclusi
int randNumber(int MIN , int MAX);

Card copyCard(Card dest , Card orig);

//scambio di valori fra due nodi
void swapElements(Nodo*  , Nodo* );

//inizializza la pila: il puntatore a nodo vale NULL e l'intero count vale zero
Stack initializeStack(Stack* );

//verifica se la pila è vuota
_Bool isEmpty(Stack*);

//verifica se la pila è piena
_Bool isFull(Stack* , int);

//inserisce nuovi elementi in cima alla pila
void pushStack(Stack* , Card , int);

//elimina la testa dalla pila e restituisce il valore eliminato
Card popStack(Stack*);

//cerca un elemento nella pila e restituisce un booleano
int searchNode(Stack , Card );

//fonde due pile insieme e salva la pila nuova nel primo elemento chiamato
void mergeStack(Stack*  , Stack* );

//mischia gli elementi all'interno della pila
void shuffleStack(Stack* );

//Elimina il nodo in testa alla seconda pila per salvare il valore in esso contenuto nella prima pila
void createSolution(Stack* , Stack* );



//
