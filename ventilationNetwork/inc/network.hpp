#ifndef NETWORK_HPP
#define NETWORK_HPP
#include "head.hpp"
using namespace std;

/**
 * @brief 别名：readCSV 后返回的二维数据结构，每行都是一个 string 向量。
 */
using DataType = vector<vector<string>>;

/**
 * @brief 表示网络中的一条有向边。
 *
 * 该结构体包含边标识、起点、终点以及与通风相关的风阻与风量。
 *
 * @param seq         边的标识符（可为字符串编号）
 * @param from        边的起点顶点索引
 * @param to          边的终点顶点索引
 * @param resistance  此边的风阻系数
 * @param airQuantity 此边的风量值
 */
struct Edge
{
    string seq;         // 边序号
    size_t from;        // 起点
    size_t to;          // 终点
    double resistance;  // 风阻
    double airQuantity; // 风量

    Edge(string edgeSeq, size_t f, size_t to, double R, double Q) : seq(edgeSeq), from(f), to(to), resistance(R), airQuantity(Q) {}
};
// 图采用邻接表存储，每个元素是一个 Edge 的向量
using Graph = vector<vector<Edge>>;

/**
 * @brief 表示生成树或余树枝，均为一维 Edge 向量
 */
using SpanningTree = vector<Edge>;

// 回路结构体，有两个成员，回路索引、组成回路的边的一维向量 `vector <Edge>`
struct Circuit
{
    size_t index;                // 回路索引
    vector<Edge> edgesInCircuit; // 回路内的边
};

/**
 * @brief 通风网络类
 *
 * 该类用于表示并操作矿井通风网络，包含有向图、生成树、余树枝以及回路的构造和分析。
 */
class Network
{
    size_t edgeNum;    // 边数量
    size_t vertexNum;  // 顶点数量
    size_t circuitNum; // 回路数量
    size_t fanNum;     // 风机数量

    Graph graph;                             // 有向邻接表，记录原始网络
    unordered_map<string, size_t> vertexMap; // 顶点名称到索引的映射
    vector<string> vertexName;               // 索引到顶点名称的反向映射

    // 有向图基本操作
    size_t addVertex(const string &vertexName);
    void addEdge(const string &seq, const string &from, const string &to, const double R, const double Q);

    // 生成树和余树枝部分
    SpanningTree spanningTree; // 生成树
    SpanningTree extraBranchs; // 余树枝

    bool isReal(size_t real, size_t next) const;
    void buildUndirectedGraph(Graph &ug) const;
    vector<int> buildSpanningTree();
    void DFS(size_t fromIdx, vector<bool> &visited, vector<int> &parent, Graph &ug);

    // 回路部分
    vector<Circuit> circuits; // 回路向量

    void buildUndirectedTree(SpanningTree &ut); // 无向树
    vector<int> getPath(int start, int tar, const vector<int> &par, bool &flag);
    auto collectEdgesFromPath(const vector<int> &path) -> vector<Edge>;

public:
    // 通风网络图构造函数与基本操作
    Network(const DataType &data);
    inline size_t vertexCount() const { return vertexNum; }
    inline size_t edgeCount() const { return edgeNum; }
    void printNetwork() const;
    inline const string &getVertexName(size_t to) const { return vertexName[to]; }
    vector<Edge> &getEdges(size_t vertexIndex);

    // 生成树和余树枝输出
    void printSpanningTree() const;
    void printExtraBranchs() const;

    // 回路部分
    void findCircuits(); // TODO
};

#endif // NETWORK_HPP