#include "headers/fileManager.h"

bool openFileStream() {
    char fileName[BUFFER_SIZE];
    sprintf(fileName, strcat(CURRENT_DIR, "\\..\\files\\%s"), "projectile.csv");
    file = fopen(fileName, "w");
    if(file == NULL) return false;
    else return true;
}

bool closeFileStream() {
    if(fclose(file) != 0) return false;
    else return true;
}

bool writeProjectileData(float xAxis, float yAxis, float time) {
    if(fprintf(file, "%.2f;%.3f;%.3f\n", time, xAxis, yAxis) < 0) return false;
    else return true;
}

bool writeHeader() {
    if(fprintf(file, "time;distance;height\n") < 0) return false;
    else return true;
}
