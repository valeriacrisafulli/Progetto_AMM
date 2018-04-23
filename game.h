//
// Created by valeria on 09/04/18.
//
#include "stack.h"
#ifndef CLUEDO_DJANNI_GAME_H
#define CLUEDO_DJANNI_GAME_H

#endif //CLUEDO_DJANNI_GAME_H

void saveGame(Stack* , Player * , int  , int );

_Bool compareCards(Card  , Card );

Stack makeHypothesis(Player*  , int );

void verifyHypotesis(Stack * , Player * , int  , int );


void changeRoom();

//ad inizio gioco chiede il nome di ogni giocatore
Player* getNames(Player* , int );

//attribuisce a ciascun giocatore un numero casuale che corrisponde alla posizione nell'array delle carte stanza.
Player* getRooms(Player*  , int );

//popola ciascuna tipologia di mazzo di carte con i valori degli array corrispondenti
void getDeck(Stack*  , Card* );


//distribuisce le carte fra i giocatori e quelle rimaste le mostra a tutti i giocatori
void distributeCards(Player*  , int  , Stack* );



void manageRounds(Player* , Stack , int , int);

//permette all'utente di scegliere quanti sono i giocatori e avvia la fase iniziale del gioco
void newGame(Player *giocatori , int *n_players , int *in_game , Stack *incognite);

//carica un file di salvataggio precedentemente generato
_Bool loadGame(Player *giocatori , int* n_players , int* in_game , Stack* incognite);

//schermata iniziale per scegliere se iniziare una nuova partita o caricare un salvataggio
void startGame();