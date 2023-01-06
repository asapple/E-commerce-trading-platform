#ifndef ADDITEMS_H
#define ADDITEMS_H

#include <QWidget>

namespace Ui {
class AddItems;
}

class AddItems : public QWidget
{
    Q_OBJECT

public:
    explicit AddItems(QWidget *parent = 0);
    QString username;

    ~AddItems();

private slots:
    void on_pushButtonadd_clicked();

private:
    Ui::AddItems *ui;
};

#endif // ADDITEMS_H
