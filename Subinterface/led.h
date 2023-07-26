#ifndef LED_H
#define LED_H

#include <QObject>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QIODevice>

#define LED1 1//LED1==1
#define LED2 2
#define LED3 3

class Led
{
public:
    //构造函数：类调用的时候调用
    Led()
    {
        //表示调用系统函数打开led文件
       fd[0]= ::open("/sys/class/leds/led1/brightness",O_RDWR | O_TRUNC);
       fd[1]= ::open("/sys/class/leds/led2/brightness",O_RDWR | O_TRUNC);
       fd[2]= ::open("/sys/class/leds/led3/brightness",O_RDWR | O_TRUNC);
    }
    //析构函数：类结束时调用
    ~Led()
    {
        ::close(fd[0]);
        ::close(fd[1]);
        ::close(fd[2]);
    }

    //可
    void on(int lednumber)
    {
        if(1==lednumber)
            ::write(fd[0],"1",strlen("1"));
        else if(2==lednumber)
            ::write(fd[1],"1",strlen("1"));
        else
            ::write(fd[2],"1",strlen("1"));
    }

    void off(int lednumber)
    {
        if(1==lednumber)
            ::write(fd[0],"0",strlen("0"));
        else if(2==lednumber)
            ::write(fd[1],"0",strlen("0"));
        else
            ::write(fd[2],"0",strlen("0"));
    }

private:
    int fd[3];
};

#endif // LED_H
