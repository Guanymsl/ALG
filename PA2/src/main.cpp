#include <iostream>
#include <fstream>
#include "max_planar_subset.h"

#define mp make_pair
#define ff first
#define ss second

using namespace std;

typedef pair<int, int> pii;

int main(int argc, char* argv[]){

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    int n;
    fin >> n;
    int i, j;
    vector<pii> data;
    while(fin >> i >> j){
        if(i > j) swap(i, j);
        data.push_back(mp(i, j));
    }

    vector<pii> ans;
    ans = mps(n, data);

    fout << ans.size() <<endl;
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i].ff << " " << ans[i].ss << '\n';

    fin.close();
    fout.close();

    return 0;
}
