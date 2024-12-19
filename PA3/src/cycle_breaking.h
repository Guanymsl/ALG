#ifndef _CYCLE_BREAKING_
#define _CYCLE_BREAKING_

#include <vector>

using namespace std;

struct Edge{
    int u, v, w;
    Edge(int _i, int _j, int _w){
        u = _i;
        v = _j;
        w = _w;
    }
};

class DSU{
    public:
        vector<int> parent, rank;

        void makeset(int n){
            parent.resize(n);
            rank.resize(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
        }

        int find(int x){
            if(parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }

        void joint(int x, int y){
            int rootX = find(x), rootY = find(y);

            if(rootX != rootY){
                if(rank[rootX] > rank[rootY]) parent[rootY] = rootX;
                else if(rank[rootX] < rank[rootY]) parent[rootX] = rootY;
                else{
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        }
};

typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef vector<int> vi;
typedef vector<Edge> vE;

#define pb push_back
#define mp make_pair
#define ff first
#define ss second

pair<int, vE> cb(char, int, vpii*);

#endif
