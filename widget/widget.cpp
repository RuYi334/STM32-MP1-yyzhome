#include "widget.h"
#include "ui_widget.h"
//标签图片
#include <QPixmap>
#include <QMovie>
//在.pro文件添加类库multimedia
#include <QSound>
#include <QDebug>
//
#include <QHostAddress>
//项目头文件
#include <fanction.h>
#include <register.h>
#include <modify.h>
//弹窗
#include <QMessageBox>
//ICON
#include <QIcon>
#include <QSize>

#include <iostream>
#include <led.h>
#include <hwmon.h>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //访问控件都需要ui指针
    ui->setupUi(this);

    ui->label->setText("欢迎使用元宇宙智慧家庭");
    //================================================//
    ui->pushButton_4->setFlat(true);
    ui->pushButton_4->setIcon(QIcon(":/source/退出.png"));
    ui->pushButton_4->setIconSize(QSize(85,86));

    QString styleSheet = "QLineEdit {"
                         "background-color: #e8f4fc;" // 设置背景颜色
                         "border: 2px solid #1894dc;" // 设置边框样式和颜色
                         "border-radius: 10px;" // 设置圆角
                         "padding: 5px;" // 设置内边距
                         "font-size: 14px;" // 设置字体大小
                         "color: #333333;" // 设置文本颜色
                         "}";

    ui->lineEdit->setStyleSheet(styleSheet);
    ui->lineEdit_2->setStyleSheet(styleSheet);
    ui->label->setStyleSheet(styleSheet);

    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/登录.png"));
    ui->pushButton->setIconSize(QSize(90,95));
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/source/注册.png"));
    ui->pushButton_2->setIconSize(QSize(90,95));
    ui->pushButton_3->setFlat(true);
    ui->pushButton_3->setIcon(QIcon(":/source/修改密码.png"));
    ui->pushButton_3->setIconSize(QSize(73,65));


    //================================================//

    //设置文本标题
    this->setWindowTitle("智慧家庭登录系统");
    //设置程序图标
    this->setWindowIcon(QIcon(":/home.png"));

    //在文本框显示文字
    ui->lineEdit->setPlaceholderText("请输入账号");
    ui->lineEdit_2->setPlaceholderText("请输入密码");
    //设置密码隐私显示
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    //按钮隐藏边框
    //ui->pushButton_2->setFlat(true);
    //按钮图片设置（图片大小）
    //ui->pushButton->setIcon(QIcon(":/ikun.jpg"));
    //ui->pushButton->setIconSize(QSize(90,60));

    ////标签显示图片（QPixmap）
    //设置一个QPixmap对象，作为setPixmap参数
    QPixmap pix;
    //调用QPixmap类的构造函数loda加载图片位置
    pix.load(":/4.jpg");
    //调用Qlible的对象libel_2的构造函数setPixmap，让其显示图片
    ui->label_2->setPixmap(pix);
    //调用Qlible的对象libel_2的构造函数setScaledContents，设置图像
    ui->label_2->setScaledContents(true);

    QPixmap pix2;
    pix2.load(":/home.png");
    ui->label_3->setPixmap(pix2);
    ui->label_3->setScaledContents(true);

    ////动态图片（QMovie）
    //QMovie *movie=new QMovie("路径");
    //ui->label_3->setMovie(movie);
    //movie->start();

    ////音乐wav（QSound）
    //QSound *sound=new QSound(":/1.wav");
    //sound->play();

    //lineEdit
    qDebug()<<ui->lineEdit->text();
    //ui->lineEdit_2->setText("2011020002");
    qDebug()<<ui->lineEdit->text();
    //++++++++++++++++键盘++++++++++++++++++
    KeyBoard *keyboard = new KeyBoard();
    ui->lineEdit->installEventFilter(keyboard);
    ui->lineEdit_2->installEventFilter(keyboard);

    //连接服务器
    client=new QTcpSocket;
    client->connectToHost(QHostAddress("192.168.7.155"),8888);

    //信号与槽：收到消息就读取消息
    connect(client,SIGNAL(readyRead()),this,SLOT(readMassage()));
}

Widget::~Widget()
{
    delete ui;
    if (func)
        {
            delete func;
        }
}

//pushButton控件的槽函数
void Widget::on_pushButton_clicked()
{
    ///发送信息给服务器
    //cmd
    char login[20]="login";
    client->write(login,20);
    //账号
    client->write(ui->lineEdit->text().toStdString().c_str(),20);
    //密码
    client->write(ui->lineEdit_2->text().toStdString().c_str(),20);

}


void Widget::readMassage()  
{
    char result[60];
    client->read(result,60);
    qDebug() << result;
    if(0==strncmp(result,"登录成功",12))
    {
        qDebug() << "登录成功";
        //打开新窗口
        func=new Fanction;
        //关闭旧窗口
        this->hide();
        func->show();

        qDebug()<<ui->lineEdit_2->text();
    }
    else if(strncmp(result, "账号不存在",15) == 0)
    {
        QMessageBox::warning(this, "登录信息", "账号不存在！", QMessageBox::Ok); // 正确的使用方式

    }
    else if(strncmp(result, "密码错误",12) == 0)
    {
        QMessageBox::warning(this, "登录信息", "密码错误！", QMessageBox::Ok); // 正确的使用方式

    }

    //qDebug()<<result;
    cout<<"返回信息："<<result<<endl;
}


//注册槽函数
void Widget::on_pushButton_2_clicked()
{
    //打开新窗口
    // 调试输出，确保按钮点击时被触发
       qDebug() << "注册按钮点击了";

       regs = new Register(client);

       // 显示注册窗口并隐藏主窗口
       regs->show();
       this->hide();




}

//修改槽函数
void Widget::on_pushButton_3_clicked()
{
    mod = new Modify(client);

    // 显示注册窗口并隐藏主窗口
    mod->show();
    this->hide();
}


void Widget::on_pushButton_4_clicked()
{
    // 退出并关闭程序
        QApplication::quit();
}

//跳过登录
void Widget::on_pushButton_5_clicked()
{
    func=new Fanction;
    func->show();
    //关闭旧窗口
    this->close();
}

// 处理返回到主窗口的槽函数
void Widget::handleReturnToWidget()
{
    qDebug()<<"返回在出口";
    func->hide(); // 隐藏子窗口
    this->show(); // 显示主窗口
}
