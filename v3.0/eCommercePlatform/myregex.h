#ifndef MYREGEX_H
#define MYREGEX_H
#include<regex>
#include<cstring>
#include<iostream>
#include<QString>
using namespace  std;
#define Pattern_Double "([-+]?)([0-9]+)(([.][0-9]+)?)"
#define Pattern_Positive "([+]?)([0-9]+)(([.][0-9]+)?)"
#define Pattern_Int "([+]?)([0-9]+)"
#define Pattern_UserName "\\w+"
#define Pattern_Passwords "aaa"
bool isDouble(QString s);
bool isName(QString s);
bool isPasswords(QString s);

#endif // MYREGEX_H
