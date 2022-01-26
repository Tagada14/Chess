#ifndef _CHESS
#define _CHESS

#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>

struct GTKmainGrid {
int posX,lenX,posY,lenY,index;
};
struct GTKmenuGrid {
int posX,lenX,posY,lenY,index;
char name[10];
};

struct boardConfiguration {
char figurePlacement[64];
int roundCounter;
int lastMoveOrigin;
bool gameOver;
bool blackKingDidNotMove;
bool whiteKingDidNotMove;
bool leftBlackRookDidNotMove;
bool rightBlackRookDidNotMove;
bool leftWhiteRookDidNotMove;
bool rightWhiteRookDidNotMove;
};
extern struct GTKmainGrid tabGrid[];
extern struct GTKmenuGrid menuGrid[];
extern struct boardConfiguration lastTurnBoardConfiguration;
extern int roundCounter;
extern GtkWidget* label;
extern int UISelectedTile;
extern char globalFigurePlacement[];
extern int globalTransitionalLegalMoveTab[];
extern int globalFinalLegalMoveTab[];
extern int lastMoveOrigin;
extern bool gameOver;
extern bool blackKingDidNotMove;
extern bool whiteKingDidNotMove;
extern bool leftBlackRookDidNotMove;
extern bool rightBlackRookDidNotMove;
extern bool leftWhiteRookDidNotMove;
extern bool rightWhiteRookDidNotMove;
extern GtkWidget* SingleplayerGameWindow;
extern GtkWidget* menuWindow;
extern GtkWidget* creditsWindow;
extern GtkWidget* chessBoardGrid;


void eventHandler(GtkWidget* clickedTile, gpointer data);
void startingLayout();
char whoseTurn();
char getFigureType(int tileIndex, char figurePlacement[]);
char getFigureSide(int tileIndex, char figurePlacement[]);
bool isEnemy(int selectedTileIndex, int possibleEnemyIndex, char figurePlacement[]);
int kingIndex(char side, char figurePlacement[]);
void resetLegalMoveTables(int transitionalLegalMoveTab[], int finalLegalMoveTab[]);
void moveFigureToTile(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]);
void setLegalMoves(int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]);
void drawBoard (GtkWidget* grid);
void resetBoardColors(GtkWidget* grid);
void drawLegalMoves(GtkWidget* boardGrid);
void myCSS(void);
void changeTurnLabel(GtkWidget* label);
void drawUI(GtkWidget* grid);
void checkMoveCheckLegality(int selectedTileIndex, int finalLegalMoveTab[], char figurePlacement[]);
int* checkedTiles(char figurePlacement[]);
void isGameOver();
void moveFigureLogic(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]);
void menuHandler();
void saveCurrentConfiguration();
void loadConfiguration();
void reverseLastMove(GtkWidget* menuButton, gpointer data);
void saveConfigurationToFile();
void loadConfigurationFromFile();
void loadBoardConfigurationFromFile(GtkWidget* menuButton, gpointer data);
void saveBoardConfigurationToFile(GtkWidget* menuButton, gpointer data);

#endif  //_CHESS
