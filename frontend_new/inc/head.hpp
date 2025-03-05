#ifndef HEAD_HPP
#define HEAD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <format>
#include <regex>
using namespace std;

struct sourceRearder
{
    static fstream file;

    static void initReader(const string &path)
    {
        file.open(path, ios::in | ios::out);
        if (!file.is_open())
        {
            cerr << "Failed to open file: " << path << endl;
            throw runtime_error("File could not be opened");
        }
    }

    static string getAllLine()
    {
        if (!file.is_open())
            throw runtime_error("File is not open");

        string content, line;
        while (getline(file, line))
            content += line + "\n"; // 逐行追加到结果字符串
        return content;
    }

    static void closeReader()
    {
        if (file.is_open())
            file.close();
    }
};

#endif // HEAD_HPP