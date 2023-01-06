#include "widgetregister.h"
#include "ui_widgetregister.h"
#include"send_info.h"
widgetRegister::widgetRegister(QWidget *parent) :           //界面类的构造函数
    QWidget(parent),
    ui(new Ui::widgetRegister)
{
    ui->setupUi(this);          //界面文件(.ui)设置界面
    this->setWindowTitle("用户注册");           //设置窗口标题为“用户注册”


    ui->lineEditUserName->setPlaceholderText(QString("长度在6~20之间，只能包含英文和数字"));           //界面账号输入框提示
    ui->lineEditPassage->setPlaceholderText(QString("以字母开头，长度在6~18之间，只能包含字母、数字"));           //界面密码输入框提示

}

widgetRegister::~widgetRegister()           //界面类的析构函数
{
    delete ui;
}

void widgetRegister::on_pushButtonExist_clicked()           //“返回”按键被点击时执行该函数
{
    emit this->widgetRegisterBack();            //Qt槽和信号：该界面发出widgetRegisterBack()的信号，界面widget的特定槽接受信号
}

void widgetRegister::on_pushButtonRegister_clicked()            //“注册”按键被点击时执行该函数
{
    if(checkRegInf() == 0)          //检查用户输入的信息是否符合要求，不符合函数返回0，也就不执行下面的添加用户操作
        return;
    struct net_info tmp_data;
    tmp_data.info_type = "Reg";
    tmp_data.username = ui->lineEditUserName->text();
    tmp_data.password = ui->lineEditPassage->text();

    bool type = 0;
    if(ui->comboBox->currentIndex() == 1)
        type = 1;

    tmp_data.type = QString::number(type);
    Send(tmp_data);
    QMessageBox::warning(this,"注册成功"
                         ,QString("账号：%1\n密码：%2\n类型：%3\n注册成功！").arg(tmp_data.username)
                         .arg(tmp_data.password).arg(type == 0 ? "买家":"卖家"));
    return;
}
bool widgetRegister::checkRegInf()          //负责检查用户输入的信息是否符合要求的函数
{
    QString username = ui->lineEditUserName->text();            //从界面输入窗口读取用户输入的信息
    QString password = ui->lineEditPassage->text();
    QString password2 = ui->lineEditPassageConfirm->text();

    if(username.length() < 6 ||username.length() > 20)           //账号长度的检验和提示
    {
        QMessageBox::warning(this,"error"
                             ,QString("账号长度不符合要求，请更换"));
        return 0;
    }

    if(password.length() < 6 || password.length() > 18)         //密码长度的检验和提示
    {
        QMessageBox::warning(this,"error"
                             ,QString("密码长度不符合要求，请更换"));
        return 0;
    }

    for(int i=0; i<password.length(); i++)
    {
        if(( password[i]>='a'&&password[i]<='z' ) || ( password[i]>='A'&&password[i]<='Z' ) || ( password[i]>='0'&&password[i]<='9' ))
            continue;
        else
        {
            QMessageBox::warning(this,"error"
                                 ,QString("密码字符仅包括大写小写字母和数字"));
            return 0;
        }
    }

    for(int i=0; i<username.length(); i++)
    {
        if(( username[i]>='a'&&username[i]<='z' ) || ( username[i]>='A'&&username[i]<='Z' ) || ( username[i]>='0'&&username[i]<='9' ))
            continue;
        else
        {
            QMessageBox::warning(this,"error"
                                 ,QString("账号字符仅包括大写小写字母和数字"));
            return 0;
        }
    }

    if(password != password2)           //重复密码的检验和提示
    {
        QMessageBox::warning(this,"error"
                             ,QString("两次密码不相同"));
        return 0;
    }

    if(findUser(username))
    {
        QMessageBox::warning(this,"error"
                             ,QString("账号已存在"));
        return 0;
    }
    return 1;
}
bool widgetRegister::findUser(const QString userName)          //从用户文件中查询用户名是否存在
{
    std::string _u,_k;
    std::ifstream myfile("../../day01/user.txt");
    if(myfile == NULL)
    {
        QMessageBox::warning(this,"error"
                                         ,QString("文件打开失败"));
    }
    while(std::getline(myfile,_u))
    {
        for(int i=0;i<3;i++)
            std::getline(myfile,_k);
        if( _u == userName.toStdString() )
        {
            myfile.close();
            return 1;
        }
    }
    myfile.close();
    return 0;
}
void widgetRegister::addUser(QString userName,QString password,bool type)          //文件中写入注册的新用户
{
        double balance = 0;
        std::ofstream myfile("../../day01/user.txt",std::ios::app);
        if(myfile == NULL)
        {
            QMessageBox::warning(this,"error"
                                             ,QString("文件打开失败"));
        }
        myfile << userName.toStdString() << "\n";
        myfile << password.toStdString() << "\n";
        myfile << balance << "\n";
        myfile << type << "\n";
        myfile.close();
}
