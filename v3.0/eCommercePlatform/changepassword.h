#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QWidget>
#include<user.h>
namespace Ui {
class changepassword;
}

class changepassword : public QWidget
{
    Q_OBJECT

public:
    explicit changepassword(QWidget *parent = 0);
    ~changepassword();

    QString username;
    double balance;
    bool type;

private slots:
    void on_pushButton_clicked();
private:
    Ui::changepassword *ui;
};

#endif // CHANGEPASSWORD_H
