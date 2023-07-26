#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QWidget>
#include <fsmpLight.h>
#include <fsmpTempHum.h>
//定时器
#include <QTimer>
#include <QCloseEvent>
namespace Ui {
class Environment;
}

class Environment : public QWidget
{
    Q_OBJECT
public:
    explicit Environment(QWidget *parent = nullptr);

    ~Environment();
    void stopTimer();


private slots:
    void updateLightIntensity();
    void on_pushButton_clicked();
/***********************/
protected:
    void closeEvent(QCloseEvent* event);

//关闭窗口信号
signals:void windowClosed_envt();


signals:
    // 自定义信号，用于通知主窗口停止定时器
    void stopTimerSignal();
private:
    QTimer* timer;
    Ui::Environment *ui;
    fsmpLight *light;
    fsmpTempHum *myTempHum;

};

#endif // ENVIRONMENT_H
