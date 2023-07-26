#include "environment.h"
#include "ui_environment.h"
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLCDNumber>
#include <fanction.h>
#include <QDebug>
Environment::Environment(QWidget *parent) :
QWidget(parent),
    ui(new Ui::Environment)
{
    ui->setupUi(this);
    ////背景图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/2.jpg");
    ui->label_4->setPixmap(pix2);
    ui->label_4->setScaledContents(true);
    //设置窗口标题
    this->setWindowTitle("环境");
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/返回1.png"));
    ui->pushButton->setIconSize(QSize(98,115));
    //light=new fsmpLight;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Environment::updateLightIntensity);
    // 设置定时器间隔，这里设为 1000ms，即每隔1秒获取一次光照强度值
    timer->start(1000);
    // 创建光照强度获取对象
    light = new fsmpLight(this);
    // 设置 LCD组件的样式表
    ui->lcdNumber->setStyleSheet("QLCDNumber { color: red; background-color: blue; }");
    ui->lcdNumber_2->setStyleSheet("QLCDNumber { color: red; background-color: blue; }");
    ui->lcdNumber_3->setStyleSheet("QLCDNumber { color: red; background-color: blue; }");
    //创建温度获取对象
    myTempHum=new fsmpTempHum;



}

Environment::~Environment()
{
    delete ui;
    // 在析构函数中释放定时器
    delete timer;
    // 释放 myTempHum 对象
    delete myTempHum;
    delete light;


}

void Environment::updateLightIntensity() {
    //光照
    double light_num = light->getValue();
    ui->progressBar->setValue(static_cast<int>(light_num));
    ui->lcdNumber->display(light_num);
    //温度
    double temp_num=myTempHum->temperature();
    ui->progressBar_2->setValue(static_cast<int>(temp_num));
    ui->lcdNumber_2->display(temp_num);
    //湿度
    double hum_num=myTempHum->humidity();
    ui->progressBar_3->setValue(static_cast<int>(hum_num));
    ui->lcdNumber_3->display(hum_num);
}

//返回
void Environment::on_pushButton_clicked()
{    

    //QWidget *myWidget = new Fanction;
    //myWidget->show();
    this->close();
}

//***********//
void Environment::closeEvent(QCloseEvent *event)
{
    qDebug()<<"关闭窗口ing.....";
    emit windowClosed_envt();
    // 发送停止定时器的信号
    emit stopTimerSignal();
    qDebug()<<"关闭成功!";
    // 调用父类的 closeEvent，确保窗口能正常关闭
    QWidget::closeEvent(event);
}

void Environment::stopTimer()
{
    if (timer)
    {
        timer->stop();
    }
}
