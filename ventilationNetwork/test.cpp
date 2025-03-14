#include <iostream>
#include <sstream>
using namespace std;

int main()
{
    // 使用stringstream
    stringstream ss;
    string str = "123456789";
    string str0 = "abc def";
    ss << str;
    ss << str0;
    string str1;
    ss >> str1;
    cout << str1 << endl;
    str = "23";
    cout << str << endl;
}