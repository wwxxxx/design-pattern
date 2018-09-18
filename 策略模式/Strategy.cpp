/*
策略模式:定义了算法家族,分别封装起来,让他们之间可以互相替换
此模式让算法的变化不会影响到使用算法的客户
*/

#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
using namespace std;

//父类抽象类
class CashSuper
{
  public:
    virtual double acceptCash(double money) = 0;
};

//子类:正常付费类型
class CashNormal : public CashSuper
{
  public:
    double acceptCash(double money)
    {
        return money;
    }
};

//子类:返现类型
class CashReturn : public CashSuper
{
  private:
    double moneyCondition;
    double moneyReturn;

  public:
    CashReturn(double moneyCondition, double moneyReturn)
    {
        this->moneyCondition = moneyCondition;
        this->moneyReturn = moneyReturn;
    }
    double acceptCash(double money)
    {
        double result = money;
        if (money > moneyCondition)
            result = money - floor(money / moneyCondition) * moneyReturn;
        return result;
    }
};

//子类:打折扣类型
class CashRebate : public CashSuper
{
  private:
    double moneyRebate;

  public:
    CashRebate(double moneyRebate)
    {
        this->moneyRebate = moneyRebate;
    }
    double acceptCash(double money)
    {
        return money * moneyRebate;
    }
};

class CashContext
{
  private:
    CashSuper *cs;

  public:
    CashContext(int type) : cs(NULL)
    {
        switch (type)
        {
        case 1:
            cs = new CashNormal();
            break;
        case 2:
            cs = new CashReturn(300, 100);
            break;
        case 3:
            cs = new CashRebate(0.8);
            break;
        default:;
        }
    }
    ~CashContext()
    {
        if (cs != NULL)
        {
            delete cs;
            cs = NULL;
        }
    };
    double GetResult(double money)
    {
        return cs->acceptCash(money);
    }
};

int main()
{
    double total = 0;
    double totalPrices = 0;

    //正常收费
    CashContext *cc1 = NULL;
    cc1 = new CashContext(1);
    totalPrices = cc1->GetResult(300);
    total += totalPrices;
    cout << totalPrices << ' ' << total << endl;
    totalPrices = 0;

    //返现类型
    CashContext *cc2 = NULL;
    cc2 = new CashContext(2);
    totalPrices = cc2->GetResult(700);
    total += totalPrices;
    cout << totalPrices << ' ' << total << endl;
    totalPrices = 0;

    //打折类型
    CashContext *cc3 = NULL;
    cc3 = new CashContext(3);
    totalPrices = cc3->GetResult(300);
    total += totalPrices;
    cout << totalPrices << ' ' << total << endl;
    totalPrices = 0;
    if (cc1 != NULL)
    {
        delete cc1;
        cc1 = NULL;
    }
    if (cc2 != NULL)
    {
        delete cc2;
        cc2 = NULL;
    }
    if (cc3 != NULL)
    {
        delete cc3;
        cc3 = NULL;
    }
    return 0;
}