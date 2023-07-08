#include<iostream>
#include<list>
#include<vector>
#include<bits/stdc++.h>

using namespace std;
long long int V[8000], D[10000000], P[10000000], S[10000000], results[8000], N, Vi, Vj;
int *Cost2, *Prev;


class Graph {
public:
    Graph(int n) : nodes_number(n) { 
        edges_of_node.resize(n); 
        cost.resize(n, vector<int>(n));
        V.resize(n);
        for (int i = 0; i < n; i++) {
            V.push_back(i);
        }

        for (int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cost[i][j] = 0;
            }
        }
    } 

    void addEdge(int u, int v, int c) {   //adds the edge (u, v) to the graph with cost c
        edges_of_node[u].push_back(v);
        cost[u][v] = c;
    }  

    // for the bfs implementation, we were helped from GeeksForGeeks. https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/ 
    // But the fill of Cost and prev arrays inside BFS is our idea.
    int * bfs(int s) {

        Cost = new int [nodes_number];
        prev = new int [nodes_number];
        for (int i = 0; i < nodes_number; i++) {
            Cost[i] = 0;
        }

        vector<int> S(nodes_number);
        vector<bool> visited;
        visited.resize(nodes_number, false);

        list<int> queue;
 
        visited[s] = true;
        queue.push_back(s);

        while (!queue.empty()) {
            s = queue.front();
            queue.pop_front();

            for (auto adjecent : edges_of_node[s]) {
                if (!visited[adjecent]) {
                    visited[adjecent] = true;
                    queue.push_back(adjecent);
                    prev[adjecent] = s;
                    auto i = adjecent;
                    auto j = adjecent;
                    while (i != 0) {
                        Cost[adjecent] += cost[prev[i]][j]; //D[prev[i]];
                        j = prev[i];
                        i = prev[i];
                    }
                }
            }
        }
        return Cost;
    }

    int *getPrev() {
        return prev;
    }

private:
    int nodes_number;
    int *prev, *Cost;

    vector< list<int> > edges_of_node;  //vector with lists where each list contains the neighbors of a node
    vector<vector<int> > cost;   // 2d vector indicating the cost of a u-v edge
    list<int> V;

};

int main () {
    cin >> N;
    Graph graph(N);
    for (int i = 0; i < N - 1; i++) {
        cin >> Vi >> Vj >> D[i];
        if (Vi > Vj) {
            int temp = Vi;
            Vi = Vj;
            Vj = temp;
        }
        graph.addEdge(Vi - 1, Vj - 1, D[i]);
    }
    for (int i = 1; i < N; i++) {
        cin >> P[i] >> S[i];
    }

    Cost2 = graph.bfs(0);
    Prev = graph.getPrev();
    Prev[0] = 0;
    results[0] = 0;
    vector<long long int> candidateResults;

    for (int i = 1; i < N; i++) {
        int j = i;
        while (j != 0) {
            candidateResults.push_back(P[i] + S[i] * (Cost2[i] - Cost2[Prev[j]]) + results[Prev[j]]);
            j = Prev[j];      
        } 
        results[i] = *min_element(candidateResults.begin(), candidateResults.end());
        candidateResults.clear();     
 
    }
    for (int i = 1; i < N; i++) {
        if (i == N - 1)
            cout << results[i] << endl;
        else
            cout << results[i] << " ";
    }
}