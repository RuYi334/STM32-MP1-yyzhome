#ifndef FANCTION_H
#define FANCTION_H

#include <QWidget>
#include <led.h>
#include <hwmon.h>
#include <buzzer.h>
#include <lighting.h>
#include <air.h>
#include <environment.h>
#include <camera.h>
#include <setting.h>
#include <qmqttclient.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
extern QMqttTopicName topicName;
extern QMqttTopicFilter topicFilter;

namespace Ui {
class Fanction;
}

class Fanction : public QWidget
{
    Q_OBJECT

public:
    explicit Fanction(QWidget *parent = nullptr);
    ~Fanction();
    Q_INVOKABLE void sendMessageToServer(const QString& message);
public slots:
    void setBUZZ_ON();
    void setBUZZ_OFF();
signals:
    void returnToWidget(); // 声明返回主窗口的信号
    void setled_on();
    void setled_off();
    void setfan_on();
    void setfan_off();
    void setbuzz_off();
    void setbuzz_on();

private slots:
    void on_pushButton_4_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_11_clicked();
    void environmentClosed();
     // 新增的槽函数，用于停止定时器的运行
    void stopTimerSlot();
    void airClosed();
    void cameraClosed();
    void lightingClosed();
    void onLineEditsChanged(const LineEditData &data);
    void xxx(QByteArray, QMqttTopicName);

    void on_pushButton_9_clicked();

private:
    Ui::Fanction *ui;
    Led leds;
    Hwmon hwms;
    Buzzer *buzz;
    //LED
    bool ledStates[5] = {false, false, false,false,false}; // 初始化为灭（false）
    bool aaa=false;
    //窗口--灯光
    Lighting  *light=nullptr;
    //窗口--空调
    air *my_air=nullptr;
    //窗口--环境
    Environment *my_envt=nullptr;
    //窗口--监控
    Camera *my_camera=nullptr;
    //窗口--设置
    Setting *set=nullptr;
    QMqttClient *client;




};

#endif // FANCTION_H
