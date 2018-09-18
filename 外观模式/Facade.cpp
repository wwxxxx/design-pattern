/*
外观模式：为子系统中的一组接口提供一个一致的界面，此模式定义了一个高层接口，这个接口使得这一子系统更加容易使用。

Q：外观模式在什么时候使用呢？
A：分为三个阶段：
（1）首先，在设计初期阶段，应该要有意识的将不同的两个层分离。
（2）第二，在开发阶段，子系统往往因为不断的重构演化而变得越来越复杂，大多数的模式使用时也会产生很多很小的类，这本是好事儿，但是也给外部调用他们的用户程序带来了使用上的困难，增加外观Facade可以提供一个简单的接口，减少他们之间的依赖。
（3）第三，在维护一个遗留的大型系统时，可能这个系统已经非常难以维护和扩展了，但因为它包含非常重要的功能，新的需求开发必须要依赖于它。此时用外观模式Facade也是非常合适的。

具体而言：为新系统开发一个外观Facade类，来提供设计粗糙或高度复杂的遗留代码的比较清晰简单的接口，让新系统与Facade对象交互，Facade与遗留代码交互所有复杂的工作。
*/

#include <iostream>
#include <string>
using namespace std;

//SubSystem Class，实现子系统的功能，处理Facade对象指派的任务。注意子类中没有Facade任何信息，即没有对Facade对象的引用。
class SubSystemOne
{
  public:
    void MethodOne()
    {
        cout << "1" << endl;
    }
};

class SubSystemTwo
{
  public:
    void MethodTwo()
    {
        cout << "2" << endl;
    }
};

class SubSystemThree
{
  public:
    void MethodThree()
    {
        cout << "3" << endl;
    }
};

//Facade Class，外观类，知道有哪些子系统类，负责处理请求，将客户的请求代理给适当的子系统对象。
class Facade
{
  private:
    SubSystemOne *one;
    SubSystemTwo *two;
    SubSystemThree *three;

  public:
    Facade()
    {
        one = new SubSystemOne();
        two = new SubSystemTwo();
        three = new SubSystemThree();
    }
    ~Facade()
    {
        delete one;
        delete two;
        delete three;
    }
    void MethodA()
    {
        cout << "A:" << endl;
        one->MethodOne();
        two->MethodTwo();
        cout << endl;
    }
    void MethodB()
    {
        cout << "B:" << endl;
        three->MethodThree();
        cout << endl;
    }
};

int main()
{
    Facade *f = new Facade();
    f->MethodA();
    f->MethodB();
    delete f;
    return 0;
}