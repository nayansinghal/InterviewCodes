#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;
struct node
{
	/* data */
	int x;
	bool isStart;
	int height;
};

vector<node> processSkyline(std::vector< pair< pair<int, int>, int> > vec){
	vector<node> line;
	for(int i=0; i<vec.size(); i++){
		node a;
		a.x = vec[i].first.first;
		a.height = vec[i].second;
		a.isStart = true;
		line.push_back(a);

		node b;
		b.x = vec[i].first.second;
		b.height = vec[i].second;
		b.isStart = false;
		line.push_back(b);
	}

	return line;
}

void printLine(vector<node>& line){
	for(int i = 0; i < line.size(); i++){
		cout << line[i].x << " "<<line[i].isStart << " " << line[i].height<<"\n";
	}
}

bool compare( const node& a, const node& b){
	if(a.x < b.x)	
		return true;
	else if(a.x > b.x)
		return false;

	if(a.isStart == b.isStart && a.isStart == true){
		if(a.height <= b.height)
			return false;
		return true;
	}
	
	if(a.isStart == b.isStart && a.isStart == false){
		if(a.height > b.height)
			return false;
		return true;
	}

	if(a.height > b.height)
		return false;

	return true;
}

vector<pair<int, int> > skyline(std::vector< pair< pair<int, int>, int> > vec){

	vector<node> line = processSkyline(vec);
	sort(line.begin(), line.end(), compare);

	priority_queue< int, vector<int>, std::less<int> > q;
	map< int, int > count;
	q.push(0);
	count[0] = 1;
	int maxElement = 0;
	int prevMaxHeight = 0;
	
	std::vector< pair<int, int> > output;
	for(int i=0; i < line.size(); i++){
		node s = line[i];

		if(s.isStart){
			if(count[s.height] != 0)
				count[s.height] += 1;
			else{
				q.push(s.height);
				count[s.height] = 1;
			}
		}
		else{
			count[s.height] -= 1;
		}

		int currentMaxHeight = q.top();
		while(count[currentMaxHeight] == 0 && !q.empty()){
			q.pop();
			currentMaxHeight = q.top();
		}

		if(currentMaxHeight != prevMaxHeight){
			output.push_back(make_pair(s.x, currentMaxHeight));
			prevMaxHeight = currentMaxHeight;
		}
	}
	return output;
}

int main()
{
	std::vector< pair< pair<int, int>, int> > vec;
	vec.push_back(make_pair(make_pair(0,5),7));
	vec.push_back(make_pair(make_pair(5,10),7));
	vec.push_back(make_pair(make_pair(5,10),12));
	vec.push_back(make_pair(make_pair(10,15),7));
	vec.push_back(make_pair(make_pair(15,20),7));
	vec.push_back(make_pair(make_pair(15,20),12));
	vec.push_back(make_pair(make_pair(20,25),7));

	vector< pair<int, int> > result;
	result = skyline(vec);

	for(int i=0 ; i<result.size(); i++)
		cout<< result[i].first <<" "<<result[i].second<<"\n";

	return 0;
}