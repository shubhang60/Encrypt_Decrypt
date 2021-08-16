#include<bits/stdc++.h>
using namespace std;

void multiply(int *mat1, int *mat2, int *res, int N) {

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            *((res+i*N) + j) = 0;
            for (int k = 0; k < N; k++)
                *((res+i*N) + j) += *((mat1+i*N) + k) * *((mat2+k*N) + j);
        }
    }
}

struct DisjointSets {
    int *parent, *rnk; 
    int n; 

    DisjointSets(int n) { 

        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 

        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0;
            parent[i] = i; 
        } 
    }
    int find(int u) {
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    }

    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (rnk[x] > rnk[y])
            parent[y] = x;
        else 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++;
    }
};


class Graph {
   private:
    int** adjMatrix;
    int numVertices;
    int E;
    vector< pair<int, pair<int, int> > > edges;

   public:
  Graph(int numVertices) {
    this->numVertices = numVertices;
    adjMatrix = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) {
      adjMatrix[i] = new int[numVertices];
      for (int j = 0; j < numVertices; j++)
        adjMatrix[i][j] = 0;
    }
  }

  void addEdge(int i, int j, int w) {
    adjMatrix[i][j] = w;
    adjMatrix[j][i] = w;
    edges.push_back(make_pair(w, make_pair(i,j)));
  }

  void removeEdge(int i, int j) {
    adjMatrix[i][j] = 0;
    adjMatrix[j][i] = 0;
  }

  int **GetAdjMatrix() {
    return adjMatrix;
  }
  std::vector<pair<int, pair<int, int> > > kruskalMST() {
    vector<pair <int, pair<int, int> > > v1;

    sort(edges.begin(), edges.end());
    DisjointSets ds(numVertices);

    vector< pair<int, pair<int, int> > >::iterator it;
    for (it=edges.begin(); it!=edges.end(); it++) {
        int w = it->first;
        int u = it->second.first;
        int v = it->second.second;
  
        int set_u = ds.find(u);
        int set_v = ds.find(v);
        if (set_u != set_v) {
            //cout << u << " - " << v <<"-("<<w<<")"<< endl;
            v1.push_back(make_pair(w, make_pair(u, v)));
            ds.merge(set_u, set_v); 
        } 
    }
    return v1;
  }
  ~Graph() {
    for (int i = 0; i < numVertices; i++)
      delete[] adjMatrix[i];
    delete[] adjMatrix;
  }
  
};


int main() {

    string str = "WAEL";
    int key[5][5] = {
        {1,1,1,1,1},
        {0,1,1,1,1},
        {0,0,1,1,1},
        {0,0,0,1,1},
        {0,0,0,0,1}
    };
    cout<<"The string you want to encrypt is "<<str<<endl;

    transform(str.begin(), str.end(), str.begin(), ::tolower);

    Graph g(str.length()+1);
    int weight = 26;

    g.addEdge(0, 1, int(str[0] - 'a'));

    g.addEdge(1, 2, int(str[1] - str[0]));
    g.addEdge(2, 3, int(str[2] - str[1]));
    g.addEdge(3, 4, int(str[3] - str[2]));
    g.addEdge(4, 1, int(str[0] - str[3]));

    g.addEdge(1, 3 , ++weight);
    g.addEdge(2, 4 , ++weight);

    int **adjMatrix = g.GetAdjMatrix();
    int M1[str.length()+1][str.length()+1];
    for (int i=0;i<str.length()+1;i++) {
        for (int j=0;j<str.length()+1;j++) {
            M1[i][j] = adjMatrix[i][j];
        }
    }

    vector<pair<int, pair<int, int> > > edgesWeight = g.kruskalMST();
    vector< pair<int, pair<int, int> > >::iterator itr;

    Graph g2(sizeof(edgesWeight));

    for (itr=edgesWeight.begin(); itr!=edgesWeight.end(); itr++) {
        int w = itr->first;
        int a = itr->second.first;
        int b = itr->second.second;

        g2.addEdge(a, b, w);
    }

    int **adjMatrix2 = g2.GetAdjMatrix();
    int M2[str.length()+1][str.length()+1];
    int M3[str.length()+1][str.length()+1];
    int C[str.length()+1][str.length()+1];

    for (int i=0;i<str.length()+1;i++) {
        for (int j=0;j<str.length()+1;j++) {
          M2[i][j] = adjMatrix2[i][j];
        }
    }
    for (int i=0;i<str.length()+1;i++) {
        M2[i][i] = i;
    }
    multiply(*M1, *M2, *M3, int(str.length()+1));
    multiply(*key, *M3, *C, int(str.length()+1));
    cout<<"\nUse Key, CipherText and M1 Matrices for Decryption "<<endl;
    cout<<"\nKey:\n";
    
    for (int i=0;i<str.length()+1;i++) {
        for (int j=0;j<str.length()+1;j++) {
            cout<<key[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nCipherText:\n";
    for (int i=0;i<str.length()+1;i++) {
        for (int j=0;j<str.length()+1;j++) {
            cout<<C[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<"\nM1:\n";
    for (int i=0;i<str.length()+1;i++) {
        for (int j=0;j<str.length()+1;j++) {
            cout<<M1[i][j]<<"\t";
        }
        cout<<endl;
    }
}
