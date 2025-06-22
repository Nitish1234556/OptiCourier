#include "headers.h"

extern vector<Courier> couriers;

int main() {
    make_graph("map.txt");
    read_courier("delivery.txt");

    int src;
    cout << "Enter source node :";
    cin >> src;

    unordered_set<int> visited_dest;
    vector<int> final_route;
    final_route.push_back(src);

    for (const Courier& delivery : couriers) {
        if (visited_dest.count(delivery.destination)) continue;

        vector<vector<int>> paths = dijkstra_allpath(src, delivery.destination);

        if (paths.empty()) {
            cout << "No path to destination " << delivery.destination << "\n";
            continue;
        }

        vector<int> bestpath;
        int MAXscore = -1;

        for (const vector<int>& path : paths) {
            unordered_set<int> pathNodes(path.begin(), path.end());
            int score = 0;
            for (const Courier& c : couriers) {
                if (visited_dest.count(c.destination)) continue;
                if (pathNodes.count(c.destination)) {
                    score += (c.priority_value) * 10 + 1;
                }
            }
            if (score > MAXscore) {
                MAXscore = score;
                bestpath = path;
            }
        }

        for (const Courier& c : couriers) {
            if (find(bestpath.begin(), bestpath.end(), c.destination) != bestpath.end()) {
                visited_dest.insert(c.destination);
            }
        }

        if (!final_route.empty() && bestpath.front() == final_route.back()) {
            final_route.insert(final_route.end(), bestpath.begin() + 1, bestpath.end());
        } else {
            final_route.insert(final_route.end(), bestpath.begin(), bestpath.end());
        }

        src = delivery.destination;
    }

    vector<int> nullDestinations;
    for (const Courier& c : couriers) {
        if (c.priority_value == 0 && !visited_dest.count(c.destination)) {
            nullDestinations.push_back(c.destination);
        }
    }

    if (!nullDestinations.empty()) {
        vector<int> bestOrder;
        int minTotalWeight = INT_MAX;

        sort(nullDestinations.begin(), nullDestinations.end());

        do {
            int totalWeight = 0;
            int tempSrc = src;
            bool valid = true;

            for (int dest : nullDestinations) {
                vector<vector<int>> paths = dijkstra_allpath(tempSrc, dest);
                if (paths.empty()) {
                    valid = false;
                    break;
                }
                totalWeight += paths[0].size() - 1;
                tempSrc = dest;
            }

            if (valid && totalWeight < minTotalWeight) {
                minTotalWeight = totalWeight;
                bestOrder = nullDestinations;
            }

        } while (next_permutation(nullDestinations.begin(), nullDestinations.end()));

        for (int dest : bestOrder) {
            vector<vector<int>> paths = dijkstra_allpath(src, dest);
            if (!paths.empty()) {
                vector<int> path = paths[0];
                if (final_route.back() == path.front()) {
                    final_route.insert(final_route.end(), path.begin() + 1, path.end());
                } else {
                    final_route.insert(final_route.end(), path.begin(), path.end());
                }
                visited_dest.insert(dest);
                src = dest;
            }
        }
    }

    cout << "\nFinal optimized delivery route:\n";
    for (int node : final_route) {
        cout << node << " -> ";
    }
    cout << "END\n";

    int total_weight = 0;
    for (size_t i = 0; i + 1 < final_route.size(); ++i) {
        int u = final_route[i];
        int v = final_route[i + 1];
        bool found = false;
        for (const auto& edge : adjlist[u]) {
            if (edge.first == v) {
                total_weight += edge.second;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Warning: No direct edge found from " << u << " to " << v << "\n";
        }
    }

    cout << "\nTotal weight of final route: " << total_weight << "\n";


    return 0;
}
