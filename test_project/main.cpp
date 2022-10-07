#include<iostream>
#include "header.h"
using namespace std;

int returns_number(int num){
    return num;
}


int main()
{
    example<int(int,int)> example_;
    example_.foo(returns_number);
    return 0;
}