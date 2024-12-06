#include "weighted_graph.cpp"
using namespace std;

int main() {
    string filePath;
    // cin >> filePath;
    filePath = "../test_file.txt";
    // filePath = "../big_data_test.txt";
    // filePath = "../America_city.txt";
    // cout << "Enter the file path : ";
    // cin >> filePath;
    WeightedGraph weightedGraph(filePath);
    cout << "请输入起点城市和终点城市，中间空格间隔开:" << endl;
    string input1, input2;
    cin >> input1 >> input2;
    weightedGraph.displayAns(input1, input2);
    // weightedGraph.display();
    return 0;
}
