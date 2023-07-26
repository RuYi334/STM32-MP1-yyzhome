#ifndef SETTING_H
#define SETTING_H

#include <QWidget>
#include <qmqttclient.h>
struct LineEditData {
    QString text1;
    QString text2;
};

namespace Ui {
class Setting;
}

class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(QWidget *parent = nullptr);
    ~Setting();


signals:void lineEditsChanged(const LineEditData &data);


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Setting *ui;
    QMqttClient *client;
    LineEditData data;
};

#endif // SETTING_H
