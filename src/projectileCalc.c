#include "headers/projectileCalc.h"
#include "headers/fileManager.h"
#include "common.c"

float getXaxisVelocity(float velocity, float angle) {
    return (velocity * cosf(angle));
}

float getYaxisVelocity(float velocity, float angle) {
    return (velocity * sinf(angle));
}

float getCombinedVelocity(float xAxisVelocity, float yAxisVelocity) {
    return sqrt((xAxisVelocity * xAxisVelocity) + (yAxisVelocity * yAxisVelocity));
}

float getDrag(float combinedVelocity, float dragCoefficient, float crossSectionalArea) {
    return 0.5 * dragCoefficient * AIR_DENSITY * crossSectionalArea * (combinedVelocity * combinedVelocity);
}

float getXAcceleration(float drag, float mass) {
    return -drag / mass;
}

float getYAcceleration(float drag, float mass) {
    return -GRAVITY - (drag / mass);
}

float getXaxis(float xAxisVelocity, float time) {
    return xAxisVelocity * time;
}

float getYaxis(float yAxisVelocity, float time) {
    return (yAxisVelocity * time) + (0.5 * (GRAVITY * -1) * (time*time));
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

void getFinalXpositionWithDrag(Axis projectileAxis, float velocity, float angle, float dragCoefficient, float crossSectionalArea, float mass, float time, float *finalXposition) {
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
    }while(projectileAxis.y > 0.00);
    *finalXposition = projectileAxis.x;
}

void getTargetWithDrag(Axis projectileAxis, float dragCoefficient, float crossSectionalArea, float mass, float time, float targetDistance) {
    float bestInitialVelocity = 0.0;
    float bestInitialAngle = 0.0;
    float closestDistance = 999999.9;

    for (float initialVelocity = 0.1; initialVelocity <= 100.0; initialVelocity += 0.1) { 
        for (float initialAngle = 0.0; initialAngle <= PI / 2; initialAngle += PI / 180) {
            float finalXposition;
            getFinalXpositionWithDrag(projectileAxis, initialVelocity, initialAngle, dragCoefficient, crossSectionalArea, mass, time, &finalXposition);

            if (fabs(finalXposition - targetDistance) < closestDistance) {
                closestDistance = fabs(finalXposition - targetDistance);
                bestInitialVelocity = initialVelocity;
                bestInitialAngle = initialAngle;
            }
        }
    }

    simulateWithDrag(projectileAxis, bestInitialVelocity, bestInitialAngle, dragCoefficient, crossSectionalArea, mass, time);
    printf("\nInitial velocity: %.2f m/s\n", bestInitialVelocity);
    printf("Initial angle: %.2f degrees\n", bestInitialAngle * (180.0 / PI));
}

void getFinalXpositionWithoutDrag(Axis projectileAxis, float velocity, float angle, float time, float *finalXposition) {
    do {
        updateTime(&time);
        projectileAxis.x = getXaxis(getXaxisVelocity(velocity, angle), time);
        projectileAxis.y = getYaxis(getYaxisVelocity(velocity, angle), time);
    }while(projectileAxis.y > 0.00);
    *finalXposition = projectileAxis.x;
}

void getTargetWithoutDrag(Axis projectileAxis, float time, float targetDistance) {
    float bestInitialVelocity = 0.0;
    float bestInitialAngle = 0.0;
    float closestDistance = 999999.9;

    for (float initialVelocity = 0.1; initialVelocity <= 100.0; initialVelocity += 0.1) { 
        for (float initialAngle = 0.1; initialAngle <= PI / 2; initialAngle += PI / 180) {
            float finalXposition;
            getFinalXpositionWithoutDrag(projectileAxis, initialVelocity, initialAngle, time, &finalXposition);

            if (fabs(finalXposition - targetDistance) < closestDistance) {
                closestDistance = fabs(finalXposition - targetDistance);
                bestInitialVelocity = initialVelocity;
                bestInitialAngle = initialAngle;
            }
        }
    }

    simulateWithoutDrag(projectileAxis, bestInitialVelocity, bestInitialAngle, time);
    printf("\nInitial velocity: %.2f m/s\n", bestInitialVelocity);
    printf("Initial angle: %.2f degrees\n", bestInitialAngle * (180.0 / PI));
}

void updateTime(float *time) {
    *time += TIME_INCREMENT;
}

void plotValues(Axis axis, float time) {
    printLine(30);
    printf("\n\nFor the time: %.2fs\nx: %.3fm\ty: %.3fm\n\n", time, axis.x, axis.y);
    printLine(30);
}
