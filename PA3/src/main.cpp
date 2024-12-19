#include "../lib/tm_usage.h"
#include <iostream>
#include <fstream>
#include "cycle_breaking.h"

int main(int argc, char* argv[]){
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2], ios::out);

    char mode;
    fin >> mode;
    int n;
    fin >> n;
    int m;
    fin >> m;

    int i, j, w;

    vpii* E = new vpii[201];

    for(int k = 0; k < m; k++){
        fin >> i >> j >> w;

        E[w + 100].pb(mp(i, j));
    }

    tmusg.periodStart();

    pair<int, vE> ans = cb(mode, n, E);

    fout << ans.ff << '\n';
    for(int i = 0; i < ans.ss.size(); i++)
        fout << ans.ss[i].u << " " << ans.ss[i].v << " " << ans.ss[i].w << '\n';

    delete[] E;

    tmusg.getPeriodUsage(stat);
    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms\n";
    cout << "memory: " << stat.vmPeak << "KB\n";

    fin.close();
    fout.close();

    return 0;
}
