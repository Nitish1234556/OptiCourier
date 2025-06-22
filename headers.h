#pragma once

#include <bits/stdc++.h>   
using namespace std;

// Global graph structure
extern unordered_map<int, vector<pair<int, int>>> adjlist;

// Graph functions
void make_graph(const string& filename);
void printGraph();

// Global courier structure
struct Courier {
    int destination;
    string priority;
    int priority_value;
};

// we will define a global vector to store courier info

extern vector<Courier>couriers;

//function to read courier
void read_courier(const string& filename);

//function to sort by priority
bool compare_priority(const Courier& a , const Courier&b);

vector<vector<int>> dijkstra_allpath(int src, int dest);
void reconstruct_paths(int src,int node,unordered_map<int, vector<int>>& parents,vector<int>& path,vector<vector<int>>& allPaths); 
