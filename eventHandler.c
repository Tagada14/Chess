#include "chess.h"

bool start_clock = false;
guint timer_id = 0;


void chessGameLoadingSequence(){
    startingChessLayout();
    resetGameState();
    resetUIState();
    sec_expired = clock_time;
    sec_expired_white = clock_time;
    sec_expired_black = clock_time;
    set_timer(timer);
    resetBoardColors(chessBoardGrid);
    drawBoard(chessBoardGrid, globalFigurePlacement);
    changeTurnLabel(label);
    gtk_widget_hide(playAgainButton);
    gtk_widget_set_name(gameOverLabel,"");
    gtk_label_set_label(GTK_LABEL(gameOverLabel),"");
    gtk_test_widget_wait_for_draw(chessBoardGrid);
}

void playAgain(){
    chessGameLoadingSequence();
}

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
            if (AI_on == false){
                iFrom = UISelectedTile;
                iWhere = actionClickedTileIndex;
                changeTurnTimers();
            }
            lastMoveOrigin = UISelectedTile;
            roundCounter++;
            //start the clock
            if (roundCounter == 1) timer_id = g_timeout_add_seconds(1, timer_update, timer);
            //Check if it's game over
            resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
            isGameOver();
            if(gameOver){
                chessGameOver();
            }
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
            for(int i = 0; i < 5; i++) gtk_test_widget_wait_for_draw(boardGrid);
            double x = minmax(0, globalFigurePlacement, 0, 0,0, (double)INT_MIN, (double)INT_MAX-1.0);
        }
    }
    drawUI(boardGrid, globalFigurePlacement, globalFinalLegalMoveTab);
}

void menuHandler (GtkWidget* menuButton, gpointer data){
    gint* i = (gint*)data;
    int menuTileIndex = (int)*i;
    if (menuTileIndex == 0){
        createChessGameWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(chessGameWindow);
        chessGameLoadingSequence();
        wagesUpdate();
        AI_on = true;
    }
    else if (menuTileIndex == 1){
        createChessGameWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(chessGameWindow);
        chessGameLoadingSequence();
        AI_on = false;
    }
    else if (menuTileIndex == 2){
        createKnightMGWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(knightGameWindow);
        KGLoadingSequence();
    }
    else if (menuTileIndex == 3){
        createCreditsWindow();
        gtk_widget_hide(menuWindow);
        gtk_widget_show_all(creditsWindow);
    }
    else if (menuTileIndex == 4){
        gtk_main_quit();
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
            if(KGGameOver){
                KGGameEnd();
            }
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

void reverseLastMove(GtkWidget* menuButton, gpointer data){
    loadConfiguration();
    resetLegalMoveTables(globalTransitionalLegalMoveTab, globalFinalLegalMoveTab);
    drawUI(chessBoardGrid, globalFigurePlacement, globalFinalLegalMoveTab);
}

void loadBoardConfigurationFromFile(GtkWidget* menuButton, gpointer data){
    GtkWidget * dialog;
    dialog = gtk_file_chooser_dialog_new("Choose a file", GTK_WINDOW(chessGameWindow),GTK_FILE_CHOOSER_ACTION_OPEN, "Choose", GTK_RESPONSE_OK, "Cancel", GTK_RESPONSE_CANCEL,NULL);
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
