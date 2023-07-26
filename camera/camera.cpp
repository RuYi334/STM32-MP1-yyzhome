#include "camera.h"
#include "ui_camera.h"
#include <QDebug>
#include <QObject>
#include <QMovie>

Camera::Camera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);
    ////背景图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/2.jpg");
    ui->label_5->setPixmap(pix2);
    ui->label_5->setScaledContents(true);
    this->setWindowTitle("实时监控");
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/返回1.png"));
    ui->pushButton->setIconSize(QSize(98,115));
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/source/按钮-关.png"));
    // 创建相机对象

    // 创建相机对象
    try {
        camera = new fsmpCamera;
    } catch (std::exception& e) {
        // 处理异常，例如输出错误信息
        qDebug() << "Exception caught: " << e.what();
        this->close(); // 返回或者进行其他处理
    }
    // 设置帧间隔为30毫秒（约每秒33帧）
    buzz=new Buzzer;
    // 连接相机信号pixReady到槽函数handleCameraImage
    connect(camera, &fsmpCamera::pixReady, this, &Camera::handleCameraImage);
    // 启动相机
    try {
        camera->start();
    } catch (std::exception& e) {
        // 处理异常，例如输出错误信息
        qDebug() << "Exception caught: " << e.what();
        delete camera;
        camera = nullptr;
        this->close(); // 返回或者进行其他处理
    }


    //camera->start();
    if(camera->isRunning())
    {
        qDebug()<<"相机运行ing";
        camera->setPixDelay(33333);
    }

    //buzz->off();

    ///evevts
    events=new fsmpEvents;
    //光闸管
    connect(events,&fsmpEvents::lightTriggered,this,&Camera::handleLightTriggered);
    // 连接检测到人体红外信号到处理槽函数
    connect(events, &fsmpEvents::peopleDetected, this, &Camera::handlePeopleDetected);
    // 连接火焰检测信号到处理函数
    connect(events, &fsmpEvents::flameDetected, this, &Camera::handleFlameDetected);
    ////标签显示图片（QPixmap）
    QPixmap pix3;
    pix3.load(":/source/安全.png");
    ui->label_6->setPixmap(pix3);
    ui->label_6->setScaledContents(true);
    ui->label_7->setText("安全");
    ////标签显示图片（QPixmap）
    QPixmap pix;
    pix.load(":/source/安全.png");
    ui->label_2->setPixmap(pix);
    ui->label_2->setScaledContents(true);
    ui->label_4->setText("安全");
    ////标签显示图片（QPixmap）
    QPixmap pix1;
    pix1.load(":/source/安全.png");
    ui->label_3->setPixmap(pix1);
    ui->label_3->setScaledContents(true);
    ui->label_5->setText("安全");

}

Camera::~Camera()
{

    qDebug()<<"关闭窗口ing.....";
    delete ui;
    delete camera;
    camera=nullptr;
    delete buzz;
    buzz=nullptr;
    delete events;
    events=nullptr;
    qDebug()<<"关闭窗口success.....";
}

void Camera::handleCameraImage(const QImage& image)
{
    // 将相机图像显示在界面上
    cameraPixmap = QPixmap::fromImage(image);
    ui->label->setPixmap(cameraPixmap.scaled(ui->label->size(), Qt::KeepAspectRatio));
}



//光闸管
void Camera::handleLightTriggered()
{
    ui->label_2->setText("光闸管阻隔事件发生");
}

//人体红外
void Camera::handlePeopleDetected(bool detected)
   {
       if (detected)
       {
           qDebug() << "检测到人体红外！执行操作 A";
           ////标签显示图片（QPixmap）
           QPixmap pix;
           pix.load(":/source/警告.png");
           ui->label_3->setPixmap(pix);
           ui->label_3->setScaledContents(true);
           ui->label_5->setText("检测到人体红外！");

           buzz->on();
           QString cmd="{\"alarm\":true}";
           emit sendMessageRequest(cmd);

       }
       if (!detected)
       {
           qDebug() << "未检测到人体红外！执行操作 B";
           ////标签显示图片（QPixmap）
           QPixmap pix1;
           pix1.load(":/source/安全.png");
           ui->label_3->setPixmap(pix1);
           ui->label_3->setScaledContents(true);
           ui->label_5->setText("安全");

           buzz->off();
           QString cmd="{\"alarm\":false}";
           emit sendMessageRequest(cmd);
       }

   }

//火焰检测
void Camera::handleFlameDetected()
{
    qDebug() << "检测到火焰！执行相应操作";
    ////标签显示图片（QPixmap）
    QPixmap pix;
    pix.load(":/source/警告.png");
    ui->label_6->setPixmap(pix);
    ui->label_6->setScaledContents(true);
    ui->label_7->setText("检测到人体红外！");
}

void Camera::on_pushButton_clicked()
{
    // 关闭窗口
    this->close();
}


void Camera::closeEvent(QCloseEvent *event)
{
    emit windowClosed_camera();
    //关闭
    camera->cameraexit();
    qDebug()<<"关闭成功!";
    QWidget::closeEvent(event);
}

//开关
void Camera::on_pushButton_2_clicked()
{
    if(aaa)
    {
        ui->pushButton_2->setIcon(QIcon(":/source/按钮-关.png"));
        buzz->off();
        QString cmd="{\"alarm\":false}";
        emit sendMessageRequest(cmd);
        aaa=false;
    }
    else
    {
        ui->pushButton_2->setIcon(QIcon(":/source/按钮-开.png"));
        buzz->on();
        QString cmd="{\"alarm\":true}";
        emit sendMessageRequest(cmd);
        aaa=true;
    }
}

