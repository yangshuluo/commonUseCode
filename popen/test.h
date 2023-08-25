#pragma once

#include <cstring>
#include <string.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <linux/input.h>
#include <limits.h>
#include "system1.h"
#include <iostream>
#include <string>
#include <event2/event.h>
#include <thread>
#include <termio.h>
#include <stdio.h>
#include <termio.h>
 

#define SCREEN_KEY_STATUS       "isAllScreen"  //是否全屏
#define KEYBOARD_MOUSE_KEY_OPERATETIME        "lastOperateTime"  //最后操作时间
#define KEY_BOARE_EVENT          "/dev/input/"  //键鼠事件目录 
#define Mouse_MICE_EVENT        "/dev/input/mice"  //鼠标事件
#define BUS_INPUT_DEVICE        "/proc/bus/input/devices" //查看设备使用
#define WINDOWID    "0x6e00006"

class CLastOperateTime
{
public:
    CLastOperateTime();
    ~CLastOperateTime();

public:
    int GetStopOperateTimeInterval() const;  
    bool GetIsAllScreen() const;
    int GetSystemTime2Sec() const;
    void appIsAllScreen(); //判断窗口是否全屏
    void DoMonitorKeyBoardOperateTime(); //键鼠停止操作时间记录
    void acceptEvent(int, int); 
    static void do_accept(evutil_socket_t listener, short event, void *arg);

    void SendLastOperateTimeResponse();
    void MonitorKeyBoardOperateTime();

    static int m_stopOperateTimeInterval;  //int型记录键鼠停止操作的时间间隔
private:
    int LastOperateTimePopen(const char *szCmd, char *out, int len);
    int LastOperateTimeSystemCmd(const char* szCmd);
    int charToint(char *t_char) const;
    bool m_isAllScreen;
    int kfd; //键盘
    int mfd; //鼠标
};

int CLastOperateTime::m_stopOperateTimeInterval = 0;

