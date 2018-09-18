/*
工厂方法模式（Factory Method）：定义一个用于创建对象的接口，让子类决定实例化哪一个类。工厂方法是一个类的实例化延迟到其子类。

包含的角色
（1）抽象工厂
（2）具体工厂
（3）抽象产品
（4）具体产品

优势
（1）工厂方法模式是对简单工厂模式的稍微的改进。工厂方法模式的用意是定义一个创建产品对象的工厂接口，将实际工作推迟到子类中。
（2）与简单工厂模式相比，制造产品的工厂类不再 只有一个，而是每种具体产品类都对应一个生产它的具体工厂类。而这些具体工厂类的共同特征再被提取出来形成一个抽象产品类，这些具体产品类都继承自这个抽象产品类。
（3）当需要增加一种产品的时候，需要做的是：增加一种继承自抽象产品的具体产品类，增加一种继承在抽象工厂的具体工厂类，更改客户端。而不需要在简单工厂模式中那样更改工厂内的switch。
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
//下面是四个具体产品类
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

//抽象工厂类
class AbstractFactory
{
  public:
    virtual Operation *createOperation()
    {
        return new Operation;
    }
};
//下面是四个具体工厂类，分别用于产生四个具体产品
class AddFactory : public AbstractFactory
{
  public:
    Operation *createOperation()
    {
        Operation *oper = new OperationAdd;
        return oper;
    }
};

class SubFactory : public AbstractFactory
{
  public:
    Operation *createOperation()
    {
        Operation *oper = new OperationSub;
        return oper;
    }
};

class MulFactory : public AbstractFactory
{
  public:
    Operation *createOperation()
    {
        Operation *oper = new OperationMul;
        return oper;
    }
};

class DivFactory : public AbstractFactory
{
  public:
    Operation *createOperation()
    {
        Operation *oper = new OperationDiv;
        return oper;
    }
};

//客户端
int main()
{
    AbstractFactory *af = NULL;
    af = new AddFactory();

    Operation *oper = NULL;
    oper = af->createOperation();

    oper->setA(1);
    oper->setB(2);
    cout << oper->GetResult() << endl;

    if (af != NULL)
    {
        delete af;
        af = NULL;
    }
    if (oper != NULL)
    {
        delete oper;
        oper = NULL;
    }
    return 0;
}
