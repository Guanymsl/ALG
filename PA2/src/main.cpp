#include <iostream>
#include <fstream>
#include "max_planar_subset.h"

int main(int argc, char* argv[]) {
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    int n;
    fin >> n;
    int i, j;
    int* vertex = new int[n];
    for (int k = 0; k < n / 2; k++) {
        fin >> i >> j;
        vertex[i] = j;
        vertex[j] = i;
    }

    vector<pii> ans = mps(n, vertex);

    fout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        fout << ans[i].ff << " " << ans[i].ss << '\n';

    delete[] vertex;

    fin.close();
    fout.close();

    return 0;
}
