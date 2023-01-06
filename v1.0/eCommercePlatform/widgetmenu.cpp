#include "widgetmenu.h"
#include "ui_widgetmenu.h"

WidgetMenu::WidgetMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetMenu)
{
    ui->setupUi(this);          //界面设置
    this->setWindowTitle("eBuy");

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");          //连接数据库
    db.setHostName("127.0.0.1");            //数据库服务器IP
    db.setUserName("root");         // 数据库用户名
    db.setPassword("123456");           //密码
    db.setDatabaseName("ebuy");         //使用哪个数据库

    if(!db.open())
    {
        QMessageBox::warning(this,"数据库打开失败"
                             ,db.lastError().text());
        return ;
    }

    model = new QSqlTableModel(this);
    model->setTable("items");           //选择表
    ui->tableView->setModel(model);         //链接tableView和model
    model->select();            //展示表
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);          //设置数据库修改策略：不可编辑

    ui->lineEditmoney->setText("100");          //充值默认值，方便调试

    modelcart = new QSqlTableModel(this);
    modelcart->setTable("ordereditems");
    ui->tableViewcart->setModel(modelcart);
    modelcart->setFilter(QObject::tr("buyer = '%1'").arg(this->user1.username));        //设置展示条件
    modelcart->select();
    ui->tableViewcart->setEditTriggers(QAbstractItemView::NoEditTriggers);          //设置数据库修改策略：不可编辑
}

WidgetMenu::~WidgetMenu()
{
    delete ui;
}

void WidgetMenu::on_pushButtonRefresh_clicked()             //刷新
{
    modelcart->setFilter(QObject::tr("buyer = '%1'").arg(this->user1.username));
    model->select();
    modelcart->select();
}

void WidgetMenu::on_pushButtonAddItems_clicked()            //添加商品
{
    wadditems = new AddItems;
    wadditems->username =this->user1.username;
    wadditems->show();           //打开添加商品的页面
}

void WidgetMenu::on_pushButtonInfo_clicked()
{
    std::string _username,_userpassword;
    double _userbalance;
    bool _usertype;
    std::ifstream userfile;
    userfile.open("../user.txt",std::ios::in);
    while(userfile >>_username>>_userpassword>>_userbalance>>_usertype)
    {
        if(QString::fromStdString(_username) == this->user1.username)
        {
            break;
        }

    }
    userfile.close();
    QMessageBox::warning(this,"账号信息"
                         ,QString("账号%1   密码%2\n类型%3   余额%4\n").arg(QString::fromStdString( _username))
                         .arg(QString::fromStdString(_userpassword)).arg(_usertype).arg(_userbalance));
}
//修改密码
void WidgetMenu::on_pushButtonPassword_clicked()
{
    wcp = new changepassword;
    wcp->username = this->user1.username;
    wcp->balance = this->user1.balance;
    wcp->type = this->user1.type;
    wcp->show();

}

void WidgetMenu::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(arg1 =="所有")
    {
        model->setFilter(QObject::tr("owner != '%1'").arg(" "));
        model->select();
        return;
    }
    if(arg1 =="我的商品")
    {
        model->setFilter(QObject::tr("owner = '%1'").arg(this->user1.username)); //根据类别进行筛选
        model->select(); //显示结果
        return;
    }
    model->setFilter(QObject::tr("type = '%1'").arg(arg1)); //根据类别进行筛选
    model->select(); //显示结果
}

void WidgetMenu::on_pushButtonedititem_clicked()
{
    editit = new edititem;
    editit->username = this->user1.username;
    editit->show();
}

void WidgetMenu::on_pushButtonMoney_clicked()
{
    if(ui->lineEditmoney->text().toDouble()<=0)
    {
        QMessageBox::warning(this,"error","充值失败");
        return ;
    }
    changeBalance(this->user1.username,this->user1.balance + ui->lineEditmoney->text().toDouble());
    QMessageBox::warning(this,"成功","充值已到账");
}
void WidgetMenu::changeBalance(const QString userName,const double newBalance)
{
    this->user1.balance = newBalance;

    std::fstream userfile;
    userfile.open("../user.txt",std::ios::in);
    std::string str,tmp;
    int i=0;
    while(getline(userfile,tmp))
    {
        i++;
        str.append(tmp).append("\n");
        if(tmp == userName.toStdString() &&i % 4 == 1)
        {
            getline(userfile,tmp);
            str.append(tmp).append("\n");
            getline(userfile,tmp);
            str.append((QString::number(newBalance)).toStdString()).append("\n");
        }
    }
    userfile.close();
    std::fstream userout;
    userout.open("../user.txt",std::ios::out);
    userout << str;
    userout.close();
    return;
}

void WidgetMenu::on_pushButtonSearch_clicked()
{
    if(ui->comboBox->currentText()=="所有")
    {
        model->setFilter(QObject::tr("(name like '%%1%') or (introduce like '%%2%')").arg(ui->lineEdit->text()).arg(ui->lineEdit->text()));
        model->select(); //显示结果
        return;
    }
    else
    {
        model->setFilter(QObject::tr(" ( type = '%1' ) and ( ( name like '%%2%' ) or (introduce like '%%3%') )").arg(ui->comboBox->currentText()).arg(ui->lineEdit->text()).arg(ui->lineEdit->text()));
        model->select(); //显示结果
    }
}

void WidgetMenu::on_pushButtoncleancart_clicked()
{
    QItemSelectionModel *sModel = ui->tableViewcart->selectionModel();
    QModelIndexList list =sModel->selectedRows();
    for(int i = 0;i< list.size();i++)
    {
        modelcart->removeRow(list.at(i).row());
    }
}

void WidgetMenu::on_pushButtonaddcart_clicked()
{
    QSqlQuery query;
    QString tmp=QString("select * from items where id = %1").arg(ui->lineEditid->text());
    query.exec(tmp);
    while(query.next())
    {
        qDebug()<<query.value(1).toString()<<query.value("introduce").toString();
    }
    query.exec(tmp);  query.next();
    int ordered = ui->lineEditnumber->text().toInt()+query.value("ordered").toInt();
    int number = -( ui->lineEditnumber->text().toInt() )+query.value("number").toInt();

    qDebug()<<ordered;
    qDebug()<<number;

        tmp=QString("insert into ordereditems (id,type,name,introduce,orderednumber,price,discount,seller,buyer) values(%1,'%2','%3','%4',%5,%6,%7,'%8','%9')")
                .arg(ui->lineEditid->text()).arg(query.value(1).toString()).arg(query.value(2).toString()).arg(query.value(3).toString()).arg(ui->lineEditnumber->text())
                .arg(QString::number(query.value(6).toDouble())).arg(QString::number(query.value(7).toDouble())).arg(query.value(8).toString()).arg(this->user1.username);
        query.exec(tmp);

    tmp = QString("update items set ordered = %1 where id = %2").arg(QString::number(ordered)).arg(ui->lineEditid->text());
    query.exec(tmp);
    tmp = QString("update items set number = %1 where id = %2").arg(QString::number(number)).arg(ui->lineEditid->text());
    query.exec(tmp);
}

void WidgetMenu::on_pushButtonbuy_clicked()
{
    double pay = 0;
    QSqlQuery query;
    QString tmp_exec = QString("select * from ordereditems where buyer = '%1'").arg(this->user1.username);
    query.exec(tmp_exec);
    while(query.next())
    {
        qDebug()<<query.value("seller").toString();
        pay += query.value("orderednumber").toInt()*query.value("price").toDouble()*query.value("discount").toDouble();
        std::fstream userfile;
        userfile.open("../user.txt",std::ios::in);
        std::string str,tmp;
        int i=0;
        while(getline(userfile,tmp))
        {
            i++;
            str.append(tmp).append("\n");
            if(tmp == query.value("seller").toString().toStdString()&&i%4==1)
            {
                getline(userfile,tmp);
                str.append(tmp).append("\n");
                getline(userfile,tmp);

                double newbalance = QString::fromStdString(tmp).toDouble() + query.value("orderednumber").toInt()*query.value("price").toDouble()*query.value("discount").toDouble();
                str.append((QString::number(newbalance)).toStdString()).append("\n");
            }
        }
        userfile.close();
        std::fstream userout;
        userout.open("../user.txt",std::ios::out);
        userout << str;
        userout.close();
    }
    std::fstream userfile;
    userfile.open("../user.txt",std::ios::in);
    std::string str,tmp;
    int i=0;
    while(getline(userfile,tmp))
    {
        i++;
        str.append(tmp).append("\n");
        if(tmp == this->user1.username.toStdString()&&i%4==1)
        {
            getline(userfile,tmp);
            str.append(tmp).append("\n");
            getline(userfile,tmp);

            double newbalance = QString::fromStdString(tmp).toDouble() - pay;
            str.append((QString::number(newbalance)).toStdString()).append("\n");
        }
    }
    userfile.close();
    std::fstream userout;
    userout.open("../user.txt",std::ios::out);
    userout << str;
    userout.close();

    tmp_exec =QString("delete from ordereditems where buyer = '%1'").arg(user1.username);
    query.exec(tmp_exec);
}
void WidgetMenu::unlogin_set()
{
    ui->pushButtonAddItems->setEnabled(false);
    ui->pushButtonedititem->setEnabled(false);
    ui->pushButtonInfo->setEnabled(false);
    ui->pushButtonMoney->setEnabled(false);
    ui->pushButtonPassword->setEnabled(false);
    ui->pushButtonRefresh->setEnabled(false);
}
