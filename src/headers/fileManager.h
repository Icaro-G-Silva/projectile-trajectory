#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include "common.h"
#include <string.h>
#include <stdbool.h>
#include <direct.h>

#define BUFFER_SIZE 100 //max buffer size
char buffer[BUFFER_SIZE]; //buffer for directory
#define CURRENT_DIR _getcwd(buffer, BUFFER_SIZE) //current directory according to the executable

FILE *file; //file pointer

/**
 * Function: openFileStream
 * @return bool
*/
bool openFileStream();
/**
 * Function: closeFileStream
 * @return bool
*/
bool closeFileStream();
/**
 * Function: writeProjectileData
 * @param xAxis x axis value
 * @param yAxis y axis value
 * @param time actual time spent
 * @return bool
*/
bool writeProjectileData(float xAxis, float yAxis, float time);
/**
 * Function: writeHeader
 * @return bool
*/
bool writeHeader();

#endif
