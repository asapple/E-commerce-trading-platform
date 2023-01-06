#ifndef WIDGTREGISTER_H
#define WIDGTREGISTER_H

#include <QWidget>
#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QTimer>
#include<QFile>
#include<fstream>
namespace Ui {
class widgetRegister;
}

class widgetRegister : public QWidget
{
    Q_OBJECT

public:
    explicit widgetRegister(QWidget *parent = 0);
    ~widgetRegister();

private slots:

    void on_pushButtonExist_clicked();

    void on_pushButtonRegister_clicked();

private:
    Ui::widgetRegister *ui;
    bool checkRegInf();
    bool findUser(const QString userName);
    void addUser(QString userName,QString password,bool type);
signals:
    void widgetRegisterBack();
};

#endif // WIDGTREGISTER_H
