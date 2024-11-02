#include <iostream>
#include <vector>
#include <algorithm>

#define pb push_back
#define mp make_pair

using namespace std;

typedef pair<int, int> pii;

int solve(int i, int j, const int* v, int** M, short** dirc){
    if(i >= j) return 0;
    if(M[i][j] != -1) return M[i][j];

    int a = v[j];
    if(a < i || a > j){
        M[i][j] = solve(i, j - 1, v, M, dirc);
        dirc[i][j] = -2;
    }else if(a > i && a <= j){
        int o1 = solve(i, j - 1, v, M, dirc);
        int o2 = solve(i, a - 1, v, M, dirc) + solve(a + 1, j - 1, v, M, dirc) + 1;

        if(o2 > o1){
            M[i][j] = o2;
            dirc[i][j] = a;
        }else{
            M[i][j] = o1;
            dirc[i][j] = -2;
        }
    }else{
        M[i][j] = solve(i + 1, j - 1, v, M, dirc) + 1;
        dirc[i][j] = -1;
    }

    return M[i][j];
}

void rec(vector<pii>& MPS, const int* v, short** dirc, int i, int j) {
    while (i < j) {
        int next = dirc[i][j];
        if(next == -2){
            j--;
        }else if (next == -1){
            MPS.pb(mp(i, j));
            i++;
            j--;
        }else{
            MPS.pb(mp(next, j));
            rec(MPS, v, dirc, i, next - 1);
            i = next + 1;
            j--;
        }
    }
}

vector<pii> mps(int n, const int* C){
    int** M = new int*[n];
    short** dirc = new short*[n];
    for(int i = 0; i < n; i++){
        M[i] = new int[n];
        dirc[i] = new short[n];
        fill(M[i], M[i] + n, -1);
    }

    solve(0, n - 1, C, M, dirc);

    vector<pii> MPS;
    rec(MPS, C, dirc, 0, n - 1);
    sort(MPS.begin(), MPS.end());

    for(int i = 0; i < n; i++){
        delete[] M[i];
        delete[] dirc[i];
    }
    delete[] M;
    delete[] dirc;

    return MPS;
}
