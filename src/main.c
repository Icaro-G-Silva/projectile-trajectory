#include "projectileCalc.c"
#include "fileManager.c"

#define PARAM_ERROR "Parameter input error"
#define VALUE_ERROR "Input value error"
#define FILE_ERROR "Error in file operation"

void errorMessage(char message[], char title[]);
void verifyAngleInput(float angle);
void verifyNonNegativeInput(float value);
void plotValues(Axis axis, float time);
void plotGraphic();
void printLine(int size);

int main(int argc, char **argv) {
    float angle, velocity, initialHeight, mass, dragCoefficient, crossSectionalArea; //User input
    float time = 0.0;
    Axis projectileAxis; //struct for the projectile axis

    if(argc > 1) {
        if(argc == 7) {
            angle = atof(argv[1]);
            velocity = atof(argv[2]);
            initialHeight = atof(argv[3]);
            mass = atof(argv[4]);
            dragCoefficient = atof(argv[5]);
            crossSectionalArea = atof(argv[6]);
            verifyAngleInput(angle);
            verifyNonNegativeInput(velocity);
            verifyNonNegativeInput(initialHeight);
            verifyNonNegativeInput(mass);
            verifyNonNegativeInput(dragCoefficient);
            verifyNonNegativeInput(crossSectionalArea);
        }
        else errorMessage("Check the minimum number of parameters for the program call", PARAM_ERROR);
    }
    else {
        printf("Enter the shooting angle (degrees): ");
        scanf("%f", &angle);
        verifyAngleInput(angle);

        printf("Enter the initial shooting velocity (m/s): ");
        scanf("%f", &velocity);
        verifyNonNegativeInput(velocity);

        printf("Enter the initial height (m): ");
        scanf("%f", &initialHeight);
        verifyNonNegativeInput(initialHeight);

        printf("Enter the mass (kg): ");
        scanf("%f", &mass);
        verifyNonNegativeInput(mass);

        printf("Enter the drag coefficient: ");
        scanf("%f", &dragCoefficient);
        verifyNonNegativeInput(dragCoefficient);

        printf("Enter the cross-sectional area (m^2): ");
        scanf("%f", &crossSectionalArea);
        verifyNonNegativeInput(crossSectionalArea);
    }

    angle *= (PI/180); //transforms degrees in radians

    if(!openFileStream()) errorMessage("Error opening file", FILE_ERROR);
    if(!writeHeader()) errorMessage("Error writing header", FILE_ERROR);
    projectileAxis.y = initialHeight;
    float xVelocity = getXaxisVelocity(velocity, angle);
    float yVelocity = getYaxisVelocity(velocity, angle);
    do {
        updateTime(&time);
        float combinedVelocity = getCombinedVelocity(xVelocity, yVelocity);
        float dragForce = getDrag(combinedVelocity, dragCoefficient, crossSectionalArea);
        float xAcceleration = getXAcceleration(dragForce, mass);
        float yAcceleration = getYAcceleration(dragForce, mass);
        xVelocity += xAcceleration * TIME_INCREMENT;
        yVelocity += yAcceleration * TIME_INCREMENT;
        projectileAxis.x += xVelocity * TIME_INCREMENT;
        projectileAxis.y += yVelocity * TIME_INCREMENT;
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
    if(angle < 0 || angle > MAX_ANGLE) errorMessage("Check the entry of the starting angle (Need to be between 0 and 90)", VALUE_ERROR);
}

void verifyNonNegativeInput(float value) {
    if(value < 0.0) errorMessage("Check the entry of the values. Ensure to not have any negative values", VALUE_ERROR);
}
