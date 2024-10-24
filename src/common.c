#include "headers/common.h"

void printLine(int size) {
    for(int column = 0; column <= size; column++) printf("-");
}

void plotGraphic() {
    printf("\n\nPress any key to visualize the plotted graph.\n");
    getch();
    system("cmd /c python plotGraphic.py");
}

void errorMessage(char message[], char title[]) {
    printLine(25);
    printf("\nERROR\n\n%s\n%s\n\n", title, message);
    printLine(25);
    getch();
    exit(0);
}
