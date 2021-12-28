#include "chess.h"
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct GTKmainGrid tabGrid[64];

void drawBoard (GtkWidget* grid){
    for (int i = 0; i < 64; i++){
        GtkWidget* button = gtk_grid_get_child_at(GTK_GRID(grid), tabGrid[i].posX, tabGrid[i].posY);
        GtkWidget* image = NULL;
        if (globalFigurePlacement[i] == 'P') image = gtk_image_new_from_file ("icons//Chess_plt60.png");
        else if (globalFigurePlacement[i] == 'p') image = gtk_image_new_from_file ("icons//Chess_pdt60.png");
        else if (globalFigurePlacement[i] == 'S') image = gtk_image_new_from_file ("icons//Chess_nlt60.png");
        else if (globalFigurePlacement[i] == 's') image = gtk_image_new_from_file ("icons//Chess_ndt60.png");
        else if (globalFigurePlacement[i] == 'B') image = gtk_image_new_from_file ("icons//Chess_blt60.png");
        else if (globalFigurePlacement[i] == 'b') image = gtk_image_new_from_file ("icons//Chess_bdt60.png");
        else if (globalFigurePlacement[i] == 'R') image = gtk_image_new_from_file("icons//Chess_rlt60.png");
        else if (globalFigurePlacement[i] == 'r') image = gtk_image_new_from_file("icons//Chess_rdt60.png");
        else if (globalFigurePlacement[i] == 'Q') image = gtk_image_new_from_file("icons//Chess_qlt60.png");
        else if (globalFigurePlacement[i] == 'q') image = gtk_image_new_from_file("icons//Chess_qdt60.png");
        else if (globalFigurePlacement[i] == 'K') image = gtk_image_new_from_file("icons//Chess_klt60.png");
        else if (globalFigurePlacement[i] == 'k') image = gtk_image_new_from_file("icons//Chess_kdt60.png");
        if (image != NULL) gtk_button_set_image(GTK_BUTTON(button), image);
        else gtk_button_set_image(GTK_BUTTON(button), NULL);
    }
}

void resetBoardColors(GtkWidget* grid){
    int l = 0;
    for (int j = 0; j < 64; j ++){
        if (j % 8 == 0) l++;
        l++;
        GtkWidget* button = gtk_grid_get_child_at(GTK_GRID(grid), tabGrid[j].posX, tabGrid[j].posY);
        if (l % 2 == 0) gtk_widget_set_name(button, "dark");
        else gtk_widget_set_name(button, "bright");
    }
}

void drawLegalMoves(GtkWidget* boardGrid){
    for (int i = 0; i < 64; i++){
        GtkWidget* button = gtk_grid_get_child_at(GTK_GRID(boardGrid), tabGrid[i].posX, tabGrid[i].posY);
        if(globalFinalLegalMoveTab[i] == 1){
            gtk_widget_set_name(button, "legalMove");
        }
        else if (globalFinalLegalMoveTab[i] == 2){
            gtk_widget_set_name(button, "legalMoveKill");
        }
    }
}

void myCSS(void){
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    provider = gtk_css_provider_new ();
    display = gdk_display_get_default ();
    screen = gdk_display_get_default_screen (display);
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    const gchar *myCssFile = "mystyle.css";
    GError *error = 0;

    gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
    g_object_unref (provider);
}

void changeTurnLabel(GtkWidget* label){
    if (whoseTurn() == 'B') gtk_label_set_text(GTK_LABEL(label), "Black's Turn");
    else gtk_label_set_text(GTK_LABEL(label), "White's Turn");
}

void drawUI(GtkWidget* grid){
    drawBoard(grid);
    resetBoardColors(grid);
    changeTurnLabel(label);
    if (UISelectedTile != -1){
        drawLegalMoves(grid);
    }
}
