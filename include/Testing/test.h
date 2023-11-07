#include <iostream>

class C
{
  private:
  public:
    int x;
    C(int c)
    {
        x = c;
        std::cout << "C is created" << std::endl;
    }
    void log()
    {
        std::cout << "C: " << x << std::endl;
    }
};
class A
{
  private:
  public:
    int a;
    C c;
    A(int a, C c) : a(a), c(c)
    {
        std::cout << "A is created" << std::endl;
    }
    void log()
    {
        std::cout << "A: " << a << " " << c.x << std::endl;
    }
};

class B
{
  private:
    int x;

  public:
    A a;
    B(A a, int x) : a(a), x(x)
    {
        std::cout << "B is created" << std::endl;
    }
    void log()
    {
        std::cout << "B: " << a.a << " " << a.c.x << " " << x << std::endl;
    }
};
