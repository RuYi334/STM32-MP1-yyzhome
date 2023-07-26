#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>
#include <QCloseEvent>
#include <fsmpCamera.h>
#include <fsmpEvents.h>
#include <QTimer>
#include <buzzer.h>
namespace Ui {
class Camera;
}

class Camera : public QWidget
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = nullptr);
    ~Camera();
    void setStopFlag(bool stop); // 设置停止标志位

protected:
    void closeEvent(QCloseEvent* event);
protected:
    void run();

    //关闭窗口信号

        signals:void windowClosed_camera();
signals:void sendMessageRequest(const QString& message); // 定义信号用于发送消息请求



private slots:
    void on_pushButton_clicked();
    void handleCameraImage(const QImage& image);
    void handleLightTriggered();
    void handlePeopleDetected(bool detected);
    void handleFlameDetected(); // 处理火焰检测的情况


    void on_pushButton_2_clicked();

private:
    Ui::Camera *ui;
    fsmpCamera* camera;

    QPixmap cameraPixmap; // 添加成员变量，用于缓存相机图像
    fsmpEvents* events;
    Buzzer *buzz;
    bool aaa=false;
};

#endif // CAMERA_H
