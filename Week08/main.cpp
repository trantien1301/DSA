#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
vector<vector<int>> convertMatrixToList(const string &filename)
{
    ifstream If(filename);
     if (!If.is_open())
    {
     return {};
    }
    int n;
    If >> n;
    vector<vector<int>> Matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            If >> Matrix[i][j];
        }
    }
    If.close();
    vector<vector<int>> List(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (Matrix[i][j] == 1)
                List[i].push_back(j);
        }
    }
    return List;
}
vector<vector<int>> convertListToMatrix(const string &filename)
{
    ifstream If(filename);
    int n;
    If >> n;
    vector<vector<int>> Matrix(n, vector<int>(n,0));
    string line;
    int edgeCount,edge;
    for(int i=0;i<n;i++)
    {
        getline(If,line);
        istringstream ss(line);
        ss >> edgeCount;
        while(ss >> edge)
        {
         Matrix[i][edge] = 1;
        }
    }
    If.close();
    return Matrix;
}
bool isDirected(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adjMatrix[i][j] != adjMatrix[j][i]) 
            {
                return true; 
            }
        }
    }
    return false; 
}
int countVertices(const vector<vector<int>>& adjMatrix)
 {
    int n = adjMatrix.size(); 
    return n;
}
int countEdges(const vector<vector<int>>& adjMatrix)
{
    int res=0;
    int n=adjMatrix.size();
    bool isdirected= isDirected(adjMatrix);
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if (adjMatrix[i][j]==1) 
            {
                res++;
            }
        }
    }
    if(!isdirected)
    {
        res = res/2;
    }
    return res;
}
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
    vector<int> isolated;
    int n = adjMatrix.size();
     for (int i = 0; i < n; i++) 
    {
         bool isIsolated=true;
        for (int j = 0; j < n; j++) 
        {
            if (adjMatrix[i][j]==1||adjMatrix[j][i]) 
            {
                isIsolated = false;
                break;
            }
        }
        if(isIsolated)
        {
            isolated.push_back(i);
        }
    }
    return isolated;
}
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            if(i!=j&&adjMatrix[i][j]==0)
            {
                return false;
            }
        } 
    }
    return true;
}
bool isBipartite(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<int> color(n, -1);

    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (int neighbor = 0; neighbor < n; neighbor++) 
                {
                    if (adjMatrix[v][neighbor]) 
                    {
                        if (color[neighbor] == -1) 
                        {
                            color[neighbor] = 1 - color[v]; 
                            q.push(neighbor);
                        } 
                        else if (color[neighbor] == color[v]) 
                        {
                            return false; 
                        }
                    }
                }
            }
        }
    }
    return true;
}
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
    if (!isBipartite(adjMatrix)) return false;

    int n = adjMatrix.size();
    vector<int> color(n, -1);
    vector<int> group1, group2;

    for (int start = 0; start < n; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0;
            group1.push_back(start);

            while (!q.empty()) {
                int v = q.front();
                q.pop();

                for (int neighbor = 0; neighbor < n; neighbor++) {
                    if (adjMatrix[v][neighbor]) {
                        if (color[neighbor] == -1) {
                            color[neighbor] = 1 - color[v];
                            if (color[neighbor] == 0) {
                                group1.push_back(neighbor);
                            } else {
                                group2.push_back(neighbor);
                            }
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
    }

    // Check if every node in group1 connects to every node in group2
    for (int u : group1) {
        for (int v : group2) {
            if (adjMatrix[u][v] == 0) return false;
        }
    }

    return true;
}
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix)
{
    int n = adjMatrix.size();
    vector<vector<int>> newMatrix(n, vector<int>(n,0));
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            if(adjMatrix[i][j]==1||adjMatrix[j][i]==1)
            {
                newMatrix[j][i]=1;
                newMatrix[i][j]=1;
            } 
        }
    }
    return newMatrix;
}
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix)
{
    int n= adjMatrix.size();
    vector<vector<int>> newMatrix(n, vector<int>(n,0));
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++)
        {
            if(i!=j&&adjMatrix[i][j]==0)
            {
                newMatrix[i][j]=1;
            }
        }
    }
    return newMatrix;
}
// vector<int> findEulerCycle(vector<vector<int>>& adjMatrix)
//  {
//     int n = adjMatrix.size();
//     stack<int> findPath;
//     vector<int> res;
//     vector<vector<int>> graph = adjMatrix;
//     vector<int> inDegree(n, 0), outDegree(n, 0);
//     for (int i = 0; i < n; i++) 
//     {
//         for (int j = 0; j < n; j++) 
//         {
//             outDegree[i] += graph[i][j]; 
//             inDegree[j] += graph[i][j];  
//         }
//     }

//     if (isDirected(adjMatrix)) 
//     {
//         for (int i = 0; i < n; i++) 
//         {
//             if (inDegree[i] != outDegree[i]) 
//                 return {}; 
//         }
//     } else 
//     {
//         for (int i = 0; i < n; i++) 
//         {
//             if (outDegree[i] % 2 != 0) 
//                 return {}; 
//         }
//     }
//     int start = 0;
//     while (start < n && outDegree[start] == 0)
//     {
//         start++;   
//     }
//     findPath.push(start);

//     while (!findPath.empty()) 
//     {
//         int v = findPath.top();
        
//         if (outDegree[v] == 0)
//         {
//             res.push_back(v);
//             findPath.pop();
//         } 
//         else 
//         {
//             for (int j = 0; j < n; j++) 
//             {
//                 if (graph[v][j] > 0) 
//                 {
//                     findPath.push(j);
//                     graph[v][j]--; 
//                     if (!isDirected(adjMatrix)) 
//                     {
//                     graph[j][v]--; 
//                     }
//                     outDegree[v]--;
//                     if (isDirected(adjMatrix)) 
//                     {
//                     inDegree[j]--;
//                     }
//                     break;
//                 }
//             }
//         }
//     }

//     return res; 
// }


vector<int> findEulerCycle(vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    stack<int> findPath;
    vector<int> res;
    vector<vector<int>> graph = adjMatrix;
    vector<int> inDegree(n, 0), outDegree(n, 0);

    // Calculate in-degrees and out-degrees
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
        {
            outDegree[i] += graph[i][j];
            inDegree[j] += graph[i][j];
        }

    // Eulerian cycle conditions
    bool directed = isDirected(adjMatrix);
    if (directed) {
        for (int i = 0; i < n; i++)
            if (inDegree[i] != outDegree[i])
                return {}; // No Euler cycle exists
    } else {
        for (int i = 0; i < n; i++)
            if (outDegree[i] % 2 != 0)
                return {}; // No Euler cycle exists
    }

    // Start from a valid node
    int start = 0;
    while (start < n && outDegree[start] == 0) start++;
    findPath.push(start);

    while (!findPath.empty()) {
        int v = findPath.top();

        if (outDegree[v] == 0) {
            res.push_back(v);
            findPath.pop();
        } else {
            for (int j = 0; j < n; j++) {
                if (graph[v][j] > 0) {
                    findPath.push(j);
                    graph[v][j]--;
                    if (!directed) graph[j][v]--; // Remove reverse edge for undirected graph
                    outDegree[v]--;
                    if (directed) inDegree[j]--;
                    break;
                }
            }
        }
    }
    
    return res;
}







// void dfs(int node, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& spanningTree) 
// {
//     visited[node] = true;
//     for (int u = 0; u < adjMatrix.size(); u++) 
//     {
//         if (adjMatrix[node][u] && !visited[u]) 
//         {
//             spanningTree[node][u] = 1;
//             spanningTree[u][node] = 1; 
//             dfs(u, adjMatrix, visited, spanningTree);
//         }
//     }
// }

// vector<vector<int>> dfsSpanningTree(vector<vector<int>>& adjMatrix, int start) 
// {
//     int n = adjMatrix.size();
//     vector<vector<int>> spanningTree(n, vector<int>(n, 0));
//     vector<bool> visited(n, false);
//     dfs(start, adjMatrix, visited, spanningTree);
//     return spanningTree;
// }


void dfs(int node, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& spanningTree) {
    visited[node] = true;
    for (int u = 0; u < adjMatrix.size(); u++) {
        if (adjMatrix[node][u] && !visited[u]) {
            spanningTree[node][u] = 1;
            spanningTree[u][node] = 1;
            dfs(u, adjMatrix, visited, spanningTree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    dfs(start, adjMatrix, visited, spanningTree);
    return spanningTree;
}


// vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) 
// {
//     int n = adjMatrix.size();
//     vector<vector<int>> spanningTree(n, vector<int>(n, 0));
//     vector<bool> visited(n, false);
//     queue<int> q;
    
//     visited[start] = true;
//     q.push(start);

//     while (!q.empty()) 
//     {
//         int node = q.front();
//         q.pop();
//         for (int neighbor = 0; neighbor < n; neighbor++) 
//         {
//             if (adjMatrix[node][neighbor] && !visited[neighbor]) 
//             {
//                 spanningTree[node][neighbor] = 1; 
//                 spanningTree[neighbor][node] = 1; 
//                 visited[neighbor] = true;
//                 q.push(neighbor);
//             }
//         }
//     }

//     return spanningTree;
// }

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < n; neighbor++) {
            if (adjMatrix[node][neighbor] && !visited[neighbor]) {
                spanningTree[node][neighbor] = 1;
                spanningTree[neighbor][node] = 1;
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return spanningTree;
}



void CheckConnection(int node, vector<vector<int>>& adjMatrix, vector<bool>& visited) 
{
    int n = adjMatrix.size();
    visited[node] = true;
    for (int u = 0; u < n; u++) 
    {
        if (adjMatrix[node][u] && !visited[u]) 
        {
            CheckConnection(u, adjMatrix, visited);
        }
    }
}

bool isConnected(int u, int v,vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    
    CheckConnection(u, adjMatrix, visited);
    
    return visited[v];
}
vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), prev(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) 
    {
        int d = pq.top().first, u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        for (int v = 0; v < n; v++) 
        {
            if (adjMatrix[u][v] > 0) 
            {
                int newDist = dist[u] + adjMatrix[u][v];
                if (newDist < dist[v]) 
                {
                    dist[v] = newDist;
                    prev[v] = u;
                    pq.push({newDist, v});
                }
            }
        }
    }

    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) path.push_back(at);
    reverse(path.begin(), path.end());

    return (path[0] == start) ? path : vector<int>();
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> dist(n, INT_MAX), prev(n, -1);
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) 
    { 
        for (int u = 0; u < n; u++) 
        {
            for (int v = 0; v < n; v++) {
                if (adjMatrix[u][v] > 0 && dist[u] != INT_MAX) 
                {
                    int newDist = dist[u] + adjMatrix[u][v];
                    if (newDist < dist[v]) 
                    {
                        dist[v] = newDist;
                        prev[v] = u;
                    }
                }
            }
        }
    }

    vector<int> path;
    for (int at = end; at != -1; at = prev[at]) path.push_back(at);
    reverse(path.begin(), path.end());

    return (path[0] == start) ? path : vector<int>(); 
}
int main() {
    // Example adjacency matrix for testing
    vector<vector<int>> adjMatrix = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}
    };

    int startVertex = 0;
    int endVertex = 3;

    // Test Euler Cycle
    vector<int> eulerCycle = findEulerCycle(adjMatrix);
    if (!eulerCycle.empty()) {
        cout << "Euler Cycle: ";
        for (int v : eulerCycle) cout << v << " ";
        cout << endl;
    } else {
        cout << "No Euler Cycle exists." << endl;
    }

    // Test DFS Spanning Tree
    vector<vector<int>> dfsTree = dfsSpanningTree(adjMatrix, startVertex);
    cout << "DFS Spanning Tree:\n";
    for (const auto& row : dfsTree) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    // Test BFS Spanning Tree
    vector<vector<int>> bfsTree = bfsSpanningTree(adjMatrix, startVertex);
    cout << "BFS Spanning Tree:\n";
    for (const auto& row : bfsTree) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }

    // Test Connectivity
    cout << "Is Connected (" << startVertex << " → " << endVertex << ")? "
         << (isConnected(startVertex, endVertex, adjMatrix) ? "Yes" : "No") << endl;

    // Test Dijkstra's Algorithm
    vector<int> shortestPathDijkstra = dijkstra(startVertex, endVertex, adjMatrix);
    if (!shortestPathDijkstra.empty()) {
        cout << "Shortest Path (Dijkstra): ";
        for (int v : shortestPathDijkstra) cout << v << " ";
        cout << endl;
    } else {
        cout << "No Path Found (Dijkstra)." << endl;
    }

    // Test Bellman-Ford Algorithm
    vector<int> shortestPathBellman = bellmanFord(startVertex, endVertex, adjMatrix);
    if (!shortestPathBellman.empty()) {
        cout << "Shortest Path (Bellman-Ford): ";
        for (int v : shortestPathBellman) cout << v << " ";
        cout << endl;
    } else {
        cout << "No Path Found (Bellman-Ford)." << endl;
    }

    return 0;
}