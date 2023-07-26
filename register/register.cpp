#include "register.h"
#include "ui_register.h"
#include <QMessageBox>
#include <keyboard.h>
#include <widget.h>
Register::Register(QTcpSocket *client,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    //设置文本标题
    this->setWindowTitle("IKUN注册系统");
    //设置程序图标
    this->setWindowIcon(QIcon(":/ikun.jpg"));
    //在文本框显示文字
    ui->lineEdit->setPlaceholderText("请输入账号");
    ui->lineEdit_2->setPlaceholderText("请输入密码");
    //设置密码隐私显示
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
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

    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/确定.png"));
    ui->pushButton->setIconSize(QSize(88,92));
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/source/返回.png"));
    ui->pushButton_2->setIconSize(QSize(88,92));

    ////背景图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/4.jpg");
    ui->label->setPixmap(pix2);
    ui->label->setScaledContents(true);
    //
    sock=client;
    //信号与槽：收到消息就读取消息
    connect(sock,SIGNAL(readyRead()),this,SLOT(readMassage()));

    KeyBoard *keyboard = new KeyBoard();
    ui->lineEdit->installEventFilter(keyboard);
    ui->lineEdit_2->installEventFilter(keyboard);

}

Register::~Register()
{
    delete ui;
}

void Register::on_pushButton_clicked()
{
    char cmd[20]="register";
    sock->write(cmd,20);
    sock->write(ui->lineEdit->text().toStdString().c_str(),20);
    sock->write(ui->lineEdit_2->text().toStdString().c_str(),20);
}

void Register::readMassage()
{
    char result[60];
    sock->read(result,60);
    if(0==strncmp(result,"注册成功",4))
    {
        //QMessageBox::warning(this, "警告", "注册成功", QMessageBox::Ok);
        QMessageBox::information(this, "注册信息", "注册成功！", QMessageBox::Ok);
        this->close();
    }
    if(0==strncmp(result,"账号已经存在",12))
    {
        QMessageBox::warning(this, "注册信息", "账号已经存在", QMessageBox::Ok);
    }
}

//返回
void Register::on_pushButton_2_clicked()
{
    this->close();
    QWidget *myWidget=new Widget;
    myWidget->show();
}

