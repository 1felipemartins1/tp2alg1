
#include "network.hpp"
#include <iostream>
#include <vector>
#include <limits>
#include <queue>

Graph::Graph(int V) : adj(V) {}

void Graph::addEdge(int from, int to, int capacity)
{
    Edge forward = {to, capacity, 0, (int)adj[to].size()};
    Edge backward = {from, 0, 0, (int)adj[from].size()};
    adj[from].push_back(forward);
    adj[to].push_back(backward);
}

int Graph::energia_nao_atendida(int source) {
    int totalFluxoSaindo = 0;

    // Calcula o fluxo total saindo da fonte
    for (const auto& edge : adj[source]) {
        totalFluxoSaindo += edge.flow;
    }
    // Retorna a diferença
    return totalFluxoSaindo;
}

bool Graph::bfs(std::vector<int> &parent, std::vector<int> &edgeIndex, int source, int sink)
{
    int V = static_cast<int>(adj.size());
    std::vector<bool> visited(V, false);
    std::queue<int> q;
    q.push(source);
    visited[source] = true;
    parent[source] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (int i = 0; i < static_cast<int>(adj[u].size()); i++)
        {
            {
                Edge &e = adj[u][i];
                if (!visited[e.to] && e.flow < e.capacity)
                {
                    parent[e.to] = u;
                    edgeIndex[e.to] = i;
                    visited[e.to] = true;
                    q.push(e.to);

                    if (e.to == sink)
                        return true;
                }
            }
        }
    }
    return false;
}

int Graph::maxFlow(int source, int sink)
{
    int maxFlow = 0;
    std::vector<int> parent(adj.size());
    std::vector<int> edgeIndex(adj.size());

    while (bfs(parent, edgeIndex, source, sink))
    {
        int pathFlow = INT_MAX;

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            int i = edgeIndex[v];
            pathFlow = std::min(pathFlow, adj[u][i].capacity - adj[u][i].flow);
        }

        for (int v = sink; v != source; v = parent[v])
        {
            int u = parent[v];
            int i = edgeIndex[v];
            adj[u][i].flow += pathFlow;
            adj[v][adj[u][i].reverseIndex].flow -= pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int Graph::energiaPerdida(int source, int sink) {
    int energiaGerada = 0;
    int energiaConsumida = 0;

    // Calcula a energia gerada pelos geradores (fluxo saindo da fonte fictícia)
    for (const auto& edge : adj[source]) {
        energiaGerada += edge.flow;
    }

    // Calcula a energia consumida pelos consumidores (fluxo entrando no sumidouro fictício)
    for (size_t i = 0; i < adj.size(); i++) {
        for (const auto& edge : adj[i]) {
            if (edge.to == sink) {
                energiaConsumida += edge.flow;
            }
        }
    }

    // Retorna a energia perdida
    return energiaGerada - energiaConsumida;
}
