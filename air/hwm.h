#ifndef HWMON_H
#define HWMON_H

#include <QObject>
#include <linux/input.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QIODevice>
class Hwmon
{
public:

   Hwmon()
    {
       fanfd = ::open("/sys/class/hwmon/hwmon1/pwm1", O_RDWR | O_TRUNC);
   }

    ~Hwmon()
    {
       ::close(fanfd);
   }

   void HwsetSpeed(int speed)
   {
       QString speedStr = QString::number(speed);
       ::write(fanfd, speedStr.toLocal8Bit().constData(), speedStr.length());
   }

    void setSpeed(int speed)
   {
        // 将速度映射到0和255之间
        int mappedSpeed = mapSpeed(speed);
        // 将映射后的速度值转为字符串
        QString speedStr = QString::number(mappedSpeed);
        // 写入映射后的速度值
        ::write(fanfd, speedStr.toLocal8Bit().constData(), speedStr.length());
    }
    void off()
    {
        ::write(fanfd,"0",strlen("0"));
    }
    void on()
    {
        ::write(fanfd,"100",strlen("100"));
    }

private:
    int fanfd;

    int mapSpeed(int value)
        {
            // 将滑块的值映射到0和255之间
            return static_cast<int>((value / 100.0) * 255);
        }
    };


#endif // HWMON_H
//Hwmon hwmon;
//int sliderValue = slider->value();  // 假设slider是一个QSlider对象
//hwmon.setSpeed(sliderValue);
