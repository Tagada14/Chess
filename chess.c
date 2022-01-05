#include "chess.h"

GtkWidget* label;

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
startingLayout();

GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_title(GTK_WINDOW(window),"GTK - Chess");
gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
gtk_container_set_border_width(GTK_CONTAINER(window), 10);

g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(gtk_main_quit), NULL);

GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
GtkWidget *box3 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

gtk_box_set_homogeneous(GTK_BOX(box3),TRUE);
gtk_box_set_homogeneous(GTK_BOX(box1),FALSE);

gtk_box_pack_start(GTK_BOX(box1), box3, FALSE, FALSE, 0);

gtk_container_add(GTK_CONTAINER(window), box1);


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
    gtk_widget_set_size_request(button, 150, 150);
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
gtk_widget_show_all(window);
gtk_main();
return 0;
}
