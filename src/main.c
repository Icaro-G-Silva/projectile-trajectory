/*
    Um projétil é atirado com uma velocidade inicial Vo(m/s) a um ângulo de inclinação θ(radianos)

    Onde: 0<θ<90 e g=9.81ms²

    Faça um programa que, dados os parâmetros θ e Vo, liste as coordenadas x e y no plano vertical em intervalos de 0.01 segundos para um tiro
    em particular, terminando a listagem quando o projétil atingir o solo.
*/

#include "projectileCalc.c"
#include "fileManager.c"

#define PARAM_ERROR "Parameter input error"
#define VALUE_ERROR "Input value error"
#define FILE_ERROR "Error in file operation"

void errorMessage(char message[], char title[]);
void verifyAngleInput(float angle);
void plotValues(Axis axis, float time);
void plotGraphic();
void printLine(int size);

int main(int argc, char **argv) {
    float angle, velocity; //User input
    float time = 0.0;
    Axis projectileAxis; //struct for the projectile axis

    if(argc > 1) {
        if(argc == 3) {
            angle = atof(argv[1]);
            velocity = atof(argv[2]);
            verifyAngleInput(angle);
        }
        else errorMessage("Check the minimum number of parameters for the program call", PARAM_ERROR);
    }
    else {
        printf("Enter the shooting angle (in degrees): ");
        scanf("%f", &angle);
        verifyAngleInput(angle);

        printf("Enter the initial shooting velocity (in m/s): ");
        scanf("%f", &velocity);
    }

    angle *= (PI/180); //transforms degrees in radians

    if(!openFileStream()) errorMessage("Error opening file", FILE_ERROR);
    if(!writeHeader()) errorMessage("Error writing header", FILE_ERROR);
    do {
        updateTime(&time);
        projectileAxis.x = getXaxis(getXaxisVelocity(velocity, angle), time);
        projectileAxis.y = getYaxis(getYaxisVelocity(velocity, angle), time);
        if(projectileAxis.y >= 0.0) {
            plotValues(projectileAxis, time);
            writeProjectileData(projectileAxis.x, projectileAxis.y, time);
        }
    }while(projectileAxis.y > 0.0);
    if(!closeFileStream()) errorMessage("Error closing file", FILE_ERROR);

    plotGraphic();    
    return 0;
}

void plotValues(Axis axis, float time) {
    printLine(30);
    printf("\n\nFor the time: %.2fs\nx: %.3fm\ty: %.3fm\n\n", time, axis.x, axis.y);
    printLine(30);
}

void plotGraphic() {
    printf("\n\nPress any key to visualize the plotted graph.\n");
    getch();
    system("cmd /c python plotGraphic.py");
}

void printLine(int size) {
    for(int column = 0; column <= size; column++) printf("-");
}

void errorMessage(char message[], char title[]) {
    printLine(25);
    printf("\nERROR\n\n%s\n%s\n\n", title, message);
    printLine(25);
    getch();
    exit(0);
}

void verifyAngleInput(float angle) {
    if(angle < 0 || angle > MAX_ANGLE) errorMessage("Check the entry of the starting angle", VALUE_ERROR);
}
