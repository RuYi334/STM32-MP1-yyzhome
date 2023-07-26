#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//在.pro文件添加类库
#include <QTcpSocket>
#include <fanction.h>
#include <register.h>
#include <modify.h>
#include <keyboard.h>

// 前向声明 Register 类
class Register;

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
//槽函数
private slots:
    void on_pushButton_clicked();
    void readMassage();
    void on_pushButton_2_clicked();
//变量定义在私有成员里，能在整个类域里使用
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    //fanction返回widget
     void handleReturnToWidget(); // 处理返回到主窗口的槽函数

private:
    Ui::Widget *ui;
    //tcp网络连接
    QTcpSocket *client;
    //新窗口--登陆成功
    Fanction *func;
    //新窗口--注册法
    Register *regs;
    //新窗口--修改
    Modify *mod;
    //键盘
    KeyBoard *keyboard;

};
#endif // WIDGET_H
