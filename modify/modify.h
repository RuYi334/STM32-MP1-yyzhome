#ifndef MODIFY_H
#define MODIFY_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class Modify;
}

class Modify : public QWidget
{
    Q_OBJECT

public:
    explicit Modify(QTcpSocket *client,QWidget *parent = nullptr);
    ~Modify();

private slots:
    void on_pushButton_clicked();
    void readMassage();

    void on_pushButton_2_clicked();

private:
    Ui::Modify *ui;
    QTcpSocket *sock;
};

#endif // MODIFY_H
