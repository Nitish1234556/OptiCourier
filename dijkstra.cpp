# include "headers.h"


void reconstruct_paths(int src,int node,unordered_map<int, vector<int>>& parents,vector<int>& path,vector<vector<int>>& allPaths) {
    path.push_back(node);
    if (node == src) {
        vector<int> onePath = path;
        reverse(onePath.begin(), onePath.end());
        allPaths.push_back(onePath);
    } else {
        for (int parent : parents[node]) {
            reconstruct_paths(src, parent, parents, path, allPaths);
        }
    }
    path.pop_back();
}






vector<vector<int>>dijkstra_allpath(int src , int dest){
    unordered_map<int,int>dist;
    unordered_map<int,vector<int>>parents;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

// Collect all nodes (including those that appear only as destination)
unordered_set<int> all_nodes;

    for (const auto& it : adjlist) {
        int u = it.first;
        const vector<pair<int, int>>& edges = it.second;

        all_nodes.insert(u); // add source node
        for (const auto& edge : edges) {
            int v = edge.first; // destination node
            all_nodes.insert(v);
        }
    }

    for (int node : all_nodes) {
        dist[node] = INT_MAX;
    }




    dist[src] = 0;
    pq.push({0,src});

    while(!pq.empty()){
        pair<int,int>top = pq.top();
        int currentDistance = top.first;
        int u = top.second;
        pq.pop();


        for(auto& edge : adjlist[u]){
            int v = edge.first;
            int w = edge.second;
            if(dist[v]>dist[u]+w){
                dist[v] = dist[u]+w;
                parents[v].clear();
                parents[v].push_back(u);
                pq.push({dist[v],v});
            }
            else if (dist[v] == dist[u] + w) {
                parents[v].push_back(u);
            }
        }
    }

    if(dist[dest]==INT_MAX){
        return {};
    }

    vector<vector<int>>allpath;
    vector<int>path;
    if (dist[dest] != INT_MAX) {
        reconstruct_paths(src, dest, parents, path, allpath);
    }

    return allpath;}
