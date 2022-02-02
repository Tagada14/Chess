#include "chess.h"

GtkWidget* label;
GtkWidget* gameOverLabel;
GtkWidget* timer;
GtkWidget* playAgainButton;
GtkWidget* menuWindow;
GtkWidget* chessGameWindow = NULL;
GtkWidget* creditsWindow = NULL;
GtkWidget* knightGameWindow = NULL;
GtkWidget* chessBoardGrid;
GtkWidget* knightGameChessBoardGrid;
GtkWidget* KGplayAgainButton;
GtkWidget* KGgameOverLabel;
const int clock_time = 600;
int sec_expired;
int sec_expired_white;
int sec_expired_black;

void initializeMenuGrid(){
    for (int i = 0; i < 6; i++){
    menuGrid[i].posX = 0;
    menuGrid[i].posY = i;
    menuGrid[i].lenX = 1;
    menuGrid[i].lenY = 1;
    menuGrid[i].index = i;
    }
}

void initializeTabGrid(){
    for (int i = 0; i < 64; i++){
    tabGrid[i].posX = i % 8;
    tabGrid[i].posY = i / 8;
    tabGrid[i].lenX = 1;
    tabGrid[i].lenY = 1;
    tabGrid[i].index = i;
}
}

void exitWithButton( GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

void returnToMenu(GtkWidget* button, gpointer data){
    if (timer_id != 0){
        g_source_remove(timer_id);
        timer_id = 0;
    }
    GtkWidget* window = gtk_widget_get_toplevel(button);
    gtk_widget_show_all(menuWindow);
    gtk_widget_hide(window);
}

void chessGameOver(){
    if (timer_id != 0){
        g_source_remove(timer_id);
        timer_id = 0;
    }
    gtk_widget_set_name(gameOverLabel, "gameOverLabel");
    switch(gameResult){
        case 1:
            gtk_label_set_label(GTK_LABEL(gameOverLabel), "White's won!");
            break;
        case 2:
            gtk_label_set_label(GTK_LABEL(gameOverLabel), "Black's won!");
            break;
        case 3:
            gtk_label_set_label(GTK_LABEL(gameOverLabel), "It's a tie!");
            break;
        default:
            printf("Error in funtion chessGameOver");
            break;
    }
    resetUIState();
    resetBoardColors(chessBoardGrid);
    gtk_widget_show(playAgainButton);
}

void createCreditsWindow(){
    if (creditsWindow != NULL) return;
    creditsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(creditsWindow),"GTK - Credits");
    gtk_window_set_position(GTK_WINDOW(creditsWindow),GTK_WIN_POS_CENTER);
    gtk_container_set_border_width(GTK_CONTAINER(creditsWindow), 30);
    label = gtk_label_new("Made by Patryk Zielinski & Jan Buszka");
    gtk_container_add(GTK_CONTAINER(creditsWindow), label);
}

void createMenuWindow(){
    strcpy(menuGrid[0].name, "Singleplayer");
    strcpy(menuGrid[1].name, "Multiplayer");
    strcpy(menuGrid[2].name, "Knight Minigame");
    strcpy(menuGrid[3].name, "Options");
    strcpy(menuGrid[4].name, "Credits");
    strcpy(menuGrid[5].name, "Quit");
    menuWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(menuWindow),"GTK - Menu");
    gtk_window_set_position(GTK_WINDOW(menuWindow),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(menuWindow), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(menuWindow), 30);
    gtk_widget_set_name(menuWindow, "menuWindow");

    GtkWidget* box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_container_add(GTK_CONTAINER(menuWindow), box4);

    GtkWidget *grid2 = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid2), 25);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid2), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid2), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid2), TRUE);

    gtk_box_pack_start(GTK_BOX(box4), grid2, TRUE, TRUE, 0);
    GtkWidget* button2;
    for(int i = 0; i < 6; i++) {
        menuGrid[i].index = i;
        button2 = gtk_button_new_with_label(menuGrid[i].name);
        gtk_widget_set_name(button2, "menuButton");
        gtk_widget_set_size_request(button2, 500, 100);
        g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(menuHandler), (gpointer) &menuGrid[i].index);
        gtk_grid_attach(GTK_GRID(grid2), button2, menuGrid[i].posX, menuGrid[i].posY, menuGrid[i].lenX, menuGrid[i].lenY);
    }
}

void createKnightMGWindow(){
    if (knightGameWindow != NULL) return;
    knightGameWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(knightGameWindow),"GTK - Knight Minigame");
    gtk_window_set_position(GTK_WINDOW(knightGameWindow),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(knightGameWindow), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(knightGameWindow), 10);

    g_signal_connect(G_OBJECT(knightGameWindow), "destroy",G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget* mainBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* knightGameBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(knightGameWindow), mainBox);
    GtkWidget* buttonBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(mainBox), buttonBox);
    gtk_container_add(GTK_CONTAINER(mainBox), knightGameBox);
    knightGameChessBoardGrid = gtk_grid_new();
    GtkWidget* button;
    for(int i = 0; i < 64; i++) {
        tabGrid[i].index = i;
        button = gtk_button_new();
        gtk_widget_set_size_request(button, 100, 100);
        gtk_button_set_always_show_image(GTK_BUTTON(button),TRUE);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(knightGameEventHandler), (gpointer) &tabGrid[i].index);
        gtk_grid_attach(GTK_GRID(knightGameChessBoardGrid), button, tabGrid[i].posX, tabGrid[i].posY, tabGrid[i].lenX, tabGrid[i].lenY);
    }
    gtk_box_pack_start(GTK_BOX(knightGameBox), knightGameChessBoardGrid, TRUE, TRUE, 0);

    KGgameOverLabel = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(buttonBox), KGgameOverLabel, FALSE, FALSE, 0);

    KGplayAgainButton = gtk_button_new_with_label("Play again");
    g_signal_connect(G_OBJECT(KGplayAgainButton), "clicked",G_CALLBACK(KGplayAgain), NULL);
    gtk_widget_set_name(KGplayAgainButton, "standardButton");
    gtk_box_pack_start(GTK_BOX(buttonBox), KGplayAgainButton, TRUE, FALSE, 0);

    button = gtk_button_new_with_label("Quit");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(exitWithButton), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(buttonBox), button, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Return to Menu");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(returnToMenu), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(buttonBox), button, FALSE, FALSE, 0);
}

gboolean timer_update(gpointer data)
{
    if(sec_expired <= 0){
        gameOver = true;
        if (whoseTurn() == 'W') gameResult = 2;
        else if (whoseTurn() == 'B') gameResult = 1;
        else printf("Error in function timer_update");
        chessGameOver();
        return false;
    }
    GtkWidget* label = (GtkWidget*)data;
    char buf[256];
    memset(&buf, 0x0, 256);
    sec_expired--;
    if (sec_expired <= 60){
        gtk_widget_set_name(label, "Timercritical");
    }
    else gtk_widget_set_name(label, "Timer");
    snprintf(buf, 255, "%02d:%02d", (sec_expired)/60, sec_expired%60);
    gtk_label_set_label(GTK_LABEL(label), buf);
    return true;
}

void set_timer(gpointer data){
    GtkWidget* label = (GtkWidget*)data;
    char buf[256];
    memset(&buf, 0x0, 256);
    if (sec_expired <= 60){
        gtk_widget_set_name(label, "Timercritical");
    }
    else gtk_widget_set_name(label, "Timer");
    snprintf(buf, 255, "%02d:%02d", (sec_expired)/60, sec_expired%60);
    gtk_label_set_label(GTK_LABEL(label), buf);
}

void createChessGameWindow(){
    if (chessGameWindow != NULL) return;
    chessGameWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(chessGameWindow),"GTK - Chess");
    gtk_window_set_position(GTK_WINDOW(chessGameWindow),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(chessGameWindow), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(chessGameWindow), 10);

    g_signal_connect(G_OBJECT(chessGameWindow), "destroy",G_CALLBACK(gtk_main_quit), NULL);

    //box1 -> box for our grid
    GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //box2 -> box for left panel
    GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    //box2 -> box for all
    GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    gtk_box_set_homogeneous(GTK_BOX(box1),FALSE);
    gtk_box_set_homogeneous(GTK_BOX(box3),FALSE);
    gtk_box_pack_start(GTK_BOX(box3), box2, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box3), box1, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(chessGameWindow), box3);
    GtkWidget *button;

    label = gtk_label_new("White's Turn");
    gtk_widget_set_name(label, "standardLabel");
    gtk_box_pack_start(GTK_BOX(box2), label, FALSE, FALSE, 5);

    timer = gtk_label_new("00:00");
    gtk_widget_set_name(timer, "Timer");
    gtk_box_pack_start(GTK_BOX(box2), timer, FALSE, FALSE, 0);

    gameOverLabel = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(box2), gameOverLabel, FALSE, FALSE, 0);

    playAgainButton = gtk_button_new_with_label("Play again");
    g_signal_connect(G_OBJECT(playAgainButton), "clicked",G_CALLBACK(playAgain), NULL);
    gtk_widget_set_name(playAgainButton, "standardButton");
    gtk_box_pack_start(GTK_BOX(box2), playAgainButton, TRUE, FALSE, 0);

    chessBoardGrid = gtk_grid_new();

    gtk_grid_set_row_spacing(GTK_GRID(chessBoardGrid), 0);
    gtk_grid_set_row_homogeneous(GTK_GRID(chessBoardGrid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(chessBoardGrid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(chessBoardGrid), TRUE);

    gtk_box_pack_start(GTK_BOX(box1), chessBoardGrid, TRUE, TRUE, 0);


    for(int i = 0; i < 64; i++) {
        tabGrid[i].index = i;
        button = gtk_button_new();
        gtk_widget_set_size_request(button, 100, 100);
        gtk_button_set_always_show_image(GTK_BUTTON(button),TRUE);
        g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(eventHandler), (gpointer) &tabGrid[i].index);
        gtk_grid_attach(GTK_GRID(chessBoardGrid), button, tabGrid[i].posX, tabGrid[i].posY, tabGrid[i].lenX, tabGrid[i].lenY);
    }

    button = gtk_button_new_with_label("Quit");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(exitWithButton), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(box2), button, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Return to Menu");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(returnToMenu), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(box2), button, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Load Configuration");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(loadBoardConfigurationFromFile), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(box2), button, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Save Configuration");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(saveBoardConfigurationToFile), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(box2), button, FALSE, FALSE, 0);

    button = gtk_button_new_with_label("Undo move");
    g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(reverseLastMove), NULL);
    gtk_widget_set_name(button, "standardButton");
    gtk_box_pack_end(GTK_BOX(box2), button, FALSE, FALSE, 0);
}
