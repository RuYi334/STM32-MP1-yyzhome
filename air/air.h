#ifndef AIR_H
#define AIR_H

#include <QWidget>
#include <QCloseEvent>
#include <hwmon.h>
namespace Ui {
class air;
}

class air : public QWidget
{
    Q_OBJECT

public:
    explicit air(QWidget *parent = nullptr);
    ~air();
protected:
    void closeEvent(QCloseEvent* event);
//关闭窗口信号

signals:void windowClosed_air();
signals:void sendMessageRequest(const QString& message); // 定义信号用于发送消息请求

public slots:
    void setFAN_ON();
    void setFAN_OFF();

private slots:
    void on_pushButton_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_2_clicked();

private:
    Ui::air *ui;
    Hwmon* myhwm;
    bool ledState=false;
};

#endif // AIR_H
