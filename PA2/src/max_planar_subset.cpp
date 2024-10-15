#include <iostream>
#include <vector>
#include <algorithm>
#include "max_planar_subset.h"

#define pii pair<int,int>
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second

using namespace std;

void rec(vector<pii>& MPS, vi v, vector<vi> d, vector<vi> M, int i, int j){
    if(i >= j) return;

    int next = d[i][j];
    if(next == -2){
        rec(MPS, v, d, M, i, j - 1);
    }else if(next == -1){
        MPS.pb(mp(i, j));
        rec(MPS, v, d, M, i + 1, j - 1);
    }else{
        MPS.pb(mp(v[j], j));
        rec(MPS, v, d, M, i, next - 1);
        rec(MPS, v, d, M, next + 1, j - 1);
    }
}

vector<pii> mps(int n, vector<pii> C) {
    vector<vi> M(n, vi(n, 0));
    vector<vi> dirc(n, vi(n, 0));
    vector<pii> MPS;

    vi vertex(n, 0);
    int N = C.size();
    for(int c = 0; c < N; c++){
        vertex[C[c].ff] = C[c].ss;
        vertex[C[c].ss] = C[c].ff;
    }

    for(int d = 1; d < n; d++){
        for(int i = 0; i + d < n; i++){
            int j = i + d;
            int a = vertex[j];

            if(a < i || a > j){

                M[i][j] = M[i][j - 1];
                dirc[i][j] = -2;

            }else if(a > i && a <= j){

                if(M[i][j - 1] <  M[i][a - 1] + M[a + 1][j - 1] + 1){

                    M[i][j] = M[i][a - 1] + M[a + 1][j - 1] + 1;
                    dirc[i][j] = a;

                }else{

                    M[i][j] = M[i][j - 1];
                    dirc[i][j] = -2;

                }

            }else{

                M[i][j] = M[i + 1][j - 1] + 1;
                dirc[i][j] = -1;

            }
        }
    }

    rec(MPS, vertex, dirc, M, 0, n - 1);

    return MPS;

}
