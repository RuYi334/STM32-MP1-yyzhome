#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    //设置窗口标题
    this->setWindowTitle("设置");
    ////背景图片（QPixmap）
    QPixmap pix3;
    pix3.load(":/6.jpg");
    ui->label_2->setPixmap(pix3);
    ui->label_2->setScaledContents(true);
    ////标签显示图片（QPixmap）
    QPixmap pix2;
    pix2.load(":/二维码.png");
    ui->label->setPixmap(pix2);
    ui->label->setScaledContents(true);

    ui->pushButton->setFlat(true);
    ui->pushButton->setIcon(QIcon(":/source/返回1.png"));
    ui->pushButton->setIconSize(QSize(98,115));
    ui->lineEdit_3->setText("qwertyuiop");
    ui->lineEdit_4->setText("poiuytrewq");
    QString styleSheet = "QLineEdit {"
                         "background-color: #e8f4fc;" // 设置背景颜色
                         "border: 2px solid #1894dc;" // 设置边框样式和颜色
                         "border-radius: 10px;" // 设置圆角
                         "padding: 5px;" // 设置内边距
                         "font-size: 14px;" // 设置字体大小
                         "color: #333333;" // 设置文本颜色
                         "}";

    ui->lineEdit_4->setStyleSheet(styleSheet);
    ui->lineEdit_3->setStyleSheet(styleSheet);
    ui->pushButton_2->setFlat(true);
    ui->pushButton_2->setIcon(QIcon(":/source/确定.png"));
    ui->pushButton_2->setIconSize(QSize(88,92));
}

Setting::~Setting()
{
    delete ui;

}

void Setting::on_pushButton_clicked()
{
    this->hide();
}



void Setting::on_pushButton_2_clicked()
{
    data.text1=ui->lineEdit_3->text();
    data.text2=ui->lineEdit_4->text();
    emit lineEditsChanged(data);
}

