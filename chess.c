#include "chess.h"

int main( int argc,char *argv[]) {
gtk_init(&argc, &argv);
myCSS();
initializeTabGrid();
initializeMenuGrid();
createMenuWindow();
gtk_widget_show_all(menuWindow);
gtk_main();
return 0;
}
