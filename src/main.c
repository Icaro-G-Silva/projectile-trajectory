#include "projectileCalc.c"
#include "fileManager.c"

#define PARAM_ERROR "Parameter input error"
#define VALUE_ERROR "Input value error"
#define FILE_ERROR "Error in file operation"

int getModeOption();
void simulateWithDrag(Axis projectileAxis, float velocity, float angle, float dragCoefficient, float crossSectionalArea, float mass, float time);
void simulateWithoutDrag(Axis projectileAxis, float velocity, float angle, float time);
void errorMessage(char message[], char title[]);
void verifyAngleInput(float angle);
void verifyNonNegativeInput(float value);
void plotValues(Axis axis, float time);
void plotGraphic();
void printLine(int size);

int main(int argc, char **argv) {
    int withDrag = 0; //Choose between different simulations
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
            withDrag = 1;
        }
        else if(argc == 4) {
            angle = atof(argv[1]);
            velocity = atof(argv[2]);
            initialHeight = atof(argv[3]);
            verifyAngleInput(angle);
            verifyNonNegativeInput(velocity);
            verifyNonNegativeInput(initialHeight);
        }
        else errorMessage("Check the number of parameters for the program call (3 - basic or 6 - advanced)", PARAM_ERROR);
    }
    else {
        withDrag = getModeOption();

        printf("Enter the shooting angle (degrees): ");
        scanf("%f", &angle);
        verifyAngleInput(angle);

        printf("Enter the initial shooting velocity (m/s): ");
        scanf("%f", &velocity);
        verifyNonNegativeInput(velocity);

        printf("Enter the initial height (m): ");
        scanf("%f", &initialHeight);
        verifyNonNegativeInput(initialHeight);

        if(withDrag) {
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
    }

    angle *= (PI/180); //transforms degrees in radians
    projectileAxis.x = 0.0;
    projectileAxis.y = initialHeight;

    if(!openFileStream()) errorMessage("Error opening file", FILE_ERROR);
    if(!writeHeader()) errorMessage("Error writing header", FILE_ERROR);
    if(withDrag) simulateWithDrag(projectileAxis, velocity, angle, dragCoefficient, crossSectionalArea, mass, time);
    else simulateWithoutDrag(projectileAxis, velocity, angle, time);
    if(!closeFileStream()) errorMessage("Error closing file", FILE_ERROR);

    plotGraphic();    
    return 0;
}

void simulateWithDrag(Axis projectileAxis, float velocity, float angle, float dragCoefficient, float crossSectionalArea, float mass, float time) {
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
        if(projectileAxis.y >= 0.00) {
            plotValues(projectileAxis, time);
            writeProjectileData(projectileAxis.x, projectileAxis.y, time);
        }
    }while(projectileAxis.y > 0.00);
}

void simulateWithoutDrag(Axis projectileAxis, float velocity, float angle, float time) {
    do {
        updateTime(&time);
        projectileAxis.x = getXaxis(getXaxisVelocity(velocity, angle), time);
        projectileAxis.y = getYaxis(getYaxisVelocity(velocity, angle), time);
        if(projectileAxis.y >= 0.00) {
            plotValues(projectileAxis, time);
            writeProjectileData(projectileAxis.x, projectileAxis.y, time);
        }
    }while(projectileAxis.y > 0.00);
}

int getModeOption() {
    printf("\nPROJECTILE TRAJECTORY SIMULATION\n\nChoose simulation mode:\n1. Basic (By a given initial velocity, angle and height get the simulation)\n2. Advanced (Simulation With Drag Force)\n\n->");
    int option;
    scanf("%d", &option);
    if(option == 1) return 0;
    if(option == 2) return 1;
    else {
        errorMessage("Check the entry of the simulation mode (Need to be 1 or 2)", VALUE_ERROR);
        return -1;
    }
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
