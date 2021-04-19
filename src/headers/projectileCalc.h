#ifndef PROJECTILECALC_H
#define PROJECTILECALC_H
#include "common.h"

#define TIME_INCREMENT 0.01 //time in seconds
#define MAX_ANGLE 90 //angle in degrees
#define MAX_ANGLE_RADIANS (MAX_ANGLE * (PI/180)) //angle in radians

struct AxisStruct; //struct for the projectile axis

/**
 * Function: getXaxisVelocity
 * @param velocity launch velocity || initial velocity (Vo)
 * @param angle launch angle in radians
 * @return float
*/
float getXaxisVelocity(float velocity, float angle);
/**
 * Function: getYaxisVelocity
 * @param velocity launch velocity || initial velocity (Vo)
 * @param angle launch angle in radians
 * @return float
*/
float getYaxisVelocity(float velocity, float angle);
/**
 * Function: getXaxis
 * @param xAxisVelocity x axis velocity
 * @param time actual time spent
 * @return float
*/
float getXaxis(float xAxisVelocity, float time);
/**
 * Function: getYaxis
 * @param yAxisVelocity y axis velocity
 * @param time actual time spent
 * @return float
*/
float getYaxis(float yAxisVelocity, float time);
/**
 * Function: updateTime -> do the addition of time
 * @param time pointer to the actual time spent
 * @return void
*/
void updateTime(float *time);

#endif