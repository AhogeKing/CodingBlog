#include "../inc/network.hpp"

/**
 * @brief 向图中添加一个新的顶点。如果顶点已存在，则直接返回其索引。
 *
 * @param vertexName 顶点名称
 * @return size_t 该顶点的索引（如果是新顶点，则返回新分配的索引；如果已存在，则返回已有索引）
 */
size_t Network::addVertex(const string &vertexName)
{
    // 1. 在哈希表中查找顶点名
    auto it = vertexMap.find(vertexName);

    // 2. 如果已经存在，同步输出提示信息，并返回它的索引
    if (it != vertexMap.end())
    {
        cerr << "顶点已存在，将返回其索引。\n";
        return it->second;
    }

    // 3. 如果不存在，则：
    //   a) 在哈希表中记录 "顶点名 -> 顶点索引"
    //   b) 为该顶点在邻接表中开一个空的 Edge 向量
    //   c) 在顶点名称数组中附加此顶点名
    vertexMap[vertexName] = vertexNum;
    graph.push_back(vector<Edge>());
    this->vertexName.push_back(vertexName);

    // 4. 返回当前顶点索引，并将计数自增（保证下次顶点索引不同）
    return vertexNum++;
}

/**
 * @brief 向图中添加一条有向边：from -> to
 *
 * 如果顶点 from 或 to 不存在，则会自动创建对应顶点。
 * 此函数在邻接表 graph[fromIndex] 中插入新的边信息，包括：
 *  - seq: 边的标识符
 *  - R:   风阻 (resistance)
 *  - Q:   风量 (airQuantity)
 *
 * @param seq  边的序号或标识符
 * @param from 边的起始顶点名称
 * @param to   边的目标顶点名称
 * @param R    边对应的风阻
 * @param Q    边对应的风量
 */
void Network::addEdge(const string &seq, const string &from, const string &to, const double R, const double Q)
{
    size_t fromIndex = addVertex(from);
    size_t toIndex = addVertex(to);
    graph[fromIndex].push_back({seq, toIndex, R, Q}); // 将边插入到 fromIndex 对应的邻接表中
    edgeNum++;
}