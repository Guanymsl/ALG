#include <iostream>
#include <vector>
#include <algorithm>

#define pb push_back

using namespace std;

typedef vector<int> vi;

int solve(int i, int j, const int* C, int** M){
    int ji = j - i;
    if(i >= j) return 0;
    if(M[i][ji] != -1) return M[i][ji];

    int a = C[j];
    if(a < i || a > j){
        M[i][ji] = solve(i, j - 1, C, M);
    }else if(a > i && a <= j){
        M[i][ji] = max(solve(i, j - 1, C, M), solve(i, a - 1, C, M) + solve(a + 1, j - 1, C, M) + 1);
    }else{
        M[i][ji] = solve(i + 1, j - 1, C, M) + 1;
    }

    return M[i][ji];
}

void rec(vi& MPS, int** M, const int* C, int i, int j){
    if(i >= j) return;

    int a = C[j];
    if(a < i || a > j){
        rec(MPS, M, C, i, j - 1);
    }else if(a > i && a <= j){
        if(solve(i, j , C, M) == solve(i, j - 1, C, M)) rec(MPS, M, C, i, j - 1);
        else{
            MPS.pb(a);
            rec(MPS, M, C, i, a - 1);
            rec(MPS, M, C, a + 1, j - 1);
        }
    }else{
        MPS.pb(a);
        rec(MPS, M, C, i + 1, j - 1);
    }
}

vi mps(int n, const int* C){
    int** M = new int*[n];
    for(int i = 0; i < n; i++){
        M[i] = new int[n - i];
        fill(M[i], M[i] + n - i, -1);
    }

    solve(0, n - 1, C, M);

    vi MPS;
    rec(MPS, M, C, 0, n - 1);
    sort(MPS.begin(), MPS.end());

    for(int i = 0; i < n; i++) delete[] M[i];
    delete[] M;

    return MPS;
}
