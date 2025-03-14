#include "../inc/network.hpp"

//! ---------------------- Network 构造函数与基本操作 ----------------------
// 顶点数量
#define v_num vertexNum

/**
 * @brief 根据 CSV 数据构造网络
 *
 * 构造函数会遍历所有数据行，并调用 addEdge 添加边，从而构造整个有向图。
 *
 * @param data 二维字符串向量，每行包含边的序号、起点、终点、风阻和风量
 */
Network::Network(const DataType &data) : edgeNum(0), vertexNum(0), circuitNum(0), fanNum(0)
{
    // 添加边的信息:边序号、起点索引、终点索引、风阻、风量
    for (const auto &row : data)
        Network::addEdge(row[0], row[1], row[2], stod(row[3]), stod(row[4]));
}

/**
 * @brief 在图中添加一个顶点，如果顶点已存在则返回其索引
 *
 * @param vertexName 顶点名称
 * @return size_t 新顶点或已有顶点的索引
 */
size_t Network::addVertex(const string &vertexName)
{
    // 1. 在哈希表中查找顶点名
    auto it = vertexMap.find(vertexName);

    // 2. 如果已经存在，同步输出提示信息，并返回它的索引
    if (it != vertexMap.end())
        return it->second;
    // cerr << "顶点已存在，将返回其索引。\n";

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
    // 构造边对象，同时记录起点和终点索引
    graph[fromIndex].push_back({seq, fromIndex, toIndex, R, Q});
    edgeNum++;
}

/**
 * @brief 打印整个网络的信息（用于调试或查看）。
 *
 * 该函数会遍历所有顶点并输出：
 *
 *  - 顶点名称
 *
 *  - 该顶点的所有出边，包括边的目标顶点、风阻 (resistance)、风量 (airQuantity)。
 */
void Network::printNetwork() const
{
    cout << "\t终点\t风阻\t\t风量\n";
    for (size_t i = 0; i < vertexNum; i++)
    {
        cout << format("顶点 {}:\n", vertexName[i]);
        for (const auto &edge : graph[i])
            cout << format("->\t{}\t{}\t{}\n", vertexName[edge.to], edge.resistance, edge.airQuantity);
        cout << endl;
    }
}

/**
 * @brief 获取给定顶点索引所对应的所有边的引用。
 *
 * 该函数首先根据 `vertexIndex` 找到对应的顶点名称，然后在 `vertexMap` 中查询。
 * 如果未能找到该顶点，则抛出 `std::runtime_error`。
 * 否则返回 `graph[vertexIndex]`，即存储在邻接表中的边向量的引用。
 *
 * @param vertexIndex 要查询的顶点在内部容器中的索引
 * @return std::vector<Edge>& 引用，表示该顶点出发的所有边
 *
 * @throws std::runtime_error 当给定的顶点索引在 `vertexMap` 中找不到匹配的顶点名称时抛出
 */
vector<Edge> &Network::getEdges(size_t vertexIndex)
{
    auto it = vertexMap.find(vertexName[vertexIndex]);
    if (it == vertexMap.end())
        throw runtime_error("Network::getEdges can't find the vertex.");
    return graph[vertexIndex];
}

//! ---------------------- 无向图构造及生成树、余树枝构造 ----------------------

/**
 * @brief 判断从顶点 real 到顶点 next 的边是否在原始有向图中存在
 *
 * 遍历 real 顶点在原始有向图中的所有出边，若发现有边的目标与 next 匹配，则返回 true
 *
 * @param real 起始顶点索引
 * @param next 目标顶点索引
 * @return true 如果存在真实的边；否则返回 false
 */
bool Network::isReal(size_t real, size_t next) const
{
    for (const Edge &edge : graph[real])
        if (edge.to == next)
            return true;
    return false;
}

/**
 * @brief 根据有向图构造无向邻接表
 *
 * 遍历原始有向图中每个顶点的出边，对于每条边，
 * 在无向邻接表中添加两条边：一条为原始边，一条为反向边。
 *
 * @param ug 输出参数，构造完成的无向邻接表
 */
void Network::buildUndirectedGraph(Graph &ug) const
{
    // 初始化 undirectedGraph (无向图)
    ug.assign(vertexNum, vector<Edge>());

    // 根据有向图的邻街边列表，为无向图添加正向边和反向边
    for (size_t i = 0; i < vertexNum; i++)
        for (const Edge &edge : graph[i])
        {
            ug[i].emplace_back(edge); // 正向边：直接添加
            // 反向边：交换 from 与 to，其他属性不变
            ug[edge.to].push_back({edge.seq, edge.to, i, edge.resistance, edge.airQuantity});
        }
}

/**
 * @brief 基于无向图构造生成树和余树枝
 *
 * 该函数首先构造无向邻接表，然后调用 DFS 遍历所有顶点，
 * 构造一棵覆盖整个弱连通图的生成树，并收集所有余树枝。
 *
 * 为确保生成树边的方向与原始有向图一致，
 * 在 DFS 结束后，对生成树边进行检查，如有需要则交换起点和终点。
 *
 * @note
 * - 生成树保存在成员变量 `spanningTree` 中；
 *
 * - 余树枝保存在 `extraBranchs`。
 */
vector<int> Network::buildSpanningTree()
{
    // 构造无向邻接表 ug，确保弱连通图只有一棵生成树
    Graph undirectedGraph;
    buildUndirectedGraph(undirectedGraph);

    vector<bool> visited(v_num, false); ///< 记录每个顶点是否已被访问
    vector<int> parent(v_num, -1);      ///< DFS 中记录父节点，-1 表示无父节点

    //? 测试用
    // cout << "\n回溯过程:\n";
    // for (int i = 0; i < vertexNum; i++)
    //     cout << vertexName[i] << "\t";
    // cout << endl;

    // 对所有顶点进行 DFS，处理可能的多连通分量
    for (size_t i = 0; i < v_num; i++)
        if (!visited[i])
            DFS(i, visited, parent, undirectedGraph);

    // 后处理：确保生成树边的方向与原始有向图一致
    // 对每条生成树边，检查从 edge.from 到 edge.to 是否在原始图中存在
    for (Edge &edge : spanningTree)
    {
        bool find = false;
        size_t to = edge.to;

        for (const Edge &realEdge : graph[edge.from]) // 遍历 edge.from 在原始有向图中的出边
            if (to == realEdge.to)
            {
                find = true;
                break;
            }
        if (!find) // 如果找不到，则交换起点和终点，使之与原有向图一致
        {
            auto temp = edge.from;
            edge.from = edge.to;
            edge.to = temp;
        }
    }
    return parent;
}

/**
 * @brief 使用 DFS 在无向图上构造生成树和收集余树枝
 *
 * 遍历当前顶点 fromIdx 的所有无向邻接边，
 * 如果发现相邻顶点未被访问，则记录该边为生成树边，并递归调用 DFS；
 * 否则，如果相邻顶点已被访问且不为当前顶点的父节点，且边在原始有向图中真实存在，
 * 则将该边记录为余树枝。
 *
 * @param fromIdx 当前 DFS 访问的顶点索引
 * @param visited 布尔向量，标记顶点是否已访问
 * @param parent  DFS 中记录的父节点数组（-1 表示无父节点）
 * @param ug      无向邻接表（由 buildUndirectedGraph 构造）
 *
 * @note
 * - `buildSpanningTree()` 调用此函数来完成整个图的生成树构建
 */
void Network::DFS(size_t fromIdx, vector<bool> &visited, vector<int> &parent, Graph &ug)
{
    // 标记当前顶点已访问
    visited[fromIdx] = true;

    //? 测试用
    // for (auto it : parent)
    //     cout << it << "\t";
    // cout << endl;

    // 遍历当前顶点在无向图中的所有邻接边
    for (Edge &edge : ug[fromIdx])
    {
        size_t next;
        // 确定与 fromIdx 相连的“另一端”顶点
        if (edge.from == fromIdx)
            next = edge.to;
        else if (edge.to == fromIdx)
            next = edge.from;

        if (!visited[next])
        {
            parent[next] = static_cast<int>(fromIdx); // 记录 fromIdx 为 next 的父节点
            // 记录生成树边：边方向以无向 DFS 访问顺序为准
            spanningTree.push_back({edge.seq, fromIdx, next, edge.resistance, edge.airQuantity});
            DFS(next, visited, parent, ug); // 递归 DFS 遍历
        }
        // 如果 next 已访问且不为当前顶点的父节点，并且该边在有向图中真实存在，则记录为余树枝
        else if (next != static_cast<size_t>(parent[fromIdx]) && isReal(fromIdx, next))
            extraBranchs.push_back(edge);
    }
}

/**
 * @brief 打印生成树边的信息
 *
 * 输出生成树中所有边的序号、起点和终点。
 */
void Network::printSpanningTree() const
{
    if (spanningTree.empty())
    {
        cout << "找不到生成树\n";
        return;
    }
    cout << "\n生成树\n边序号\t起点\t\t终点\n";
    for (const Edge &edge : spanningTree)
        cout << format("{}:\t{}\t->\t{}\n", edge.seq, vertexName[edge.from], vertexName[edge.to]);
}

/**
 * @brief 打印余树枝边的信息
 *
 * 输出余树枝中所有边的序号、起点和终点。
 */
void Network::printExtraBranchs() const
{
    if (extraBranchs.empty())
    {
        cout << "找不到余树枝\n";
        return;
    }
    cout << "\n余树枝\n边序号\t起点\t\t终点\n";
    for (const Edge &edge : extraBranchs)
        cout << format("{}:\t{}\t->\t{}\n", edge.seq, getVertexName(edge.from), getVertexName(edge.to));
}

//! ---------------------- 无向树构造及回路生成 ----------------------*/

void Network::buildUndirectedTree(SpanningTree &ut)
{
    ut = spanningTree;
    for (Edge &edge : spanningTree)
    {
        Edge tmp(edge.seq, edge.to, edge.from, edge.resistance, edge.airQuantity);
        ut.push_back(tmp);
    }
}

vector<int> Network::getPath(int start, int tar, const vector<int> &par, bool &flag)
{
    int cur = start;
    vector<int> path;

    while (cur != -1)
    {
        path.push_back(cur);
        if (cur == tar)
        {
            flag = true;
            break;
        }
        cur = par[cur];
    }
    return path;
}

auto Network::collectEdgesFromPath(const vector<int> &path) -> vector<Edge>
{
    int length = path.size();
    vector<Edge> circuit(length - 1);

    for (int i = 0; i < length - 2; i++)
    {
        int u = path[i], v = path[i + 1];
        for (Edge &edge : spanningTree)
            if (edge.from == u && edge.to == v || edge.from == v && edge.to == u)
                circuit[i] = edge;
    }
    return circuit;
}

void Network::findCircuits() // TODO
{
    vector<int> parentList{buildSpanningTree()}; // 构造生成树和余树枝
    SpanningTree undirectedTree;
    buildUndirectedTree(undirectedTree); // 构造无向树
    size_t seq = 0;
    for (Edge &extraBranch : extraBranchs)
    {
        int u = extraBranch.from, v = extraBranch.to;
        bool flag = false;
        vector<int> pathU{getPath(u, v, parentList, flag)}, pathV;
        if (flag)
        {

            circuits.push_back({seq, collectEdgesFromPath(pathU)});
        }
        if (!flag)
            pathV = getPath(v, u, parentList, flag);

        //? 调试用
        cout << vertexName[v] << "\t" << vertexName[u] << endl;
        for (auto a : pathU)
            cout << vertexName[a] << " ";
        cout << "\t";
        for (auto b : pathV)
            cout << vertexName[b] << " ";
        cout << "\n"
             << endl;
    }
}
