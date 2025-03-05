#include <iostream>
using namespace std;

struct student
{
    string name;
    int age;
    char id[20];
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
    return 0;
}
