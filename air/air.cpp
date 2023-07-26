#include "air.h"
#include "ui_air.h"
#include <QDebug>
#include <QSlider>
air::air(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::air)
{
    ui->setupUi(this);
    ////背景图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/3.jpg");
    ui->label->setPixmap(pix2);
    ui->label->setScaledContents(true);
    //设置窗口标题
    this->setWindowTitle("空调");
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/返回1.png"));
    ui->pushButton->setIconSize(QSize(98,115));
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/source/按钮-关.png"));
    ui->pushButton_2->setIconSize(QSize(98,115));
    myhwm = new Hwmon;
    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &air::on_horizontalSlider_valueChanged);
}

air::~air()
{
    delete ui;
}

void air::setFAN_ON()
{
    ui->pushButton_2->setIcon(QIcon(":/source/按钮-开.png"));
    myhwm->on(); // 假设使用 leds.on(LED1) 来打开 LED
    ledState = true;
}

void air::setFAN_OFF()
{
    ui->pushButton_2->setIcon(QIcon(":/source/按钮-关.png"));
    myhwm->off(); // 假设使用 leds.off(LED1) 来关闭 LED
    ledState = false;
}


void air::closeEvent(QCloseEvent *event)
{
    qDebug()<<"关闭窗口ing.....";
    emit windowClosed_air();
    qDebug()<<"关闭成功!";
    QWidget::closeEvent(event);
}
void air::on_pushButton_clicked()
{
    this->hide();
}


void air::on_horizontalSlider_valueChanged(int value)
{
    // 调用 Hwmon 类的 setSpeed 函数，将滑块的值传递给 Hwmon 类，实现风扇转速控制
    qDebug()<<"111111111111";
        myhwm->setSpeed(value);
}

//开关
void air::on_pushButton_2_clicked()
{
    if (ledState) {
            // 如果 LED 状态为亮，则切换为灭
            ui->pushButton_2->setIcon(QIcon(":/source/按钮-关.png"));
            myhwm->off(); // 假设使用 leds.off(LED1) 来关闭 LED
            QString cmd="{\"fan\":false}";
            emit sendMessageRequest(cmd);
            ledState = false;
        } else {
            // 如果 LED 状态为灭，则切换为亮
            ui->pushButton_2->setIcon(QIcon(":/source/按钮-开.png"));
            myhwm->on(); // 假设使用 leds.on(LED1) 来打开 LED
            QString cmd="{\"fan\":true}";
            emit sendMessageRequest(cmd);
            ledState = true;
        }
}

