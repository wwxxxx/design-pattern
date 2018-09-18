/*
单例模式：保证一个类仅有一个实例，并提供一个访问他的全局访问点。[DP]

通常我们可以让一个全局变量使得一个对象被访问，但它不能防止你实例化多个对象。一个最好的办法就是，让类自身负责保护它的唯一实例。这个类可以保证没有其他实例可以被创建，并且他可以提供一个访问该实例的方法。

使用单例模式，只能保证一个线程内对象不会被多次创建，而不不能保证多线程的情况。因此，需要考虑多线程的话，就要用锁。
*/

#include <iostream>
#include <mutex>
using namespace std;

class Lock
{
  private:
    mutex m;

  public:
    void lock() { m.lock(); }
    void unlock() { m.unlock(); }
};

//懒汉模式
class Singleton
{
  public:
    static Singleton *getInstance()
    {
        if (m_Instance == NULL)
        {
            locker->lock();
            if (m_Instance == NULL)
                m_Instance = new Singleton();
            locker->unlock();
        }
        return m_Instance;
    }
    static void destoryInstance()
    {
        if (m_Instance != NULL)
        {
            delete m_Instance;
            m_Instance = NULL;
        }
    }
    int getTest() { return m_Test; }
    mutex m;

  private:
    Singleton() {}
    Singleton(const Singleton &) {}
    Singleton &operator=(const Singleton &) {}
    static Singleton *m_Instance;
    static Lock *locker;
    int m_Test;
};

Singleton *Singleton::m_Instance = NULL;

int main()
{
    Singleton *sObj = Singleton::getInstance();
    cout << sObj->getTest() << endl;
    Singleton::destoryInstance();
    return 0;
}