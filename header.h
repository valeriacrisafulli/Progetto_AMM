//
// Created by valeria on 09/04/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define DIM_NAME 24
#define MIN_PLAYERS 3
#define MAX_PLAYERS 6
#define MIN_ROLL 1
#define MAX_ROLL 6
#define N_ROOMS 9
#define N_SUSPECTS 6
#define N_WEAPONS 6
#define ZERO 0
#define MILLE 1000
int turno;
int firstPlayer;

typedef enum{
    ARMA , SOSPETTO , STANZA
}CardType;

typedef struct {
    char cardName[DIM_NAME+1];
    CardType type;
}Card;

struct nodo{
    Card info;
    struct nodo *next;
};

typedef struct nodo Nodo;

typedef struct{
    Nodo* top;
    int count;
}Stack;

typedef struct{
    char playerName[DIM_NAME+1];
    int position;
    int flag;
    Stack hand;
    Stack outOfHand;
}Player;
/*
 * un intero rappresentante il giocatore corrente
un intero rappresentante il numero di turni
•
• un intero rappresentante il numero di giocatori
un blocco per giocatore, contenente:
• una stringa del nome giocatore (24 char)
• un intero rappresentante la stanza in cui si trova il giocatore
• un intero di flag che indica se il giocatore ha formulato l’ipotesi corretta (0: no, 1: si)
• un intero rappresentante il numero delle carte del giocatore
• un blocco per ogni carta giocatore, contenente:
• il tipo della carta (enum)
• una stringa della frase riportata sulla carta (24 char)
•
• un intero rappresentante le carte scoperte
un blocco per ogni carta scoperta, contenente:
• il tipo della carta (enum)
• una stringa della frase riportata sulla carta (24 char)
• un blocco per ogni carta incognita (3), contenente:
• il tipo della carta (enum)
• una stringa della frase riportata sulla carta (24 char)
 */