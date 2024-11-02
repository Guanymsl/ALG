#include "../lib/tm_usage.h"
#include <iostream>
#include <fstream>
#include "max_planar_subset.h"

int main(int argc, char* argv[]){
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    int n;
    fin >> n;
    int i, j;
    int* vertex = new int[n];
    for(int k = 0; k < n / 2; k++){
        fin >> i >> j;
        vertex[i] = j;
        vertex[j] = i;
    }

    tmusg.periodStart();

    vector<pii> ans = mps(n, vertex);

    fout << ans.size() << '\n';
    for(int i = 0; i < ans.size(); i++)
        fout << ans[i].ff << " " << ans[i].ss << '\n';

    delete[] vertex;

    tmusg.getPeriodUsage(stat);
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms\n";
    cout << "memory: " << stat.vmPeak << "KB\n";

    fin.close();
    fout.close();

    return 0;
}
