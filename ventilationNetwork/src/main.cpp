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
    //? 文件过大时使用
    // ofstream outfile("../out/bigTestOutput.txt", ios::out | ios::trunc);
    // if (!outfile)
    // {
    //     cerr << "无法打开文件" << endl;
    //     return 1;
    // }
    // // 保存 std::cout 的原始缓冲区
    // streambuf *coutbuf = cout.rdbuf();
    // // 重定向 std::cout 到文件
    // cout.rdbuf(outfile.rdbuf());

    //? 测试文件路径
    // string filePath = "../test/test00.csv";
    // string filePath = "../test/test01.csv";
    // string filePath = "../test/test02.csv";
    string filePath = "../test/test03.csv";
    // string filePath = "../test/test04.csv";
    // string filePath = "../test/bigTest1.csv";
    DataType data{readCSV(filePath)};

    Network network(data);
    network.printNetwork();
    network.findCircuits();

    //? 文件过大时使用
    // outfile.close();
    // // 恢复 std::cout 的缓冲区
    // cout.rdbuf(coutbuf);
    // cout << "success!\n";
}
