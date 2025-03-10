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

void initNetwork(const DataType &data, Network &network)
{
    // 添加边的信息:边序号、终点索引、风阻、风量
    for (const auto &row : data)
        network.addEdge(row[0], row[1], row[2], stod(row[3]), stod(row[4]));
}

int main()
{
    Network network;
    string filePath = "../test00.csv";
    DataType data{readCSV(filePath)};

    initNetwork(data, network); // 初始化通风网络图

    network.printNetwork();
}
