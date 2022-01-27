#include "chess.h"

// UI state
int KGUISelectedTile = -1;
//game state
bool KGGameOver = false;
char KGg_FigurePlacement[64];

int KGglobalTransitionalLegalMoveTab[144];
int KGglobalFinalLegalMoveTab[64];

void startingKnightLayout(){
    for (int i = 0; i < 64; i++){
        KGg_FigurePlacement[i] = 'E'; // E - Empty
    }
    KGg_FigurePlacement[0] = 'S';
}

void KGResetLegalMoveTables(int transitionalLegalMoveTab[], int finalLegalMoveTab[]){
    for (int i = 0; i < 144; i++){
        transitionalLegalMoveTab[i] = 0;
    }
    for (int i = 0; i < 64; i++){
        finalLegalMoveTab[i] = 0;
    }
}

void KGknight(int selectedTileIndex, int transitionalLegalMoveTab[]){
    int indextransitionalLegalMoveTable = selectedTileIndex + 26 + (selectedTileIndex/8) * 4;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 14] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 25] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 23] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 10] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 14] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 23] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 25] = 1;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 10] = 1;
}

void KGSetLegalMoves (int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]){
   if (figurePlacement[selectedTileIndex] == 's' || figurePlacement[selectedTileIndex] == 'S') KGknight(selectedTileIndex, KGglobalTransitionalLegalMoveTab);
    int j = 0;
    for (int i = 26; i < 118; i++){
        if (finalLegalMoveTab[j] == 0){
            if(figurePlacement[j] == 'E'){
                if (transitionalLegalMoveTab[i] == 1) finalLegalMoveTab[j] = 1;
            }
        }
        j++;
        if (j%8 == 0) i += 4;
    }
}

void KGMoveFigureLogic(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]){
    moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable, figurePlacement);
    figurePlacement[selectedTileIndex] = 'X'; // mark tile as visited
}

void KGIsGameOver(){
    bool isOver = true;
    bool won = true;
    for (int i = 0; i < 64; i++){
        if (KGg_FigurePlacement[i] == 'S'){
            KGResetLegalMoveTables(KGglobalTransitionalLegalMoveTab, KGglobalFinalLegalMoveTab);
            KGSetLegalMoves(i, KGglobalFinalLegalMoveTab, KGglobalTransitionalLegalMoveTab, KGg_FigurePlacement);
            for (int j = 0; j < 64; j++){
                if (KGglobalFinalLegalMoveTab[j] == 1) isOver = false;
            }
        }
    }
    KGResetLegalMoveTables(KGglobalTransitionalLegalMoveTab, KGglobalFinalLegalMoveTab);
    for (int i = 0; i < 64; i++){
        if (KGg_FigurePlacement[i] == 'E') won = false;
    }
    if(isOver){
        if (won){
            printf("Congratulations, You've won!");
            KGGameOver = true;
        }
        else{
            printf("Game Over");
            KGGameOver = true;
        }
    }
}
