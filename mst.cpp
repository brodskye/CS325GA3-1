#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <limits.h>



using namespace std; 

struct ListVert
{
	int V;
	int EW;
	struct ListVert* nextV;
};

struct ListV
{
	struct ListVert *Top;  
};

struct G
{
	int V;
	struct ListV* ar;
};

struct MinH
{
	int  V;
	int H;
};

struct MinHArr
{
	int S;      
	int SS;  
	int *ind;     
	struct MinH **arr;
};

struct Pair {
	int v1;
	int v2;
};

vector<Pair> pairs;

struct MST {
	int weight;
	vector<Pair> pairs;
};


void Swap(struct MinH** one, struct MinH** two)
{
struct MinH* temp = *one;
	
	*one = *two;
	*two = temp;
}

int isEmpty(struct MinHArr* Heap)
{
	return Heap->S == 0;
}

bool Contains(struct MinHArr *min, int V)
{
	if (min->ind[V] < min->S)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void FindMin(struct MinHArr* min, int index)
{
	
	int i = index;
	int in2 = index*2;
	int L = (in2 + 1);
	int R = (in2 + 2);
	MinH *SH, *ind;

		if (L < min->S && min->arr[L]->H < min->arr[i]->H)
		{
			i = L;
		}
		if (R < min->S && min->arr[R]->H < min->arr[i]->H)
		{
			i = R;
		}	
		if (i != index)
		{
			SH = min->arr[i];
			ind = min->arr[index];
			min->ind[SH->V] = index;
			min->ind[ind->V] = i;
			Swap(&min->arr[i], &min->arr[index]);
			FindMin(min, i);
		}
}

struct MinH* getMin(struct MinHArr* min)
{
	struct MinH* newmin;
	struct MinH* prev;
		if (isEmpty(min))
		{
		return 0;
		}

	newmin = min->arr[0];
	prev = min->arr[(min->S) - 1];
	min->arr[0] = prev;
	min->ind[newmin->V] = min->S - 1;
	min->ind[prev->V] = 0;
	(min->S)--;
	FindMin(min, 0);

return newmin;
}

void FindInd(struct MinHArr* min, int v, int key)
{
	int ind = min->ind[v];
	min->arr[ind]->H = key;
		while (ind && min->arr[ind]->H < min->arr[(ind - 1) / 2]->H)
		{
			min->ind[min->arr[ind]->V] = (ind - 1) / 2;
			min->ind[min->arr[(ind - 1) / 2]->V] = ind;
			Swap(&min->arr[ind], &min->arr[(ind - 1) / 2]);
			ind = (ind - 1) / 2;
		}
}

void printArr(int arr[], int n)
{
	pairs.clear();
	for (int i = 1; i < n; ++i) {
		Pair newPair;
		newPair.v1 = i;
		newPair.v2 = arr[i];
		pairs.push_back(newPair);
	}
}

struct MinHArr* createH(int SS)
{
struct MinHArr* newminH = (struct MinHArr*) malloc(sizeof(struct MinHArr));
	newminH->ind = (int *)malloc(SS * sizeof(int));
	newminH->S = 0;
	newminH->SS = SS;
	newminH->arr =(struct MinH**) malloc(SS * sizeof(struct MinH*));
	return newminH;
}

struct MinH* newMinH(int V, int H)
{
struct MinH* newminH = (struct MinH*) malloc(sizeof(struct MinH));

	newminH->V = V;
	newminH->H = H;

return newminH;
}

void PrimsAlg(struct G* G)
{
	int V = G->V;
	int P[V], H[V];      
	struct MinHArr* min = createH(V);
	int i;

		for (i = 1; i < V; i++)
		{
			P[i] = -1;
			H[i] = INT_MAX;
			min->arr[i] = newMinH(i, H[i]);
			min->ind[i] = i;
		}
	H[0] = 0;
	min->arr[0] = newMinH(0, H[0]);
	min->ind[0] = 0;
	min->S = V;
		while (!isEmpty(min))
		{
		struct MinH* minH = getMin(min);
		int j = minH->V; 
		struct ListVert* prim = G->ar[j].Top;
			while (prim != 0)
			{
			int h = prim->V;
				if (Contains(min, h) && prim->EW < H[h])
				{
					H[h] = prim->EW;
					P[h] = j;
					FindInd(min, h, H[h]);
				}
			prim = prim->nextV;
			}
		}

	printArr(P, V);
}

struct ListVert* newListVert(int V, int EW)
{
	struct ListVert* newV =	(struct ListVert*) malloc(sizeof(struct ListVert));

	newV->V = V;
	newV->EW = EW;
	newV->nextV = 0;

return newV;
}

void Edge(struct G* newG, int VS, int DS, int EW)
{
	struct ListVert* newV = newListVert(DS, EW);
	newV->nextV = newG->ar[VS].Top;
	newG->ar[VS].Top = newV;
	newV = newListVert(VS, EW);
	newV->nextV = newG->ar[DS].Top;
	newG->ar[DS].Top = newV;
}

struct G* NewGraph(int Vsize)
{
	struct G* newG = (struct G*) malloc(sizeof(struct G));
	newG->V = Vsize;
	newG->ar = (struct ListV*) malloc(Vsize * sizeof(struct ListV));

	int i;
	for (i = 0; i < Vsize; ++i)
	{
		newG->ar[i].Top = 0;
	}

return newG;
}

int main()
{
	int n;
	int k;
	int test;
	FILE* fp;
	fp = fopen("input.txt", "rb");
	fscanf(fp, "%d", &n);
	int graph[n][n];

	for (int i = 0;; i++) {
	for (int j = 0;; j++) {
	if (fscanf(fp, "%d", &test) == -1)
	goto end;
	graph[i][j] = test;
	if ((k = fgetc(fp)) == '\n')
	break;
	}
	}
	end:

	int V = n;
	struct G* ggraph = NewGraph(V); 
	for (int i = 0; i < V; i++) {
		for (int j = 0; j < i; j++) {
			if (graph[i][j] != 0) {
				Edge(ggraph, i, j, graph[i][j]);
			}
		}
	}


	PrimsAlg(ggraph); 
	int total = 0; 
	for (vector<Pair>::const_iterator i = pairs.begin(); i != pairs.end(); ++i) {
		total += graph[i->v2][i->v1];
	}

	struct MST mst1;
	mst1.weight = total;
	mst1.pairs = pairs;
	cout << "first MST: " << mst1.weight << endl; 

	pairs.clear();

	vector<int> mstWeights;
	mstWeights.push_back(mst1.weight);
	vector<MST> mstVec;
	for (vector<Pair>::const_iterator iter = mst1.pairs.begin(); iter != mst1.pairs.end(); ++iter) {
		ggraph = NewGraph(V); 
		for (int i = 0; i < V; i++) {
			for (int j = 0; j <= i; j++) {
				if (graph[i][j] != 0 && !((i == iter->v1 && j == iter->v2) || (i == iter->v2 && j == iter->v1))) {
					Edge(ggraph, i, j, graph[i][j]);
				}
			}
		}
		PrimsAlg(ggraph); 
		total = 0;
		for (vector<Pair>::const_iterator k = pairs.begin(); k != pairs.end(); ++k) {
			total += graph[k->v1][k->v2];
		}
		struct MST mst;
		mst.weight = total;
		mst.pairs = pairs;
		mstVec.push_back(mst);

	}


	struct MST smallest = mstVec.at(0);
	int c = 0;

	for (int l = 0; l < mstVec.size(); l++) {
		if (mstVec.at(l).weight < smallest.weight) {
			if (find(mstWeights.begin(), mstWeights.end(), mstVec.at(l).weight) == mstWeights.end()) 
			{
				smallest = mstVec.at(l);
			}
		}
	}

	struct MST mst2 = smallest;
	cout << "Second MST: " << mst2.weight << endl;
	mstWeights.push_back(mst2.weight);


	mstVec.clear();
	for (vector<Pair>::const_iterator iter = mst2.pairs.begin(); iter != mst2.pairs.end(); ++iter) {
		ggraph = NewGraph(V); 
		for (int i = 0; i < V; i++) {
			for (int j = 0; j <= i; j++) {
				if (graph[i][j] != 0 && !((i == iter->v1 && j == iter->v2) || (i == iter->v2 && j == iter->v1))) {
					Edge(ggraph, i, j, graph[i][j]);
				}
			}
		}

		PrimsAlg(ggraph);
		total = 0;
		for (vector<Pair>::const_iterator k = pairs.begin(); k != pairs.end(); ++k) {
			total += graph[k->v1][k->v2];
		}
		struct MST mst;
		mst.weight = total;
		mst.pairs = pairs;
		pairs.clear();
		mstVec.push_back(mst);
	}
	smallest = mstVec.at(0);
	smallest.weight = INT_MAX;

	for (int l = 0; l < mstVec.size(); l++) {
		if (mstVec.at(l).weight < smallest.weight) {
			if (find(mstWeights.begin(), mstWeights.end(), mstVec.at(l).weight) == mstWeights.end()) {
				smallest = mstVec.at(l);
			}
		}
	}
	struct MST mst3 = smallest;
	cout << "Third MST: " << mst3.weight << endl;
	mstWeights.push_back(mst3.weight);

	/*
	Use Prim's to find MST
	For Each edge in MST:
	Remove edge from graph
	Calculate MST' on MST
	Keep track of smallest MST
	Add edge back to graph
	Return the smallest MST*/

	return 0;
}
