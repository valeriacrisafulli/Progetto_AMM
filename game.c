//
// Created by valeria on 09/04/18.
//
#include "game.h"

void saveGame(Stack* incognita , Player *giocatori , int n_players , int in_game){
        int i, j;
        Nodo* aux = NULL;
        FILE *my_file;
        Card eachCard;
        char* nomeFile = malloc(DIM_NAME+1);
        char* estensioneFile = ".sav";

        printf("\nNome del file per il salvataggio? \n");
        scanf("%s", nomeFile);
        strcat(nomeFile, estensioneFile);
        my_file = fopen(nomeFile, "w+b");
        printf("Hai salvato la partita in: %s\n" , nomeFile);
        //un intero rappresentante il giocatore corrente
        fwrite(&in_game , sizeof(int) , 1 , my_file);
        //un intero rappresentante il numero di turni
        fwrite(&turno , sizeof(int) , 1 , my_file);
        //un intero rappresentante il numero di giocatori
        fwrite(&n_players , sizeof(int) , 1 , my_file);



        ///BLOCCO GIOCATORE
/*
 *  • una stringa del nome giocatore (24 char)
    • un intero rappresentante la stanza in cui si trova il giocatore
    • un intero di flag che indica se il giocatore ha formulato l’ipotesi corretta (0: no, 1: si)
    • un intero rappresentante il numero delle carte del giocatore
*/
    for (i=0; i<n_players; i++)
        {
            fwrite(giocatori[i].playerName, sizeof(char)*(DIM_NAME+1), 1, my_file);

            fwrite(&giocatori[i].position, sizeof(int), 1, my_file);

            fwrite(&giocatori[i].flag, sizeof(int), 1, my_file);

            fwrite(&giocatori[i].hand.count, sizeof(int), 1, my_file);

                ///Blocco carte del giocatore
            /*
             *• un blocco per ogni carta giocatore, contenente:
             * • il tipo della carta (enum)
             * • una stringa della frase riportata sulla carta (24 char)
             * • un intero rappresentante le carte scoperte
            */
                aux=(Nodo*)malloc(sizeof(Nodo));
                aux=giocatori[i].hand.top;
                for (j=0; j<(giocatori[i].hand.count); j++)
                {
                    eachCard=copyCard(eachCard , aux->info);
                    fwrite(&eachCard.type, sizeof(CardType), 1, my_file);
                    fwrite(&eachCard.cardName, sizeof(char)*(DIM_NAME+1), 1, my_file);
                    aux=aux->next;
                }
            /*
             * un blocco per ogni carta scoperta, contenente:
             * • il tipo della carta (enum)
             * • una stringa della frase riportata sulla carta (24 char)
             */

                if(giocatori[i].outOfHand.count!=0){
                    aux=giocatori[i].outOfHand.top;
                    for(j=0 ; j<(giocatori[i].outOfHand.count) ; j++){
                        eachCard=copyCard(eachCard , aux->info);
                        fwrite(&eachCard.type, sizeof(CardType), 1, my_file);
                        fwrite(&eachCard.cardName, sizeof(char)*(DIM_NAME+1), 1, my_file);
                        aux=aux->next;
                    }
                }

        }
        //BLOCCO INCOGNITE
        /** • un blocco per ogni carta incognita (3), contenente:
        * • il tipo della carta (enum)
        * • una stringa della frase riportata sulla carta (24 char)
        */
        aux=incognita->top;
        for(i=0 ; i<incognita->count ; i++){
            eachCard=copyCard(eachCard , aux->info);
            fwrite(&eachCard.type , sizeof(CardType) , 1 , my_file);
            fwrite(&eachCard.cardName , sizeof(char)*(DIM_NAME+1), 1 , my_file);
            aux=aux->next;
        }
    fclose(my_file);
}


Stack makeHypothesis(Player* giocatori , int in_game){
    Card rooms[N_ROOMS]={{"Laboratorio T" , STANZA} , {"Bagno", STANZA} , {"Simaz", STANZA} ,
                         {"Parcheggio", STANZA} , {"Laboratorio M", STANZA} , {"BatCaverna", STANZA} ,
                         {"Entrata", STANZA} , {"Giardino", STANZA} , {"Aula Costa", STANZA}};
    Card weapons[N_WEAPONS]={{"Cavo di Rete" , ARMA} , {"Sparacoriandoli" , ARMA} , {"Calcinaccio" , ARMA} ,
                             {"Tastiera USB" , ARMA} , {"Fumo Caldaia" , ARMA} , {"Floppy Disk 3.5" , ARMA}};
    Card suspects[N_SUSPECTS]={{"Alan Turing" , SOSPETTO} , {"G.M. Hopper" , SOSPETTO} , {"Edsger Dijkstra" , SOSPETTO} ,
                               {"G.F. Voronoj" , SOSPETTO} , {"J.V. Neumann" , SOSPETTO} , {"M. Hamilton" , SOSPETTO}};
    Stack ipotesi;
    int val;
    Nodo *tmp=(Nodo*)malloc(sizeof(Nodo));
    initializeStack(&ipotesi);
    tmp->info=rooms[giocatori[in_game].position];
    pushStack(&ipotesi , tmp->info , ipotesi.count+1);
    printf("\nScegli l'arma:\n[0] Cavo di Rete\n[1] Sparacoriandoli\n[2] Calcinaccio\n[3] Tastiera USB\n[4] Fumo Caldaia\n[5] Floppy Disk 3.5");
    scanf("%d" , &val);
    tmp->info=weapons[val];
    pushStack(&ipotesi , tmp->info , ipotesi.count+1);
    printf("\nScegli il sospetto:\n[0] Alan Turing\n[1] G.M. Hopper\n[2] Edsger Dijkstra\n[3] G.F. Voronoj\n[4] J.V. Neumann\n[5] M. Hamilton");
    scanf("%d" , &val);
    tmp->info=suspects[val];
    pushStack(&ipotesi , tmp->info , ipotesi.count+1);
    printf("\n\nIpotesi formulata:");
    printStack(ipotesi);
    printf("\n");
    return ipotesi;
}


_Bool compareCards(Card carta1 , Card carta2){
    int cmp;
    printf("\nCarta 1: %s" , carta1.cardName);
    printf("\tCarta 2: %s" , carta2.cardName);
    if(carta1.type==carta2.type){
        cmp=strcmp(carta1.cardName , carta2.cardName);
        if(cmp==0){
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}



void verifyHypotesis(Stack *ipotesi , Player *giocatori , int in_game , int n_players){

}

void changeRoom(){
    printf("\nTi sei spostato in un'altra stanza");
}

Player *getNames(Player *giocatori , int n_players) {
    int i;
    for(i=0 ; i<n_players ; i++){
        printf("\n%d - Nome giocatore: " , i+1);
        getchar();
        scanf("%[^\n]s" , giocatori[i].playerName);
    }
    return giocatori;
}


Player* getRooms(Player* giocatori , int n_players){
    int i , num;
    for(i=0 ; i<n_players ; i++){
        num=randNumber(ZERO , N_ROOMS-1);
        giocatori->position=num;
    }
    return giocatori;
}

void getDeck(Stack* pila , Card* array){
    int i;
    if(array[ZERO].type==ARMA || array[ZERO].type==SOSPETTO){
        for(i=0 ; i<N_WEAPONS ; i++) {
            pushStack(pila, array[i] , N_WEAPONS);
        }
    }else{
        for(i=0 ; i<N_ROOMS ; i++){
            pushStack(pila , array[i] , N_ROOMS);
        }
    }
}

//distribuisce le carte fra i giocatori e quelle rimaste le mostra a tutti i giocatori
void distributeCards(Player *giocatori, int n_players, Stack *mazzo) {
    int div , mod , i , j;
    Card aux;
    div=mazzo->count/n_players;
    mod=mazzo->count%n_players;
    for(i=0 ; i<n_players ; i++){
        initializeStack(&giocatori[i].hand);
        initializeStack(&giocatori[i].outOfHand);
    }
    for(i=0 ; i<div ; i++){
        for(j=0 ; j<n_players ; j++) {
            aux=popStack(mazzo);
            pushStack(&giocatori[j].hand , aux , div);
        }
    }
    if(mod!=0){
        for(i=0 ; i<mod ; i++){
            aux=popStack(mazzo);
            for(j=0 ; j<n_players ; j++){
                pushStack(&giocatori[i].outOfHand , aux , mod);
            }
        }
    }
}


void manageRounds(Player* giocatori , Stack incognite , int in_game , int n_players){
    Card rooms[N_ROOMS]={{"Laboratorio T" , STANZA} , {"Bagno", STANZA} , {"Simaz", STANZA} ,
                         {"Parcheggio", STANZA} , {"Laboratorio M", STANZA} , {"BatCaverna", STANZA} ,
                         {"Entrata", STANZA} , {"Giardino", STANZA} , {"Aula Costa", STANZA}};
    int i , j , k , choice1 , choice2;
    Stack ipotesi;
        i=firstPlayer;
        turno++;
        printf("\n\nTurno N. %d" , turno);

        for(j=0 ; j<n_players ;j++){
            in_game=i;
            if(i<n_players){

                printf("\n%s si trova nella stanza %s" , giocatori[i].playerName , rooms[giocatori[i].position].cardName);
                do{
                    printf("\nVuoi salvare?\n[0]Sì\t[1]No");
                    scanf("%d" , &choice1);
                    if(choice1<0 || choice1>1){
                        printf("\nScelta non prevista. Riprova");
                    }
                }while(choice1<0 || choice1>1);
                    if(choice1==0){
                        saveGame(&incognite , giocatori , n_players , i);
                        printHand(giocatori[i]);
                        do{
                            printf("\n[0] Formula un'ipotesi\n[1] Spostati in un'altra stanza\n");
                            scanf("%d" , &choice2);
                            if(choice2<0 || choice2>2){
                                printf("\nScelta non prevista. Riprova");
                            }
                        }while(choice2<0 || choice2>2);
                        if(choice2==0){
                            initializeStack(&ipotesi);
                            ipotesi=makeHypothesis(giocatori , in_game);
                        }else if(choice2==1){
                            changeRoom();
                        }
                        i++;
                    }else{
                        do{
                            printHand(giocatori[i]);
                            printf("\n[0] Formula un'ipotesi\n[1] Spostati in un'altra stanza");
                            scanf("%d" , &choice2);
                            if(choice2<0 || choice2>1){
                                printf("\nScelta non prevista. Riprova");
                            }
                        }while(choice2<0 || choice2>1);
                        if(choice2==0){
                            initializeStack(&ipotesi);
                            ipotesi=makeHypothesis(giocatori , in_game);
                            verifyHypotesis(&ipotesi , giocatori , in_game , n_players);
                        }else if(choice2==1){
                            changeRoom();
                        }
                        i++;
                    }
            }else{
                i=0;
                j--;
            }
        }
}

//permette all'utente di scegliere quanti sono i giocatori e avvia la fase iniziale del gioco
void newGame(Player *giocatori , int *n_players , int *in_game , Stack *incognite){
    turno=0;
    Card rooms[N_ROOMS]={{"Laboratorio T" , STANZA} , {"Bagno", STANZA} , {"Simaz", STANZA} ,
                         {"Parcheggio", STANZA} , {"Laboratorio M", STANZA} , {"BatCaverna", STANZA} ,
                         {"Entrata", STANZA} , {"Giardino", STANZA} , {"Aula Costa", STANZA}};
    Card weapons[N_WEAPONS]={{"Cavo di Rete" , ARMA} , {"Sparacoriandoli" , ARMA} , {"Calcinaccio" , ARMA} ,
                {"Tastiera USB" , ARMA} , {"Fumo Caldaia" , ARMA} , {"Floppy Disk 3.5" , ARMA}};
    Card suspects[N_SUSPECTS]={{"Alan Turing" , SOSPETTO} , {"G.M. Hopper" , SOSPETTO} , {"Edsger Dijkstra" , SOSPETTO} ,
                             {"G.F. Voronoj" , SOSPETTO} , {"J.V. Neumann" , SOSPETTO} , {"M. Hamilton" , SOSPETTO}};
    Stack stanze;
    Stack armi;
    Stack sospetti;
    Stack mazzo;


    do{
        printf("\nScegli il numero di giocatori (da 3 a 6):\n");
        scanf("%d" , n_players);
        if(*n_players<MIN_PLAYERS || *n_players>MAX_PLAYERS){
            printf("\nErrore! Scelta non prevista. Riprova.");
        }
    }while(*n_players<MIN_PLAYERS || *n_players>MAX_PLAYERS);

    giocatori=(Player*)malloc(*n_players*sizeof(Player));
    giocatori=getNames(giocatori , *n_players);
    giocatori=getRooms(giocatori , *n_players);

    stanze=initializeStack(&stanze);
    armi=initializeStack(&armi);
    sospetti=initializeStack(&sospetti);
    initializeStack(incognite);
//    printf("\n\nPrima:");
    getDeck(&stanze , rooms);
//    printStack(stanze);
//    printf("\nDopo:");
    shuffleStack(&stanze);
//    printStack(stanze);
//    printf("\n\nPrima:");
    getDeck(&armi , weapons);
//    printStack(armi);
//    printf("\nDopo:");
    shuffleStack(&armi);
//    printStack(armi);
//    printf("\n\nPrima:");
    getDeck(&sospetti , suspects);
//    printStack(sospetti);
//    printf("\nDopo:");
    shuffleStack(&sospetti);
//    printStack(sospetti);
    createSolution(incognite , &stanze);
    createSolution(incognite , &armi);
    createSolution(incognite, &sospetti);
/*
    printf("\nSoluzione:");
    printStack(incognite);
*/
    initializeStack(&mazzo);
//  printf("\n\n");

    mergeStack(&mazzo , &armi);
    mergeStack(&mazzo , &stanze);
    mergeStack(&mazzo , &sospetti);
/*    printStack(mazzo);
    printf("\n\n");
*/
    shuffleStack(&mazzo);
/*
 * printStack(mazzo);
*/
    distributeCards(giocatori , *n_players , &mazzo);

    firstPlayer=randNumber(ZERO , MAX_PLAYERS-1);
    manageRounds(giocatori , *incognite , *in_game , *n_players);

}


_Bool loadGame(Player *giocatori , int* n_players , int* in_game , Stack* incognite) {
    int i, j;
    char fileName[DIM_NAME+1];
    char estensione[DIM_NAME+1]=".sav";
    Card eachCard;
    FILE *savedGame = NULL;
    int dimLista = 0;
    printf("\nIndicare il nome del file di salvataggio: ");
    scanf("%s" , fileName);
    getchar();
    strcat(fileName , estensione);
    savedGame = fopen(fileName, "r+b");
    if (savedGame != NULL) {
        printf("\nCaricamento salvataggio");
        // un intero rappresentante il giocatore corrente
        fread(in_game, sizeof(int), 1, savedGame);
        printf("\nGiocatore in gioco: %d" , *in_game);
        //un intero rappresentante il numero di turni
        fread(&turno, sizeof(int), 1, savedGame);
        printf("\nNumero del turno: %d " , turno);
        //un intero rappresentante il numero di giocatori
        fread(n_players, sizeof(int), 1, savedGame);
        printf("\nNumero di giocatori: %d" , *n_players);
        printf("\n");
        /*un blocco per giocatore, contenente:
        • una stringa del nome giocatore (24 char)
        • un intero rappresentante la stanza in cui si trova il giocatore
        • un intero di flag che indica se il giocatore ha formulato l’ipotesi corretta (0: no, 1: si)
        • un intero rappresentante il numero delle carte del giocatore
        • un blocco per ogni carta giocatore, contenente:
        • il tipo della carta (enum)
        • una stringa della frase riportata sulla carta (24 char)
        */
        for (i = 0; i < *n_players; i++) {
            fread(&giocatori[i], sizeof(char), DIM_NAME , savedGame);
            printf("\nNome giocatore: %s" , giocatori[i].playerName );
            fread(&giocatori[i].position, sizeof(int), 2, savedGame);
            printf("\nPosizione: %d" , giocatori[i].position);
            fread(&giocatori[i].flag, sizeof(int), 2, savedGame);
            printf("\nFlag %d" , giocatori[i].flag);
            initializeStack(&giocatori[i].hand);
            fread(&dimLista, sizeof(int), 2, savedGame);
            ///BLOCCO CARTE IN MANO
            for (j = 0; j < dimLista; j++) {
                fread(&eachCard.type, sizeof(CardType), 1, savedGame);
                fread(&eachCard.cardName, sizeof(char) , DIM_NAME, savedGame);
                pushStack(&giocatori[i].hand, eachCard, giocatori[i].hand.count + 1);
            }

            //BLOCCO CARTE SCOPERTE
            /*
             * • un intero rappresentante le carte scoperte
             * un blocco per ogni carta scoperta, contenente:
             * • il tipo della carta (enum)
             * • una stringa della frase riportata sulla carta (24 char)
             */
            fread(&dimLista, sizeof(int), 1, savedGame);
            initializeStack(&giocatori[i].outOfHand);
            if (dimLista != 0) {
                for (j = 0; j < dimLista; j++) {
                    fread(&eachCard.type, sizeof(CardType), 1, savedGame);
                    fread(&eachCard.cardName, sizeof(char) * (DIM_NAME + 1), 1, savedGame);
                    pushStack(&giocatori[i].outOfHand, eachCard, giocatori[i].outOfHand.count + 1);
                }
            }

        }
        //BLOCCO CARTE INCOGNITA
        /*
         * • un blocco per ogni carta incognita (3), contenente:
         * • il tipo della carta (enum)
         * • una stringa della frase riportata sulla carta (24 char)
         */
        fread(&dimLista, sizeof(int), 1, savedGame);
        for (i = 0; i < dimLista; i++) {
            fread(&eachCard.type, sizeof(CardType), 1, savedGame);
            fread(&eachCard.cardName, sizeof(char) * (DIM_NAME + 1), 1, savedGame);
            pushStack(incognite, eachCard, incognite->count + 1);
        }

    fclose(savedGame);
        return true;
    }else{
        printf("\nCaricamento non riuscito");
        return false;
    }

}

//schermata iniziale per scegliere se iniziare una nuova partita o caricare un salvataggio
void startGame(){
    int choice;
    char fileName[DIM_NAME+1];
    Player *giocatori;
    int n_players, in_game;
    Stack incognite;
    _Bool flag=false;
    printf("\t\tCluedo\n\tDjanni Edition\n");
    do{
        printf("\nVuoi iniziare una nuova partita [0] oppure caricare un salvataggio? [1]");
        scanf("%d" , &choice);
        if(choice<0 || choice>1){
            printf("\nErrore! Scelta non prevista\n");
        }
    }while(choice<0 || choice>1);
        if(choice==0){
            newGame(giocatori , &n_players , &in_game , &incognite);
        }else if(choice==1){
            do{
                flag=loadGame(giocatori , &n_players , &in_game , &incognite);
                if(flag==false){
                    printf("\nForse hai sbagliato il nome del file. Ritenta");
                }
            }while(flag==false);
        }

}


