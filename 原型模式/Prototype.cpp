/*
原型模式（Prototype）：用原型示例指定创建对象的种类，并且通过拷贝这些原型创建新的对象。

（1）原型模式实际上就是从一个对象再创建另外一个可定制的对象，而且不需要知道任何创建的细节。
（2）一般在初始化的信息不发生变化的情况下，克隆是最好的办法。这既隐藏了对象创建的细节，有对性能是大大的提高。因为如果不用Clone，每次new，都需要执行一次构造函数，如果构造函数的执行时间很长，那么多次的执行这个初始化操作就实在是太低效了。
（3）浅复制和深复制：

浅复制：被复制的对象的所有变量都含有与原来的对象相同的值，而所有对其他对象的引用都仍然指向原来的对象。
深复制：把引用对象的变量指向复制过的新对象，而不是原有的被引用的对象。
Clone的时候使用深复制。
*/

#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;

class WorkExperience
{
  private:
    string workDate;
    string company;

  public:
    WorkExperience() {}
    ~WorkExperience() {}
    //供克隆调用的构造函数
    WorkExperience(WorkExperience *work)
    {
        this->workDate = work->workDate;
        this->company = work->company;
    }
    string GetWorkDate()
    {
        return workDate;
    }
    void SetWorkDate(string workDate)
    {
        this->workDate = workDate;
    }
    string GetCompany()
    {
        return company;
    }
    void SetCompany(string company)
    {
        this->company = company;
    }
    //clone
    WorkExperience *Clone()
    {
        //调用供克隆调用的函数
        return new WorkExperience(this);
    }
};

//原型类,声明一个克隆自身的接口
class Prototype
{
  protected:
    string name;
    string sex;
    string age;
    string timeArea;
    string company;

  public:
    virtual void SetPersonalInfo(string sex, string age) = 0;
    virtual void Display() = 0;
    virtual Prototype *Clone() = 0;
};

//具体原型类,即ConcretePrototype类,实现一个克隆自身的操作
class Resume : public Prototype
{
  private:
    WorkExperience *work;

  public:
    Resume(string name)
    {
        this->name = name;
        work = new WorkExperience();
    }
    ~Resume()
    {
        if (work != NULL)
        {
            delete work;
            work = NULL;
        }
    }
    //供克隆调用的构造函数
    Resume(WorkExperience *work)
    {
        this->work = work->Clone();
    }
    void SetPersonalInfo(string sex, string age)
    {
        this->sex = sex;
        this->age = age;
    }
    void SetWorkExperience(string workDate, string company)
    {
        work->SetWorkDate(workDate);
        work->SetCompany(company);
    }
    void Display()
    {
        cout << name << ' ' << sex << ' ' << age << endl;
        cout << work->GetWorkDate() << ' ' << work->GetCompany() << endl;
    }
    Resume *Clone()
    {
        Resume *cloneResume = new Resume(work);
        cloneResume->name = this->name;
        cloneResume->age = this->age;
        cloneResume->sex = this->sex;
        return cloneResume;
    }
};

int main()
{
    Resume *a = new Resume("大鸟");
    a->SetPersonalInfo("男", "29");
    a->SetWorkExperience("1998-2000", "XX公司");

    Resume *b = a->Clone();
    b->SetWorkExperience("1998-2006", "YY公司");

    Resume *c = b->Clone();
    c->SetPersonalInfo("男", "24");
    c->SetWorkExperience("1998-2003", "ZZ公司");

    a->Display();
    b->Display();
    c->Display();

    delete a;
    delete b;
    delete c;
    a = b = c = NULL;
    return 0;
}