#include "myregex.h"
bool isDouble(QString s)
{
    regex pat(Pattern_Double);
    string str = s.toStdString();
    return regex_match(str, pat);
}
bool isName(QString s)
{
    regex pat("(\\w{5, 20})");
    string str = s.toStdString();
    return regex_match(str, pat);
}
bool isPasswords(QString s)
{
    regex pat(Pattern_Passwords);
    string str = s.toStdString();
    return regex_match(str, pat);
}
