#include "chess.h"

GtkWidget* label;
GtkWidget* menuWindow;
GtkWidget* SingleplayerGameWindow;
GtkWidget* creditsWindow;

static void exitWithButton( GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main( int argc,char *argv[]) {
gtk_init(&argc, &argv);
myCSS();

for (int i = 0; i < 64; i++){
    tabGrid[i].posX = i % 8;
    tabGrid[i].posY = i / 8;
    tabGrid[i].lenX = 1;
    tabGrid[i].lenY = 1;
    tabGrid[i].index = i;
}
for (int i = 0; i < 4; i++){
    menuGrid[i].posX = 0;
    menuGrid[i].posY = i;
    menuGrid[i].lenX = 1;
    menuGrid[i].lenY = 1;
    menuGrid[i].index = i;
}
//char* names = (char*)malloc(sizeof(char)*20);
//strcpy(names, "Singleplayer");
strcpy(menuGrid[0].name, "Singleplayer");
strcpy(menuGrid[1].name, "Multiplayer");
strcpy(menuGrid[2].name, "Options");
strcpy(menuGrid[3].name, "Credits");
startingLayout();

menuWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(menuWindow),"GTK - Menu");
gtk_window_set_position(GTK_WINDOW(menuWindow),GTK_WIN_POS_CENTER);
gtk_container_set_border_width(GTK_CONTAINER(menuWindow), 30);

GtkWidget* box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
gtk_container_add(GTK_CONTAINER(menuWindow), box4);

GtkWidget *grid2 = gtk_grid_new();

gtk_grid_set_row_spacing(GTK_GRID(grid2), 25);
gtk_grid_set_row_homogeneous(GTK_GRID(grid2), TRUE);
gtk_grid_set_column_spacing(GTK_GRID(grid2), 0);
gtk_grid_set_column_homogeneous(GTK_GRID(grid2), TRUE);

gtk_box_pack_start(GTK_BOX(box4), grid2, TRUE, TRUE, 0);

creditsWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(creditsWindow),"GTK - Credits");
gtk_window_set_position(GTK_WINDOW(creditsWindow),GTK_WIN_POS_CENTER);
gtk_container_set_border_width(GTK_CONTAINER(creditsWindow), 30);

label = gtk_label_new("Made by Patryk Zielinski & Jan Buszka");
gtk_container_add(GTK_CONTAINER(creditsWindow), label);

GtkWidget* button2;
for(int i = 0; i < 4; i++) {
    menuGrid[i].index = i;
    button2 = gtk_button_new_with_label(menuGrid[i].name);
    gtk_widget_set_name(button2, "menuButton");
    gtk_widget_set_size_request(button2, 300, 100);+
    g_signal_connect(G_OBJECT(button2), "clicked", G_CALLBACK(menuHandler), (gpointer) &menuGrid[i].index);
    gtk_grid_attach(GTK_GRID(grid2), button2, menuGrid[i].posX, menuGrid[i].posY, menuGrid[i].lenX, menuGrid[i].lenY);
}



SingleplayerGameWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(SingleplayerGameWindow),"GTK - Chess");
gtk_window_set_position(GTK_WINDOW(SingleplayerGameWindow),GTK_WIN_POS_CENTER);
gtk_container_set_border_width(GTK_CONTAINER(SingleplayerGameWindow), 10);

g_signal_connect(G_OBJECT(SingleplayerGameWindow), "destroy",G_CALLBACK(gtk_main_quit), NULL);

GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

gtk_box_set_homogeneous(GTK_BOX(box3),TRUE);
gtk_box_set_homogeneous(GTK_BOX(box1),FALSE);

gtk_box_pack_start(GTK_BOX(box1), box3, FALSE, FALSE, 0);

gtk_container_add(GTK_CONTAINER(SingleplayerGameWindow), box1);


label = gtk_label_new("White's Turn");
gtk_box_pack_start(GTK_BOX(box3), label, FALSE, FALSE, 0);


GtkWidget *grid = gtk_grid_new();

gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
gtk_grid_set_column_spacing(GTK_GRID(grid), 0);
gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);

gtk_box_pack_start(GTK_BOX(box1), grid, TRUE, TRUE, 0);

GtkWidget *button;
for(int i = 0; i < 64; i++) {
    tabGrid[i].index = i;
    button = gtk_button_new();
    gtk_widget_set_size_request(button, 100, 100);
    gtk_button_set_always_show_image(GTK_BUTTON(button),TRUE);
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(eventHandler), (gpointer) &tabGrid[i].index);
    gtk_grid_attach(GTK_GRID(grid), button, tabGrid[i].posX, tabGrid[i].posY, tabGrid[i].lenX, tabGrid[i].lenY);
}
drawBoard(grid);
resetBoardColors(grid);
GtkWidget *box2 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

button = gtk_button_new_with_label("Quit");
g_signal_connect(G_OBJECT(button), "clicked",G_CALLBACK(exitWithButton), NULL);


gtk_box_pack_start(GTK_BOX(box2), button, TRUE, FALSE, 0);

gtk_box_pack_start(GTK_BOX(box1), box2, FALSE, FALSE, 0);



gtk_widget_show_all(menuWindow);
gtk_main();
return 0;
}
