// C++ program to check if there is exist a path between two vertices 
// of a graph. 
#include<iostream> 
#include <vector> 
#include <queue>

using namespace std;

typedef struct edge {
    int start;
    int end;
    int distance;
}Edge;

typedef struct node {
    int vertex;
    int depth;
    int path_cost;
}Node;
class Graph {
public:
    vector<vector<Edge>> adjList;
    Graph(const vector<Edge>& edges, int V) {
        adjList.resize(V);
        for (auto& edge : edges) {
            adjList[edge.start].push_back(edge);
        }
    }
};
void printPath(vector<vector<Edge>> adjList)
{
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << endl;
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << "->" << adjList[i][j].end << " ";
        }
        cout << endl;
    }
}
bool bfs(Graph const& g, int src, int dest, vector<bool> visited, int* pred, int n) {
    queue<Node*> q;

    for (int i = 0; i < n; i++) {
        visited[i] = false;
        pred[i] = -1;
    }

    visited[src] = true;
    Node* current = (Node*)malloc(sizeof(Node));
    current->vertex = src;
    current->depth = 0;
    current->path_cost = 0;
    q.push(current);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        int v = node->vertex;
        int depth = node->depth;
        int cost = node->path_cost;
        for (int i = 0; i < g.adjList[v].size(); i++) {
            Node* newnode = (Node*)malloc(sizeof(Node));
            if (visited[g.adjList[v][i].end] == false) {
                visited[g.adjList[v][i].end] = true;
                newnode->vertex = g.adjList[v][i].end;
                newnode->depth = depth + 1;
                newnode->path_cost = g.adjList[v][i].distance;
                pred[g.adjList[v][i].end] = v;
                q.push(newnode);

                if (g.adjList[v][i].end == dest)
                    return true;
            }
        }
    }
    return false;
}

void printShortestDistance(Graph const& g, int src, int dest, vector<bool> visited, int n) {
    int* pred = new int[n];
    vector<int> path(n);

    if (bfs(g, src, dest, visited, pred, n) == false) {
        cout << "Given source and destination"
            << " are not connected";
        return;
    }
    int crawl = dest;
    path.push_back(crawl);
    while (pred[crawl] != -1) {
        path.push_back(pred[crawl]);
        crawl = pred[crawl];
    }

    // printing path from source to destination 
    cout << "\nPath is::\n";
    for (int i = path.size() - 1; i >= 0; i--) {
        cout << path[i] << " ";
        if (path[i] == dest)
            return;
    }

}



//void printPath(Node* node) {
//    if (node->parent == NULL)
//        return;
//    printPath(node->parent);
//    cout << node->vertex + " ";
//}
int main()
{
    // Create a graph given in the above diagram 
   /* Graph g(23);
    g.addEdge(1,2,71);
    g.addEdge(1,4,151);
    g.addEdge(2,3,75);
    g.addEdge(3,4,140);
    g.addEdge(3,5, 118);
    g.addEdge(4, 12, 99);
    g.addEdge(4, 10, 80);
    g.addEdge(5, 6, 111);
    g.addEdge(6, 7, 70);
    g.addEdge(7, 8, 75);
    g.addEdge(8, 9, 120);
    g.addEdge(9, 10, 146);
    g.addEdge(9, 11, 138);
    g.addEdge(10, 11, 97);
    g.addEdge(11, 13, 101);
    g.addEdge(12, 13, 211);
    g.addEdge(13, 14, 90);
    g.addEdge(13, 15, 85);
    g.addEdge(15, 19, 98);
    g.addEdge(15, 16, 142);
    g.addEdge(16, 17, 92);
    g.addEdge(17, 18, 87);
    g.addEdge(19, 20, 86);*/
    /*vector<Edge> edges =
    {
        {0,1,71},{0,3,151},{1,2,75},{2,3,140},
        {2,4,118}, {3,11,99},{3,9,80},{4,5,111},
        {5,6,70},{6,7,75},{7,8,120},{8,9,146},
        {8,10,138},{9,10,97},{10,12,101},{11,12,211},
        {12,13,90},{12,14,85},{14,18,98},{14,15,142},
        {15,16,92},{16,17,87},{18,19,86}
    };*/
    vector<Edge> edges =
    {
        {0,1,71},{0,3,151},{1,2,75},{2,3,140},
        {2,4,118}, {3,11,99},{3,9,80},{4,5,111},
        {5,6,70},{6,7,75},{7,8,120},{8,9,146},
        {8,10,138},{9,10,97},{10,12,101},{11,12,211},
        {12,13,90},{12,14,85},{14,18,98},{14,15,142},
        {15,16,92},{16,17,87},{18,19,86}
    };
    int N = 20;
    Graph g(edges, N);
    int src = 0, dest = 19;
    vector<bool> visited(N);
    int* path = new int[N];


    printPath(g.adjList);
    /*  if (bfs(g, src, dest, visited, path)) {
          cout << "Path exists from vertex " << src << " to vertex " << dest;
          cout << "\nThe complete path is: ";
      }
      else {
          cout << "No path exists between vertices " << src << " and " << dest;
      }*/
    if (bfs(g, src, dest, visited, path, N) == false) {
        cout << "False";
    }
    else {
        printShortestDistance(g, src, dest, visited, N);
        cout << "True";
    }
    return 0;
}