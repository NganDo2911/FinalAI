// C++ program to check if there is exist a path between two vertices 
// of a graph. 
#include<iostream> 
#include <vector> 
#include <queue>
#include <list>
#include <map>

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
	struct node* nextNode;
	struct node* parent;
}Node;

typedef struct NodeList {
	unsigned int nodeCount;    //the number of nodes in the list
	Node* head;            //pointer to the first node in the list
	Node* tail;            //pointer to the last node in the list
};

NodeList* FIFO_initial() {
	NodeList* list;
	list = (NodeList*)malloc(sizeof(NodeList));
	list->nodeCount = 0;
	list->head = NULL;
	list->tail = NULL;
	return list;
}
void FIFO_add(NodeList* list, Node* node) {
	if (list->nodeCount <= 0) {
		list->head = node;
		list->tail = node;
		list->nodeCount += 1;
		return;
	}
	if (node->path_cost)
		list->tail->nextNode = node;


	list->tail = node;
	list->nodeCount += 1;
}

Node* FIFO_pop(NodeList* list) {
	if (list->nodeCount <= 0) {
		return NULL;
	}
	Node* temp = list->head;
	list->nodeCount -= 1;
	if (list->nodeCount <= 0) {
		list->head = NULL;
		list->tail = NULL;
	}
	else {
		list->head = temp->nextNode;
	}
	return temp;
}

class Graph {
public:
	vector<vector<Edge>> adjList;
	Graph(const vector<Edge>& edges, int V) {		// dua cac dinh vao ma tran ke 
		adjList.resize(V);
		for (auto& edge : edges) {
			adjList[edge.start].push_back(edge);
			adjList[edge.end].push_back({ edge.end,edge.start,edge.distance });
		}
	}
	bool bfs(Graph const& g, int src, int dest, vector<int>& path, int n);
	void ucs(Graph const& g, int src, int dest, vector<bool> visited, int* pred, int n);
	int tinhThoiGian(vector<int> path, vector<vector<Edge>>adj);
};

void printEdge(vector<vector<Edge>> adjList)			//in ra cac dinh ke 
{
	std::vector<vector<Edge>>::iterator i;
	std::vector<Edge>::iterator j;
	for (i = adjList.begin(); i != adjList.end(); ++i) {
		for (j = i->begin(); j != i->end(); ++j) {
			cout << "->" << j->end << " " << j->distance << endl;
		}
	}
}
bool checkExit(NodeList* q, Node* node) {
	Node* _node;
	int i = 0;
	_node = q->head;
	while (i < q->nodeCount) {
		if (_node->vertex == node->vertex) {
			return true;
		}
		_node = _node->nextNode;
		i++;
	}
	return false;
}

void printPath(vector<int>& path, int src) {
	std::vector<int>::iterator i;
	for (i = path.begin(); i != path.end(); ++i) {
		cout << *i << " ";
		if (*i == src)
			break;
	}
}

void savePath(Node* node, int src, int& soDinh, vector<int>& path)
{
	soDinh = 0;
	while (node->parent != NULL) {
		path[soDinh] = node->vertex;
		soDinh++;
		if (node->vertex == src) {
			path.resize(soDinh);
			return;
		}
		node = node->parent;
	}
}

int Graph::tinhThoiGian(vector<int> path, vector<vector<Edge>>adj) {
	int* cost = (int*)malloc(path.size() - 1 * sizeof(int));
	int sum = 0;
	std::vector<Edge>::iterator j;
	std::vector<vector<Edge>>::iterator it;
	for (int i = 0; i < path.size() - 1; i++) {
		for (j = adj[path[i]].begin(); j != adj[path[i]].end(); ++j) {
			if (j->end == path[i + 1])
				cost[i] = j->distance;
		}
	}
	int i = 0;
	int z = path.size() - 2;
	while (i < path.size() / 2 && z >= path.size() / 2) {
		sum += cost[i];
		sum += cost[z];
		sum += abs(cost[i] - cost[z]);
		i++;
		z--;
	}
	return sum;
}
void printPathFromAToB(vector<int> path, int dest, std::string variable_names[]) {			//in ra duong di 
	cout << "\nPath is::\n";
	int j = dest;
	for (int z = path.size() - 1; z >= 0; z--) {
		if (path[z] == dest) {
			j = z;
			break;
		}
	}
	cout << "Nguoi A khoi hanh tu thanh pho: " << variable_names[path[path.size() - 1]] << endl;
	cout << "Nguoi B khoi hanh tu thanh pho: " << variable_names[path[j]] << endl;
	for (int i = path.size() - 2; i >= 0; i--) {

		cout << "Nguoi A di chuyen den thanh pho: " << variable_names[path[i]] << endl;
		if (path[i] == path[j]) {
			cout << "Hai nguoi da gap nhau tai thanh pho: " << variable_names[path[i]] << endl;
			return;
		}
		j += 1;
		cout << "Nguoi B di chuyen den thanh pho: " << variable_names[path[j]] << endl;
		if (path[i] == path[j]) {
			cout << "Hai nguoi da gap nhau tai thanh pho: " << variable_names[path[i]] << endl;
			return;
		}
	}


}
bool Graph::bfs(Graph const& g, int src, int dest, vector<int>& path, int n) {
	NodeList* frontier;
	NodeList* explorer;
	int minCost = INT_MAX;
	int soDinh;
	//danh sach cac duong co the di
//vector<int>listpath;
	frontier = FIFO_initial();
	explorer = FIFO_initial();
	Node* current = (Node*)malloc(sizeof(Node));
	current->vertex = src;
	current->depth = 0;
	current->path_cost = 0;
	FIFO_add(frontier, current);
	do {
		current = (FIFO_pop(frontier));
		FIFO_add(explorer, current);
		int v = current->vertex;
		int depth = current->depth;
		int cost = current->path_cost;
		std::vector<Edge>::iterator j;
		for (j = adjList[v].begin(); j != g.adjList[v].end(); ++j) {
			path.resize(n);
			Node* child = (Node*)malloc(sizeof(Node));
			child->vertex = j->end;
			child->path_cost = j->distance;
			child->parent = current;
			if ((checkExit(frontier, child) == false || checkExit(explorer, child) == false)) {
				if (child->vertex == dest) {
					savePath(child, src, soDinh, path);
					if (soDinh % 2 == 1 && soDinh != 1) {
						return true;
						//return tinhThoiGian(path, g.adjList);
					}
				}
				FIFO_add(frontier, child);
			}
		}
	} while (frontier->nodeCount > 0);
	return false;
}

void Graph::ucs(Graph const& g, int src, int dest, vector<bool> visited, int* pred, int n) {
	NodeList* frontier;
	NodeList* explorer;
	priority_queue<int> pq;
	int minCost = INT_MAX;
	int soDinh;
	vector<int>path(n);		//danh sach cac duong co the di
	vector<int>listpath;
	frontier = FIFO_initial();
	explorer = FIFO_initial();
	Node* current = (Node*)malloc(sizeof(Node));
	current->vertex = src;
	current->depth = 0;
	current->path_cost = 0;

	FIFO_add(frontier, current);
	do {
		current = (FIFO_pop(frontier));
		FIFO_add(explorer, current);
		int v = current->vertex;
		int depth = current->depth;
		int cost = current->path_cost;
		std::vector<Edge>::iterator j;
		for (j = adjList[v].begin(); j != g.adjList[v].end(); ++j) {
			Node* child = (Node*)malloc(sizeof(Node));
			child->vertex = j->end;
			child->path_cost = j->distance + cost;
			child->parent = current;
			if (checkExit(frontier, child) == false || checkExit(explorer, child) == false) {
				if (child->vertex == dest) {
					/*	savePath(child, src, soDinh);
						if (soDinh % 2 == 1) {
							printPath(child, src, path);
							return;
						}*/
				}
				FIFO_add(frontier, child);
			}
			/*else if (checkExit(frontier, child) == true && ) {

			}*/
		}
	} while (frontier->nodeCount > 0);
}

enum city {
	Oradea,
	Zerind,
	Arad,
	Sibiu,
	Timisoara,
	Lugoj,
	Mehadia,
	Drobeta,
	Craiova,
	RiminicuVilcea,
	Pitesti,
	Fagaras,
	Bucharest,
	Giurgiu,
	Urziceni,
	Vaslui,
	Iasi,
	Neamt,
	Hirsova,
	Eforie
};

void khoiTaoThanhPho() {
	std::cout << "0. Oradea" << std::endl;
	std::cout << "1. Zerind" << std::endl;
	std::cout << "2. Arad" << std::endl;
	std::cout << "3. Sibiu" << std::endl;
	std::cout << "4. Timisoara" << std::endl;
	std::cout << "5. Lugoj" << std::endl;
	std::cout << "6. Mehadia" << std::endl;
	std::cout << "7. Drobeta" << std::endl;
	std::cout << "8. Craivoa" << std::endl;
	std::cout << "9. RiminicuVilcea" << std::endl;
	std::cout << "10.Pitesti" << std::endl;
	std::cout << "11.Fagaras" << std::endl;
	std::cout << "12.Bucharest" << std::endl;
	std::cout << "13.Giurgiu" << std::endl;
	std::cout << "14.Urziceni" << std::endl;
	std::cout << "15.Vaslui" << std::endl;
	std::cout << "16.Iasi" << std::endl;
	std::cout << "17.Neamt" << std::endl;
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
	case city::Fagaras:
		std::cout << "Ban chon Fagaras" << std::endl;
		viTriNguoiA = city::Fagaras;
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
	case city::Vaslui:
		std::cout << "Ban chon Vaslui" << std::endl;
		viTriNguoiA = city::Neamt;
		break;
	case city::Iasi:
		std::cout << "Ban chon Iasi" << std::endl;
		viTriNguoiA = city::Iasi;
		break;
	case city::Neamt:
		std::cout << "Ban chon Neamt" << std::endl;
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
	//int variables_values[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };
	std::string variable_names[] = { "Oredea", "Zerind","Arad","Sibiu","Timisoara",
									"Lugoj","Mehadia","Drobeta","Cariova","Rimivicea",
									"Pitesti","Fafaras","Buchares","Giurgiu","Urzicen",
									"Vaslui","Iasi","Neamt","Hirsova","Eforie" };
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
	int* pred = new int[N];
	vector<int> path(N);
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

	printEdge(g.adjList);

	if (viTriNguoiA == viTriNguoiB) {
		cout << "Hai nguoi dang tren cung mot thanh pho" << endl;
	}
	else if (g.bfs(g, viTriNguoiA, viTriNguoiB, path, N) == true) {
		printPathFromAToB(path, viTriNguoiB, variable_names);
		cout << "Tong thoi gian di va cho cua ca hai nguoi la: " << g.tinhThoiGian(path, g.adjList) << endl;
	}
	else {
		cout << "Not Found" << endl;
	}


	return 0;
}