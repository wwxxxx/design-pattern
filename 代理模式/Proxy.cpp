/*
代理模式：为其他对象提供一种代理以控制对这个对象的访问。

应用场景
（1）远程代理，也就是为一个对象在不同的地址空间提供局部代表。这样可以隐藏一个对象存在于不同地址空间的事实。
（2）虚拟代理，是根据需要创建开销很大的对象。通过他来存放实例化需要很长时间的真实对象。例如：图片加载的时候。
（3）安全代理，用来控制真是对象访问时的权限。
（4）智能指引，是指当调用真实的对象的时候，代理处理另外一些事。

根本原理：代理模式其实就是在访问对象的时候引入了一定程度的间接性，因为这种间接性，可以附加多种用途。
*/

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

//SchoolGirl类
class SchoolGirl
{
  private:
    string name;

  public:
    void setName(string name)
    {
        this->name = name;
    }
    string getName()
    {
        return name;
    }
};

//Subject类，定义了RealSubject和Proxy的共用接口，这样就可以在任何使用RealSubject的地方使用Proxy
class IGiveGift
{
  public:
    virtual void GiveDolls() = 0;
    virtual void GiveFlowers() = 0;
    virtual void GiveChocolate() = 0;
};

//RealSubject类,定义了Proxy所代表的真实实体
class Pursuit : public IGiveGift
{
  private:
    SchoolGirl *mm;

  public:
    Pursuit(SchoolGirl *mm)
    {
        this->mm = mm;
    }
    void GiveDolls()
    {
        cout << mm->getName() << " dolls" << endl;
    }
    void GiveFlowers()
    {
        cout << mm->getName() << " flowers" << endl;
    }
    void GiveChocolate()
    {
        cout << mm->getName() << " chocolate" << endl;
    }
};

//Proxy类，保存一个引用是的代理可以访问实体，并提供一个与Subject的接口相同的接口，这样代理就可以用来替代实体
class Proxy : public IGiveGift
{
  private:
    Pursuit *gg;

  public:
    Proxy(SchoolGirl *mm)
    {
        gg = new Pursuit(mm);
    }
    void GiveDolls()
    {
        gg->GiveDolls();
    }
    void GiveFlowers()
    {
        gg->GiveFlowers();
    }
    void GiveChocolate()
    {
        gg->GiveChocolate();
    }
};

int main()
{
    SchoolGirl *sg = new SchoolGirl();
    sg->setName("sg");

    Proxy *p = new Proxy(sg);

    p->GiveDolls();
    p->GiveFlowers();
    p->GiveChocolate();

    delete sg;
    sg = NULL;
    delete p;
    p = NULL;
    return 0;
}