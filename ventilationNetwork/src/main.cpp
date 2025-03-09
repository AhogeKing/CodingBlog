#include "../inc/head.hpp"

vector<vector<string>> readCSV(const string &filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << format("无法打开文件: {}\n", filename);
        return {};
    }

    string line;
    getline(file, line); // 跳过第一行（标题）

    // 读取每一行
    vector<vector<string>> data;
    while (getline(file, line))
    {
        stringstream ss(line);
        string field;
        vector<string> fields;
        int cnt = 0;

        // 分割字段
        while (getline(ss, field, ','))
        {
            switch (cnt)
            {
            case 9:
                cnt = -1;
                break;
            case 8:
            case 7:
            case 2:
            case 1:
            case 0:
                if (!field.empty() && field != "\r" && field != "\n")
                    fields.push_back(field);
            default:
                break;
            }
            cnt++;
        }
        data.push_back(fields);
    }
    return data;
}

int main()
{
    Network network;
    string filePath = "../test00.csv";
    vector<vector<string>> data{readCSV(filePath)};

    for (const auto row : data)
    {
        Edge tmp(row[0], stoi(row[2]), stod(row[3]), stod(row[4]));
        string vertexName{row[1]};
    }
}
