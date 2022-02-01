#include "chess.h"

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
for (int i = 0; i < 5; i++){
    menuGrid[i].posX = 0;
    menuGrid[i].posY = i;
    menuGrid[i].lenX = 1;
    menuGrid[i].lenY = 1;
    menuGrid[i].index = i;
}
createMenuWindow();
gtk_widget_show_all(menuWindow);
gtk_main();
return 0;
}
