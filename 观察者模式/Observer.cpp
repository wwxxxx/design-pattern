/*
观察者模式：定义了一种一对多的依赖关系，让多个观察者对象同时监听某一主题对象。这个主题对象在状态发生变化时，会通知所有观察者对象，使他们能够自动更新自己。

角色：

（1）Subject类：可以翻译为主题或者抽象通知者，一般用一个抽象类或者一个接口实现。他把所有对观察者对象的引用保存在一个聚集里，每个主题都可以有任何数量的观察者。抽象主题提供一个接口，可以增加和删除观察者对象。

（2）Observer类：抽象观察者，为所有的具体观察者定义一个接口，在得到主题的通知时更新自己。这个接口叫做更新接口。抽象观察者一般用一个抽象类或者一个接口实现。更新接口通常包含一个Update()方法，这个方法叫做更新方法。

（3）ConcreteSubject类：叫做具体主题或者具体通知者，将有关状态存入具体观察者对象；在具体主题的内部状态改变时，给所有登记过的观察者发出通知。

（4）ConcreteObserver类：具体观察者，实现抽象观察者角色所要求的更新接口，以便使本身的状态与主题的状态相协调。具体观察者角色可以保存一个指向具体主题对象的引用。

什么时候用观察者模式？

（1）当一个对象的改变需要同时改变其他对象的时候；

（2）而且不知道具体有多少对象有待改变时，应该考虑使用观察者模式；

（3）当一个抽象模型有两个方面，其中一方面依赖于另一方面，这时用观察者模式可以将这两者封装在独立的对象中使他们各自独立地改变和复用。

本质：

观察者模式所做的工作其实就是在解除耦合，让耦合的双方都依赖于抽象，而不是依赖于具体。从而使得各自的变化都不会影响另一边的变化。
*/

#include <iostream>
#include <cstdlib>
#include <string>
#include <list>
using namespace std;

class Subject;
class Boss;
class Observer;
class StockObserver;
class NBAObserver;

//Subject,抽象通知者或者主题
class Subject
{
  protected:
    string SubjectState;

  public:
    virtual void Attach(Observer *observer) = 0;
    virtual void Detach(Observer *observer) = 0;
    virtual void Notify() = 0;
    string GetSubjectState();
    void SetSubjectState(string state);
};

//ConcreteSubject,具体通知者或者具体主题
class Boss : public Subject
{
  private:
    list<Observer *> observers;
    string action;

  public:
    void Attach(Observer *observer);
    void Detach(Observer *observer);
    void Notify();
};

//Observer,抽象观察者
class Observer
{
  protected:
    string name;
    Subject *sub;

  public:
    Observer();
    Observer(string name, Subject *sub);
    virtual void Update();
    bool operator==(const Observer &) const;
};

//ConcreteObserver,具体观察者，股票观察者
class StockObserver : public Observer
{
  public:
    StockObserver();
    StockObserver(string name, Subject *sub);
    void Update();
};

//ConcreteObserver，具体观察者，NBA观察者
class NBAObserver : public Observer
{
  public:
    NBAObserver();
    NBAObserver(string name, Subject *sub);
    void Update();
};

string Subject::GetSubjectState()
{
    return SubjectState;
}

void Subject::SetSubjectState(string state)
{
    SubjectState = state;
}

Observer::Observer() {}

Observer::Observer(string name, Subject *sub)
{
    this->name = name;
    this->sub = sub;
}

void Observer::Update()
{
    cout << "Observer.Update()" << endl;
}

bool Observer::operator==(const Observer &observer) const
{
    return (this->name == observer.name) && (this->sub == observer.sub);
}

StockObserver::StockObserver() {}

StockObserver::StockObserver(string name, Subject *sub)
{
    this->name = name;
    this->sub = sub;
}

void StockObserver::Update()
{
    cout << sub->GetSubjectState() << " " << name << " "
         << "关闭股市行情，继续工作！" << endl;
}

NBAObserver::NBAObserver() {}

NBAObserver::NBAObserver(string name, Subject *sub)
{
    this->name = name;
    this->sub = sub;
}

void NBAObserver::Update()
{
    cout << sub->GetSubjectState() << " " << name << " "
         << "关闭NBA直播，继续工作！" << endl;
}

void Boss::Attach(Observer *observer)
{
    observers.push_back(observer);
}

void Boss::Detach(Observer *observer)
{
    list<Observer *>::iterator it;
    for (it = observers.begin(); it != observers.end(); ++it)
    {
        if (*it == observer)
        {
            observers.erase(it);
            break;
        }
    }
}

void Boss::Notify()
{
    list<Observer *>::iterator it;
    for (it = observers.begin(); it != observers.end(); ++it)
        (**it).Update();
}

int main()
{
    //通知者
    Subject *huhansan = new Boss();

    //4个观察者实例
    Observer *tongshi1 = new StockObserver("魏关姹", huhansan);
    Observer *tongshi2 = new StockObserver("易管察", huhansan);
    Observer *tongshi3 = new NBAObserver("霍华德", huhansan);
    Observer *tongshi4 = new NBAObserver("林书豪", huhansan);

    //将4个观察者都加入到通知者的通知队列中
    huhansan->Attach(tongshi1);
    huhansan->Attach(tongshi2);
    huhansan->Attach(tongshi3);
    huhansan->Attach(tongshi4);

    //魏关姹没有被老板通知到，减去。
    huhansan->Detach(tongshi1);

    huhansan->SetSubjectState("我胡汉三回来了！");

    //通知
    huhansan->Notify();

    delete huhansan;
    delete tongshi1;
    delete tongshi2;
    delete tongshi3;
    delete tongshi4;
    return 0;
}