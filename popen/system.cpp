#include "system1.h"

int SystemHelper::SystemGetPopen(const char* command, char* out, int len){
    int iRet;
    FILE *stream;

    if (command == NULL){
        return 1;
    }

    memset(out, 0, len);
    stream = SystemPopen(command, "r");
    if (stream != NULL ){
        iRet = fread(out, sizeof(char), len, stream);
    }

    SystemPclose(stream);

    return iRet;
}


FILE *SystemHelper::SystemPopen(const char* command, const char* mode)
{
    FILE *fp = NULL;

    if (command == NULL){
        return NULL;
    }
    if (mode == NULL){
        return NULL;
    }

    fp = popen(command, mode);
    if (fp == NULL){
        return NULL;
    }

    return fp; 
}


int SystemHelper::SystemPclose(FILE *filestream)
{
    int iRet;

    if (filestream == NULL){
        return 1;        
    }

    iRet = pclose(filestream);
    if(iRet == -1){
        return 1;
    }

    return iRet;
}
