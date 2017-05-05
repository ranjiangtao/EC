#include "account.h"

extern int number;
Account::Account()
{
}

//注册成功返回帐号
string Account::addAcountInformation(string password, string nickname, string sex, string age)
{
    QString account;
    do{
        srand(time(NULL));
        int act=rand()%100000+100000;
        account = QString::number(act);
    }while(IsAccountExist(account.toStdString()));

    QSqlQuery query;
    query.prepare("INSERT INTO account(account, password,nickname, sex, age)"
                  "VALUES (:account, :password,:nickname, :sex, :age)");
    query.bindValue(":account", account);
    query.bindValue(":password", QString::fromStdString(password));
    query.bindValue(":nickname", QString::fromStdString(nickname));
    query.bindValue(":sex",QString::fromStdString(sex));
    query.bindValue(":age", QString::fromStdString(age));
    query.exec();


    return account.toStdString();
}

//获取密码
string Account::getPassword(string account)
{
    QString ac = QString::fromStdString(account);
    QString infoInDB=QString("SELECT account,password FROM account "
                             "WHERE account = '%1'").arg(ac);
    QSqlQuery query;
    query.exec(infoInDB);

    if(query.next())
    {
        QString pwd = query.value(1).toString();
        return pwd.toStdString();
    }
    else
        return "";
}

//按帐号，昵称，性别，年龄返回
vector<string> Account::getAccountInformation(string account)
{
    QString ac = QString::fromStdString(account);
    QString infoInDB=QString("SELECT account,nickname,sex,age "
                             "FROM account WHERE account ='%1'").arg(ac);
    QSqlQuery query;
    query.exec(infoInDB);

    vector<string> ret;
    if(query.next())
    {
        for(int i=0;i<query.size();i++)
        {
            QString tmpvalue = query.value(i).toString();
            ret.push_back(tmpvalue.toStdString());
        }
    }

    return ret;

}

bool Account::IsAccountExist(string account)
{
    QString ac = QString::fromStdString(account);
    QString infoInDB=QString("SELECT account,password FROM account "
                             "WHERE account = '%1'").arg(ac);
    QSqlQuery query;
    query.exec(infoInDB);

    if(query.next())
        return true;
    else
        return false;
}


