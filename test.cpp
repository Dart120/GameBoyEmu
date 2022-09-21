#include <SDL2/SDL.h>

#include<iostream>


using namespace std;

int multiply(int x, int y)
{
    return x * y;
}

template <class F>
void foo(int x, int y, F f)
{
    cout << f(x, y) << endl;
}

template <class F>
void bar(int x, int y)
{
    cout << F(x, y) << endl;
}

int main()
{
    foo(3, 4, multiply); // works
    // bar<multiply>(3, 4); // fails

    return 0;
}
