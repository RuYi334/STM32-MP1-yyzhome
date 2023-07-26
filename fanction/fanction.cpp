#include "fanction.h"
#include "ui_fanction.h"
#include <QPixmap>
#include <led.h>
#include <hwmon.h>
#include <QDebug>
#include <widget.h>
#include <environment.h>
#include <QObject>
#include <air.h>
#include <QMovie>

QMqttTopicName topicName("qwertyuiop"); // 初始化全局变量
QMqttTopicFilter topicFilter("poiuytrewq"); // 初始化全局变量
Fanction::Fanction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Fanction)
{
    ui->setupUi(this);
    ////背景图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/1.jpg");
    ui->label->setPixmap(pix2);
    ui->label->setScaledContents(true);
      my_envt=nullptr;
      my_air=nullptr;
      light=nullptr;
      buzz=nullptr;
      my_camera =nullptr;
      light=new Lighting;
      connect(this, &Fanction::setled_on, light, &Lighting::setLED_ON);
      connect(this, &Fanction::setled_off, light, &Lighting::setLED_OFF);
      QObject::connect(light, &Lighting::sendMessageRequest, this, &Fanction::sendMessageToServer);
      my_air=new air;
      connect(this, &Fanction::setfan_on, my_air, &air::setFAN_ON);
      connect(this, &Fanction::setfan_off, my_air, &air::setFAN_OFF);
      QObject::connect(my_air, &air::sendMessageRequest, this, &Fanction::sendMessageToServer);
      set=new Setting;
      QObject::connect(set,&Setting::lineEditsChanged,this,&Fanction::onLineEditsChanged);
      buzz=new Buzzer;
      connect(this, &Fanction::setbuzz_on, this, &Fanction::setBUZZ_ON);
      connect(this, &Fanction::setbuzz_off, this, &Fanction::setBUZZ_OFF);



    //++++++++++++美化+++++++++++++++//
    //0-灯光 10-环境 8-空调 11-监控 7-设置
    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/灯光.png"));
    ui->pushButton->setIconSize(QSize(125,75));

    ui->pushButton_10->setFlat(true);
    ui->pushButton_10->setIcon(QIcon(":/source/环境.png"));
    ui->pushButton_10->setIconSize(QSize(125,75));

    ui->pushButton_8->setFlat(true);
    ui->pushButton_8->setIcon(QIcon(":/source/空调.png"));
    ui->pushButton_8->setIconSize(QSize(125,75));

    ui->pushButton_11->setFlat(true);
    ui->pushButton_11->setIcon(QIcon(":/source/监控.png"));
    ui->pushButton_11->setIconSize(QSize(125,75));

    ui->pushButton_7->setFlat(true);
    ui->pushButton_7->setIcon(QIcon(":/source/设置.png"));
    ui->pushButton_7->setIconSize(QSize(125,75));

    ui->pushButton_5->setFlat(true);
    ui->pushButton_5->setIcon(QIcon(":/source/返回1.png"));
    ui->pushButton_5->setIconSize(QSize(98,115));

    ui->pushButton_4->setFlat(true);
    ui->pushButton_4->setIcon(QIcon(":/source/退出.png"));
    ui->pushButton_4->setIconSize(QSize(90,90));

    ui->pushButton_9->setFlat(true);
    ui->pushButton_9->setIcon(QIcon(":/source/按钮-关.png"));
    ui->pushButton_9->setIconSize(QSize(125,75));

    //连接MQTT服务器
    client = new QMqttClient;
    client->setHostname("mqtt.yyzlab.com.cn");
    client->setPort(1883);
    client->connectToHost();
    QMqttTopicFilter topicFilter("poiuytrewq");
    client->subscribe(topicFilter);






    //设置窗口标题
    this->setWindowTitle("主菜单");
    //初始化LED==Hwmon==buzzer=====
    connect(client,SIGNAL(messageReceived(QByteArray, QMqttTopicName)),this,SLOT(xxx(QByteArray, QMqttTopicName)));


}

Fanction::~Fanction()
{
    delete ui;
    delete my_envt;
    delete my_air;
    delete client;
    delete buzz;
    delete light;
    delete my_camera;
}


void Fanction::onLineEditsChanged(const LineEditData &data)
{
    qDebug()<<"setting singnals";
     topicName = QMqttTopicName(data.text1); // 更新全局变量
     topicFilter = QMqttTopicFilter(data.text2); // 更新全局变量 topicFilte
     qDebug()<<"data.text1:"<<data.text1;
     qDebug()<<"data.text2:"<<data.text2;
     client->subscribe(topicFilter);
}


void Fanction::sendMessageToServer(const QString& message)
{
    qDebug()<<"发布+++++++++++++++";
    QByteArray payload = message.toUtf8();
            //QMqttTopicName topic("qwertyuiop"); // 你要发布消息的频道名称
            client->publish(topicName, payload);
}

void Fanction::xxx(QByteArray buf, QMqttTopicName)
{
    QJsonDocument jdoc=QJsonDocument::fromJson(buf);
    QJsonObject jobj=jdoc.object();
    if(jobj.contains("lamp"))
    {
        QJsonValue jval=jobj.value("lamp");
        if(jval.toBool()==true)
        {
            qDebug()<<"led on";
            emit setled_on();

        }
        else
        {
            qDebug()<<"led off";
            emit setled_off();
        }
    }
    else if(jobj.contains("fan"))
       {
        QJsonValue jval=jobj.value("fan");
        if(jval.toBool()==true)
        {

            emit setfan_on();
        }
        else
        {
            emit setfan_off();
        }
       }
    else if(jobj.contains("alarm"))
       {
        QJsonValue jval=jobj.value("alarm");
        if(jval.toBool()==true)
        {
            qDebug()<<"on";
            emit setbuzz_on();
        }
        else
        {
            qDebug()<<"off";
           emit setbuzz_off();
        }
       }
}

void Fanction::setBUZZ_ON()
{
    ui->pushButton_9->setIcon(QIcon(":/source/按钮-开.png"));
    buzz->on();
    aaa=true;
}

void Fanction::setBUZZ_OFF()
{
    ui->pushButton_9->setIcon(QIcon(":/source/按钮-关.png"));
    buzz->off();
    aaa=false;
}

void Fanction::on_pushButton_4_clicked()
{
    // 退出并关闭程序
        QApplication::quit();
}


//设置
void Fanction::on_pushButton_7_clicked()
{
    set->show();
}

//空调
void Fanction::on_pushButton_8_clicked()
{
   my_air->show();

}

//灯光
void Fanction::on_pushButton_clicked()
{

    light->show();

}

//环境
void Fanction::on_pushButton_10_clicked()
{
    my_envt=new Environment;
    my_envt->show();
    connect(my_envt, &Environment::stopTimerSignal, this, &Fanction::stopTimerSlot);

}
//返回
void Fanction::on_pushButton_5_clicked()
{
    this->close();
    QWidget *myWidget=new Widget;
    myWidget->show();
}

//监控
void Fanction::on_pushButton_11_clicked()
{
    if(my_camera==nullptr)
    {
        my_camera= new Camera;
        //connect(my_camera,SIGNAL(windowClosed_camera()),this,SLOT(cameraClosed()));
    }
    QObject::connect(my_camera, &Camera::sendMessageRequest, this, &Fanction::sendMessageToServer);
    my_camera->show();
}


void Fanction::environmentClosed()
{
    qDebug() << "environment 窗口已关闭";
    delete my_envt;
    my_envt=nullptr;

}

void Fanction::lightingClosed()
{
    qDebug() << "lighting 窗口已关闭";
    delete light;
    light=nullptr;
}

void Fanction::airClosed()
{
    qDebug() << "Air 窗口已关闭";
    delete my_air;
    my_air=nullptr;
}

void Fanction::cameraClosed()
{
    qDebug() << "Camera 窗口已关闭";
    delete my_camera;
    my_camera=nullptr;
}
void Fanction::stopTimerSlot()
{
        if (my_envt)
        {
            my_envt->stopTimer();
        }
}

void Fanction::on_pushButton_9_clicked()
{
    if(aaa)
    {
        ui->pushButton_9->setIcon(QIcon(":/source/按钮-关.png"));
        buzz->off();
        QString cmd="{\"alarm\":false}";
        client->publish(topicName,cmd.toUtf8());
        aaa=false;
    }
    else
    {
        ui->pushButton_9->setIcon(QIcon(":/source/按钮-开.png"));
        buzz->on();
        QString cmd="{\"alarm\":true}";
        client->publish(topicName,cmd.toUtf8());
        aaa=true;
    }
}
