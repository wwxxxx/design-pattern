/*
建造者模式（Builder）：将一个复杂对象的构建和它的表示分离，使得同样的构建过程可以创建不同的表示。

角色：
（1）Builder：是为创建一个Product对象的各个部件指定的抽象接口。
（2）ConcreteBuilder：是具体创建者，实现Builder接口，构造和装配各个部件。
（3）Product：具体的产品角色。
（4）Director：指挥者，他是构建一个使用Builder接口的对象。

Q：什么时候使用建造者模式？
A：它主要是用于创建一些复杂的对象，这些对象内部构造间的建造顺序通常是稳定的，但对象内部的构建通常面临着复杂的变化。

Q：使用建造者模式的好处？
A：建造者模式的好处就是使得建造代码与表示代码分离，由于建造者隐藏了该产品是如何组装的，所以若需要改变一个产品的内部表示，只需要再定义一个具体的建造者就可以了。
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

//产品类,有多个部件组成
class Product
{
  private:
    vector<string> parts;

  public:
    //添加产品部件
    void Add(string part)
    {
        parts.push_back(part);
    }
    //列举所有的产品部件
    void Show()
    {
        cout << "product:" << endl;
        for (int i = 0; i < parts.size(); i++)
            cout << parts[i] << endl;
    }
};

//Builder,抽象建造者
class Builder
{
  public:
    virtual void BuildPartA() = 0;
    virtual void BuildPartB() = 0;
    virtual Product *GetResult() = 0;
};

//ConcreteBuilder,具体建造者类
class ConcreteBuilder1 : public Builder
{
  private:
    Product *product;

  public:
    ConcreteBuilder1()
    {
        product = new Product();
    }
    ~ConcreteBuilder1()
    {
        delete product;
    }
    void BuildPartA()
    {
        product->Add("A");
    }
    void BuildPartB()
    {
        product->Add("B");
    }
    Product *GetResult()
    {
        return product;
    }
};

class ConcreteBuilder2 : public Builder
{
  private:
    Product *product;

  public:
    ConcreteBuilder2()
    {
        product = new Product();
    }
    ~ConcreteBuilder2()
    {
        delete product;
    }
    void BuildPartA()
    {
        product->Add("X");
    }
    void BuildPartB()
    {
        product->Add("Y");
    }
    Product *GetResult()
    {
        return product;
    }
};

//指挥者类
class Director
{
  public:
    void Construct(Builder *builder)
    {
        builder->BuildPartA();
        builder->BuildPartB();
    }
};

//客户不知道具体的建造过程
int main()
{
    Director *director = new Director();

    Builder *builder1 = new ConcreteBuilder1();
    Builder *builder2 = new ConcreteBuilder2();

    cout << "1" << endl;
    director->Construct(builder1);
    Product *p1 = builder1->GetResult();
    p1->Show();
    cout << endl;

    cout << "2" << endl;
    director->Construct(builder2);
    Product *p2 = builder2->GetResult();
    p2->Show();
    cout << endl;

    delete director;
    delete builder1;
    delete builder2;
    return 0;
}