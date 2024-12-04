#include "Graph.cpp"
#include<iostream>
int main() {
    Graph graph(7);
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 2, 4);
    graph.addEdge(1, 3, 7);
    graph.addEdge(1, 4, 1);
    graph.addEdge(2, 5, 3);
    graph.addEdge(2, 6, 5);
    graph.addEdge(4, 5, 2);

	graph.displayGraph();
    // BFS 和 DFS 的区别
    cout << "\n从节点0开始进行BFS:" << endl;
    graph.BFS(0); // 广度优先搜索

    cout << "\n从节点0开始进行DFS:" << endl;
    graph.DFS(0); // 深度优先搜索
	cout<<endl;
	
	cout << "\n从节点0开始的最短路径:" << endl;
    graph.dijkstra(0);
    cout << "\n从节点3开始的最短路径:" << endl;
    graph.dijkstra(3);
	cout<<endl;
    graph.kruskal(); // 测试最小生成树算法

    return 0;
}

