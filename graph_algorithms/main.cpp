#include <iostream>
#include <limits>
#include <vector>

const std::vector<std::vector<int>> graph = {
    {0, 1, 8, 0, 0},
    {1, 0, 2, 5, 0},
    {8, 2, 0, 0, 3},
    {0, 5, 0, 0, 1},
    {0, 0, 3, 1, 0}
};

const std::vector<char> names = {'A', 'B', 'C', 'D', 'E'};

void dfs(int v, std::vector<int>& used) {
    used[v] = 1;
    std::cout << names[v] << ' ';

    const int vertexCount = static_cast<int>(graph.size());
    for (int u = 0; u < vertexCount; ++u) {
        if (graph[v][u] != 0 && !used[u]) {
            dfs(u, used);
        }
    }
}

int main() {
    const int vertexCount = static_cast<int>(graph.size());
    const int start = 0;  // A
    const int target = 4; // E

    if (start < 0 || start >= vertexCount ||
        target < 0 || target >= vertexCount) {
        std::cerr << "Invalid start or target vertex.\n";
        return 1;
    }

    std::cout << "Matrix:\n";
    for (const auto& row : graph) {
        for (int weight : row) {
            std::cout << weight << ' ';
        }
        std::cout << '\n';
    }

    // BFS search
    std::vector<int> queue = {start};
    std::vector<int> seen(vertexCount, 0);
    seen[start] = 1;

    std::cout << "\nBFS: ";
    for (std::size_t head = 0; head < queue.size(); ++head) {
        const int v = queue[head];
        std::cout << names[v] << ' ';

        for (int u = 0; u < vertexCount; ++u) {
            if (graph[v][u] != 0 && !seen[u]) {
                seen[u] = 1;
                queue.push_back(u);
            }
        }
    }

    // DFS search
    std::vector<int> used(vertexCount, 0);
    std::cout << "\nDFS: ";
    dfs(start, used);

    // Dijkstra
    const long long infinity = std::numeric_limits<long long>::max();
    std::vector<long long> dist(vertexCount, infinity);
    std::vector<int> prev(vertexCount, -1);
    std::vector<int> done(vertexCount, 0);
    dist[start] = 0;

    for (int step = 0; step < vertexCount; ++step) {
        int v = -1;
        for (int i = 0; i < vertexCount; ++i) {
            if (!done[i] && (v == -1 || dist[i] < dist[v])) {
                v = i;
            }
        }

        if (v == -1 || dist[v] == infinity || v == target) {
            break;
        }

        done[v] = 1;
        for (int u = 0; u < vertexCount; ++u) {
            const int weight = graph[v][u];
            if (weight != 0 && dist[v] + weight < dist[u]) {
                dist[u] = dist[v] + weight;
                prev[u] = v;
            }
        }
    }

    if (dist[target] == infinity) {
        std::cout << "\nNo path from " << names[start]
                  << " to " << names[target] << ".\n";
        return 0;
    }

    std::cout << "\nDistance to " << names[target] << ": " << dist[target];
    std::cout << "\nPath: ";

    std::vector<int> path;
    for (int v = target; v != -1; v = prev[v]) {
        path.push_back(v);
    }

    for (auto it = path.rbegin(); it != path.rend(); ++it) {
        std::cout << names[*it] << ' ';
    }
    std::cout << '\n';
    return 0;
}