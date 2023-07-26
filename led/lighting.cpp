#include "lighting.h"
#include "ui_lighting.h"
#include <fanction.h>
Lighting::Lighting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Lighting)
{
    ui->setupUi(this);
    ////背景图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/2.jpg");
    ui->label_5->setPixmap(pix2);
    ui->label_5->setScaledContents(true);
    //设置窗口标题
    this->setWindowTitle("灯光");
    //++++Init Led++++++//
    leds.off(LED1);
    leds.off(LED2);
    leds.off(LED2);
    //按钮隐藏边框
    ui->pushButton_5->setFlat(true);
    ui->pushButton_3->setFlat(true);
    ui->pushButton_6->setFlat(true);
    ui->pushButton_7->setFlat(true);
    ui->pushButton->setFlat(true);
    //按钮图片设置（图片大小）
    ui->pushButton_5->setIcon(QIcon(":/source/按钮-关.png"));
    ui->pushButton_5->setIconSize(QSize(100,120));
    ui->pushButton_3->setIcon(QIcon(":/source/按钮-关.png"));
    ui->pushButton_3->setIconSize(QSize(100,120));
    ui->pushButton_6->setIcon(QIcon(":/source/按钮-关.png"));
    ui->pushButton_6->setIconSize(QSize(100,120));
    ui->pushButton_7->setIcon(QIcon(":/source/按钮-关.png"));
    ui->pushButton_7->setIconSize(QSize(100,120));
    ui->pushButton->setIcon(QIcon(":/source/返回1.png"));
    ui->pushButton->setIconSize(QSize(100,120));

    //


}

Lighting::~Lighting()
{
    delete ui;
}

void Lighting::setLED_ON()
{
    qDebug()<<"led on";
    ui->pushButton_7->setIcon(QIcon(":/source/按钮-开.png"));
    leds.on(LED1);
    leds.on(LED2);
    leds.on(LED3);
    ledStates[3] = true;

}
void Lighting::setLED_OFF()
{
    qDebug()<<"led off";
    ui->pushButton_7->setIcon(QIcon(":/source/按钮-关.png"));
    leds.off(LED1);
    leds.off(LED2);
    leds.off(LED3);
    ledStates[3] = false;

}
//LED1
void Lighting::on_pushButton_5_clicked()
{

    if (ledStates[0]) {
            // 如果 LED 状态QObject::connect(light, &Lighting::sendMessageRequest, this, &Fanction::sendMessageToServer);为亮，则切换为灭
            ui->pushButton_5->setIcon(QIcon(":/source/按钮-关.png"));
            leds.off(LED1); // 假设使用 leds.off(LED1) 来关闭 LED
            ledStates[0] = false;
        } else {
            // 如果 LED 状态为灭，则切换为亮
            ui->pushButton_5->setIcon(QIcon(":/source/按钮-开.png"));
            leds.on(LED1); // 假设使用 leds.on(LED1) 来打开 LED
            ledStates[0] = true;
        }
}

//LED2
void Lighting::on_pushButton_3_clicked()
{

    if (ledStates[1]) {
            // 如果 LED 状态为亮，则切换为灭
            ui->pushButton_3->setIcon(QIcon(":/source/按钮-关.png"));
            leds.off(LED2); // 假设使用 leds.off(LED1) 来关闭 LED
            ledStates[1] = false;
        } else {
            // 如果 LED 状态为灭，则切换为亮
            ui->pushButton_3->setIcon(QIcon(":/source/按钮-开.png"));
            leds.on(LED2); // 假设使用 leds.on(LED1) 来打开 LED
            ledStates[1] = true;
        }
}

//LED3
void Lighting::on_pushButton_6_clicked()
{

    if (ledStates[2]) {
            // 如果 LED 状态为亮，则切换为灭
            ui->pushButton_6->setIcon(QIcon(":/source/按钮-关.png"));
            leds.off(LED3); // 假设使用 leds.off(LED1) 来关闭 LED
            ledStates[2] = false;
        } else {
            // 如果 LED 状态为灭，则切换为亮
            ui->pushButton_6->setIcon(QIcon(":/source/按钮-开.png"));
            leds.on(LED3); // 假设使用 leds.on(LED1) 来打开 LED
            ledStates[2] = true;
        }
}

//ALL
void Lighting::on_pushButton_7_clicked()
{
    if (ledStates[3]) {
            ui->pushButton_7->setIcon(QIcon(":/source/按钮-关.png"));
            leds.off(LED1);
            leds.off(LED2);
            leds.off(LED3);
            QString cmd="{\"lamp\":false}";
            emit sendMessageRequest(cmd);

            ledStates[3] = false;
        } else {
            ui->pushButton_7->setIcon(QIcon(":/source/按钮-开.png"));
            leds.on(LED1);
            leds.on(LED2);
            leds.on(LED3);
            QString cmd="{\"lamp\":true}";
            emit sendMessageRequest(cmd);
            ledStates[3] = true;


        }

}

void Lighting::closeEvent(QCloseEvent *event)
{
    qDebug()<<"关闭窗口ing.....";
    emit windowClosed_led();
    qDebug()<<"关闭成功!";
    QWidget::closeEvent(event);
}

//返回
void Lighting::on_pushButton_clicked()
{


    this->hide();
    //emit windowClosed_led();
}

