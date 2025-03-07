#include <iostream>
using namespace std;
struct A;
struct A
{
    int x;
    int y;
};
struct A
{
    int x;
    int y;
} aliasA;
struct
{
    int x;
    int y;
} var;

void func()
{
    if (true)
    {
        struct A
        {
            int a = 1;
        };
    }
    cout << 2 > 3;
    int c = 3;
    {
        int a = 2;
        return;
    }
}

// int func(int a)
// {

// // 变量声明与函数声明的区别
// int a;         // 变量声明
// int b = 10;    // 带初始化的变量声明
// int compute(); // 函数声明

// // 全局函数声明示例
// int add(int x, int y); // 返回 int，两个参数
// // void greet(string name);             // 返回 void，一个 string 参数
// double multiply(double m, double n); // 返回 double，两个参数
// bool isEven(int number);             // 返回 bool，一个参数
// float average(int a, int b, int c);  // 返回 float，三个参数

// // 函数定义示例
// char getChar()
// { // 返回 char，无参数
//     return 'c';
// }
// int square(int num)
// { // 返回 int，一个参数
//     return num * num;
// }

// // 结构体内的成员函数声明
// struct Student
// {
//     int getAge(); // 返回 int，无参数
//     // void setName(string name); // 返回 void，一个参数
// };
