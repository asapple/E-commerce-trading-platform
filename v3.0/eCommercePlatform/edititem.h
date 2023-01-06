#ifndef EDITITEM_H
#define EDITITEM_H

#include <QWidget>
#include<QSqlTableModel>
namespace Ui {
class edititem;
}

class edititem : public QWidget
{
    Q_OBJECT

public:
    explicit edititem(QWidget *parent = 0);
    QString username;
    QSqlTableModel *model;
    ~edititem();

private slots:
    void on_pushButtonRefresh_clicked();

    void on_pushButtondelete_clicked();

private:
    Ui::edititem *ui;
};

#endif // EDITITEM_H
