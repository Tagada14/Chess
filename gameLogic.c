#include "chess.h"

// UI state
int UISelectedTile = -1;
int iFrom = -1;
int iWhere = -1;

// Game state
char globalFigurePlacement[64];
int roundCounter = 0;
int lastMoveOrigin = -1;
bool gameOver = false;
bool blackKingDidNotMove = true;
bool whiteKingDidNotMove = true;
bool leftBlackRookDidNotMove = true;
bool rightBlackRookDidNotMove = true;
bool leftWhiteRookDidNotMove = true;
bool rightWhiteRookDidNotMove = true;


int globalTransitionalLegalMoveTab[484]; // actual 8x8 table is from 160 to 224
int globalFinalLegalMoveTab[64];

struct boardConfiguration lastTurnBoardConfiguration;
// PAWN -> P, BISHOP-> B, ROOK -> R, KNIGHT -> S, QUEEN -> Q, KING -> K
// small letter -> BLACK, capital letter -> WHITE, E -> none
void startingChessLayout(){
    for (int i = 16; i < 48; i++){
        globalFigurePlacement[i] = 'E'; // E - Empty
    }
    for (int i = 8; i < 16; i++){
        globalFigurePlacement[i] = 'p'; //Black Pawn
        globalFigurePlacement[63-i] = 'P'; //White Pawn
    }
    globalFigurePlacement[0] = 'r'; globalFigurePlacement[7] = 'r'; globalFigurePlacement[63] = 'R'; globalFigurePlacement[56] = 'R';
    globalFigurePlacement[1] = 's'; globalFigurePlacement[6] = 's'; globalFigurePlacement[62] = 'S'; globalFigurePlacement[57] = 'S';
    globalFigurePlacement[2] = 'b'; globalFigurePlacement[5] = 'b'; globalFigurePlacement[61] = 'B'; globalFigurePlacement[58] = 'B';
    globalFigurePlacement[3] = 'q'; globalFigurePlacement[4] = 'k'; globalFigurePlacement[60] = 'K'; globalFigurePlacement[59] = 'Q';
}

void resetGameState(){
    roundCounter = 0;
    lastMoveOrigin = -1;
    gameOver = false;
    blackKingDidNotMove = true;
    whiteKingDidNotMove = true;
    leftBlackRookDidNotMove = true;
    rightBlackRookDidNotMove = true;
    leftWhiteRookDidNotMove = true;
    rightWhiteRookDidNotMove = true;
}

void resetUIState(){
    UISelectedTile = -1;
    iFrom = -1;
    iWhere = -1;
}

char whoseTurn(){
    if(roundCounter%2 == 0)return 'W';
    else return 'B';
}

inline char getFigureType(int tileIndex, char figurePlacement[]){
    return figurePlacement[tileIndex];
}

char getFigureSide(int tileIndex, char figurePlacement[]){
    char figureSide;
    if (figurePlacement[tileIndex] == 'E') figureSide = 'E';
    else if (figurePlacement[tileIndex] <= 'Z') figureSide = 'W';
    else if (figurePlacement[tileIndex] >= 'a') figureSide = 'B';
    else printf("Error in function getFigureSide\n");
    return figureSide;
}

bool isEnemy(int selectedTileIndex, int possibleEnemyIndex, char figurePlacement[]){
    char a = getFigureSide(selectedTileIndex, figurePlacement);
    char b = getFigureSide(possibleEnemyIndex, figurePlacement);
    return (a == b) ? false : true;
}

int kingIndex(char side, char figurePlacement[]){
    for (int i = 0; i < 64; i++){
        if (getFigureType(i, figurePlacement) == 'K' || getFigureType(i, figurePlacement) == 'k'){
            if (getFigureSide(i, figurePlacement) == side){
                return i;
            }
        }
    }
    printf("Error in kingIndex\n");
    return -1;
}

int howManyFigures(char figurePlacement[]){
    int count = 0;
    for (int i = 0; i < 64; i++){
        if (figurePlacement[i] != 'E') count++;
    }
    return count;
}

void resetLegalMoveTables(int transitionalLegalMoveTab[], int finalLegalMoveTab[]){
    for (int i = 0; i < 484; i++){
        transitionalLegalMoveTab[i] = 0;
    }
    for (int i = 0; i < 64; i++){
        finalLegalMoveTab[i] = 0;
    }
}

void moveFigureToTile(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]){
    if (legalMoveTable[actionTileIndex] == 1){
            char temp = figurePlacement[selectedTileIndex];
            figurePlacement[selectedTileIndex] = figurePlacement[actionTileIndex];
            figurePlacement[actionTileIndex] = temp;
        }
        else if (legalMoveTable[actionTileIndex] == 2){
            figurePlacement[actionTileIndex] = figurePlacement[selectedTileIndex];
            figurePlacement[selectedTileIndex] = 'E'; // E - empty
        }
        else printf("Error in moveFigureToTile\n");
}

void moveFigureLogic(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]){
    // Check if move Rooks or Kings for the first time
    if (leftBlackRookDidNotMove && getFigureType(selectedTileIndex, figurePlacement) == 'r' && selectedTileIndex == 0) leftBlackRookDidNotMove = false;
    else if (rightBlackRookDidNotMove && getFigureType(selectedTileIndex, figurePlacement) == 'r' && selectedTileIndex == 7) rightBlackRookDidNotMove = false;
    else if (leftWhiteRookDidNotMove && getFigureType(selectedTileIndex, figurePlacement) == 'R' && selectedTileIndex == 56) leftWhiteRookDidNotMove = false;
    else if (rightWhiteRookDidNotMove && getFigureType(selectedTileIndex, figurePlacement) == 'R' && selectedTileIndex == 63) rightWhiteRookDidNotMove = false;
    else if (whiteKingDidNotMove && getFigureType(selectedTileIndex, figurePlacement) == 'K') whiteKingDidNotMove = false;
    else if (blackKingDidNotMove && getFigureType(selectedTileIndex, figurePlacement) == 'k') blackKingDidNotMove = false;
    // Look for special movement cases
    if ((getFigureType(selectedTileIndex, figurePlacement) == 'K' || getFigureType(selectedTileIndex, figurePlacement) == 'k') &&
        selectedTileIndex - 2 == actionTileIndex){ // Left side castling
        if (getFigureType(selectedTileIndex, figurePlacement) == 'K') leftWhiteRookDidNotMove = false;
        else if (getFigureType(selectedTileIndex, figurePlacement) == 'k') leftBlackRookDidNotMove = false;
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable,figurePlacement); // Move the king
        moveFigureToTile(actionTileIndex - 2, selectedTileIndex - 1, legalMoveTable, figurePlacement); // Move the rook
    }
    else if ((getFigureType(selectedTileIndex, figurePlacement) == 'K' || getFigureType(selectedTileIndex, figurePlacement) == 'k') &&
        selectedTileIndex + 2 == actionTileIndex){ // Right side castling
        if (getFigureType(selectedTileIndex, figurePlacement) == 'K') rightWhiteRookDidNotMove = false;
        else if (getFigureType(selectedTileIndex, figurePlacement) == 'k') rightBlackRookDidNotMove = false;
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable,figurePlacement); // Move the king
        moveFigureToTile(actionTileIndex + 1, selectedTileIndex + 1, legalMoveTable, figurePlacement); // Move the rook

    }else if(getFigureType(selectedTileIndex, figurePlacement) == 'p' && selectedTileIndex/8 == 4 &&
        getFigureType(actionTileIndex, figurePlacement) == 'E' && lastMoveOrigin - 8  == actionTileIndex){
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable, figurePlacement);
        figurePlacement[lastMoveOrigin - 16] = 'E';

    }else if(getFigureType(selectedTileIndex, figurePlacement) == 'P' && selectedTileIndex/8 == 3 &&
        getFigureType(actionTileIndex, figurePlacement) == 'E' && lastMoveOrigin + 8  == actionTileIndex){
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable, figurePlacement);
        figurePlacement[lastMoveOrigin + 16] = 'E';

    }else if(getFigureType(selectedTileIndex, figurePlacement) == 'p' && selectedTileIndex/8 == 6){
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable, figurePlacement);
        figurePlacement[actionTileIndex] = 'q';
    }else if(getFigureType(selectedTileIndex, figurePlacement) == 'P' && selectedTileIndex/8 == 1){
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable, figurePlacement);
        figurePlacement[actionTileIndex] = 'Q';
    }
    else {
        moveFigureToTile(selectedTileIndex, actionTileIndex, legalMoveTable, figurePlacement);
    }
}

void pawnBlack(int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]){
    int indextransitionalLegalMoveTable = selectedTileIndex + 161 + (selectedTileIndex/8) * 14;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 21] = 2;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 23] = 2;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 22] = 1;
    if (selectedTileIndex >= 8 && selectedTileIndex <= 15 && getFigureType(selectedTileIndex + 8, figurePlacement) == 'E')
        transitionalLegalMoveTab[indextransitionalLegalMoveTable + 44] = 1;
    if(figurePlacement == globalFigurePlacement){
        if(selectedTileIndex/8 == 4){
            if(selectedTileIndex%8 > 0 && getFigureType(selectedTileIndex+7, figurePlacement) == 'E' &&
               getFigureType(selectedTileIndex - 1, figurePlacement) == 'P' && lastMoveOrigin == selectedTileIndex + 15)
                finalLegalMoveTab[selectedTileIndex+7] = 2;
            if(selectedTileIndex%8 < 7 && getFigureType(selectedTileIndex+9, figurePlacement) == 'E' &&
               getFigureType(selectedTileIndex + 1, figurePlacement) == 'P' && lastMoveOrigin == selectedTileIndex + 17)
                finalLegalMoveTab[selectedTileIndex+9] = 2;
        }
    }

}

void king(int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]){
    int indextransitionalLegalMoveTable = selectedTileIndex + 161 + (selectedTileIndex/8) * 14;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 21] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 22] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 23] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 21] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 22] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 23] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 1] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 1] = 3;
    // Check if we can castle
    if (figurePlacement == globalFigurePlacement){
        if (getFigureSide(selectedTileIndex, figurePlacement) == 'W'){
            if (whiteKingDidNotMove){ // Check if the King has moved before
                char temporaryFigurePlacement[64];
                        for (int j = 0; j < 64; j++){
                            temporaryFigurePlacement[j] = figurePlacement[j];
                        }
                int* CheckTiles = checkedTiles(temporaryFigurePlacement);
                if (CheckTiles[selectedTileIndex] == 0){ // Check if the King isn't checked
                    // Left side castling
                    if (leftWhiteRookDidNotMove){ // Check if the rook has moved before
                        // Check if there is a Rook and the tiles between the Rook and the King are empty
                        if (getFigureType(selectedTileIndex - 3, figurePlacement) == 'E' && getFigureType(selectedTileIndex - 2, figurePlacement) == 'E' &&
                             getFigureType(selectedTileIndex - 1, figurePlacement) == 'E' && getFigureType(selectedTileIndex - 4, figurePlacement) == 'R'){
                            //Check if any of the tiles are checked
                            temporaryFigurePlacement[selectedTileIndex-1] = 'K';
                            temporaryFigurePlacement[selectedTileIndex-2] = 'K';
                            temporaryFigurePlacement[selectedTileIndex-3] = 'K';
                            CheckTiles = checkedTiles(temporaryFigurePlacement);
                            if (CheckTiles[selectedTileIndex-1] == 0 && CheckTiles[selectedTileIndex-2] == 0 && CheckTiles[selectedTileIndex-3] == 0 && CheckTiles[selectedTileIndex-4] == 0){
                                finalLegalMoveTab[selectedTileIndex - 2] = 1;
                            }
                            free(CheckTiles);
                        }
                    }
                    // Right side castling
                    if (rightWhiteRookDidNotMove){ // Check if the rooks has moved before
                        // Check if there is a Rook and the tiles between the Rook and the King are empty
                        if (getFigureType(selectedTileIndex + 1, figurePlacement) == 'E' && getFigureType(selectedTileIndex + 2, figurePlacement) == 'E' &&
                            getFigureType(selectedTileIndex + 3, figurePlacement) == 'R'){
                            //Check if any of the tiles are checked
                            temporaryFigurePlacement[selectedTileIndex+1] = 'K';
                            temporaryFigurePlacement[selectedTileIndex+2] = 'K';
                            CheckTiles = checkedTiles(temporaryFigurePlacement);
                            if (CheckTiles[selectedTileIndex+1] == 0 && CheckTiles[selectedTileIndex+2] == 0 && CheckTiles[selectedTileIndex+3] == 0){
                                finalLegalMoveTab[selectedTileIndex + 2] = 1;
                            }
                            free(CheckTiles);
                        }
                    }
                }
            }
        }
        else if (getFigureSide(selectedTileIndex, figurePlacement) == 'B'){
            if (blackKingDidNotMove){ // Check if the King has moved before
                int* CheckTiles = checkedTiles(figurePlacement);
                if (CheckTiles[selectedTileIndex] == 0){ // Check if the King isn't checked
                    // Left side castling
                    if (leftBlackRookDidNotMove){
                        // Check if there is a Rook and the tiles between the Rook and the King are empty
                        if (getFigureType(selectedTileIndex - 3, figurePlacement) == 'E' && getFigureType(selectedTileIndex - 2, figurePlacement) == 'E' &&
                            getFigureType(selectedTileIndex - 1, figurePlacement) == 'E' && getFigureType(selectedTileIndex - 4, figurePlacement) == 'r'){
                            //Check if any of the tiles are checked
                            char temporaryFigurePlacement[64];
                            for (int j = 0; j < 64; j++){
                                temporaryFigurePlacement[j] = figurePlacement[j];
                            }
                            temporaryFigurePlacement[selectedTileIndex-1] = 'k';
                            temporaryFigurePlacement[selectedTileIndex-2] = 'k';
                            temporaryFigurePlacement[selectedTileIndex-3] = 'k';
                            CheckTiles = checkedTiles(temporaryFigurePlacement);
                            if (CheckTiles[selectedTileIndex-1] == 0 && CheckTiles[selectedTileIndex-2] == 0 && CheckTiles[selectedTileIndex-3] == 0 && CheckTiles[selectedTileIndex-4] == 0){
                                finalLegalMoveTab[selectedTileIndex - 2] = 1;
                            }
                            free(CheckTiles);
                        }
                    }
                    // Right side castling
                    if (rightBlackRookDidNotMove){
                        // Check if there is a Rook and the tiles between the Rook and the King are empty
                        if (getFigureType(selectedTileIndex + 1, figurePlacement) == 'E' &&
                        getFigureType(selectedTileIndex + 2, figurePlacement) == 'E' && getFigureType(selectedTileIndex + 3, figurePlacement) == 'r'){
                            //Check if any of the tiles are checked
                            char temporaryFigurePlacement[64];
                            for (int j = 0; j < 64; j++){
                                temporaryFigurePlacement[j] = figurePlacement[j];
                            }
                            temporaryFigurePlacement[selectedTileIndex+1] = 'k';
                            temporaryFigurePlacement[selectedTileIndex+2] = 'k';
                            CheckTiles = checkedTiles(temporaryFigurePlacement);
                            if (CheckTiles[selectedTileIndex+1] == 0 && CheckTiles[selectedTileIndex+2] == 0 && CheckTiles[selectedTileIndex+3] == 0){
                                finalLegalMoveTab[selectedTileIndex + 2] = 1;
                            }
                            free(CheckTiles);
                        }
                    }
                }
            }
        }
    }
}

void rook(int clickedTileIndex, int finalLegalMoveTab[], char figurePlacement[]){
    for (int i = clickedTileIndex; i < 56; i += 8){
        if (figurePlacement[i + 8] != 'E'){
            if (isEnemy(clickedTileIndex, i + 8,figurePlacement)){
                finalLegalMoveTab[i + 8] = 2;
            }
            break;
        }
        else if (figurePlacement[i + 8] == 'E'){
            finalLegalMoveTab[i + 8] = 1;
        }
    }
    for (int i = clickedTileIndex; i > 7; i -= 8){
        if (figurePlacement[i - 8] != 'E'){
            if (isEnemy(clickedTileIndex, i - 8,figurePlacement)){
                finalLegalMoveTab[i - 8] = 2;
            }
            break;
        }
        else if (figurePlacement[i - 8] == 'E'){
            finalLegalMoveTab[i - 8] = 1;
        }
    }
    for (int i = clickedTileIndex; i % 8 < 7; i++){
        if (figurePlacement[i + 1] != 'E'){
            if (isEnemy(clickedTileIndex, i + 1,figurePlacement)){
                finalLegalMoveTab[i + 1] = 2;
            }
            break;
        }
        else if (figurePlacement[i + 1] == 'E'){
            finalLegalMoveTab[i + 1] = 1;
        }
    }
    for (int i = clickedTileIndex; i % 8 > 0; i--){
        if (figurePlacement[i - 1] != 'E'){
            if (isEnemy(clickedTileIndex, i - 1,figurePlacement)){
                finalLegalMoveTab[i - 1] = 2;
            }
            break;
        }
        else if (figurePlacement[i - 1] == 'E'){
            finalLegalMoveTab[i - 1] = 1;
        }
    }
}

void bishop(int clickedTileIndex, int finalLegalMoveTab[], char figurePlacement[]){
    for (int i = clickedTileIndex; i < 56 && i % 8 < 7; i += 9){
        if (figurePlacement[i + 9] != 'E'){
            if (isEnemy(clickedTileIndex, i + 9,figurePlacement)){
                finalLegalMoveTab[i + 9] = 2;
            }
            break;
        }
        else if (figurePlacement[i + 9] == 'E'){
            finalLegalMoveTab[i + 9] = 1;
        }
    }
    for (int i = clickedTileIndex; i < 56 && i % 8 > 0; i += 7){
        if (figurePlacement[i + 7] != 'E'){
            if (isEnemy(clickedTileIndex, i + 7,figurePlacement)){
                finalLegalMoveTab[i + 7] = 2;
            }
            break;
        }
        else if (figurePlacement[i + 7] == 'E'){
            finalLegalMoveTab[i + 7] = 1;
        }
    }
    for (int i = clickedTileIndex; i > 7 && i % 8 > 0; i -= 9){
        if (figurePlacement[i - 9] != 'E'){
            if (isEnemy(clickedTileIndex, i - 9,figurePlacement)){
                finalLegalMoveTab[i - 9] = 2;
            }
            break;
        }
        else if (figurePlacement[i - 9] == 'E'){
            finalLegalMoveTab[i - 9] = 1;
        }
    }
    for (int i = clickedTileIndex; i > 7 && i % 8 < 7; i -= 7){
        if (figurePlacement[i - 7] != 'E'){
            if (isEnemy(clickedTileIndex, i - 7,figurePlacement)){
                finalLegalMoveTab[i - 7] = 2;
            }
            break;
        }
        else if (figurePlacement[i - 7] == 'E'){
            finalLegalMoveTab[i - 7] = 1;
        }
    }
}

void pawnWhite(int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]){
    int indextransitionalLegalMoveTable = selectedTileIndex + 161 + (selectedTileIndex/8) * 14;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 21] = 2;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 23] = 2;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 22] = 1;
    if (selectedTileIndex >= 48 && selectedTileIndex <= 55 && getFigureType(selectedTileIndex - 8, figurePlacement) == 'E')
        transitionalLegalMoveTab[indextransitionalLegalMoveTable - 44] = 1;
    if(figurePlacement == globalFigurePlacement){
        if(selectedTileIndex/8 == 3){
            if(selectedTileIndex%8 > 0 && getFigureType(selectedTileIndex-7, figurePlacement) == 'E' &&
               getFigureType(selectedTileIndex + 1, figurePlacement) == 'p' && lastMoveOrigin == selectedTileIndex - 15)
                finalLegalMoveTab[selectedTileIndex-7] = 2;
            if(selectedTileIndex%8 < 7 && getFigureType(selectedTileIndex-9, figurePlacement) == 'E' &&
               getFigureType(selectedTileIndex - 1, figurePlacement) == 'p' && lastMoveOrigin == selectedTileIndex - 17)
                finalLegalMoveTab[selectedTileIndex-9] = 2;
        }
    }
}

void queen(int selectedTileIndex, int finalLegalMoveTab[], char figurePlacement[]){
    bishop(selectedTileIndex, finalLegalMoveTab, figurePlacement);
    rook(selectedTileIndex, finalLegalMoveTab, figurePlacement);
}

void knight(int selectedTileIndex, int transitionalLegalMoveTab[]){
    int indextransitionalLegalMoveTable = selectedTileIndex + 161 + (selectedTileIndex/8) * 14;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 24] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 45] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 43] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable - 20] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 24] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 45] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 43] = 3;
    transitionalLegalMoveTab[indextransitionalLegalMoveTable + 20] = 3;
}

void setLegalMoves(int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]){
    /* in transitionalLegalMoveTab 0 - can't move there, 1 - can move if there is no enemy figure, 2 - can move there if there is enemy figure,
    3 - can move there regardless if the tile is empty or occupied by the enemy
    in finalLegalMoveTab 0 - can't move there, 1 - can move there and there is no enemy figure there, 2 - can move there and kill enemy figure
    */
    if (figurePlacement[selectedTileIndex] == 'P') pawnWhite(selectedTileIndex, finalLegalMoveTab, transitionalLegalMoveTab, figurePlacement);
    else if (figurePlacement[selectedTileIndex] == 'p') pawnBlack(selectedTileIndex, finalLegalMoveTab, transitionalLegalMoveTab, figurePlacement);
    else if (figurePlacement[selectedTileIndex] == 'r' || figurePlacement[selectedTileIndex] == 'R') rook(selectedTileIndex, finalLegalMoveTab, figurePlacement);
    else if (figurePlacement[selectedTileIndex] == 'b' || figurePlacement[selectedTileIndex] == 'B') bishop(selectedTileIndex, finalLegalMoveTab, figurePlacement);
    else if (figurePlacement[selectedTileIndex] == 's' || figurePlacement[selectedTileIndex] == 'S') knight(selectedTileIndex, transitionalLegalMoveTab);
    else if (figurePlacement[selectedTileIndex] == 'q' || figurePlacement[selectedTileIndex] == 'Q') queen(selectedTileIndex, finalLegalMoveTab, figurePlacement);
    else if (figurePlacement[selectedTileIndex] == 'k' || figurePlacement[selectedTileIndex] == 'K') king(selectedTileIndex, finalLegalMoveTab, transitionalLegalMoveTab, figurePlacement);
    else printf("Error in function setLegalMoves\n");
    int j = 0;
    for (int i = 161; i < 323; i++){
        if (finalLegalMoveTab[j] == 0){
            if(figurePlacement[j] == 'E'){
                if (transitionalLegalMoveTab[i] == 1 || transitionalLegalMoveTab[i] == 3) finalLegalMoveTab[j] = 1;
            }
            else if(figurePlacement[j] != 'E' && isEnemy(selectedTileIndex, j, figurePlacement)){
                if (transitionalLegalMoveTab[i] > 1) finalLegalMoveTab[j] = 2;
            }
            else if(figurePlacement[j] != 'E' && getFigureSide(j, figurePlacement) == getFigureSide(selectedTileIndex, figurePlacement)) finalLegalMoveTab[j] = 0;
        }
        j++;
        if (j%8 == 0) i += 14;
    }
}

void checkMoveCheckLegality(int selectedTileIndex, int finalLegalMoveTab[], char figurePlacement[]){
    char temporaryFigurePlacement[64];
    for (int i = 0; i < 64; i++){
        if (finalLegalMoveTab[i] != 0){
            for (int j = 0; j < 64; j++){
                temporaryFigurePlacement[j] = figurePlacement[j];
            }
            moveFigureToTile(selectedTileIndex, i, finalLegalMoveTab, temporaryFigurePlacement);
            int* checkedTileTable = checkedTiles(temporaryFigurePlacement);
            int KingIndex = kingIndex(whoseTurn(),temporaryFigurePlacement);
            if (checkedTileTable[KingIndex] == 1) finalLegalMoveTab[i] = 0;
            free(checkedTileTable);
        }
    }
}

int* checkedTiles(char figurePlacement[]){
    int* checkedTilesTable = malloc(sizeof(int)*64);
    memset(checkedTilesTable,0,sizeof(int)*64);
    int* funcionTemporaryLegalMoveTable = malloc(sizeof(int)*484);
    memset(funcionTemporaryLegalMoveTable,0,sizeof(int)*484);
    for (int i = 0; i < 64; i++){
        if (getFigureType(i, figurePlacement) != 'E' && getFigureSide(i, figurePlacement) != whoseTurn()){
            setLegalMoves(i, checkedTilesTable, funcionTemporaryLegalMoveTable, figurePlacement);
        }
    }
    for (int i = 0; i < 64; i++){
        if (checkedTilesTable[i] >= 1) checkedTilesTable[i] = 1; // 1 means the tile is attacked
        else checkedTilesTable[i] = 0; // 0 means the tile isn't attacked
    }
    free(funcionTemporaryLegalMoveTable);
    return checkedTilesTable;
}

void isGameOver(){
    bool flagMoves = false;
    bool flagCheck = false;
    char temporaryFigurePlacement[64];
    for (int j = 0; j < 64; j++){
                temporaryFigurePlacement[j] = globalFigurePlacement[j];
    }
    int* CheckedTile = checkedTiles(temporaryFigurePlacement);
    int KingIndex = kingIndex(whoseTurn(),temporaryFigurePlacement);
    if (CheckedTile[KingIndex] == 1) flagCheck = true;
        for (int i = 0; i < 64; i++){
            if (flagMoves) break;
            if (getFigureType(i, temporaryFigurePlacement) != 'E' && getFigureSide(i, temporaryFigurePlacement) == whoseTurn()){
                resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
                setLegalMoves(i, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab, temporaryFigurePlacement);
                checkMoveCheckLegality(i, globalFinalLegalMoveTab, temporaryFigurePlacement);
                for (int j = 0; j < 64; j++){
                    if (globalFinalLegalMoveTab[j] != 0){
                        flagMoves = true;
                        break;
                    }
                }
            }
        }
    if(!flagMoves){
        if (timer_id != 0){
            g_source_remove(timer_id);
            timer_id = 0;
        }
    }
    if(flagCheck && !flagMoves){
        printf("Game Over\n");
        if (whoseTurn() == 'W') printf("Black wins\n");
        else if (whoseTurn() == 'B') printf ("White wins\n");
        gameOver = true;
    }
    else if (!flagCheck && !flagMoves){
        printf("Game Over\n");
        printf("It's a tie!\n");
    }
}

void saveCurrentConfiguration(){
    lastTurnBoardConfiguration.gameOver = gameOver;
    lastTurnBoardConfiguration.leftBlackRookDidNotMove = leftBlackRookDidNotMove;
    lastTurnBoardConfiguration.leftWhiteRookDidNotMove = leftWhiteRookDidNotMove;
    lastTurnBoardConfiguration.rightBlackRookDidNotMove = rightBlackRookDidNotMove;
    lastTurnBoardConfiguration.rightWhiteRookDidNotMove = rightWhiteRookDidNotMove;
    lastTurnBoardConfiguration.blackKingDidNotMove = blackKingDidNotMove;
    lastTurnBoardConfiguration.whiteKingDidNotMove = whiteKingDidNotMove;
    lastTurnBoardConfiguration.roundCounter = roundCounter;
    lastTurnBoardConfiguration.lastMoveOrigin = lastMoveOrigin;
    for (int i = 0; i < 64; i++){
        lastTurnBoardConfiguration.figurePlacement[i] = globalFigurePlacement[i];
    }
}

void loadConfiguration(){
    gameOver = lastTurnBoardConfiguration.gameOver;
    leftBlackRookDidNotMove = lastTurnBoardConfiguration.leftBlackRookDidNotMove ;
    leftWhiteRookDidNotMove = lastTurnBoardConfiguration.leftWhiteRookDidNotMove;
    rightBlackRookDidNotMove = lastTurnBoardConfiguration.rightBlackRookDidNotMove;
    rightWhiteRookDidNotMove = lastTurnBoardConfiguration.rightWhiteRookDidNotMove;
    blackKingDidNotMove = lastTurnBoardConfiguration.blackKingDidNotMove;
    whiteKingDidNotMove = lastTurnBoardConfiguration.whiteKingDidNotMove;
    roundCounter = lastTurnBoardConfiguration.roundCounter;
    lastMoveOrigin = lastTurnBoardConfiguration.lastMoveOrigin;
    for (int i = 0; i < 64; i++){
       globalFigurePlacement[i] = lastTurnBoardConfiguration.figurePlacement[i];
    }
}

void saveConfigurationToFile(){
    char* fileName = malloc(sizeof(char)*28);
    time_t secs = time(0);
    struct tm *local = localtime(&secs);
    sprintf(fileName, "save%02d-%02d-%d_%02d_%02d_%02d.chess",local->tm_mday,local->tm_mon +1, local->tm_year+1900, local->tm_hour, local->tm_min, local->tm_sec);
    printf("%s\n", fileName);
    FILE *file  = fopen(fileName, "w");
     if (file == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    }
    fprintf(file, "%d %d %d %d %d %d\n",leftBlackRookDidNotMove, rightBlackRookDidNotMove, leftWhiteRookDidNotMove, rightWhiteRookDidNotMove, blackKingDidNotMove, whiteKingDidNotMove);
    fprintf(file, "%d %d\n", roundCounter, lastMoveOrigin);
    for(int i = 0; i < 64; i++){
        putc(globalFigurePlacement[i], file);
        if ((i+1)%8 == 0) putc('\n', file);
    }
    fflush(file);
    free(fileName);
    int fclose(FILE *file);
}

void loadConfigurationFromFile(char* filename){
        FILE *file  = fopen(filename, "r");
     if (file == NULL){
        printf("Error! Could not open file\n");
        exit(-1);
    }
    int temp1,temp2,temp3,temp4,temp5,temp6;
    fscanf(file, "%d %d %d %d %d %d\n", &temp1, &temp2, &temp3, &temp4, &temp5, &temp6);
    leftBlackRookDidNotMove = temp1; rightBlackRookDidNotMove = temp2; leftWhiteRookDidNotMove = temp3; rightWhiteRookDidNotMove = temp4;
    blackKingDidNotMove = temp5; whiteKingDidNotMove = temp6;
    fscanf(file, "%d %d\n", &temp1, &temp2);
    roundCounter = temp1; lastMoveOrigin = temp2;
    for(int i = 0; i < 64; i++){
        globalFigurePlacement[i] = getc(file);
        if ((i+1)%8 == 0) getc(file);
    }
    int fclose(FILE *file);
}
