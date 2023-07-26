#ifndef LIGHTING_H
#define LIGHTING_H

#include <QWidget>
#include <led.h>


namespace Ui {
class Lighting;
}

class Lighting : public QWidget
{
    Q_OBJECT

public:
    explicit Lighting(QWidget *parent = nullptr);
    ~Lighting();

protected:
    void closeEvent(QCloseEvent* event);

signals:void windowClosed_led();
signals:void sendMessageRequest(const QString& message); // 定义信号用于发送消息请求


public slots:
    // 子窗口的槽函数，用于接收来自主窗口的 MQTT 消息
    void setLED_ON();
    void setLED_OFF();
private slots:
    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();
    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();




    void on_pushButton_clicked();

private:
    Ui::Lighting *ui;
    Led leds;
    //LED
    bool ledStates[5] = {false, false, false,false,false}; // 初始化为灭（false）


};

#endif // LIGHTING_H
