#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QTcpSocket *client,QWidget *parent = nullptr);
    ~Register();

private slots:
    void on_pushButton_clicked();
    void readMassage();

    void on_pushButton_2_clicked();

private:
    Ui::Register *ui;
    QTcpSocket *sock;
};

#endif // REGISTER_H
