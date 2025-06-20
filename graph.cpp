# include "headers.h"


unordered_map <int,vector<pair<int,int>>>adjlist;

void make_graph(const string & filename){
    ifstream infile(filename);
    int nodes;
    int edges;
    infile >> nodes >> edges;

    for(int i = 0 ; i < edges ; i++){
        int u , v , w;
        infile >> u >> v >> w;
        adjlist[u].push_back({v,w});
        if (!adjlist.count(v)) adjlist[v] = {};
    }
}

void printGraph() {
    cout << "\n--- Graph (Adjacency List) ---\n";

    for (auto it = adjlist.begin(); it != adjlist.end(); it++) {
        int node = it->first;
        const vector<pair<int, int>>& neighbours = it->second;

        cout << "Node " << node << ": ";
        for (const pair<int, int>& edge : neighbours) {
            int next = edge.first;
            int weight = edge.second;
            cout << "(" << next << ", wt=" << weight << ") ";
        }
        cout << "\n";
    }
}
