#include "../inc/head.hpp"

DataType readCSV(const string &filename)
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
    DataType data;
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
    string filePath = "../test00.csv";
    DataType data{readCSV(filePath)};

    Network network(data);
    network.printNetwork();
}
