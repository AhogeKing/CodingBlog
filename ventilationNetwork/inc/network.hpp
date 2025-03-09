#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "head.hpp"
using namespace std;

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

public:
    Network() : edgeNum(0), vertexNum(0), circuitNum(0), fanNum(0) {}
    inline size_t getVertexNum() const { return vertexNum; }
    inline size_t getEdgeNum() const { return edgeNum; }
    size_t addVertex(const string &vertexName);
    void addEdge(const string &seq, const string &from, const string &to, const double R, const double Q);
};

#endif // NETWORK_HPP