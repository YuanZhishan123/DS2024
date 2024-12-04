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
    // BFS �� DFS ������
    cout << "\n�ӽڵ�0��ʼ����BFS:" << endl;
    graph.BFS(0); // �����������

    cout << "\n�ӽڵ�0��ʼ����DFS:" << endl;
    graph.DFS(0); // �����������
	cout<<endl;
	
	cout << "\n�ӽڵ�0��ʼ�����·��:" << endl;
    graph.dijkstra(0);
    cout << "\n�ӽڵ�3��ʼ�����·��:" << endl;
    graph.dijkstra(3);
	cout<<endl;
    graph.kruskal(); // ������С�������㷨

    return 0;
}

