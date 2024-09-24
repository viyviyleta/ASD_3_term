#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <array>

using namespace std;

const int N = 10;  //кол-во вершин графа
bool* visited = new bool[N];  //посещенные вершинах

struct Edge { 
	int start;  //начало ребра (вершина)
	int finish;  //конец ребра (вершина)
};

// Матрица смежности графа
int graph[N][N] = {
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0}, 
	{1, 0, 0, 0, 0, 0, 1, 1, 0, 0},  
	{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},  
	{0, 0, 0, 0, 0, 1, 0, 0, 1, 0},  
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0},  
	{0, 0, 0, 1, 1, 0, 0, 0, 1, 0},  
	{0, 1, 0, 0, 0, 0, 0, 1, 0, 0},  
	{0, 1, 1, 0, 0, 0, 1, 0, 0, 0},  
	{0, 0, 0, 1, 0, 1, 0, 0, 0, 1},  
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 0}   
};

//обход графа в ширину (BFS)
void BFS(int start) {
	queue<int> q;  
	bool visited[N]{};  //посещенные вершин
	bool inqueue[N]{};  //добавленые в очередь
	int view;  //текущая вершина

	for (int i = 0; i < N; i++) {
		visited[i] = inqueue[i] = false;
	}

	q.push(start);
	visited[start] = inqueue[start] = true;  

	//пока очередь не пуста, продолжаем обход
	while (!q.empty()) {
		view = q.front();
		cout << view + 1 << " ";  
		visited[view] = true; 
		q.pop();  

		for (int i = 0; i < N; i++) {
			if (!inqueue[i] && graph[view][i]) {  
				q.push(i);  
				inqueue[i] = true;  
			}
		}
	}
}

//обход графа в глубину (DFS)
void DFS(int start) {
	stack<int> s;  
	bool visited[N]{};  
	bool inqueue[N]{};  
	int view;  

	for (int i = 0; i < N; i++) {
		visited[i] = inqueue[i] = false;
	}

	s.push(start);
	visited[start] = inqueue[start] = true; 

	while (!s.empty()) {
		view = s.top(); 
		cout << view + 1 << " "; 
		visited[view] = true; 
		s.pop();  

		for (int i = 0; i < N; i++) {
			if (!inqueue[i] && graph[view][i]) {  
				s.push(i);  
				inqueue[i] = true;  
			}
		}
	}
}

void main() {
	setlocale(LC_ALL, "rus"); 
	cout << "Список смежности: " << endl;

	vector<Edge> edges = {
		{1, 2}, {2, 1}, {1, 5}, {5, 1},  
		{2, 7}, {7, 2}, {2, 8}, {8, 2},  
		{7, 8}, {8, 7}, {8, 3}, {3, 8},
		{5, 6}, {6, 5}, {4, 6}, {6, 4},
		{4, 9}, {9, 4}, {6, 9}, {9, 6},
		{9, 10}, {10, 9} 
	};

	int n = 11;  
	vector<vector<int>> adjList;  // Список смежности
	adjList.resize(n);  

	for (auto& edge : edges) {
		adjList[edge.start].push_back(edge.finish);  
	}

	for (int i = 1; i < n; i++) {
		cout << i << "--> { ";  
		for (int v : adjList[i]) {
			cout << v << " ";  
		}
		cout << "}" << endl;
	}
	cout << endl;

	cout << "Список ребер: " << endl;
	for (int i = 1; i < n; i++) {
		for (int v : adjList[i]) {
			cout << "{" << i << "," << v << "}"; 
		}
		cout << endl;
	}
	cout << endl;

	int start;  
	cout << "Матрица смежности графа: " << endl;

	//выводим матрицу смежности графа
	for (int i = 0; i < N; i++) {
		visited[i] = false;  // Инициализация посещенных вершин
		for (int j = 0; j < N; j++)
			cout << " " << graph[i][j];  
		cout << endl;
	}
	cout << endl;

	cout << "Стартовая вершина: ";
	cin >> start; 
	if (start > 10 || start < 1) cout << "Ошибка";
	else {
		cout << "\n\nПорядок обхода в ширину: ";
		BFS(start - 1);
		cout << endl;
		delete[]visited;
		cout << "\nПорядок обхода в глубину: ";
		DFS(start - 1);
		cout << endl;
		cout << endl;
	}
	//cout << "Расчёт О-большое: " << endl;
	//int v = 10, e = 11;
	//cout << "O(|V| + |E|) = " << abs(v) + abs(e) << endl;  
}
