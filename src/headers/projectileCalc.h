#ifndef PROJECTILECALC_H
#define PROJECTILECALC_H

#define TIME_INCREMENT 0.01 //time in seconds
#define PI 3.1415 //PI
#define GRAVITY 9.81 //ms²
#define AIR_DENSITY 1.1515 //air density (Campinas) in kg/m³
#define MAX_ANGLE 90 //angle in degrees
#define MAX_ANGLE_RADIANS (MAX_ANGLE * (PI/180)) //angle in radians

struct AxisStruct; //struct for the projectile axis
typedef struct AxisStruct
{
    float x;
    float y;
} Axis;

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
 * Function: getCombinedVelocity
 * @param xAxisVelocity launch velocity || initial velocity (Vo)
 * @param yAxisVelocity launch angle in radians
 * @return float
*/
float getCombinedVelocity(float xAxisVelocity, float yAxisVelocity);
/**
 * Function: getDrag
 * @param combinedVelocity combined X and Y axis velocity
 * @param dragCoefficient projectile drag coefficient
 * @param crossSectionalArea projectile cross-sectional area
 * @return float
*/
float getDrag(float combinedVelocity, float dragCoefficient, float crossSectionalArea);
/**
 * Function: getXAcceleration
 * @param drag projectile drag
 * @param mass projectile mass
 * @return float
*/
float getXAcceleration(float drag, float mass);
/**
 * Function: getYAcceleration
 * @param drag projectile drag
 * @param mass projectile mass
 * @return float
*/
float getYAcceleration(float drag, float mass);
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
 * Function: simulateWithDrag
 * @param projectileAxis projectile axis struct
 * @param velocity initial velocity
 * @param angle initial angle
 * @param dragCoefficient drag coefficient
 * @param crossSectionalArea cross-sectional area
 * @param mass weight
 * @param time time
 * @return void
*/
void simulateWithDrag(Axis projectileAxis, float velocity, float angle, float dragCoefficient, float crossSectionalArea, float mass, float time);
/**
 * Function: simulateWithoutDrag
 * @param projectileAxis projectile axis struct
 * @param velocity initial velocity
 * @param angle initial angle
 * @param time time
 * @return void
*/
void simulateWithoutDrag(Axis projectileAxis, float velocity, float angle, float time);
/**
 * Function: getFinalXpositionWithDrag
 * @param projectileAxis projectile axis struct
 * @param velocity initial velocity
 * @param angle initial angle
 * @param dragCoefficient drag coefficient
 * @param crossSectionalArea cross-sectional area
 * @param mass weight
 * @param time time
 * @param finalXposition final x axis position
 * @return void
*/
void getFinalXpositionWithDrag(Axis projectileAxis, float velocity, float angle, float dragCoefficient, float crossSectionalArea, float mass, float time, float *finalXposition);
/**
 * Function: getTargetWithDrag
 * @param projectileAxis projectile axis struct
 * @param dragCoefficient drag coefficient
 * @param crossSectionalArea cross-sectional area
 * @param mass weight
 * @param time time
 * @param targetDistance target distance
 * @return void
*/
void getTargetWithDrag(Axis projectileAxis, float dragCoefficient, float crossSectionalArea, float mass, float time, float targetDistance);
/**
 * Function: getFinalXpositionWithoutDrag
 * @param projectileAxis projectile axis struct
 * @param velocity initial velocity
 * @param angle initial angle
 * @param time time
 * @param finalXposition final x axis position
 * @return void
*/
void getFinalXpositionWithoutDrag(Axis projectileAxis, float velocity, float angle, float time, float *finalXposition);
/**
 * Function: getTargetWithoutDrag
 * @param projectileAxis projectile axis struct
 * @param time time
 * @param targetDistance target distance
 * @return void
*/
void getTargetWithoutDrag(Axis projectileAxis, float time, float targetDistance);
/**
 * Function: updateTime -> do the addition of time
 * @param time pointer to the actual time spent
 * @return void
*/
void updateTime(float *time);
/**
 * Function: plotValues
 * @param axis axis struct
 * @param time actual time spent
 * @return void
*/
void plotValues(Axis axis, float time);

#endif