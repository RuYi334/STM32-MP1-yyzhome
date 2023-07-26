#ifndef BUZZER_H
#define BUZZER_H

#include <QObject>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QIODevice>

class Buzzer
{
public:
    Buzzer(){
        fd=::open("/dev/input/event0", O_RDWR | O_TRUNC);
    }
    ~Buzzer(){
        ::close(fd);
    }
    void on()
    {
        event.type = EV_SND;//声音模式
        event.code = SND_TONE;//开启蜂鸣器
        event.value = 1;//振动频率
        time.tv_sec = 1;//1s
        time.tv_usec = 0;//0us
        event.time = time;//设置时间结构体
        write(fd, &event, sizeof(event));

    }
    void off()
    {
        event.type = EV_SND;//声音模式
        event.code = SND_BELL;//关闭蜂鸣器
        event.value = 0;//振动频率
        time.tv_sec = 1;//1s
        time.tv_usec = 0;//0us
        event.time = time;//设置时间结构体
        write(fd, &event, sizeof(event));

    }
private:
    int fd;
    struct input_event event;
    struct timeval time;
};

#endif // BUZZER_H
