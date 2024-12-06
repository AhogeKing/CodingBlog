# 数据结构实验自主学习结题报告

## 一、引言

在本次数据结构实验选题中，需要设计一个程序，根据给定的全国部分高速公路地图，计算从源点城市到终点城市的最短路径，并显示具体路径。为了实现这一目标，选择使用有权邻接表来表示无向加权图，并采用 Dijkstra 算法计算最短路径。本文将详细解释选择这些数据结构和算法的原因，分析代码中各个结构体和类成员的作用，探讨程序的优势，并提出未来优化的方向。

## 二、题目分析

### **1、问题背景**

在智能驾驶和导航系统中，我们需要在城市网络中找到从源点到终点的最短路径。城市之间通过道路连接，每条道路都有一定的距离或权重。很明显，这与数据结构中图的定义较为贴切，为了在计算机程序中表示和处理这种城市网络，我们需要将城市网络抽象为图。

---



### **2、城市网络抽象为图**

1.  **图的定义**

    -   **顶点**：图中的顶点，表示对象或位置。在城市网络中，顶点代表城市。
    -   **边**：连接顶点的线，表示顶点之间的关系或通路。在城市网络中，边代表连接城市的道路。
    -   **权重**：边上附加的数值，表示一对顶点之间的某种度量。在当前城市网络中，权重表示道路的距离（路程）。

    

2.  **图的类型**

    -   **无向图**：边没有方向，表示关系是双向的。在城市网络中，道路通常是双向的，车辆可以在道路上双向行驶，因此适合使用无向图。
    -   **有向图**：边有方向，表示关系是单向的。如果道路是单行线，那么需要用有向图表示。

显然，经过分析，当前的城市网络图适合定义为无向权值图。

----



### 3、使用无向权值图的原因

1.  **城市网络的特点**

    -   **双向通行：**大多数公路允许车辆在两端城市之间双向行驶。
    -   **距离重要性：**在导航中，我们着重关注两城市之间的距离，以找到最短路径。

    

2.  **无向图的实用性**

    -   **对称性：**无向图中的边表示两节点之间的双向连接，适合表示双向道路。
    -   **简化模型：**使用无向图可以简化模型，不需要为每条道路建立两个方向的边。

3.  **权值的必要性**

    -   **距离度量：**权值能够准确表示两城市之间的距离，这对于计算最短路径至关重要。
    -   **灵活性：**权值还可以表示其他度量，如通行时间、费用等，增强模型的通用性。

---



### **4、选择邻接表作为存储结构的好处**

1.  **图的存储方式**
    -   **邻接矩阵**：
        -   **定义：**使用一个二维矩阵存储图的顶点连接关系，矩阵的行和列表示顶点，元素表示边的存在和权值。
        -   **优点**：查询两顶点是否相连速度快，时间复杂度为 $O(1)$ 。
        -   **缺点：**
            -   **空间复杂度高**：对于 n 个顶点，空间复杂度为 $O(n^2)$ ，当图较大且稀疏时（边数远小于 $n^2$ ），会浪费大量空间。
            -   **不适合稀疏图**：现实中的城市网络通常是稀疏图，每个城市只与少数城市直接相连。
    -   **邻接表：**
        -   **定义**：对于每个顶点，存储一个链表（或向量），记录其所有相邻的顶点和对应的权值。
        -   **优点：**
            -   **空间效率高**：只存储实际存在的边，空间复杂度为 $O(n + m)$ ，其中 m 为边数。
            -   **适合稀疏图**：当边数远小于 $n^2$ 时，邻接表更节省空间。
        -   **缺点：**查询两顶点是否相连需要遍历链表，最坏时间复杂度为 O(n) 。
2.  **城市网络的特点**
    -   **稀疏性**：每个城市通常只与少数相邻城市直接相连，而非与所有城市相连。
    -   **需要遍历邻接节点**：在算法（如 Dijkstra 算法）中，需要遍历当前节点的所有邻接节点，邻接表对此操作支持良好，时间复杂度为邻接节点数量。
3.  **邻接表对城市网络的优势**
    -   **节省空间**：对于大量城市（顶点）和较少的直接道路（边），邻接表大大降低了空间需求。
    -   **方便遍历**：在计算最短路径时，频繁需要获取某个城市的所有相邻城市及对应的距离，邻接表使得这一操作高效且直接。

---



### **5、总结**

==思路的由来：==

1.  **根据问题特性选择模型：**
    -   城市作为顶点，公路作为边，路程作为权值，这是将城市网络抽象为图的自然方式。
    -   道路通常是双向的，使用无向图能够准确地表示这种双向关系。
2.  **根据图的特性选择存储结构**：
    -   现实中的城市网络是稀疏图，邻接表在稀疏图中具有空间优势。
    -   邻接表方便获取某个节点的所有邻接节点，适合实现需要遍历邻接节点的算法。
3.  **根据算法需求选择实现方式**：
    -   Dijkstra 算法需要频繁遍历节点的邻接边，邻接表能够高效支持这一操作。
    -   节省的空间可以用于处理更大的图，提高程序的扩展性和性能。

**实际应用中的考虑**

-   **可拓展性：**当城市数量增加时，邻接表能够更好地适应规模的扩大。
-   **灵活性**：邻接表可以方便地添加或删除节点和边，适应动态变化的网络。
-   **效率**：在路径搜索算法中，邻接表提供了高效的邻接节点访问方式，提高了算法的整体效率。

==结论：==使用**无向权值图的邻接表**来表示城市网络，是基于城市网络的特性、存储空间效率和算法实现需求综合考虑的结果。它能够准确地模型化城市和道路的关系，节省存储空间，并有效支持最短路径算法的实现。

## 三、算法分析

在智能驾驶和导航系统中，常常需要在城市网络中找到从源点城市到终点城市的最短路径。城市之间通过道路相连，每条道路都有一定的距离（权重）。为了高效、准确地计算最短路径，我们需要选择合适的算法。

---

### **当前模型特点**

1.  **图的抽象**
    -   **顶点：**城市。
    -   **边：**连接两个城市的道路。
    -   **权重：**边上的数值，表示两城市之间的距离（路程）。
2.  **数据特点：**
    -   **边权重为非负数**：道路距离不可能为负数。
    -   **需要求解单源最短路径**：从指定的源点城市到所有其他城市的最短路径，或者到特定终点城市的最短路径。

----



### **可选的最短路径算法**

1.  **Dijkstra 算法**
    -   **适用范围**：边权重为非负数的图。
    -   **特点：**
        -   **高效性**：时间复杂度为 $O((V + E) \log V)$ ，
            其中 V 为顶点数， E 为边数（使用最小堆优化）。
        -   **贪心策略**：每次选择未处理的、具有最小暂时距离的顶点。
        -   **确保最短路径**：在边权重非负的情况下，能保证找到从源点到其他所有顶点的最短路径。
2.  **Bellman-Ford 算法**
    -   **适用范围**：可以处理包含负权边的图，但不能有负权回路。
    -   **特点**：
        -   **时间复杂度较高**：$O(V \times E)$ 。
        -   **能够检测负权回路**。
3.  **Floyd-Warshall 算法**
    -   **适用范围**：求解所有顶点对之间的最短路径。
    -   **特点**：
        -   **时间复杂度高**： O(V^3) ，不适合大型图。
        -   **应用场景有限**：一般用于顶点数较少的全源最短路径问题。

---



### ==选择 Dijkstra 算法的原因：==

1.  **满足算法的适用条件**
    -   **非负权重**：道路距离均为非负数，Dijkstra 算法适用。
    -   **单源最短路径**：需要从源点找到到终点的最短路径，Dijkstra 算法正是为此设计的。
2.  **算法的高效性**
    -   **时间复杂度低**：相比 Bellman-Ford 算法，Dijkstra 算法更高效，特别是对于稀疏图。
    -   **实际应用中效率高**：使用堆优化的 Dijkstra 算法在实际中表现良好，适合实时计算。
3.  **算法的准确性**
    -   **保证找到最短路径**：在非负权重的图中，Dijkstra 算法能够准确找到最短路径。
    -   **确定性**：算法是确定性的，每次选择都是基于当前已知的最小距离，不依赖于随机性或启发式。
4.  **实现的简单性**
    -   **相对容易实现**：相比于其他复杂的算法，Dijkstra 算法的逻辑清晰，容易编码和调试。
    -   **广泛应用和支持**：有大量的资源、库和示例可供参考，实现风险低。

---



### **Dijkstra 算法的基本原理**

**贪心策略**

-   **核心思想**：在每一步选择当前未处理的、具有最小暂时距离的顶点进行处理。
-   **初始化**：设置源点到自身的距离为 0，其他顶点的距离为无穷大。
-   **迭代：**
    -   选取未访问顶点中距离源点最近的顶点 u 。
    -   更新 u 的所有邻接顶点 v 的距离：如果 `dist[u] + weight(u, v) < dist[v]` ，则更新 `dist[v] = dist[u] + weight(u, v)` 。
    -   将 u 标记为已访问。

**与其他算法的比较**

1.  **Bellman-Ford 算法：**虽然它可以处理负权边，但城市网络中不存在负权边。并且时间复杂度较高，不适合实时计算。
2.  **Floyd-Warshall 算法：**它求解所有顶点对之间的最短路径，但我们只需单源最短路径。且时间复杂度同样较高。

----



### **总结**

**Dijkstra 算法**是解决**非负权重图的单源最短路径**问题的最优选择。



## 四、代码分析

### 一、结构体和类成员的作用分析

#### **1. 结构体 Edge**

```cpp
struct Edge {
    int desIndex;	// 终点索引（邻接节点的索引）
    int weight;		// 权值（高速路长度）
    Edge *to;		// 指向下一条边的指针
};
```

**desIndex (终点索引):**

-   **作用：**表示这条边所连接的目标顶点（城市）的索引。
-   **意义**：在城市网络中，desIndex 指示从当前城市可以直接到达的相邻城市。

**Weight (权值):**

-   **作用**：表示这条边的权重，在本程序中是两城市之间的高速公路长度（距离）。
-   **意义**：在最短路径算法中，权值用于计算路径的总距离，从而找到路径长度最短的路线。

**to (指向下一条边的指针):**

-   **作用**：用于在邻接表中链接当前顶点的所有边，形成一条边的链表。
-   **意义**：在邻接表中，每个顶点的所有邻接边通过 to 指针连接，方便遍历该顶点的所有相邻城市。

---



#### **2. 结构体 Node (vexType)**

```cpp
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
```

**nIndex (顶点索引):**

-   **作用**：唯一标识该顶点（城市）在图中的位置，用于数组索引和快速定位。
-   **意义**：在城市网络中，每个城市都有一个唯一的编号，方便在算法中进行索引和比较。

**data (数据域):**

-   **作用**：存储城市的名称。
-   **意义**：在城市网络中，data 保存城市的实际名称，便于显示和用户交互。

**firstEdge (指向第一条邻接边的指针):**

-   **作用**：指向与该顶点相连的第一条边（即与该城市直接相连的第一个城市）。
-   **意义**：在邻接表中，每个顶点的所有邻接边通过 firstEdge 开始链接，形成一条边的链表，表示该城市的所有直接相邻城市。

**lastEdge (尾指针):**

-   **作用**：指向该顶点的邻接边链表的最后一条边，方便在链表末尾插入新的边（尾插法）。
-   **意义**：提高在构建邻接表时添加边的效率，避免每次插入都需要遍历整个链表。

**构造函数 vexType():**

-   **作用**：初始化顶点的成员变量，nIndex 为 0，firstEdge 和 lastEdge 为 nullptr。
-   **意义**：确保在创建顶点对象时，其成员变量有合理的初始值，防止未初始化带来的错误。

---



#### **3. pair 结构体**

```cpp
struct Pair {
    int souIdx;         // 源顶点索引
    int distance;       // 从源点到该顶点的当前最短距离

    Pair(int nIndex, int weight) : souIdx(nIndex), distance(weight) {}

    bool operator<(const Pair &other) const {
        return distance > other.distance;
    }
};
```

**souIdx (源顶点索引):**

-   **作用**：表示在优先队列中存储的顶点的索引。
-   **意义**：用于在算法中标识当前处理的顶点。

**distance (距离):**

-   **作用: **表示从源点到当前顶点的已知最短距离。
-   **意义: **在 Dijkstra 算法中，distance 用于比较和更新最短路径。

**构造函数 Pair(int nIndex, int weight):**

-   **作用: **初始化 Pair 对象，将顶点索引和距离赋值给成员变量。
-   **意义: **便于在创建 Pair 对象时直接设置其值。

**重载运算符 operator< :**

-   **作用: **定义 Pair 在优先队列（最小堆）中的排序规则。
-   **意义**：确保在 Dijkstra 算法中，每次都能从优先队列中取出当前距离最小的顶点进行处理。
-   **实现**：distance 越小，优先级越高（因为 std::priority_queue 默认是最大堆，故使用 > 符号）。

---



#### **4. Ans结构体**

```cpp
using Ans = struct dist_way {
    int minWeight;              // 最短路径的总权值（总距离）
    std::vector<int> prev;      // 前驱数组，用于还原最短路径
};
```

**minWeight (最短路径长度): **

-   **作用**：存储从源点到目标点的最短路径的总距离。
-   **意义**：供程序在输出结果时显示最短路径的长度。

**prev (前驱数组):**

-   **作用**：记录每个顶点在最短路径上的前驱顶点索引。
-   **意义**：在路径还原时，通过 prev 数组从目标点反向追踪到源点，重建最短路径。

---



### 二、WeightedGraph 类

```cpp
class WeightedGraph {
    Node **adjList;     // 邻接表，存储所有顶点的指针数组
    int nodeCount;      // 顶点数量（城市数量）
    int edgeCount;      // 边数量（高速公路数量）

    // 其他成员函数和变量
};
```

#### ==成员变量==

##### **1. adjList (邻接表):**

-   **类型**：Node **，指向指针的指针，表示一个指针数组，每个元素是一个 Node *。
-   **作用**：存储所有顶点（城市）的指针数组，形成邻接表的数据结构。
-   **城市网络的表示**：邻接表是图的常用表示方式，适合稀疏图，节省空间。
-   **快速访问顶点**：通过顶点索引直接访问对应的 Node 对象，方便算法的实现。

---



##### **2. nodeCount (顶点数量):**

-   **作用**：记录图中顶点的总数，即城市的数量。
-   **意义**：用于初始化数据结构、循环遍历顶点，以及检测数据完整性。

---



##### **3. edgeCount (边数量):**

-   **作用**：记录图中边的总数，即高速公路的数量。
-   **意义**：用于检测数据完整性，了解图的规模。

---



#### ==成员函数==

##### **1. 构造函数 WeightedGraph(const std::string &fileName)**

```cpp
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
```

**概述：**该构造函数的主要作用是从指定的文件中读取图的数据信息，构建加权无向图的邻接表表示。下面将对该构造函数进行逐步分析，解释每一部分的功能和实现细节。

**参数：**`const std::string &fileName` 数据文件的名称，包含图的节点和边的信息。

**功能：**打开指定的文件，读取城市数量、道路数量和城市之间的连接信息。构建邻接表，表示图的结构。



**打开文件并检查**

```cpp
std::ifstream mapReader(fileName);
if (!mapReader.is_open()) {
    std::cerr << "Could not open file " 
        << fileName << std::endl;
    exit(1);
}
```

**作用：**尝试打开指定的文件 fileName，用于读取图的数据。

**逻辑：**创建 std::ifstream 对象 mapReader，打开文件。
	如果文件未能成功打开，输出错误信息并退出程序。



**读取城市数量和高速路数量**

```cpp
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
```

**作用：**从文件中读取城市数量 nodeCount 和高速路数量 edgeCount。

**逻辑：**读取第一行 line，假设其中包含城市数量的信息。遍历 line 中的每个字符，如果是数字字符（‘0’ 到 ‘9’），将其追加到字符串 cityNum 中。同样的方法，读取第二行，获取字符串 roadNum。使用 std::stoi 将字符串转换为整数，得到 nodeCount 和 edgeCount。



**为邻接表分配空间**

```cpp
// 为邻接表分配空间
adjList = new Node *[nodeCount];
for (int i = 0; i < nodeCount; i++) {
    adjList[i] = new Node();
    adjList[i]->nIndex = i;
    adjList[i]->firstEdge = nullptr;
    adjList[i]->lastEdge = nullptr;
}
```

**作用：**为邻接表 adjList 分配空间，创建 nodeCount 个节点（城市）。

**逻辑：**创建一个指针数组 adjList，大小为 nodeCount。逐个分配 Node 对象，并初始化其成员变量。



**跳过一行：**`getline(mapReader, line);`
**作用：**跳过文件中的一行，可能是标题行或空行。
**逻辑：**调用 getline 读取一行，但不对其进行处理。



**读取城市名称和邻接信息**

```cpp
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
```

**作用：**逐行读取城市名称和对应的邻接信息，存储在 adjList 和 tokens 中。

**逻辑：**

-   使用 getline 读取文件的每一行，直到文件结束。
-   检查 index 是否超过了 nodeCount，如果超过，说明文件中的城市数量超过了预期，输出错误并退出。
-   使用 std::istringstream 将 line 转换为流，便于解析。
-   使用 getline(iss, adjList[index]->data, ';')，以分号 ; 为分隔符，读取城市名称，存储在 adjList[index]->data 中。
-   使用 line.find(';') 找到第一个分号的位置，提取分号后面的字符串，保存为该城市的邻接信息，存储在 tokens 向量中。
-   index++，处理下一个城市。



**检查实际读取的城市数量**

```cpp
if (index < nodeCount) {
    std::cerr << "实际城市数量少于预期的 " 
        << nodeCount << " 个。" << std::endl;
    exit(EXIT_FAILURE);
}
mapReader.close();
```

**作用：**在读取完文件后，检查实际读取的城市数量是否与预期的 nodeCount 一致。关闭文件 mapReader。



**构建邻接表**

```cpp
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
```

**作用：**根据读取的邻接信息，构建邻接表，即为每个节点添加邻接边，形成完整的图结构。

**逻辑：**

-   外层循环遍历每个节点 v0Index，对应城市的索引。
-   从 tokens 向量中获取该节点的邻接信息字符串 token。
-   使用 std::istringstream 和 getline，以分号 ; 为分隔符，解析邻接信息，每个 block 对应一个邻接城市及其权值。
-   对于每个 block：使用 block.find(',') 找到逗号 , 的位置，将 block 分割为城市名称和权值字符串。



==总结：==

1.  使用 `std::ifstream` 打开文件。如果打开失败，输出错误信息并退出程序。
2.  使用字符串读取第一行和第二行，前者包含城市数量 (*nodeCount*)，后者包含高速路数量 (*edgeCount*)，并将之转换为 `int` 类型。
3.  初始化邻接表，创建一个 `Node*` 类型的数组 `adjList`，大小为 `nodeCount`，用于储存每个城市的城市编号(`nIndex`)和指向邻接表的首个指针(`firstEdge`)
4.  略过一行，再从文件的剩余部分读取城市的名称和与其它城市的邻接关系。
    格式为：==城市名称;城市1,权重1;城市2,权重2;…==
5.  遍历每个城市的邻接信息，使用==尾插法==构建邻接表。

****



##### ==2. Dijkstra 算法实现函数==

```cpp
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
```

**概括：**该函数的作用是计算从起始节点 start 到目标节点 destination 的最短路径，
下面对该函数进行逐行分析，解释其工作原理和实现细节。

**函数声明：**`Ans dijkstra(Node *start, Node *destination) const`

-   **功能：**实现 Dijkstra 算法，计算从 start 到 destination 的最短路径。
-   **参数：**`Node *start` 起始顶点的指针 ，`Node *destination`目标顶点的指针。
-   **返回值：**Ans 结构体，包含最短路径长度和前驱节点数组，用于重建最短路径。



**变量初始化**

```cpp
std::vector<bool> visited(nodeCount, false);    // 标记数组，初始化为 false，表示所有节点均未被访问
std::vector<int> dist(nodeCount, INT_MAX);      // 距离数组，初始化为 INT_MAX，表示初始时各节点距离无穷大
std::vector<int> prev(nodeCount, -1);           // 前驱数组，初始化为 -1，表示各节点的前驱节点未知
std::priority_queue<Pair> pq;                   // 优先队列，存储待处理的节点，按照距离排序

dist[start->nIndex] = 0;						// 设置起始顶点的距离为0
pq.push(Pair(start->nIndex, 0));				// 将起始节点加入优先队列
```

-   **visited: **用于标记节点是否已被访问过，防止重复处理。
-   **dist: **存储从起始节点到每个节点的当前最短距离，初始时除起始节点外均为无穷大。
-   **prev: **存储每个节点的前驱节点索引，用于最终重建最短路径。
-   **pq: **优先队列，按照节点距离的升序（实现上为最小堆）存储待处理的节点。

---



**主循环详细解析**

`while (!pq.empty() && !visited[destination->nIndex]) { // ... }`

==循环条件:== **优先队列不为空**，表示还有待处理节点；**目标节点未被访问**，如果目标节点已被访问，说明已找到最短路径。



```cpp
Pair temp = pq.top();
pq.pop();
int sourceIdx = temp.souIdx;
```

-   **取出优先队列顶部的节点**：这是当前距离最小的未处理顶点。
-   获取当前顶点的索引 `sourceIdx`



```cpp
if (visited[sourceIdx])
    continue;
```

-   **如果当前节点已被访问**：跳过，继续处理下一个节点。
-   **防止重复处理节点**：由于可能有多个路径到达同一节点，只有第一次处理时才需要更新其邻接节点的距离。



```cpp
Node *souv = adjList[sourceIdx];    // 获取当前节点
Edge *curvEdge = souv->firstEdge;   // 获取当前节点的第一条邻接边
```

-   souv：指向当前处理的节点。
-   curvEdge：指向当前节点的第一条邻接边，用于遍历所有邻接节点。



```cpp
while (curvEdge != nullptr) {
    // ...
    curvEdge = curvEdge->to;
}
```

-   **遍历方式**：通过邻接链表，依次访问当前节点的每一条邻接边。
-   curvEdge：在循环中不断更新，直到遍历完所有邻接边。



```cpp
if (visited[curvEdge->desIndex]) {
    curvEdge = curvEdge->to;
    continue;
}
```

**检查邻接节点是否已被访问**，如果已访问，不需要再更新其距离，跳过该邻接节点。



```cpp
int newDist = dist[sourceIdx] + curvEdge->weight; // 计算从起始节点到邻接节点的距离
if (newDist < dist[curvEdge->desIndex]) {         // 如果新的距离小于已知的最短距离
    dist[curvEdge->desIndex] = newDist;           // 更新最短距离
    prev[curvEdge->desIndex] = sourceIdx;         // 更新前驱节点
    pq.push(Pair(curvEdge->desIndex, newDist));   // 将邻接节点加入优先队列
}
```

==松弛操作(更新距离)==

1.  **计算新的距离** newDist：即从起始节点到当前邻接节点的距离，等于起始节点到当前节点的距离加上当前边的权值。
2.  **比较新的距离与已知的最短距离: **如果新的距离更短，更新`dist`数组中的最短距离，更新`prev`数组中的前驱节点索引，记录路径，将邻接节点加入优先队列，以便后续处理其邻接节点；否则，不进行任何操作，继续处理下一条邻接边。



`visited[sourceIdx] = true`
标记当前节点为已访问状态，防止后续重复计算。



返回结果：`return {dist[destination->nIndex], prev};`

-   dist[destination->nIndex]：从起始节点到目标节点的最短距离。
-   prev：前驱节点数组，用于重建最短路径。
-   **返回一个** Ans **结构体**，包含最短路径长度和前驱节点信息。



==总结==

1.  **初始化**：设置所有节点的初始距离为无穷大，起始节点的距离为 0，所有节点未被访问。
2.  **使用优先队列**：按照当前已知的最短距离，从小到大处理节点，确保每次处理的节点都是未访问节点中距离起始节点最近的。
3.  **松弛操作**：对于当前节点的每个未访问的邻接节点，尝试通过当前节点更新其最短距离，如果找到更短的路径，则更新距离和前驱节点。
4.  **标记已访问**：当前节点处理完毕后，标记为已访问，防止重复处理。
5.  **循环终止**：当目标节点被访问或所有可达节点都处理完毕，算法结束。

---



##### 3. Ans输出函数

```cpp
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
```

**概括：**计算并显示从起点到终点的最短路径及其长度。重点在于如何利用栈来重建从起点到终点的路径。

**函数声明：**`void displayAns(const std::string &startName, const std::string &destinationName) const`

-   参数：`const std::string &startName` 起点城市的名称，`const std::string &destionationName` 终点城市的名称。
-   功能：通过调用 Dijkstra 算法，计算从起点到终点的最短路径；使用栈来重建并按正确顺序输出路径。



**查找起点和终点的索引**

```cpp
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
```

**作用：**遍历邻接表 adjList，找到起点和终点城市对应的索引 v0Index 和 v1Index。

**逻辑：**初始化 v0Index 和 v1Index 为 -1，表示未找到；遍历节点列表，
当 adjList[i]->data 与 startName 或 destinationName 相等时，记录其索引；
如果在遍历结束后，仍有索引为 -1，表示未找到对应的城市，输出错误信息并返回。



**调用 Dijkstra 算法**

`Ans ans = dijkstra(getNodeByName(startName), getNodeByName(destinationName));`

**作用：**通过起点和终点的节点指针，调用 dijkstra 函数，计算最短路径。

**逻辑：**使用 getNodeByName 函数获取起点和终点的节点指针；
dijkstra 函数返回一个 Ans 结构体，包含最短路径长度和前驱节点数组。



==重建最短路径==

```cpp
int desIndex = getIndexByName(destinationName);
std::stack<int> st;
for (int i = desIndex; i != -1; i = ans.prev[i])
    st.push(i);
```

**作用：**通过前驱节点数组 ans.prev，从终点回溯到起点，重建最短路径。

**栈的使用**：由于回溯过程是从终点到起点，得到的节点序列是逆序的。
使用栈的“后进先出”特性，能够在输出时将路径顺序反转，得到从起点到终点的正确顺序。

**逻辑：**初始化 desIndex 为终点的索引，使用 for 循环，从终点索引开始，
沿着前驱节点数组 prev 回溯，将当前节点索引 i 压入栈 st，更新 i 为 ans.prev[i]，
即当前节点的前驱节点索引，当 i 为 -1 时，表示已到达起点，结束循环。



**输出最短路径**

```cpp
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
```

**作用：**从栈中弹出节点索引，按照正确的顺序构建路径字符串，并输出结果。

**逻辑：**初始化字符串 passCity，用于存储路径。使用 while 循环，当栈不为空时：弹出栈顶元素 pos，这是路径中的下一个城市的索引。将城市名称 adjList[pos]->data 追加到 passCity。如果栈不为空，表示还未到达终点，追加箭头 " -> " 作为分隔符。输出完整的路径字符串和最短路径长度 ans.minWeight。



## 五、测试样例

![截屏2024-12-05 22.09.45](../../../../Desktop/截屏2024-12-05 22.09.45.png)

![截屏2024-12-05 22.09.59](../../../../Desktop/截屏2024-12-05 22.09.59.png)



## 六、改进与完善

1.  统一变量命名规范。
2.  增加代码注释和文档
3.  **模块化代码**：
    -   **现状**：所有功能集中在单个类中，代码结构较为紧密。
    -   **优化方案**：**分离数据读取和图构建**：将文件解析和图结构构建分离，形成独立的模块或类；**封装算法实现**：将 Dijkstra 算法实现封装为单独的函数或类，便于复用和测试；**引入接口和抽象类**：为图结构和算法定义接口，支持多种实现方式。
4.  **增强用户交互：**完善输入处理：支持模糊搜索、自动补全，提升输入城市名称的便捷性；错误提示和帮助信息：在用户输入错误时，提供详细的提示和解决方案。
5.  **错误处理：**使用异常处理机制，确保程序在异常情况下能够安全退出或继续运行；在数组访问、指针操作等地方，严格检查边界条件，防止越界和空指针引用。
6.  **输入验证和安全：**确保用户输入的城市名称、文件名等符合预期格式，防止非法操作。





# 附件 完整的代码和更大型的测试数据

```cpp
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
```



```txt
城市数量:19
高速路数量:23
#城市;邻接城市,权值
西宁;兰州,216
兰州;西宁,216;西安,676
西安;兰州,676;成都,842;郑州,511
郑州;西安,511;北京,695;徐州,349;武汉,534
北京;郑州,695;天津,137
天津;徐州,674;北京,137
徐州;郑州,349;天津,674;上海,651
上海;徐州,651;南昌,825
成都;西安,842;昆明,1100;贵阳,967
武汉;株洲,429;郑州,534
昆明;贵阳,639;成都,1100
贵阳;昆明,639;株洲,902;柳州,607;成都,967
株洲;贵阳,902;武汉,429;南昌,367;广州,675;柳州,672
南昌;株洲,367;上海,825;福州,622
福州;南昌,622
柳州;贵阳,607;株洲,672;南宁,255
南宁;柳州,255
广州;株洲,675;深圳,140
深圳;广州,140;香港,47
```



```txt
城市数量:70
高速路数量:102
#城市;邻接城市,权值
哈尔滨;长春,260
长春;哈尔滨,260;沈阳,310;唐山,944
沈阳;长春,310;大连,380;锦州,235
大连;沈阳,380
烟台;青岛,219
锦州;沈阳,235;秦皇岛,210
秦皇岛;锦州,210;唐山,140
唐山;长春,944;天津,132;秦皇岛,140;北京,176
北京;张家口,194;天津,137;唐山,176;石家庄,301
张家口;北京,194;呼和浩特,303
呼和浩特;张家口,303;银川,679;乌鲁木齐,2337
乌鲁木齐;呼和浩特,2337;西宁,1787;拉萨,2636
西宁;乌鲁木齐,1787;兰州,223;拉萨,1810
拉萨;西宁,1810;攀枝花,1925;成都,1964;乌鲁木齐,2636
银川;呼和浩特,679;兰州,434;太原,707
太原;银川,707;石家庄,223;西安,601
石家庄;太原,223;北京,301;济南,315;邯郸,168
天津;北京,137;唐山,132;济南,324;连云港,629
青岛;烟台,219;济南,351;连云港,242
济南;天津,324;青岛,351;邯郸,272;石家庄,315;商丘,332;临沂,235;徐州,319
邯郸;石家庄,168;济南,272;兰州,1203;郑州,253
兰州;西宁,223;银川,434;邯郸,1203;广元,616;西安,650
广元;兰州,616;西安,450;成都,306;重庆,378
西安;兰州,650;广元,450;信阳,614;太原,601;郑州,483
郑州;邯郸,253;信阳,323;商丘,208;西安,483
商丘;郑州,208;济南,332;景德镇,665;徐州,174
徐州;商丘,174;济南,319;临沂,191;连云港,206;南京,323;合肥,324;淮安,199
临沂;济南,235;徐州,191;连云港,117;淮安,227
连云港;天津,629;青岛,242;盐城,188;淮安,130;徐州,206;临沂,117
盐城;连云港,188;淮安,119;南通,187;无锡,227
淮安;徐州,199;临沂,227;连云港,130;盐城,119;无锡,292;南京,190
南通;盐城,187;上海,146;无锡,109;苏州,105
信阳;西安,614;郑州,323;武汉,199;合肥,331
南京;合肥,170;徐州,323;淮安,190;无锡,189;杭州,280
无锡;南京,189;淮安,292;盐城,227;南通,109;苏州,40
苏州;无锡,40;南通,105;上海,100;杭州,158
上海;南通,146;苏州,100;宁波,228;杭州,173
宁波;上海,228;温州,309;丽水,288;杭州,156
杭州;景德镇,387;合肥,431;南京,280;苏州,158;上海,173;宁波,156;温州,294;金华,175
合肥;景德镇,335;武汉,378;信阳,331;徐州,324;南京,170;杭州,387
成都;广元,306;重庆,303;攀枝花,637;拉萨,1964
重庆;成都,303;广元,378;武汉,869;贵阳,376;昆明,843;岳阳,806
武汉;信阳,199;重庆,869;合肥,378;南昌,345;岳阳,218
攀枝花;成都,637;昆明,308;拉萨,1925
贵阳;成都,607;重庆,376;岳阳,840;长沙,783;桂林,466;南宁,572;昆明,516
岳阳;重庆,806;武汉,218;景德镇,469;长沙,150;贵阳,840
景德镇;岳阳,469;商丘,665;合肥,335;杭州,387;金华,279;河源,769;南昌,192
金华;景德镇,279;杭州,175;丽水,116;南昌,426
丽水;金华,116;宁波,288;温州,130;梅州,734
温州;丽水,130;杭州,294;宁波,309;福州,332
昆明;攀枝花,308;重庆,843;贵阳,516;柳州,880;南宁,776
长沙;贵阳,783;岳阳,150;南昌,336;株洲,65
南昌;长沙,336;武汉,345;景德镇,192;金华,426;福州,560;河源,635;韶关,622;株洲,337
株洲;长沙,65;南昌,337;衡阳,142
福州;南昌,560;温州,332;厦门,254
衡阳;株洲,142;桂林,338;郴州,160
桂林;贵阳,466;衡阳,338;郴州,360;柳州,150
郴州;桂林,360;衡阳,160;韶关,160
柳州;昆明,880;桂林,150;韶关,567;南宁,241
韶关;柳州,567;郴州,160;南昌,622;河源,262;惠州,248;广州,220
河源;韶关,262;南昌,635;景德镇,769;梅州,191;惠州,87
梅州;河源,191;丽水,734;厦门,268;汕头,200;汕尾,222
厦门;梅州,268;福州,254;汕头,252
南宁;昆明,776;贵阳,512;柳州,241;广州,557
广州;南宁,557;韶关,220;惠州,147;深圳,140
惠州;广州,147;韶关,248;河源,87;深圳,90
汕头;厦门,252;梅州,200;汕尾,188
汕尾;梅州,222;汕头,188;深圳,169
深圳;香港,10;惠州,90;汕尾,169;广州,140
香港;深圳,10
```
