#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// data structure to store graph edges
struct Edge {
	int source, dest, weight;
};

// class to represent a graph object
class Graph
{
public:
	// construct a vector of vectors to represent an adjacency list
	vector<vector<int>> adjList;

	// Graph Constructor
	Graph(vector<Edge> const& edges, int N)
	{
		// resize the vector to 3*N elements of type vector<int>
		adjList.resize(N);

		// add edges to the undirected graph
		for (auto& edge : edges)
		{
			int v = edge.source;
			int u = edge.dest;
			int weight = edge.weight;

			//// create two new vertices v+N and v+2*N if the weight
			//// of edge is 3x. Also, split the edge (v, u) into (v, v+N),
			//// (v+N, v+2N) and (v+2N, u) each having weight x
			//if (weight == 3 * x)
			//{
			//	adjList[v].push_back(v + N);
			//	adjList[v + N].push_back(v + 2 * N);
			//	adjList[v + 2 * N].push_back(u);
			//}

			//// create one new vertex v+N if the weight of the edge
			//// is 2x. Also split the edge (v, u) into (v, v+N),
			//// (v+N, u) each having weight x
			//else if (weight == 2 * x)
			//{
			//	adjList[v].push_back(v + N);
			//	adjList[v + N].push_back(u);
			//}

			//// no splitting is needed if edge weight is 1x
			//else
			adjList[v].push_back(u);
		}
	}
};

// Recursive function to print path of given vertex v from
// the source vertex
void printPath(vector<int> const& predecessor, int v, int& cost, int N)
{
	if (v < 0)
		return;

	printPath(predecessor, predecessor[v], cost, N);
	cost++;

	// consider only original nodes present in the graph
	if (v < N)
		cout << v << " ";
}

// Perform BFS on graph starting from vertex source
void BFS(Graph const& graph, int source, int dest, int N)
{
	// stores vertex is discovered in BFS traversal or not
	vector<bool> discovered(N, false);

	// mark source vertex as discovered
	discovered[source] = true;

	// predecessor[] stores predecessor information. It is used
	// to trace least cost path from destination back to source.
	vector<int> predecessor(N, -1);

	// create a queue used to do BFS and push source vertex
	// into the queue
	queue<int> q;
	q.push(source);

	// run till queue is not empty
	while (!q.empty())
	{
		// pop front node from queue and print it
		int curr = q.front();
		q.pop();

		// if destination vertex is reached
		if (curr == dest)
		{
			int cost = 0;
			cout << "Least path between " << source << " and " <<
				dest << " is "; printPath(predecessor, dest, cost, N);
		}

		// do for every adjacent edge of current vertex
		for (int v : graph.adjList[curr])
		{
			if (!discovered[v])
			{
				// mark it discovered and push it into queue
				discovered[v] = true;
				q.push(v);

				// set curr as predecessor of vertex v
				predecessor[v] = curr;
			}
		}
	}
}

// Least cost path in weighted digraph using BFS
int main()
{
	int x = 1;

	// vector of graph edges as per above diagram
	vector<Edge> edges =
	{
		{0,1,71},{0,3,151},{1,2,75},{2,3,140},
		{2,4,118}, {3,11,99},{3,9,80},{4,5,111},
		{5,6,70},{6,7,75},{7,8,120},{8,9,146},
		{8,10,138},{9,10,97},{10,12,101},{11,12,211},
		{12,13,90},{12,14,85},{14,18,98},{14,15,142},
		{15,16,92},{16,17,87},{18,19,86}
	};

	// Number of nodes in the graph
	int N = 20;

	// create a graph from edges
	Graph graph(edges, N);

	// given source and destination vertex
	int source = 1, dest = 13;

	// Do BFS traversal from given source
	BFS(graph, source, dest, N);

	return 0;
}