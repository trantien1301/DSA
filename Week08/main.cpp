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
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix)
 {
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
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) 
{
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
bool isBipartite(const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> color(n, -1);

    for (int start = 0; start < n; start++)
     {
        if (color[start] == -1) {
            queue<int> queue;
            queue.push(start);
            color[start] = 0;

            while (!queue.empty()) {
                int v = queue.front();
                queue.pop();

                for (int neighbor = 0; neighbor < n; neighbor++) 
                {
                    if (adjMatrix[v][neighbor]) 
                    {
                        if (color[neighbor] == -1) 
                        {
                            color[neighbor] = 1 - color[v]; 
                            queue.push(neighbor);
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
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) 
{
    if (!isBipartite(adjMatrix)) 
    {
        return false;
    }
    int n = adjMatrix.size();
    vector<int> color(n, -1);
    vector<int> group1, group2;

    for (int start = 0; start < n; start++) 
    {
        if (color[start] == -1) 
        {
            queue<int> queue;
            queue.push(start);
            color[start] = 0;
            group1.push_back(start);

            while (!queue.empty()) 
            {
                int v = queue.front();
                queue.pop();

                for (int neighbor = 0; neighbor < n; neighbor++) 
                {
                    if (adjMatrix[v][neighbor])
                    {
                        if (color[neighbor] == -1)
                        {
                            color[neighbor] = 1 - color[v];
                            if (color[neighbor] == 0) 
                            {
                                group1.push_back(neighbor);
                            } 
                            else 
                            {
                                group2.push_back(neighbor);
                            }
                            queue.push(neighbor);
                        }
                    }
                }
            }
        }
    }

    for (int u=0;u<group1.size();u++) 
    {
        for (int v=0;v<group2.size();v++) 
        {
            if (adjMatrix[u][v] == 0) 
            {
                return false;
            }
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

vector<int> findEulerCycleUndirected(vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    stack<int> stack;
    vector<int> res;
    vector<vector<int>> graph = adjMatrix;
    vector<int> degree(n, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            degree[i] += graph[i][j];


    for (int i = 0; i < n; i++)
        if (degree[i] % 2 != 0)
            return {}; 

    int start = 0;
    while (start < n && degree[start] == 0) start++;
    stack.push(start);

    while (!stack.empty()) 
    {
        int vertices = stack.top();

        if (degree[vertices] == 0)
        {
            res.push_back(vertices);
            stack.pop();
        } 
        else
        {
            for (int u = 0; u < n; u++) 
            {
                if (graph[vertices][u] > 0) 
                {
                    stack.push(u);
                    graph[vertices][u]--;
                    graph[u][vertices]--;
                    degree[vertices]--;
                    degree[u]--;
                    break;
                }
            }
        }
    }

    return res;
}

vector<int> findEulerCycleDirected(vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    stack<int> stack;
    vector<int> res;
    vector<vector<int>> graph = adjMatrix;
    vector<int> inDegree(n, 0), outDegree(n, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) 
        {
            outDegree[i] += graph[i][j];
            inDegree[j] += graph[i][j];
        }
    for (int i = 0; i < n; i++)
        if (inDegree[i] != outDegree[i])
        {
            return {}; 
        } 
    int start = 0;
    while (start < n && outDegree[start] == 0) start++;
    stack.push(start);

    while (!stack.empty()) 
    {
        int vertices = stack.top();

        if (outDegree[vertices] == 0) 
        {
            res.push_back(vertices);
            stack.pop();
        } 
        else 
        {
            int u = -1;
            for (int neighbor = 0; neighbor < n; neighbor++) 
            {
                if (graph[vertices][neighbor] > 0) 
                {
                    u = neighbor;
                    break;
                }
            }

            if (u != -1) 
            {
                stack.push(u);
                graph[vertices][u]--;
                outDegree[vertices]--;
                inDegree[u]--;
            }
        }
    }
    return res;
}

vector<int> findEulerCycle(vector<vector<int>>& adjMatrix) 
{
    if(isDirected(adjMatrix))
    {
        return findEulerCycleDirected(adjMatrix);
    }
    else
    {
        return findEulerCycleUndirected(adjMatrix);
    }
}

void dfs(int node, vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<vector<int>>& spanningTree) 
{
    visited[node] = true;
    for (int u = 0; u < adjMatrix.size(); u++) 
    {
        if (adjMatrix[node][u] && !visited[u]) 
        {
            spanningTree[node][u] = 1;
            spanningTree[u][node] = 1;
            dfs(u, adjMatrix, visited, spanningTree);
        }
    }
}

vector<vector<int>> dfsSpanningTree(vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    dfs(start, adjMatrix, visited, spanningTree);
    return spanningTree;
}

vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start)
{
    int n = adjMatrix.size();
    vector<vector<int>> spanningTree(n, vector<int>(n, 0));
    vector<bool> visited(n, false);
    queue<int> queue;

    visited[start] = true;
    queue.push(start);

    while (!queue.empty()) 
    {
        int node = queue.front();
        queue.pop();

        for (int neighbor = 0; neighbor < n; neighbor++) 
        {
            if (adjMatrix[node][neighbor] && !visited[neighbor]) 
            {
                spanningTree[node][neighbor] = 1;
                spanningTree[neighbor][node] = 1;
                visited[neighbor] = true;
                queue.push(neighbor);
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
    vector<int> distance(n, INT_MAX), prev(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> queue;

    distance[start] = 0;
    queue.push({0, start});

    while (!queue.empty()) 
    {
        int d = queue.top().first, u = queue.top().second;
        queue.pop();

        if (d > distance[u]) 
        {
            continue;
        }

        for (int v = 0; v < n; v++) 
        {
            if (adjMatrix[u][v] > 0) 
            {
                int newDist = distance[u] + adjMatrix[u][v];
                if (newDist < distance[v]) 
                {
                    distance[v] = newDist;
                    prev[v] = u;
                    queue.push({newDist, v});
                }
            }
        }
    }

    vector<int> path;
    for (int curr = end; curr != -1; curr = prev[curr]) 
    {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());

if(path[0] == start)
{
    return path;
}
else
{
    return  vector<int>();
}

}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix) 
{
    int n = adjMatrix.size();
    vector<int> distance(n, INT_MAX), prev(n, -1);
    distance[start] = 0;

    for (int i = 0; i < n - 1; i++) 
    { 
        for (int u = 0; u < n; u++) 
        {
            for (int v = 0; v < n; v++) 
            {
                if (adjMatrix[u][v] > 0 && distance[u] != INT_MAX) 
                {
                    int newDist = distance[u] + adjMatrix[u][v];
                    if (newDist < distance[v]) 
                    {
                        distance[v] = newDist;
                        prev[v] = u;
                    }
                }
            }
        }
    }

    vector<int> path;
    for (int curr = end; curr != -1; curr = prev[curr]) 
    {
        path.push_back(curr);
    }
    reverse(path.begin(), path.end());

    if(path[0] == start)
{
    return path;
}
else
{
    return  vector<int>();
}
}
