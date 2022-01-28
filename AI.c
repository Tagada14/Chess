#include <stdio.h>
#include <limits.h>
#include "chess.h"



double knightWages[8][8] = {
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0},
    {-4.0, -2.0,  0.0,  0.0,  0.0,  0.0, -2.0, -4.0},
    {-3.0,  0.0,  1.0,  1.5,  1.5,  1.0,  0.0, -3.0},
    {-3.0,  0.5,  1.5,  2.0,  2.0,  1.5,  0.5, -3.0},
    {-3.0,  0.0,  1.5,  2.0,  2.0,  1.5,  0.0, -3.0},
    {-3.0,  0.5,  1.0,  1.5,  1.5,  1.0,  0.5, -3.0},
    {-4.0, -2.0,  0.0,  0.5,  0.5,  0.0, -2.0, -4.0},
    {-5.0, -4.0, -3.0, -3.0, -3.0, -3.0, -4.0, -5.0}
};

double queenWages[8][8] = {
    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0},
    {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-1.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    {-0.5,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    { 0.0,  0.0,  0.5,  0.5,  0.5,  0.5,  0.0, -0.5},
    {-1.0,  0.5,  0.5,  0.5,  0.5,  0.5,  0.0, -1.0},
    {-1.0,  0.0,  0.5,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-2.0, -1.0, -1.0, -0.5, -0.5, -1.0, -1.0, -2.0}
};

double bishopWhiteWages[8][8] = {
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
    {-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
    {-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
    {-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
    {-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0}
};
double bishopBlackWages[8][8] = {
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
    {-1.0,  0.5,  0.0,  0.0,  0.0,  0.0,  0.5, -1.0},
    {-1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0, -1.0},
    {-1.0,  0.0,  1.0,  1.0,  1.0,  1.0,  0.0, -1.0},
    {-1.0,  0.5,  0.5,  1.0,  1.0,  0.5,  0.5, -1.0},
    {-1.0,  0.0,  0.5,  1.0,  1.0,  0.5,  0.0, -1.0},
    {-1.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -1.0},
    {-2.0, -1.0, -1.0, -1.0, -1.0, -1.0, -1.0, -2.0},
};

double rookWhiteWages[8][8] = {
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    { 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0}
};

double rookBlackWages[8][8] = {
    { 0.0,  0.0,  0.0,  0.5,  0.5,  0.0,  0.0,  0.0},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    {-0.5,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -0.5},
    { 0.5,  1.0,  1.0,  1.0,  1.0,  1.0,  1.0,  0.5},
    { 0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};

double kingWhiteWages[8][8] = {

    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    { 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
    { 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0}
};

double kingBlackWages[8][8] = {
    { 2.0,  3.0,  1.0,  0.0,  0.0,  1.0,  3.0,  2.0},
    { 2.0,  2.0,  0.0,  0.0,  0.0,  0.0,  2.0,  2.0},
    {-1.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -1.0},
    {-2.0, -3.0, -3.0, -4.0, -4.0, -3.0, -3.0, -2.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0},
    {-3.0, -4.0, -4.0, -5.0, -5.0, -4.0, -4.0, -3.0}
};


double pawnWhiteWages[8][8] = {
        {7.0,  7.0,  7.0,  7.0,  7.0,  7.0,  7.0,  7.0},
        {5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
        {1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
        {0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
        {0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
        {0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
        {0.5,  1.0, 1.0,  -3.0, -3.0,  1.0,  1.0,  0.5},
        {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};
double pawnBlackWages[8][8] = {
        {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
        {0.5,  1.0, 1.0,  -3.0, -3.0,  1.0,  1.0,  0.5},
        {0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
        {0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
        {0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
        {1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
        {5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
        {7.0,  7.0,  7.0,  7.0,  7.0,  7.0,  7.0,  7.0}
};
struct tile{
    int wages;
    char tileName;
} tableTileWages[] = {
    {-10, 'P'}, {-20, 'S'}, {-30, 'B'}, {-50, 'R'}, {-90, 'Q'}, {-300, 'K'},
    {10, 'p'}, {20, 's'}, {30, 'b'}, {50, 'r'}, {90, 'q'}, {300, 'k'}
};

int evaluateBoard(char board[], int n){
    int res = 0;
    for(int i = 0; i < n; i++){
        double temp = 0;
        if (board[i] != 'E'){
            // here we can use later union or simple ENUM
            for(int j = 0; j < 12; j++){
                if (board[i] == tableTileWages[j].tileName){
                    temp = (double)tableTileWages[j].wages;
                    if(board[i] == 'K') temp += kingWhiteWages[i/8][i%8];
                    else if(board[i] == 'k') temp += kingBlackWages[i/8][i%8];
                    else if(board[i] == 'Q') temp += queenWages[i/8][i%8];
                    else if(board[i] == 'q') temp += queenWages[i/8][i%8];
                    else if(board[i] == 'R') temp += rookWhiteWages[i/8][i%8];
                    else if(board[i] == 'r') temp += rookBlackWages[i/8][i%8];
                    else if(board[i] == 'B') temp += bishopWhiteWages[i/8][i%8];
                    else if(board[i] == 'b') temp += bishopBlackWages[i/8][i%8];
                    else if(board[i] == 'S') temp += knightWages[i/8][i%8];
                    else if(board[i] == 's') temp += knightWages[i/8][i%8];
                    else if(board[i] == 'P') temp += pawnWhiteWages[i/8][i%8];
                    else if(board[i] == 'p') temp += pawnBlackWages[i/8][i%8];
                    res += temp;
                    break;
                }
            }
        }
    }
    return res;
}


int minmax(int deepth, char board[], int fromTile, int whereTile, int alfa, int beta){

    if(deepth == 2)
        return evaluateBoard(board, 64);

    char tempFigurePlacement[64];
    int tempLegalMoveTab[64] = {0};
    int tempTransitionalLegalMoveTab[484] = {0};
    for(int i = 0; i < 64; i++) tempFigurePlacement[i] = board[i];

    if(deepth != 0){
        setLegalMoves(fromTile, tempLegalMoveTab, tempTransitionalLegalMoveTab, tempFigurePlacement);
        checkMoveCheckLegality(fromTile, tempLegalMoveTab, tempFigurePlacement);
        moveFigureLogic(fromTile,whereTile,tempLegalMoveTab,tempFigurePlacement);
    }

    int indexWhere = 0;
    int indexFrom = 0;
    if(deepth%2 == 0){
        int best = INT_MIN;
        if(deepth != 0)
            roundCounter++;
        for(int i = 0; i < 64; i++){
            if(getFigureSide(i, tempFigurePlacement) == 'B'){
                for(int i = 0; i < 484; i++) tempTransitionalLegalMoveTab[i] = 0;
                for(int i = 0; i < 64; i++) tempLegalMoveTab[i] = 0;
                setLegalMoves(i, tempLegalMoveTab, tempTransitionalLegalMoveTab, tempFigurePlacement);
                printf("Before\n");
                for(int i = 0; i < 64; i++){
                     printf("%d ", tempLegalMoveTab[i]);
                     if((i+1)%8 == 0)
                        putchar('\n');
                }
                        putchar('\n');
                checkMoveCheckLegality(i, tempLegalMoveTab, tempFigurePlacement);
                printf("After\n");
                for(int i = 0; i < 64; i++){
                     printf("%d ", tempLegalMoveTab[i]);
                     if((i+1)%8 == 0)
                        putchar('\n');
                }
                        putchar('\n');
                for(int j = 0; j < 64; j++){
                    if(tempLegalMoveTab[j] != 0){
                            int val = minmax(deepth+1, tempFigurePlacement, i, j, alfa, beta);
                            if(val > best){
                                best = val;
                                indexWhere = j;
                                indexFrom = i;
                            }
                            if(best>alfa)
                                alfa = best;

                            if(beta <= alfa)
                                    break;
                    }
                }
            }
        }
            if(deepth != 0){
                roundCounter--;
                return best;
            }
        }else{
            int best = INT_MAX;
            roundCounter++;
            for(int i = 0; i < 64; i++){
                if(getFigureSide(i, tempFigurePlacement) == 'W'){
                    for(int i = 0; i < 484; i++) tempTransitionalLegalMoveTab[i] = 0;
                    for(int i = 0; i < 64; i++) tempLegalMoveTab[i] = 0;
                    setLegalMoves(i, tempLegalMoveTab, tempTransitionalLegalMoveTab, tempFigurePlacement);
                    checkMoveCheckLegality(i, tempLegalMoveTab, tempFigurePlacement);
                    for(int j = 0; j < 64; j++){
                        if(tempLegalMoveTab[j] != 0){
                            int val = minmax(deepth+1, tempFigurePlacement, i, j, alfa, beta);
                                if(val < best){
                                    best = val;
                                    indexWhere = j;
                                    indexFrom = i;
                                }
                                if(best<beta)
                                    beta = best;

                                if(beta <= alfa)
                                        break;
                        }
                    }
                }
            }
            roundCounter--;
            return best;
        }
    if(deepth == 0){
        resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
        setLegalMoves(indexFrom, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab, globalFigurePlacement);
        checkMoveCheckLegality(indexFrom, globalFinalLegalMoveTab, globalFigurePlacement);
        loadBools();
        printf("%d %d %d\n", indexFrom, indexWhere);
        moveFigureLogic(indexFrom, indexWhere, globalFinalLegalMoveTab, globalFigurePlacement);
        lastMoveOrigin = indexFrom;
        roundCounter++;
        isGameOver();
    }
    return -1;
}

