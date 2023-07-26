#include<iostream>
using namespace std;

int main()
{
    uint16_t sp = 0x0000;
    uint16_t* psp = &sp;
    (*psp)--;
    cout<<*psp<<endl;
    return 0;
}