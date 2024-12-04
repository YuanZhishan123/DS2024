#include "Vector.cpp"
#include <queue>
#include <climits>
#include <algorithm>
#include <functional>
using namespace std;

// ͼ�����ݽṹ
class Graph {
public:
    int numVertices;
    vector<vector<pair<int, int>>> adjacencyList; // �ڽӱ�: �ڵ��Ȩ��

    Graph(int vertices) {
        numVertices = vertices;
        adjacencyList.resize(vertices);
    }

    void addEdge(int from, int to, int weight = 1) {
        adjacencyList[from].push_back({to, weight});
        adjacencyList[to].push_back({from, weight}); // ����ͼ
    }
	 void displayGraph() {
        cout << "graph����������:" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "�ڵ� " << i << ":";
            for (auto neighbor : adjacencyList[i]) {
                cout << " -> (" << neighbor.first << ", " << neighbor.second << ")";
            }
            cout << endl;
        }
    }
    // BFS �㷨
    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> vertexQueue;
        visited[startVertex] = true;
        vertexQueue.push(startVertex);

        cout << "BFS�㷨�����������: ";
        while (!vertexQueue.empty()) {
            int currentVertex = vertexQueue.front();
            vertexQueue.pop();
            cout << currentVertex << " ";
            for (auto neighbor : adjacencyList[currentVertex]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    vertexQueue.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    // DFS �㷨
    void DFSUtil(int currentVertex, vector<bool> &visited) {
        visited[currentVertex] = true;
        cout << currentVertex << " ";
        for (auto neighbor : adjacencyList[currentVertex]) {
            if (!visited[neighbor.first]) {
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        cout << "DFS�㷨�����������: ";
        DFSUtil(startVertex, visited);
        cout << endl;
    }

    // Dijkstra ���·���㷨
    void dijkstra(int startVertex) {
        vector<int> distances(numVertices, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;

        distances[startVertex] = 0;
        minHeap.push({0, startVertex});

        while (!minHeap.empty()) {
            int currentVertex = minHeap.top().second;
            int currentDistance = minHeap.top().first;
            minHeap.pop();

            for (auto neighbor : adjacencyList[currentVertex]) {
                int nextVertex = neighbor.first;
                int edgeWeight = neighbor.second;

                if (currentDistance + edgeWeight < distances[nextVertex]) {
                    distances[nextVertex] = currentDistance + edgeWeight;
                    minHeap.push({distances[nextVertex], nextVertex});
                }
            }
        }

        cout << "�ӽڵ� " << startVertex << "��ʼ�����·����: ";
        for (int i = 0; i < numVertices; i++) {
            cout << "�ڵ� " << i << " -> " << distances[i] << "; ";
        }
        cout << endl;
    }

    // Kruskal ��С�������㷨
    void kruskal() {
        vector<pair<int, pair<int, int>>> allEdges;
        for (int vertex = 0; vertex < numVertices; vertex++) {
            for (auto neighbor : adjacencyList[vertex]) {
                allEdges.push_back({neighbor.second, {vertex, neighbor.first}});
            }
        }
        sort(allEdges.begin(), allEdges.end());

        // ���鼯
        vector<int> parent(numVertices);
        for (int i = 0; i < numVertices; i++) parent[i] = i;

        function<int(int)> findParent = [&](int vertex) {
            if (parent[vertex] != vertex)
                parent[vertex] = findParent(parent[vertex]);
            return parent[vertex];
        };

        auto unionSets = [&](int vertex1, int vertex2) {
            int root1 = findParent(vertex1);
            int root2 = findParent(vertex2);
            if (root1 != root2) parent[root1] = root2;
        };

        cout << "��С֧�����ı�: ";
        int mstTotalWeight = 0;
        for (auto edge : allEdges) {
            int weight = edge.first;
            int vertex1 = edge.second.first;
            int vertex2 = edge.second.second;

            if (findParent(vertex1) != findParent(vertex2)) {
                mstTotalWeight += weight;
                unionSets(vertex1, vertex2);
                cout << "(" << vertex1 << ", " << vertex2 << ", " << weight << ") ";
            }
        }
        cout << "\n���бߵĵ�Ȩ�غ�: " << mstTotalWeight << endl;
    }
};


