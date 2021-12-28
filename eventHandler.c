#include "chess.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

void eventHandler(GtkWidget* clickedTile, gpointer data){
    if (gameOver) return;
    gint* i = (gint*)data;
    int actionClickedTileIndex = (int)*i;
    GtkWidget* boardGrid = gtk_widget_get_parent(clickedTile);
    //Check if we need to change game state
    resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
    if (UISelectedTile != -1){
        if (getFigureType(UISelectedTile, globalFigurePlacement) != 'E' && whoseTurn() == getFigureSide(UISelectedTile,globalFigurePlacement)){
            setLegalMoves(UISelectedTile, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab,globalFigurePlacement);
            checkMoveCheckLegality(UISelectedTile, globalFinalLegalMoveTab, globalFigurePlacement);
        }
        if (getFigureType(UISelectedTile, globalFigurePlacement) != 'E' && whoseTurn() == getFigureSide(UISelectedTile, globalFigurePlacement) &&
           globalFinalLegalMoveTab[actionClickedTileIndex] != 0){
            moveFigureLogic(UISelectedTile, actionClickedTileIndex, globalFinalLegalMoveTab, globalFigurePlacement);
            lastMoveOrigin = UISelectedTile;
            roundCounter++;
            //Check if it's game over
            resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
            isGameOver();
        }
    }
    //Change the UI state based on action
    if (UISelectedTile == -1 && getFigureType(actionClickedTileIndex, globalFigurePlacement) != 'E' &&
             getFigureSide(actionClickedTileIndex, globalFigurePlacement) == whoseTurn()){
        UISelectedTile = actionClickedTileIndex;
        resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
        setLegalMoves(UISelectedTile, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab, globalFigurePlacement);
        checkMoveCheckLegality(UISelectedTile, globalFinalLegalMoveTab, globalFigurePlacement);
    }
    else if ((getFigureType(UISelectedTile, globalFigurePlacement) == 'E' || whoseTurn() != getFigureSide(UISelectedTile, globalFigurePlacement)) &&
       (getFigureType(actionClickedTileIndex, globalFigurePlacement) == 'E' || whoseTurn() != getFigureSide(actionClickedTileIndex, globalFigurePlacement)))
       UISelectedTile = -1;
    else if (getFigureType(UISelectedTile, globalFigurePlacement) != 'E' && whoseTurn() == getFigureSide(UISelectedTile, globalFigurePlacement) &&
       globalFinalLegalMoveTab[actionClickedTileIndex] != 0)
        UISelectedTile = -1;
    else if (UISelectedTile == actionClickedTileIndex)
        UISelectedTile = -1;
    else if (UISelectedTile != actionClickedTileIndex && getFigureType(actionClickedTileIndex, globalFigurePlacement) != 'E' &&
             getFigureSide(actionClickedTileIndex, globalFigurePlacement) == whoseTurn()){
        UISelectedTile = actionClickedTileIndex;
        resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
        setLegalMoves(UISelectedTile, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab, globalFigurePlacement);
        checkMoveCheckLegality(UISelectedTile, globalFinalLegalMoveTab, globalFigurePlacement);
    }
    //Draw the UI
    drawUI(boardGrid);
}
