/*
模板方法模式：定义一个操作中的算法的骨架，而将一些步骤延迟到子类中。模板方法使得子类可以不改变一个算法的结构即可重定义该算法的某些特定步骤。

角色：
（1）AbstractClass：是抽象类，其实也就是一个抽象模板，定义并实现了一个模板方法。这个模板方法一般是一个具体方法，它给出了一个顶级逻辑的框架，而逻辑的组成步骤在相应的抽象操作中，推迟到子类实现。顶级逻辑也有可能调用一些具体方法。
（2）ConcreteClass：实现父类所定义的一个或多个抽象方法。每一个AbstractClass都可以有任意多个ConcreteClass与之对应，而每一个ConcreteClass都可以给出这些抽象方法（也就是顶级逻辑的组成步骤）的不同实现，从而使得顶级逻辑的实现各不相同。

总结：当不变的和可变的行为在方法的子类实现中混合在一起的时候，不变的行为就会在子类中重复出现。我们通过模板方法模式，把这些行为搬移到单一的地方，这样帮助子类摆脱重复的不变行为的纠缠。
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

//AbstractClass,实现了一个模板,定义了算法的骨架,组成骨架的具体步骤放在子类中实现
class TestPaper
{
  public:
    void TestQuestion1()
    {
        cout << "1: " << Answer1() << endl;
    }
    void TestQuestion2()
    {
        cout << "2: " << Answer2() << endl;
    }
    void TestQuestion3()
    {
        cout << "3: " << Answer3() << endl;
    }

  protected:
    virtual string Answer1()
    {
        return "";
    }
    virtual string Answer2()
    {
        return "";
    }
    virtual string Answer3()
    {
        return "";
    }
};

//ConcreteClass,实现具体步骤
class TestPaperA : public TestPaper
{
  protected:
    virtual string Answer1()
    {
        return "a";
    }
    virtual string Answer2()
    {
        return "b";
    }
    virtual string Answer3()
    {
        return "c";
    }
};

class TestPaperB : public TestPaper
{
  protected:
    virtual string Answer1()
    {
        return "c";
    }
    virtual string Answer2()
    {
        return "b";
    }
    virtual string Answer3()
    {
        return "a";
    }
};

int main()
{
    cout << "A: " << endl;
    TestPaper *studentA = new TestPaperA();
    studentA->TestQuestion1();
    studentA->TestQuestion2();
    studentA->TestQuestion3();
    cout << endl;

    cout << "B: " << endl;
    TestPaper *studentB = new TestPaperB();
    studentB->TestQuestion1();
    studentB->TestQuestion2();
    studentB->TestQuestion3();
    cout << endl;

    if (studentA != NULL)
    {

        delete studentA;
        studentA = NULL;
    }
    if (studentA != NULL)
    {

        delete studentB;
        studentB = NULL;
    }
    return 0;
}