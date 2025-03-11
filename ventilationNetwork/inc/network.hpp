#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "head.hpp"
using namespace std;

#define FROM size_t
#define TO size_t
// readCSV返回类型
using DataType = vector<vector<string>>;
// 生成树类型
using TreeEdge = vector<pair<FROM, TO>>;

struct Edge
{
    string seq;         // 边序号
    size_t to;          // 终点
    double resistance;  // 风阻
    double airQuantity; // 风量

    Edge(string edgeSeq, size_t to, double R, double Q) : seq(edgeSeq), to(to), resistance(R), airQuantity(Q) {}
};

class Network
{
    size_t edgeNum;    // 边数量
    size_t vertexNum;  // 顶点数量
    size_t circuitNum; // 回路数量
    size_t fanNum;     // 风机数量

    vector<vector<Edge>> graph; // 邻接表
    unordered_map<string, size_t> vertexMap;
    vector<string> vertexName;

    void DFS(size_t fromIdx, vector<bool> &visited, vector<int> &parent, TreeEdge &extraEdge);

public:
    Network(const DataType &data);
    inline size_t vertexCount() const { return vertexNum; }
    inline size_t edgeCount() const { return edgeNum; }

    size_t addVertex(const string &vertexName); //* finished

    void addEdge(const string &seq, const string &from, const string &to, const double R, const double Q); //* finished

    void printNetwork() const; //* finished

    string getVertexName(size_t to) const { return vertexName[to]; } //* finished

    vector<Edge> &getEdges(size_t vertexIndex);

    void buildSpanningTree(TreeEdge &spanningTreeEdge, TreeEdge &extraEdge);
};

#endif // NETWORK_HPP