#include <stdio.h>
#include <limits.h>
#include "chess.h"
/*
Old version of calculating board value
struct tile{
    int wages;
    char tileName;
} tableTileWages[] = {
    {-10, 'P'}, {-20, 'S'}, {-30, 'B'}, {-50, 'R'}, {-90, 'Q'}, {-300, 'K'},
    {10, 'p'}, {20, 's'}, {30, 'b'}, {50, 'r'}, {90, 'q'}, {300, 'k'}, {0, 'E'}
};



int evaluateBoard(char board[]){
    int res = 0;
    for(int i = 0; i < 64; i++){
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
*/




double tileWages[120][8][8] = {0};


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
    { 2.0,  5.0,  0.0,  0.0,  0.0,  0.0,  5.0,  2.0}
};

double kingBlackWages[8][8] = {
    { 2.0,  5.0,  0.0,  0.0,  0.0,  0.0,  5.0,  2.0},
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
    {0.5,  1.0,  1.0,  -3.0, -3.0,  1.0,  1.0,  0.5},
    {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0}
};
double pawnBlackWages[8][8] = {
    {0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0},
    {0.5,  1.0,  1.0,  -3.0, -3.0,  1.0,  1.0,  0.5},
    {0.5, -0.5, -1.0,  0.0,  0.0, -1.0, -0.5,  0.5},
    {0.0,  0.0,  0.0,  2.0,  2.0,  0.0,  0.0,  0.0},
    {0.5,  0.5,  1.0,  2.5,  2.5,  1.0,  0.5,  0.5},
    {1.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0,  1.0},
    {5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0,  5.0},
    {7.0,  7.0,  7.0,  7.0,  7.0,  7.0,  7.0,  7.0}
};
double wages[120] = {0};
void wagesUpdate(){
    wages[80] = -10.0;
    wages[83] = -20.0;
    wages[66] = -30.0;
    wages[82] = -50.0;
    wages[81] = -90.0;
    wages[75] = -300.0;

    wages[69] = 0.0;

    wages[112] = 10.0;
    wages[115] = 20.0;
    wages[98] = 30.0;
    wages[114] = 50.0;
    wages[113] = 90.0;
    wages[107] = 300.0;
    for(int i = 0; i < 64; i++) tileWages[113][i/8][i%8] = queenWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[81][i/8][i%8] = queenWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[80][i/8][i%8] = pawnWhiteWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[112][i/8][i%8] = pawnBlackWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[66][i/8][i%8] = bishopWhiteWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[98][i/8][i%8] = bishopBlackWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[75][i/8][i%8] = kingWhiteWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[107][i/8][i%8] = kingBlackWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[82][i/8][i%8] = rookWhiteWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[114][i/8][i%8] = rookBlackWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[83][i/8][i%8] = knightWages[i/8][i%8];
    for(int i = 0; i < 64; i++) tileWages[115][i/8][i%8] = knightWages[i/8][i%8];
}

double evaluateBoard(char board[]){
    double res = 0;
    for(int i = 0; i < 64; i++){
        if(board[i] != 'E'){
            res += wages[(int)board[i]] + tileWages[(int)board[i]][i/8][i%8];
        }
    }
    return res;
}
int minmax(int deepth, char board[], int fromTile, int whereTile, int fromWhereLegalmoveTab, double alfa, double beta){
    char tempFigurePlacement[64];
    int tempLegalMoveTab[64] = {0};
    int tempTransitionalLegalMoveTab[484] = {0};
    for(int i = 0; i < 64; i++) tempFigurePlacement[i] = board[i];
    if(deepth != 0){
        tempLegalMoveTab[whereTile]=fromWhereLegalmoveTab;
        moveFigureLogic(fromTile,whereTile,tempLegalMoveTab,tempFigurePlacement);
    }
    if(deepth == 4)
        return evaluateBoard(tempFigurePlacement);
    int indexWhere = 0;
    int indexFrom = 0;
    if(deepth%2 == 0){
        double best = (double)INT_MIN;
        if(deepth != 0)
            roundCounter++;
        for(int i = 0; i < 64; i++){
            if(getFigureSide(i, tempFigurePlacement) == 'B'){
                for(int i = 0; i < 484; i++) tempTransitionalLegalMoveTab[i] = 0;
                for(int i = 0; i < 64; i++) tempLegalMoveTab[i] = 0;
                setLegalMoves(i, tempLegalMoveTab, tempTransitionalLegalMoveTab, tempFigurePlacement);
                checkMoveCheckLegality(i, tempLegalMoveTab, tempFigurePlacement);
                for(int j = 0; j < 64; j++){
                    if(tempLegalMoveTab[j] != 0){
                            double val = minmax(deepth+1, tempFigurePlacement, i, j, tempLegalMoveTab[j] ,alfa, beta);
                            if(val >= best){
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
            double best = (double)INT_MAX;
            roundCounter++;
            for(int i = 0; i < 64; i++){
                if(getFigureSide(i, tempFigurePlacement) == 'W'){
                    for(int i = 0; i < 484; i++) tempTransitionalLegalMoveTab[i] = 0;
                    for(int i = 0; i < 64; i++) tempLegalMoveTab[i] = 0;
                    setLegalMoves(i, tempLegalMoveTab, tempTransitionalLegalMoveTab, tempFigurePlacement);
                    checkMoveCheckLegality(i, tempLegalMoveTab, tempFigurePlacement);
                    for(int j = 0; j < 64; j++){
                        if(tempLegalMoveTab[j] != 0){
                            double val = minmax(deepth+1, tempFigurePlacement, i, j, tempLegalMoveTab[j] , alfa, beta);
                                if(val <= best){
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
            if(deepth != 0){
                roundCounter--;
                return best;
            }
        }
    if(deepth == 0){
        resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
        setLegalMoves(indexFrom, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab, globalFigurePlacement);
        checkMoveCheckLegality(indexFrom, globalFinalLegalMoveTab, globalFigurePlacement);
        loadBools();
        printf("%d %d\n", indexFrom, indexWhere);
        moveFigureLogic(indexFrom, indexWhere, globalFinalLegalMoveTab, globalFigurePlacement);
        lastMoveOrigin = indexFrom;
        roundCounter++;
        isGameOver();
    }
    return -1;
}
