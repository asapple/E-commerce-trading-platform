#include "edititem.h"
#include "ui_edititem.h"
#include<QDebug>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>

edititem::edititem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edititem)
{
    ui->setupUi(this);
    this->setWindowTitle("商品管理");
    model = new QSqlTableModel(this);
    model->setTable("items");
    model->setFilter(QObject::tr("owner = '%1'").arg(username));
    model->select();
    model->removeColumn(8);
    model->removeColumn(7);
    model->removeColumn(5);
    model->removeColumn(0);
    ui->tableView->setModel(model);
}
edititem::~edititem()
{
    delete ui;
}

void edititem::on_pushButtonRefresh_clicked()
{
    model->setFilter(QObject::tr("owner = '%1'").arg(this->username)); //根据类别进行筛选
    model->select(); //显示结果
    return;
}

void edititem::on_pushButtondelete_clicked()
{
    QItemSelectionModel *sModel = ui->tableView->selectionModel();
    QModelIndexList list =sModel->selectedRows();
    for(int i = 0;i< list.size();i++)
    {
        model->removeRow(list.at(i).row());
    }
}
