#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
void dijakstra(map<int, vector< pair<int,int> > > graph, int source){
	queue< pair<int, int> > q;
	q.push(make_pair(source, 0));
	map<int, bool> visited;

	while(!q.empty()){
		pair<int, int> node = q.front();
		q.pop();

		for(int i = 0; i < graph[node.first].size(); i++){
			pair<int, int> child = graph[node.first][i];

			if(!visited[child.first])

			if(!visited[child.first])
				q.push()
		}
	}
}

int main()
{
	map<int, vector< pair<int,int> > > graph;
	graph[1].push_back(make_pair(2,5));
	graph[2].push_back(make_pair(3,2));
	graph[1].push_back(make_pair(4,9));
	graph[1].push_back(make_pair(5,3));
	graph[5].push_back(make_pair(6,2));
	graph[6].push_back(make_pair(4,2));
	graph[3].push_back(make_pair(4,3));


	return 0;
}