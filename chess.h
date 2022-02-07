#ifndef _CHESS
#define _CHESS

#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

struct GTKmainGrid {
int posX,lenX,posY,lenY,index;
};
struct GTKmenuGrid {
int posX,lenX,posY,lenY,index;
char name[20];
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
extern int iFrom;
extern int iWhere;
extern char globalFigurePlacement[];
extern int globalTransitionalLegalMoveTab[];
extern int globalFinalLegalMoveTab[];
extern int gameResult;
extern int lastMoveOrigin;
extern bool gameOver;
extern bool blackKingDidNotMove;
extern bool whiteKingDidNotMove;
extern bool leftBlackRookDidNotMove;
extern bool rightBlackRookDidNotMove;
extern bool leftWhiteRookDidNotMove;
extern bool rightWhiteRookDidNotMove;
//Knight Mini-game
extern char KGg_FigurePlacement[];
extern int KGglobalTransitionalLegalMoveTab[];
extern int KGglobalFinalLegalMoveTab[];
extern int KGUISelectedTile;
extern bool KGGameOver;
extern bool KGGameWon;
extern GtkWidget* KGplayAgainButton;
extern GtkWidget* KGgameOverLabel;
//GTK
extern GtkWidget* chessGameWindow;
extern GtkWidget* menuWindow;
extern GtkWidget* creditsWindow;
extern GtkWidget* chessBoardGrid;
extern GtkWidget* knightGameWindow;
extern GtkWidget* knightGameChessBoardGrid;
extern GtkWidget* timer;
extern GtkWidget* playAgainButton;
extern GtkWidget* gameOverLabel;
extern int sec_expired;
extern int sec_expired_white;
extern int sec_expired_black;
extern const int clock_time;
extern guint timer_id;
//AI
extern bool AI_on;
extern int DEPTH;

void eventHandler(GtkWidget* clickedTile, gpointer data);
void startingChessLayout();
char whoseTurn();
char getFigureType(int tileIndex, char figurePlacement[]);
char getFigureSide(int tileIndex, char figurePlacement[]);
bool isEnemy(int selectedTileIndex, int possibleEnemyIndex, char figurePlacement[]);
int kingIndex(char side, char figurePlacement[]);
int howManyFigures(char figurePlacement[]);
void resetLegalMoveTables(int transitionalLegalMoveTab[], int finalLegalMoveTab[]);
void moveFigureToTile(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]);
void setLegalMoves(int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]);
void drawBoard (GtkWidget* grid, char figurePlacement[]);
void resetBoardColors(GtkWidget* grid);
void drawLegalMoves(GtkWidget* boardGrid, int legalMoveTab[]);
void myCSS(void);
void changeTurnLabel(GtkWidget* label);
void drawUI(GtkWidget* grid, char figurePlacement[], int legalMoveTab[]);
void drawLastMove(GtkWidget* boardGrid);
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
void resetGameState();
void resetUIState();
void changeTurnTimers();
gboolean timer_update(gpointer data);
void playAgain();
//Knight Mini-game
void knightGameEventHandler (GtkWidget* menuButton, gpointer data);
void startingKnightLayout();
void KGSetLegalMoves (int selectedTileIndex, int finalLegalMoveTab[], int transitionalLegalMoveTab[], char figurePlacement[]);
void KGResetLegalMoveTables(int transitionalLegalMoveTab[], int finalLegalMoveTab[]);
void KGMoveFigureLogic(int selectedTileIndex, int actionTileIndex, int legalMoveTable[], char figurePlacement[]);
void KGIsGameOver();
void KGdrawUI(GtkWidget* grid, char figurePlacement[], int legalMoveTab[]);
//void displayEngGameMessage(bool didWin);
void KGLoadingSequence();
void KGplayAgain();
void KGGameEnd();
//AI
double minmax(int deepth, char board[], int fromTile, int whereTile, int fromWhereLegalmoveTab, double alfa, double beta);
void wagesUpdate();
double evaluateBoard(char board[]);
//GTK
void exitWithButton( GtkWidget *widget, gpointer data);
void createCreditsWindow();
void createMenuWindow();
void createKnightMGWindow();
void createChessGameWindow();
void set_timer(gpointer data);
void chessGameOver();
void initializeMenuGrid();
void initializeTabGrid();
#endif  //_CHESS
