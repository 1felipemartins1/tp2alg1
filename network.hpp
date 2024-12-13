#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <queue>
#include <climits>

struct Edge {
    int to;
    int capacity;
    int flow;
    int reverseIndex;
};

class Graph {
private:
    std::vector<std::vector<Edge>> adj;

public:
    Graph(int V);

    void addEdge(int from, int to, int capacity);
    int energia_nao_atendida(int source);
    int energiaPerdida(int source, int sink);
    int maxFlow(int source, int sink);


private:
    bool bfs(std::vector<int>& parent, std::vector<int>& edgeIndex, int source, int sink);
};

#endif // GRAPH_HPP
