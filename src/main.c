#include "projectileCalc.c"
#include "fileManager.c"

#define TARGET_MESSAGE "\nPROJECTILE TRAJECTORY SIMULATION\n\nChoose target mode:\n1. Trajectory without target\n2. Trajectory with target\n\n->"
#define MODE_MESSAGE "\n\nChoose simulation mode:\n1. Basic\n2. Advanced (Simulation With Drag Force)\n\n->"

int getModeOption();
void verifyAngleInput(float angle);
void verifyNonNegativeInput(float value);

int main(int argc, char **argv) {
    int withDrag = 0, targetAcquire = 0; //Choose between different simulations
    float angle = 0.0, velocity, initialHeight, mass, dragCoefficient, crossSectionalArea, targetDistance; //User input
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
        else if(argc == 6) {
            targetDistance = atof(argv[1]);
            initialHeight = atof(argv[2]);
            mass = atof(argv[3]);
            dragCoefficient = atof(argv[4]);
            crossSectionalArea = atof(argv[5]);
            verifyNonNegativeInput(targetDistance);
            verifyNonNegativeInput(initialHeight);
            verifyNonNegativeInput(mass);
            verifyNonNegativeInput(dragCoefficient);
            verifyNonNegativeInput(crossSectionalArea);
            withDrag = 1;
            targetAcquire = 1;
        }
        else if(argc == 4) {
            angle = atof(argv[1]);
            velocity = atof(argv[2]);
            initialHeight = atof(argv[3]);
            verifyAngleInput(angle);
            verifyNonNegativeInput(velocity);
            verifyNonNegativeInput(initialHeight);
        }
        else if(argc == 3) {
            targetDistance = atof(argv[1]);
            initialHeight = atof(argv[2]);
            verifyNonNegativeInput(targetDistance);
            verifyNonNegativeInput(initialHeight);
            targetAcquire = 1;
        }
        else errorMessage("Check the number of parameters for the program call (2 - basic with target | 3 - basic | 5 - advanced with target | 6 - advanced)", PARAM_ERROR);
    }
    else {
        targetAcquire = getModeOption(TARGET_MESSAGE);
        withDrag = getModeOption(MODE_MESSAGE);

        if(!targetAcquire) {
            printf("Enter the shooting angle (degrees): ");
            scanf("%f", &angle);
            verifyAngleInput(angle);

            printf("Enter the initial shooting velocity (m/s): ");
            scanf("%f", &velocity);
            verifyNonNegativeInput(velocity);
        }
        else {
            printf("Enter the target distance (m): ");
            scanf("%f", &targetDistance);
            verifyNonNegativeInput(targetDistance);
        }

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

    if(withDrag && !targetAcquire) simulateWithDrag(projectileAxis, velocity, angle, dragCoefficient, crossSectionalArea, mass, time);
    else if(!withDrag && !targetAcquire) simulateWithoutDrag(projectileAxis, velocity, angle, time);
    if(withDrag && targetAcquire) getTargetWithDrag(projectileAxis, dragCoefficient, crossSectionalArea, mass, time, targetDistance);
    else if(!withDrag && targetAcquire) getTargetWithoutDrag(projectileAxis, time, targetDistance);
    if(!closeFileStream()) errorMessage("Error closing file", FILE_ERROR);

    plotGraphic();    
    return 0;
}

int getModeOption(char message[]) {
    printf(message);
    int option;
    scanf("%d", &option);
    if(option == 1) return 0;
    if(option == 2) return 1;
    else {
        errorMessage("Check the entry of the simulation mode (Need to be 1 or 2)", VALUE_ERROR);
        return -1;
    }
}

void verifyAngleInput(float angle) {
    if(angle < 0 || angle > MAX_ANGLE) errorMessage("Check the entry of the starting angle (Need to be between 0 and 90)", VALUE_ERROR);
}

void verifyNonNegativeInput(float value) {
    if(value < 0.0) errorMessage("Check the entry of the values. Ensure to not have any negative values", VALUE_ERROR);
}
