#include "headers/projectileCalc.h"

typedef struct AxisStruct
{
    float x;
    float y;
} Axis;

float getXaxisVelocity(float velocity, float angle) {
    return (velocity * cosf(angle));
}

float getYaxisVelocity(float velocity, float angle) {
    return (velocity * sinf(angle));
}

float getXaxis(float xAxisVelocity, float time) {
    return xAxisVelocity * time;
}

float getYaxis(float yAxisVelocity, float time) {
    return (yAxisVelocity * time) + (0.5 * (GRAVITY * -1) * (time*time));
}

void updateTime(float *time) {
    *time += TIME_INCREMENT;
}
