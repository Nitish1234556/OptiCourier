# include "headers.h"

vector<int> dijkstra(int src , int dest){
    unordered_map<int,int>dist;
    unordered_map<int,int>parent;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    for(auto& node : adjlist){
        dist[node.first] = INT_MAX;
    }

    dist[src] = 0;
    parent[src] = -1;
    pq.push({0,src});

    while(!pq.empty()){
        pair<int,int>top = pq.top();
        int currentDistance = top.first;
        int u = top.second;
        pq.pop();

        if(u == dest){
            break;
        }

        for(auto& edge : adjlist[u]){
            int v = edge.first;
            int w = edge.second;
            if(dist[v]>dist[u]+w){
                dist[v] = dist[u]+w;
                parent[v] = u;
                pq.push({dist[v],v});
            }
        }
    }

    if(dist[dest]==INT_MAX){
        return {};
    }

    vector<int>path;
    for(int node = dest ; node != -1 ; node = parent[node]){
        path.push_back(node);
    }

    reverse(path.begin(),path.end());
    return path;
}
