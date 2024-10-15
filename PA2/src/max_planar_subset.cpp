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

int solve(int i, int j, const vi& v, vector<vi>& M, vector<vi>& dirc){
    if(i >= j) return 0;
    if(M[i][j] != -1) return M[i][j];

    int a = v[j];
    if (a < i || a > j){
        M[i][j] = solve(i, j - 1, v, M, dirc);
        dirc[i][j] = -2;
    } else if(a > i && a <= j){
        int o1 = solve(i, j - 1, v, M, dirc);
        int o2 = solve(i, a - 1, v, M, dirc) + solve(a + 1, j - 1, v, M, dirc) + 1;

        if(o2 > o1){
            M[i][j] = o2;
            dirc[i][j] = a;
        }else{
            M[i][j] = o1;
            dirc[i][j] = -2;
        }
    } else {
        M[i][j] = solve(i + 1, j - 1, v, M, dirc) + 1;
        dirc[i][j] = -1;
    }

    return M[i][j];
}

void rec(vector<pii>& MPS, const vi& v, const vector<vi>& dirc, int i, int j) {
    if (i >= j) return;

    int next = dirc[i][j];
    if (next == -2) {
        rec(MPS, v, dirc, i, j - 1);
    } else if (next == -1) {
        MPS.pb(mp(i, j));
        rec(MPS, v, dirc, i + 1, j - 1);
    } else {
        MPS.pb(mp(v[j], j));
        rec(MPS, v, dirc, i, next - 1);
        rec(MPS, v, dirc, next + 1, j - 1);
    }
}

vector<pii> mps(int n, vector<pii> C) {
    vector<vi> M(n, vi(n, -1));
    vector<vi> dirc(n, vi(n, 0));
    vector<pii> MPS;

    vi vertex(n, 0);
    int N = C.size();
    for (int c = 0; c < N; c++) {
        vertex[C[c].ff] = C[c].ss;
        vertex[C[c].ss] = C[c].ff;
    }

    solve(0, n - 1, vertex, M, dirc);
    rec(MPS, vertex, dirc, 0, n - 1);
    sort(MPS.begin(), MPS.end());

    return MPS;
}
