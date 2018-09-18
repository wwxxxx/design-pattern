/*
适配器模式：将一个类的接口转换成客户希望的另外一个接口。Adapter模式使得原来由于接口不兼容而不能一起工作的那些类可以一起工作。

角色：

（1）Target：这是客户所期待的接口，Target可以是具体的或抽象的类，也可以是接口。

（2）Adaptee：需要适配的类。

（3）Adapter：通过在内部包装一个Adaptee对象，把源接口转换成目标接口。

什么时候用？

（1）在想使用一个已存在的类，但是如果他的接口，也就是它的方法和你的要求不相同时，就应该考虑用适配器模式。

（2）用了适配器模式，客户代码可以统一调用统一接口就行了，这样可以更简单，更直接，更紧凑。

（3）要在双方都不太容易修改的时候再使用适配器模式适配，而不是一有不同是就使用它。
*/

#include <iostream>
#include <cstdlib>
#include <string>

//Target,此处为运动员
class Player
{
  protected:
    std::string name;

  public:
    Player(std::string name)
    {
        this->name = name;
    }
    virtual void Attack() = 0;
    virtual void Defense() = 0;
};

//Adaptee，此处为外籍中锋，它的接口和Target的接口不一样，需要翻译来帮忙转换
class ForeignCenter
{
  private:
    std::string name;

  public:
    void SetName(std::string name)
    {
        this->name = name;
    }
    std::string GetName()
    {
        return name;
    }
    void ForeignAttack()
    {
        std::cout << "外籍中锋  " << name << "  进攻" << std::endl;
    }

    void ForeignDefense()
    {
        std::cout << "外籍中锋  " << name << "  防守" << std::endl;
    }
};

//Adapter,此处为翻译
class Translator : public Player
{
  private:
    ForeignCenter *wjzf;

  public:
    Translator(std::string name) : Player(name)
    {
        wjzf = new ForeignCenter;
        wjzf->SetName(name);
    }
    ~Translator()
    {
        delete wjzf;
    }
    void Attack()
    {
        wjzf->ForeignAttack();
    }

    void Defense()
    {
        wjzf->ForeignDefense();
    }
};

//下面是普通的  接口和Target接口一样的 3个子类，必须要翻译
//前锋
class Forwards : public Player
{
  public:
    Forwards(std::string name) : Player(name) {}

    void Attack()
    {
        std::cout << "前锋  " << name << "  进攻" << std::endl;
    }

    void Defense()
    {
        std::cout << "前锋  " << name << "  防守" << std::endl;
    }
};

//中锋
class Center : public Player
{
  public:
    Center(std::string name) : Player(name) {}

    void Attack()
    {
        std::cout << "中锋  " << name << "  进攻" << std::endl;
    }

    void Defense()
    {
        std::cout << "中锋  " << name << "  防守" << std::endl;
    }
};

//后卫
class Guards : public Player
{
  public:
    Guards(std::string name) : Player(name) {}

    void Attack()
    {
        std::cout << "后卫  " << name << "  进攻" << std::endl;
    }

    void Defense()
    {
        std::cout << "后卫  " << name << "  防守" << std::endl;
    }
};

//Client
int main()
{
    Player *b = new Forwards("巴蒂尔");
    b->Attack();

    Player *m = new Guards("麦克格雷迪");
    m->Attack();

    //翻译告诉姚明，教练让你既要进攻，又要防守
    Player *ym = new Translator("姚明");
    ym->Attack();
    ym->Defense();

    delete b;
    delete m;
    delete ym;

    return 0;
}