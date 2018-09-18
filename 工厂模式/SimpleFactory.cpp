/*
简单工厂模式包含三个角色
(1)工厂类Factory,用来制造产品.其中有create或generate之类的函数,根据不同的标识符生成不同的产品
(2)抽象产品类AbstractProduct:只有一个
(3)具体产品类ConcreteProduct:继承自抽象产品类,可以有多个

实现了松耦合,当需要增加一种新产品时,只需要做两点改动:
(1)增加一个继承自抽象产品(抽象的运算)的具体产品(一种具体的运算)
(2)在工厂类中,switch中,增加一种根据标识符产生新运算的case即可.
*/
#include <iostream>
#include <cstdlib>

using namespace std;

//抽象产品类
class Operation
{
  protected:
    double numberA;
    double numberB;

  public:
    double getA()
    {
        return numberA;
    }
    double getB()
    {
        return numberB;
    }
    void setA(double number)
    {
        numberA = number;
    }
    void setB(double number)
    {
        numberB = number;
    }
    virtual double GetResult()
    {
        double result = 0;
        return result;
    }
};

//具体产品类
class OperationAdd : public Operation
{
  public:
    double GetResult()
    {
        double result = 0;
        result = numberA + numberB;
        return result;
    }
};

class OperationSub : public Operation
{
  public:
    double GetResult()
    {
        double result = 0;
        result = numberA - numberB;
        return result;
    }
};

class OperationMul : public Operation
{
  public:
    double GetResult()
    {
        double result = 0;
        result = numberA * numberB;
        return result;
    }
};

class OperationDiv : public Operation
{
  public:
    double GetResult()
    {
        double result = 0;
        if (numberB != 0)
            result = numberA / numberB;
        return result;
    }
};

class OperationPow : public Operation
{
  public:
    double GetResult()
    {
        if (numberB == 0)
            return 1;
        if (numberB > 0)
        {
            double result = 1;
            for (int i = 0; i < numberB; i++)
                result *= numberA;
            return result;
        }
    }
};

class OperationFactory
{
  public:
    Operation *createOperation(char type)
    {
        Operation *oper;
        switch (type)
        {
        case '+':
            oper = new OperationAdd;
            break;
        case '-':
            oper = new OperationSub;
            break;
        case '*':
            oper = new OperationMul;
            break;
        case '/':
            oper = new OperationDiv;
            break;
        case '^':
            oper = new OperationPow;
            break;
        }
    }
};

//客户端
int main()
{
    Operation *oper = NULL;

    OperationFactory of;
    oper = of.createOperation('^');
    oper->setA(3);
    oper->setB(0);
    cout << oper->GetResult() << endl;
    if (oper != NULL)
    {
        delete oper;
        oper = NULL;
    }
}