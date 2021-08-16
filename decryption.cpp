#include<bits/stdc++.h>
using namespace std;
#define N 5


class Graph {
	int V;
	list<int> *adj; 
	void DFSUtil(int v, bool visited[]);

public:
    vector <int> vFinal;
	Graph(int V);
	void addEdge(int v, int w);
	void DFS(int v);
    std::vector<int> getFinalVector() {
        return vFinal;
    }
}; 

Graph::Graph(int V) {
	this->V = V; 
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w) {
	adj[v].push_back(w); 
}

void Graph::DFSUtil(int v, bool visited[]) {
	visited[v] = true; 
	//cout << v << " ";
    vFinal.push_back(v);
	list<int>::iterator i; 
	for (i = adj[v].begin(); i != adj[v].end(); ++i) 
		if (!visited[*i]) 
			DFSUtil(*i, visited); 
} 

void Graph::DFS(int v) {
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	DFSUtil(v, visited);
}

void multiply(float *mat1, float *mat2, float *res) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *((res+i*N) + j) = 0;
            for (int k = 0; k < N; k++)
                *((res+i*N) + j) += *((mat1+i*N) + k) * *((mat2+k*N) + j);
        }
    }
}

void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n) {
	int i = 0, j = 0; 
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (row != p && col != q) {
				temp[i][j++] = A[row][col];
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

int determinant(int A[N][N], int n) {
	int D = 0;
	if (n == 1)
		return A[0][0];

	int temp[N][N];
	int sign = 1;
	for (int f = 0; f < n; f++) {
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);
		sign = -sign;
	}

	return D;
}

void adjoint(int A[N][N],int adj[N][N]) {
	if (N == 1) {
		adj[0][0] = 1;
		return;
	}
	int sign = 1, temp[N][N];

	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++) {
			getCofactor(A, temp, i, j, N);
			sign = ((i+j)%2==0)? 1: -1;
			adj[j][i] = (sign)*(determinant(temp, N-1));
		}
	}
}

void inverse(int A[N][N], float inverse[N][N]) {
	int det = determinant(A, N);
	int adj[N][N];
	adjoint(A, adj);
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			inverse[i][j] = adj[i][j]/float(det);
}

int main() {
    int key[5][5] = {
       {1,1,1,1,1},
       {0,1,1,1,1},
       {0,0,1,1,1},
       {0,0,0,1,1},
       {0,0,0,0,1}
    };
    int M1[5][5] = {
        {0, 22, 0, 0, 0},
        {22, 0, -22, 27, 11},
        {0, -22, 0, 4, 28},
        {0, 27, 4, 0, 7},
        {0, 11, 28, 7, 0}
    };
    float C[5][5] = {
        {836, 302, -664, 476, 450},
        {352, 280, -180, 476, 450},
        {352, -688, -244, 406, 217},
        {836, -666, -744, 198, 77},
        {242, -605, -158, 133, 49}
    };

    float M1Inverse[5][5];
    float keyInverse[5][5];
    float M2[5][5];
    float M3[5][5];

    inverse(key, keyInverse);
    inverse(M1, M1Inverse);
    multiply(*keyInverse,*C,  *M3);

    multiply(*M1Inverse, *M3, *M2);

    Graph g(5);
    for (int i=0;i<5;i++) {
        for (int j=0;j<5;j++) {
           if (!(round(M1[i][j]) == 0  && round(M1[i][j] == -0))) {
               g.addEdge(i, j);
           }
        }
    }
    g.DFS(0);
    vector<int> v = g.getFinalVector();
    int prev = 0; 
    char ltr = 'a';
    char ltrnow;
    cout<<"The Encrypted word is :"<<endl;
    for (auto itr = v.begin()+1; itr != v.end(); itr++) {
       
        ltrnow = char(int(ltr) + M1[prev][*itr]);
        cout<<ltrnow;
        ltr = ltrnow;
        prev = *itr;
    }
    cout<<endl;

}