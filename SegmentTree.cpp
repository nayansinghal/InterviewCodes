#include <iostream>
#include <stdio.h>
#include <vector>
#include <limits.h>
#include <assert.h>
using namespace std;

unsigned int nextPowerOf2(unsigned int n)
{
	unsigned count = 0;
 
	/* First n in the below condition is for the case where n is 0*/
	if (n && !(n&(n-1)))
		return n;
 
	while( n != 0)
	{
		n  >>= 1;
		count += 1;
	}
 
	return 1<<count;
}

class SegmentTree {
public:

	//create segment tree and lazy tree in memory
	void init(vector<int>& vec){

		element_size = vec.size();
		//create segment tree
		int segment_length = nextPowerOf2(vec.size()) * 2 - 1;
		vector<int> seg_tree(segment_length, INT_MAX);
		
		constructMinTree(vec, seg_tree, 0, vec.size()-1, 0);
		segment_tree = seg_tree;

		//construct lazy tree
		std::vector<int> lazy(segment_length, 0);
		lazy_tree = lazy;
	}

	// update range in segment tree
	void update(int sRange, int eRange, int delta){
		updateSegmentTree(0, element_size-1, 0, sRange, eRange, delta);
	}

	// find minimum element in range 
	int rangeMinQuery(int qlow, int qhigh){
		return rangeMinQuery(0, element_size-1, qlow, qhigh, 0);
	}

private:

	//construct min segment tree using vector elements
	void constructMinTree(vector<int>& vec, vector<int>& segment_tree, int low, int high, int pos){
		//leaf node
		if(low == high){
			segment_tree[pos] = vec[low];
			return;
		}

		//update left and right trees
		int mid = (low+high)/2;
		constructMinTree(vec, segment_tree, low, mid, 2*pos + 1);
		constructMinTree(vec, segment_tree, mid+1, high, 2*pos +2);

		//update current node using left and right subtrees
		segment_tree[pos] = min(segment_tree[2*pos+1], segment_tree[2*pos+2]);
	}

	//update segment tree using lazy propagation
	void updateSegmentTree(int low, int high, int pos, int sRange, int eRange, int delta){
		if(low > high)
			return;

		//lazy tree at pos is not updated
		if(lazy_tree[pos] != 0){
			segment_tree[pos] += lazy_tree[pos];
			// if it's a leaf
			if(low != high){
				lazy_tree[2*pos+1] += lazy_tree[pos];
				lazy_tree[2*pos+2] += lazy_tree[pos];
			}
			lazy_tree[pos] = 0;
		}

		//no overalp
		if(eRange < low || eRange > high)
			return;

		// totally overlap
		if(sRange <= low && eRange >= high){
			segment_tree[pos] += delta;
			if(low != high){
				segment_tree[2*pos+1] += delta; 
				segment_tree[2*pos+2] += delta;
			}
		}

		//update left and right segment tree
		int mid = (low + high)/2;
		updateSegmentTree(low, mid, 2*pos+1, sRange, eRange, delta);
		updateSegmentTree(low, mid, 2*pos+2, sRange, eRange, delta);
		segment_tree[pos] = min(segment_tree[2*pos+1], segment_tree[2*pos+2]);
	}

	//minimum element while updating segment tree using lazy tree
	int rangeMinQuery(int low, int high, int qlow, int qhigh, int pos){

		if(low > high)
			return INT_MAX;

		//lazy tree is not updated
		if(lazy_tree[pos] != 0){
			segment_tree[pos] += lazy_tree[pos];
			if(low != high){
				lazy_tree[2*pos+1] += lazy_tree[pos];
				lazy_tree[2*pos+2] += lazy_tree[pos];
			}
			lazy_tree[pos] = 0;
		}

		//totally overlap
		if(qlow <= low && qhigh >= high)
			return segment_tree[pos];

		// no overlap 
		if(qhigh < low || qhigh > high)
			return INT_MAX;

		//partial overlap
		int mid = (low+high)/2;
		return min(rangeMinQuery(low, mid, qlow, qhigh, 2*pos +1), 
							 rangeMinQuery(mid+1, high, qlow, qhigh, 2*pos+2));
	}

	vector<int> segment_tree;
	vector<int> lazy_tree;
	int element_size;
};

int main()
{
	static const int arr[] = {0,3,4,2,1,6,-1};
	vector<int> vec (arr, arr + sizeof(arr) / sizeof(arr[0]));
	int len = vec.size();

	SegmentTree segTree;
	segTree.init(vec);

	assert(0 == segTree.rangeMinQuery(0, 3));
	assert(1 == segTree.rangeMinQuery(1, 5));
	assert(-1 == segTree.rangeMinQuery(1, 6));

	segTree.update(2, 2, 1);
	assert(2 == segTree.rangeMinQuery(1, 3));

	segTree.update(3, 5, -2);
	assert(-1 == segTree.rangeMinQuery(5, 6));
	assert(0 == segTree.rangeMinQuery(0, 3));
	return 0;
}
