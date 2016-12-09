#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;
void topoSortUtil(map<int, vector<int> > & graph, map<int, bool> & visited, stack<int>& st, int root){

	visited[root] = true;
	for(int i=0; i < graph[root].size(); i++){
		if(!visited[graph[root][i]]){
			topoSortUtil(graph, visited, st, graph[root][i]);
			
		}
	}
	st.push(root);
}

stack<int> topoSort(map<int, vector<int> >& graph){
	map<int, bool> visited;
	stack<int> st;

	map<int, vector<int> > ::iterator it;
	for(it = graph.begin(); it != graph.end(); it++){
		if(!visited[it->first])
			topoSortUtil(graph, visited, st, it->first);
	}

	return st;
}
int main()
{
	map<int, vector<int> > graph;
	graph[1].push_back(3);
	graph[1].push_back(2);
	graph[3].push_back(4);
	graph[5].push_back(6);
	graph[6].push_back(3);
	graph[3].push_back(8);
	graph[8].push_back(11);

	stack<int> tSort = topoSort(graph);
	while(!tSort.empty()){
		cout << tSort.top()<<" ";
		tSort.pop();
	}

	return 0;
}