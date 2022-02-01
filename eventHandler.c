#include "chess.h"

void eventHandler(GtkWidget* clickedTile, gpointer data){
    if (gameOver) return;
    gint* i = (gint*)data;
    int actionClickedTileIndex = (int)*i;
    GtkWidget* boardGrid = gtk_widget_get_parent(clickedTile);
    //Check if we need to change game state
    if (UISelectedTile != -1){
        if (getFigureType(UISelectedTile, globalFigurePlacement) != 'E' && whoseTurn() == getFigureSide(UISelectedTile,globalFigurePlacement)){
            resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
            setLegalMoves(UISelectedTile, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab,globalFigurePlacement);
            checkMoveCheckLegality(UISelectedTile, globalFinalLegalMoveTab, globalFigurePlacement);
        }
        if (getFigureType(UISelectedTile, globalFigurePlacement) != 'E' && whoseTurn() == getFigureSide(UISelectedTile, globalFigurePlacement) &&
           globalFinalLegalMoveTab[actionClickedTileIndex] != 0){
            saveCurrentConfiguration();
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
    else if (UISelectedTile == actionClickedTileIndex)
        UISelectedTile = -1;
    else if ((getFigureSide(actionClickedTileIndex, globalFigurePlacement) != whoseTurn() || getFigureType(actionClickedTileIndex, globalFigurePlacement) == 'E') &&
              globalFinalLegalMoveTab[actionClickedTileIndex] == 0)
        UISelectedTile = -1;
    else if (UISelectedTile != actionClickedTileIndex && getFigureType(actionClickedTileIndex, globalFigurePlacement) != 'E' &&
             getFigureSide(actionClickedTileIndex, globalFigurePlacement) == whoseTurn()){
        UISelectedTile = actionClickedTileIndex;
        resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
        setLegalMoves(UISelectedTile, globalFinalLegalMoveTab, globalTransitionalLegalMoveTab, globalFigurePlacement);
        checkMoveCheckLegality(UISelectedTile, globalFinalLegalMoveTab, globalFigurePlacement);
    }
    //Draw the UI
    if (AI_on){
        drawUI(boardGrid, globalFigurePlacement, globalFinalLegalMoveTab);
        gtk_test_widget_wait_for_draw(boardGrid);
        if(roundCounter%2 && !gameOver){
            for(int i = 0; i < 1; i++) gtk_test_widget_wait_for_draw(boardGrid);
            double x = minmax(0, globalFigurePlacement, 0, 0,0, (double)INT_MIN, (double)INT_MAX-1.0);
        }
    }
//    globalFinalLegalMoveTab[18] = 1;
//    moveFigureToTile(1, 18, globalFinalLegalMoveTab,globalFigurePlacement);
//    evaluateBoard(globalFigurePlacement);
    drawUI(boardGrid, globalFigurePlacement, globalFinalLegalMoveTab);
}

void menuHandler (GtkWidget* menuButton, gpointer data){
    gint* i = (gint*)data;
    int menuTileIndex = (int)*i;
    if (menuTileIndex == 0){
        createSingleplayerGameWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(SingleplayerGameWindow);
        startingChessLayout();
        wagesUpdate();
        resetBoardColors(chessBoardGrid);
        drawBoard(chessBoardGrid, globalFigurePlacement);
        AI_on = true;
    }
    else if (menuTileIndex == 1){
        createMultiplayerGameWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(MultiplayerGameWindow);
        startingChessLayout();
        resetBoardColors(chessBoardGrid);
        drawBoard(chessBoardGrid, globalFigurePlacement);
        AI_on = false;
    }
    else if (menuTileIndex == 2){
        createKnightMGWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(knightGameWindow);
        startingKnightLayout();
        resetBoardColors(knightGameChessBoardGrid);
        drawBoard(knightGameChessBoardGrid, KGg_FigurePlacement);
    }
    else if (menuTileIndex == 4){
        createCreditsWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(creditsWindow);
    }
}

void knightGameEventHandler (GtkWidget* clickedTile, gpointer data){
    if (KGGameOver) return;
    gint* i = (gint*)data;
    int actionClickedTileIndex = (int)*i;
    GtkWidget* boardGrid = gtk_widget_get_parent(clickedTile);
    //Check if we need to change game state
    if (KGUISelectedTile != -1){
        if (getFigureType(KGUISelectedTile, KGg_FigurePlacement) != 'E' && getFigureType(KGUISelectedTile, KGg_FigurePlacement) != 'X'){
            KGResetLegalMoveTables(KGglobalTransitionalLegalMoveTab, KGglobalFinalLegalMoveTab);
            KGSetLegalMoves(KGUISelectedTile, KGglobalFinalLegalMoveTab, KGglobalTransitionalLegalMoveTab, KGg_FigurePlacement);
        }
        if ((getFigureType(KGUISelectedTile, KGg_FigurePlacement) != 'E' && getFigureType(KGUISelectedTile, KGg_FigurePlacement) != 'X') &&
           KGglobalFinalLegalMoveTab[actionClickedTileIndex] != 0){
            KGMoveFigureLogic(KGUISelectedTile, actionClickedTileIndex, KGglobalFinalLegalMoveTab, KGg_FigurePlacement);
            KGUISelectedTile = -1;
            //Check if it's game over
            KGResetLegalMoveTables(KGglobalTransitionalLegalMoveTab, KGglobalFinalLegalMoveTab);
            KGIsGameOver();
        }
    }
    //Change the UI state based on action
    if (KGUISelectedTile == -1 && getFigureType(actionClickedTileIndex, KGg_FigurePlacement) != 'E' && getFigureType(actionClickedTileIndex, KGg_FigurePlacement) != 'X'){
        KGUISelectedTile = actionClickedTileIndex;
        KGResetLegalMoveTables(KGglobalTransitionalLegalMoveTab, KGglobalFinalLegalMoveTab);
        KGSetLegalMoves(KGUISelectedTile, KGglobalFinalLegalMoveTab, KGglobalTransitionalLegalMoveTab, KGg_FigurePlacement);
    }
    else if ((getFigureType(KGUISelectedTile, KGg_FigurePlacement) == 'E' || whoseTurn() != getFigureSide(KGUISelectedTile, KGg_FigurePlacement)) &&
       (getFigureType(actionClickedTileIndex, KGg_FigurePlacement) == 'E' || whoseTurn() != getFigureSide(actionClickedTileIndex, KGg_FigurePlacement)))
       KGUISelectedTile = -1;
    else if (KGUISelectedTile == actionClickedTileIndex)
        KGUISelectedTile = -1;
    else if ((getFigureType(actionClickedTileIndex, KGg_FigurePlacement) == 'E' || getFigureType(actionClickedTileIndex, KGg_FigurePlacement) == 'X') &&
              KGglobalFinalLegalMoveTab[actionClickedTileIndex] == 0)
        KGUISelectedTile = -1;
    //Draw the UI
    KGdrawUI(boardGrid, KGg_FigurePlacement, KGglobalFinalLegalMoveTab);
//    displayEngGameMessage(true);
    if(KGGameOver) displayEngGameMessage(KGGameWon);
}

void reverseLastMove(GtkWidget* menuButton, gpointer data){
    loadConfiguration();
    resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
    drawUI(chessBoardGrid, globalFigurePlacement, globalFinalLegalMoveTab);
}

void loadBoardConfigurationFromFile(GtkWidget* menuButton, gpointer data){
    GtkWidget * dialog;
    dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(SingleplayerGameWindow),GTK_FILE_CHOOSER_ACTION_OPEN, "Choose", GTK_RESPONSE_OK, "Cancel", GTK_RESPONSE_CANCEL,NULL);
    gtk_widget_show(dialog);
    gint resp = gtk_dialog_run(GTK_DIALOG(dialog));
    if(resp==GTK_RESPONSE_OK)
        loadConfigurationFromFile(gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog)));
    gtk_widget_destroy(dialog);
    resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
    drawUI(chessBoardGrid, globalFigurePlacement, globalFinalLegalMoveTab);
}

void saveBoardConfigurationToFile(GtkWidget* menuButton, gpointer data){
    saveConfigurationToFile();
}
