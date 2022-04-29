#include<iostream>
using namespace std;

int main()
{
    union{
        char* abcd;
        struct{
            char a; 
            char b; 
            char c; 
            char d; 
        } str;
    } uni;
    
    uni.str.a = 'a';
    uni.str.b = 'b';
    uni.str.c = 'c';
    uni.str.d = 'd';
    cout << uni.abcd[0];
    return 0;
}