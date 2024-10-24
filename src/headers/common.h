#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>

#define PARAM_ERROR "Parameter input error"
#define VALUE_ERROR "Input value error"
#define FILE_ERROR "Error in file operation"

/**
 * Function: printLine
 * @param size amount of line
 * @return void
*/
void printLine(int size);
/**
 * Function: plotGraphic
 * @return void
*/
void plotGraphic();
/**
 * Function: errorMessage
 * @param message message string
 * @param title title string
 * @return void
*/
void errorMessage(char message[], char title[]);

#endif