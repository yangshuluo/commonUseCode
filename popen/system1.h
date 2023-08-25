#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <unistd.h>
#include <stdio.h>
#include <string.h>


class SystemHelper {
public: 
    static int SystemGetPopen(const char* command, char* out, int len);
    static FILE *SystemPopen(const char* command, const char* mode);
    static int SystemPclose(FILE *filestream);
};

#endif