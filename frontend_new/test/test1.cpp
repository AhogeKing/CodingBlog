#include <iostream>
using namespace std;

struct Student
{
    string name;
    int age;
    char id[20];
} student;

struct School
{
    string name;
    double price;

    Student getStudent(string name);
};

int add(int a, int b)
{
    int ret;
    ret = a + b;
    return ret;
}

int main()
{
    int a = 3;
    int b = 4;
    int c;
    c = add(a, b);
    printf("value of c : %d\n", c);

    auto d = .8;
    cout << d << endl;
    cout << 1 + 1 << 2 * 1 << endl;
    return 0;
}
