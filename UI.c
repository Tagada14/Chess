#include "chess.h"

struct GTKmainGrid tabGrid[64];
struct GTKmenuGrid menuGrid[4];

void drawBoard (GtkWidget* grid, char figurePlacement[]){
    for (int i = 0; i < 64; i++){
        GtkWidget* button = gtk_grid_get_child_at(GTK_GRID(grid), tabGrid[i].posX, tabGrid[i].posY);
        GtkWidget* image = NULL;
        if (figurePlacement[i] == 'P') image = gtk_image_new_from_file ("icons//Chess_plt60.png");
        else if (figurePlacement[i] == 'p') image = gtk_image_new_from_file ("icons//Chess_pdt60.png");
        else if (figurePlacement[i] == 'S') image = gtk_image_new_from_file ("icons//Chess_nlt60.png");
        else if (figurePlacement[i] == 's') image = gtk_image_new_from_file ("icons//Chess_ndt60.png");
        else if (figurePlacement[i] == 'B') image = gtk_image_new_from_file ("icons//Chess_blt60.png");
        else if (figurePlacement[i] == 'b') image = gtk_image_new_from_file ("icons//Chess_bdt60.png");
        else if (figurePlacement[i] == 'R') image = gtk_image_new_from_file("icons//Chess_rlt60.png");
        else if (figurePlacement[i] == 'r') image = gtk_image_new_from_file("icons//Chess_rdt60.png");
        else if (figurePlacement[i] == 'Q') image = gtk_image_new_from_file("icons//Chess_qlt60.png");
        else if (figurePlacement[i] == 'q') image = gtk_image_new_from_file("icons//Chess_qdt60.png");
        else if (figurePlacement[i] == 'K') image = gtk_image_new_from_file("icons//Chess_klt60.png");
        else if (figurePlacement[i] == 'k') image = gtk_image_new_from_file("icons//Chess_kdt60.png");
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
        if (l % 2 == 0) gtk_widget_set_name(button, "bright");
        else gtk_widget_set_name(button, "dark");
    }
}

void drawLegalMoves(GtkWidget* boardGrid, int legalMoveTab[]){
    for (int i = 0; i < 64; i++){
        GtkWidget* button = gtk_grid_get_child_at(GTK_GRID(boardGrid), tabGrid[i].posX, tabGrid[i].posY);
        if(legalMoveTab[i] == 1){
            gtk_widget_set_name(button, "legalMove");
        }
        else if (legalMoveTab[i] == 2){
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

void KGdrawVisitedTiles(GtkWidget* grid, char figurePlacement[]){
    for (int i = 0; i < 64; i++){
        GtkWidget* button = gtk_grid_get_child_at(GTK_GRID(grid), tabGrid[i].posX, tabGrid[i].posY);
        if (figurePlacement[i] == 'X')
            gtk_widget_set_name(button, "tileVisited");
    }
}

void drawUI(GtkWidget* grid, char figurePlacement[], int legalMoveTab[]){
    drawBoard(grid, figurePlacement);
    resetBoardColors(grid);
    changeTurnLabel(label);
    if (UISelectedTile != -1){
        drawLegalMoves(grid, legalMoveTab);
    }
}

void KGdrawUI(GtkWidget* grid, char figurePlacement[], int legalMoveTab[]){
    drawBoard(grid, figurePlacement);
    resetBoardColors(grid);
    KGdrawVisitedTiles(grid, figurePlacement);
    if (KGUISelectedTile != -1){
        drawLegalMoves(grid, legalMoveTab);
    }
}
