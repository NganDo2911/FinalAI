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

enum city {
	Oradea,
	Zerind,
	Arad,
	Sibiu,
	Fagaras,
	Timisoara,
	Lugoj,
	Mehadia,
	Drobeta,
	Craiova,
	RiminicuVilcea,
	Pitesti,
	Bucharest,
	Giurgiu,
	Urziceni,
	Neamt,
	Iasi,
	Vaslui,
	Hirsova,
	Eforie
};
void khoiTaoThanhPho() {
	std::cout << "0. Oradea" << std::endl;
	std::cout << "1. Zerind" << std::endl;
	std::cout << "2. Arad" << std::endl;
	std::cout << "3. Sibiu" << std::endl;
	std::cout << "4. Fagaras" << std::endl;
	std::cout << "5. Timisoara" << std::endl;
	std::cout << "6. Lugoj" << std::endl;
	std::cout << "7. Mehadia" << std::endl;
	std::cout << "8. Drobeta" << std::endl;
	std::cout << "9. Craiova" << std::endl;
	std::cout << "10.RiminicuVilcea" << std::endl;
	std::cout << "11.Pitesti" << std::endl;
	std::cout << "12.Bucharest" << std::endl;
	std::cout << "13.Giurgiu" << std::endl;
	std::cout << "14.Urziceni" << std::endl;
	std::cout << "15.Neamt" << std::endl;
	std::cout << "16.Iasi" << std::endl;
	std::cout << "17.Vaslui" << std::endl;
	std::cout << "18.Hirsova" << std::endl;
	std::cout << "19.Eforie" << std::endl;
}


void chonThanhPho(int viTriNguoiA)
{
	switch (viTriNguoiA) {
	case city::Oradea:
		std::cout << "Ban chon Oradea" << std::endl;
		viTriNguoiA = city::Oradea;
		break;
	case city::Zerind:
		std::cout << "Ban chon Zerind" << std::endl;
		viTriNguoiA = city::Zerind;
		break;
	case city::Arad:
		std::cout << "Ban chon Arad" << std::endl;
		viTriNguoiA = city::Arad;
		break;
	case city::Sibiu:
		std::cout << "Ban chon Sibiu" << std::endl;
		viTriNguoiA = city::Sibiu;
		break;
	case city::Fagaras:
		std::cout << "Ban chon Fagaras" << std::endl;
		viTriNguoiA = city::Fagaras;
		break;
	case city::Timisoara:
		std::cout << "Ban chon Timisoara" << std::endl;
		viTriNguoiA = city::Timisoara;
		break;
	case city::Lugoj:
		std::cout << "Ban chon Lugoj" << std::endl;
		viTriNguoiA = city::Lugoj;
		break;
	case city::Mehadia:
		std::cout << "Ban chon Mehadia" << std::endl;
		viTriNguoiA = city::Mehadia;
		break;
	case city::Drobeta:
		std::cout << "Ban chon Drobeta" << std::endl;
		viTriNguoiA = city::Drobeta;
		break;
	case city::Craiova:
		std::cout << "Ban chon Craiova" << std::endl;
		viTriNguoiA = city::Craiova;
		break;
	case city::RiminicuVilcea:
		std::cout << "Ban chon RiminicuVilcea" << std::endl;
		viTriNguoiA = city::RiminicuVilcea;
		break;
	case city::Pitesti:
		std::cout << "Ban chon Pitesti" << std::endl;
		viTriNguoiA = city::Pitesti;
		break;
	case city::Bucharest:
		std::cout << "Ban chon Bucharest" << std::endl;
		viTriNguoiA = city::Bucharest;
		break;
	case city::Giurgiu:
		std::cout << "Ban chon Giurgiu" << std::endl;
		viTriNguoiA = city::Giurgiu;
		break;
	case city::Urziceni:
		std::cout << "Ban chon Urziceni" << std::endl;
		viTriNguoiA = city::Urziceni;
		break;
	case city::Neamt:
		std::cout << "Ban chon Neamt" << std::endl;
		viTriNguoiA = city::Neamt;
		break;
	case city::Iasi:
		std::cout << "Ban chon Iasi" << std::endl;
		viTriNguoiA = city::Iasi;
		break;
	case city::Vaslui:
		std::cout << "Ban chon Vaslui" << std::endl;
		viTriNguoiA = city::Vaslui;
		break;
	case city::Hirsova:
		std::cout << "Ban chon Hirsova" << std::endl;
		viTriNguoiA = city::Hirsova;
		break;
	case city::Eforie:
		std::cout << "Ban chon Eforie" << std::endl;
		viTriNguoiA = city::Eforie;
		break;
	default:
		std::cout << "Vui long chon thanh pho tren danh sach" << std::endl;
	};
}


int main()
{
	// Create a graph given in the above diagram 
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
	vector<bool> visited(N);
	int* path = new int[N];
	std::cout << "Chon thanh pho cho nguoi A" << std::endl;
	khoiTaoThanhPho();
	int viTriNguoiA;
	std::cout << "Vi tri nguoi A: ";
	std::cin >> viTriNguoiA;
	chonThanhPho(viTriNguoiA);
	std::cout << std::endl;
	std::cout << "Chon thanh pho cho nguoi B" << std::endl;
	khoiTaoThanhPho();
	int viTriNguoiB;
	std::cout << "Vi tri nguoi B: ";
	std::cin >> viTriNguoiB;
	chonThanhPho(viTriNguoiB);
	std::cout << std::endl;

	//printPath(g.adjList);
	if (bfs(g, viTriNguoiA, viTriNguoiB, visited, path, N) == false) {
		cout << "False";
	}
	else {
		printShortestDistance(g, viTriNguoiA, viTriNguoiB, visited, N);
		cout << "True";
	}
	return 0;
}