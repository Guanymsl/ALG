#include <iostream>
#include "cycle_breaking.h"

pair<int, vE> cb(char mode, int V, vpii* G, vpii* E){
    if(mode == 'u'){
        DSU dsu;
        dsu.makeset(V);

        vE ans;
        int sum = 0;

        for(int w = 201; w >= 0; w--){
            for(int i = 0; i < E[w].size(); i++){
                int u = E[w][i].ff, v = E[w][i].ss;

                if(dsu.find(u) != dsu.find(v)){
                    dsu.joint(u, v);
                }else{
                    Edge e(u, v, w - 100);
                    ans.pb(e);
                    sum += w - 100;
                }
            }
        }

        return mp(sum, ans);
    }else{
        vE ans;
        int sum = 0;

        return mp(sum, ans);
    }
}
