#include <iostream>
#include "cycle_breaking.h"

bool dfs(vpii* G, int u, int v, vector<bool>& vis){
    if(u == v) return true;

    vis[u] = true;

    for(int i = 0; i < G[u].size(); i++){
        int next = G[u][i].ff;
        if(!vis[next] && dfs(G, next, v, vis)) return true;
    }

    return false;
}

pair<int, vE> cb(char mode, int V, vpii* E){
    DSU dsu;
    dsu.makeset(V);

    vE ans;
    int sum = 0;

    if(mode == 'u'){
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
    }else{
        vpii* G = new vpii[V];

        for(int w = 201; w >= 0; w--){
            for(int i = 0; i < E[w].size(); i++){
                int u = E[w][i].ff, v = E[w][i].ss;

                if(dsu.find(u) != dsu.find(v)){
                    dsu.joint(u, v);
                    G[u].pb(mp(v,w - 100));
                    E[w][i] = mp(-1, -1);
                }
            }
        }

        for(int w = 201; w > 100; w--){
            for(int i = 0; i < E[w].size(); i++){
                int u = E[w][i].ff, v = E[w][i].ss;

                if(u != -1){
                    vector<bool> vis(V, false);
                    bool isfa = dfs(G, v, u, vis);

                    if(isfa){
                        ans.pb(Edge(u, v, w - 100));
                        sum += w - 100;
                    }else{
                        G[u].pb(mp(v,w - 100));
                    }
                }
            }
        }

        for(int w = 100; w >= 0; w--){
            for(int i = 0; i < E[w].size(); i++){
                int u = E[w][i].ff, v = E[w][i].ss;

                if(u != -1){
                    ans.pb(Edge(u, v, w - 100));
                    sum += w - 100;
                }
            }
        }

        delete []G;
    }

    return mp(sum, ans);
}
