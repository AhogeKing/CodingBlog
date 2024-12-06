//
// Created by LeoXavier on 24-12-2.
//
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <format>
#include <queue>
#include <stack>

struct Edge;

using Node = struct vexType{
    int nIndex;         // 顶点索引
    std::string data;   // 数据域 城市名称
    Edge* firstEdge;    // 指向第一条邻接边的指针
    Edge* lastEdge;     // 尾指针

    vexType() {
        nIndex = 0;
        firstEdge = nullptr;
        lastEdge = nullptr;
    }
};

struct Edge {
    int desIndex;       // 终点索引（邻接节点的索引）
    int weight;         // 权值（高速路长度）
    Edge *to;           // 指向下一条边的指针
};

struct Pair {   // 顶点权值对
    int souIdx;
    int distance;

    Pair(int nIndex, int weight) : souIdx(nIndex), distance(weight) {}

    bool operator<(const Pair &other) const {
        return distance > other.distance;
    }
};

using Ans = struct dist_way{
    int minWeight;
    std::vector<int> prev;
};

class WeightedGraph {
    Node **adjList;     // 邻接表，存储所有顶点的指针数组
    int nodeCount;      // 顶点数量 城市数量
    int edgeCount;      // 边数量 高速路数量

    bool static isAllVisited(const std::vector<bool> &visited) {
        for (auto i : visited)
            if (!i)
                return false;
        return true;
    }

    Ans dijkstra(Node *start, Node *destination) const {
        std::vector<bool> visited(nodeCount, false);    // 标记数组，初始化为false，表示所有节点均未被访问
        std::vector<int> dist(nodeCount, INT_MAX);      // 距离数组，将所有节点的距离初始化为INT_MAX
        std::vector<int> prev(nodeCount, -1);           // 前驱数组，记录前驱节点的索引，初始化为-1，表示均未被访问
        std::priority_queue<Pair> pq;

        dist[start->nIndex] = 0;
        pq.push(Pair(start->nIndex, 0));

        while (!pq.empty() && !visited[destination->nIndex]) {
            Pair temp = pq.top();
            pq.pop();
            int sourceIdx = temp.souIdx;           // 当前顶点索引

            if (visited[sourceIdx])                 // 跳过已处理顶点
                continue;

            Node *souv = adjList[sourceIdx];        // 获取顶点
            Edge *curvEdge = souv->firstEdge;       // 初始化当前边为当前顶点的首个邻接边

            while (curvEdge != nullptr) {           // 当邻接边不为空时
                if (visited[curvEdge->desIndex])    // 跳过已处理节点
                {
                    curvEdge = curvEdge->to;
                    continue;
                }

                int newDist = dist[sourceIdx] + curvEdge->weight;    // 新距离 = dist[当前顶点] + 边的权值
                if (newDist < dist[curvEdge->desIndex]) {           // 如果新距离小于dist[当前节点]
                    dist[curvEdge->desIndex] = newDist;             // 更新dist[当前节点]
                    prev[curvEdge->desIndex] = sourceIdx;        // 更新当前节点的前驱顶点
                    pq.push(Pair(curvEdge->desIndex, dist[curvEdge->desIndex]));
                }
                curvEdge = curvEdge->to;
            }
            visited[sourceIdx] = true;    // 在处理完所有邻接节点后将当前顶点标记为已处理
        }

        return {dist[destination->nIndex], prev};
    }

public:
    explicit WeightedGraph(const std::string &fileName) {
        std::ifstream mapReader(fileName);
        if (!mapReader.is_open()) {
            std::cerr << "Could not open file " << fileName << std::endl;
            exit(1);
        }
        std::string line, cityNum, roadNum;

        // 读取第一、二行，获取城市数量和高速路数量
        getline(mapReader, line);
        for (char c : line)
            if (c >= '0' && c <= '9')
                cityNum += c;
        getline(mapReader, line);
        for (char c : line)
            if (c >= '0' && c <= '9')
                roadNum += c;
        nodeCount = std::stoi(cityNum);
        edgeCount = std::stoi(roadNum);
        // std::cout << nodeCount << " " << edgeCount << std::endl;

        // 为邻接表分配空间
        adjList = new Node *[nodeCount];
        for (int i = 0; i < nodeCount; i++) {
            adjList[i] = new Node();
            adjList[i]->nIndex = i;
            adjList[i]->firstEdge = nullptr;
            adjList[i]->lastEdge = nullptr;
        }

        getline(mapReader, line);   // 跳过一行
        int index = 0;
        std::vector<std::string> tokens;    // 用于储存邻接信息
        while (getline(mapReader, line)) {
            if (index >= nodeCount) {
                std::cerr << "城市数量超过预期的 " << nodeCount << " 个。" << std::endl;
                exit(EXIT_FAILURE);
            }
            std::istringstream iss(line);
            getline(iss, adjList[index]->data, ';');    // 读取城市名称
            adjList[index]->nIndex = index;
            tokens.push_back(line.substr(line.find(';') + 1));  // 保存邻接信息
            index++;
        }

        if (index < nodeCount) {
            std::cerr << "实际城市数量少于预期的 " << nodeCount << " 个。" << std::endl;
            exit(EXIT_FAILURE);
        }
        mapReader.close();

        for (int v0Index = 0; v0Index < nodeCount; v0Index++) { // 构建邻接表
            const std::string &token = tokens[v0Index];
            std::istringstream iss(token);
            std::string block;

            while (getline(iss, block, ';')) {
                size_t pos = block.find(',');
                std::string cityName = block.substr(0, pos);
                int weight = std::stoi(block.substr(pos + 1));
                int v1index = getIndexByName(cityName);

                // 创建新边节点并添加到邻接表
                Edge* newEdge = new Edge();
                newEdge->desIndex = v1index;
                newEdge->weight = weight;
                newEdge->to = nullptr;

                // 将新边节点添加到当前顶点的边链表末尾（尾插法）
                if (adjList[v0Index]->firstEdge == nullptr) {
                    adjList[v0Index]->firstEdge = newEdge;
                    adjList[v0Index]->lastEdge = newEdge;
                }
                else {
                    adjList[v0Index]->lastEdge->to = newEdge; // 使用尾指针直接插入
                    adjList[v0Index]->lastEdge = newEdge;     // 更新尾指针
                }
            }
        }
    }

    int getIndexByName(const std::string &cityName) const {
        for (int i = 0; i < nodeCount; i++)
            if (adjList[i]->data == cityName)
                return i;
        return -1;
    }

    Node *getNodeByName(const std::string &nodeName) const {
        for (int i = 0; i < nodeCount; i++)
            if (nodeName == adjList[i]->data)
                return adjList[i];
        return nullptr;
    }

    void displayAns(const std::string &startName, const std::string &destinationName) const {
        int v0Index = -1, v1Index = -1;
        for (int i = 0; i < nodeCount && (v0Index == -1 || v1Index == -1); i++) {
            if (adjList[i]->data == startName)
                v0Index = i;
            if (adjList[i]->data == destinationName)
                v1Index = i;
        }

        if (v0Index == -1 || v1Index == -1) {
            std::cout << "找不到起点城市或终点城市!" << std::endl;
            return;
        }

        Ans ans = dijkstra(getNodeByName(startName), getNodeByName(destinationName));

        int desIndex = getIndexByName(destinationName);
        std::stack<int> st;
        for (int i = desIndex; i != -1; i = ans.prev[i])
            st.push(i);

        std::string passCity;
        while (!st.empty()) {
            int pos = st.top();
            st.pop();
            passCity += adjList[pos]->data;
            if (!st.empty())
                passCity += " -> ";
        }
        std::cout << std::format("最短路径沿途城市: {}\n"
                                 "最短路径长度: {}", passCity, ans.minWeight)
        << std::endl;
    }

    void display() const {
        for (int i = 0; i < nodeCount; i++) {
            std::cout << adjList[i]->data << ": ";
            Edge *curv = adjList[i]->firstEdge;
            while (curv != nullptr) {
                int pos = curv->desIndex;
                std::cout << std::format("-> {}({})", adjList[pos]->data, curv->weight);
                curv = curv->to;
            }
            std::cout << std::endl;
        }
    }

    ~WeightedGraph() {
        for (int i = 0; i < nodeCount; i++) {   // 释放每个顶点的边链表
            Edge* prev = adjList[i]->firstEdge;
            while (prev != nullptr) {
                Edge* curv = prev;
                prev = prev->to;
                delete curv;
            }
            delete adjList[i];  // 释放顶点
        }
        delete[] adjList; // 释放邻接表数组
    }
};