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

    int * dijkstra(int s) {

        //int Cost[nodes_number];    //Cost[u] = estimated cost of path s-u
        Cost = new int [nodes_number];
        prev = new int [nodes_number];
        //int prev[nodes_number];    //prev[u] = previus of node u in s-u path;
        vector<int> S(nodes_number);
        list<int> help;

        for(int i = 0; i < nodes_number; i++) {
            Cost[i] = INT_MAX;
            prev[i] = s;
        }
        Cost[s] = 0;
        int w;

        for(int i = 0; i < nodes_number; i++) {
            w = select(V, Cost, nodes_number);
            S.push_back(w);
            V.remove(w);
            for(auto u = edges_of_node[w].begin(); u != edges_of_node[w].end(); u++) {
                if (Cost[*u] > Cost[w] + cost[w][*u]) {
                    prev[*u] = w;
                    Cost[*u] = Cost[w] + cost[w][*u];
                }
            }
        }

        // cout << "Starting node: " << s << endl;
        int j;
        for (int i = 0; i < nodes_number; i++) {
            //cout << "Path " << s << "-" << i << ": ";
            j = i;
            help.clear();
            help.push_back(i);
            while (j != s) {
                help.push_back(prev[j]);
                j = prev[j];
            }
            help.reverse();
            // for (auto p = help.begin(); p != help.end(); p++) {
            //     cout << *p << " ";
            // }
            // cout << "--- Cost of path: " << Cost[i] << endl;
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

    int select(const list<int> & V, int Cost[], int size) {  //returns the node w from V-S (V) such thaw Cost[w] is minimum
        int minim = Cost[*V.begin()];
        auto j = V.begin();
        auto i = V.begin();
        for (j = V.begin(); j != V.end(); j++) {
            if (Cost[*j] < minim) {
                minim = Cost[*j];
                i = j;
            }
        }
        return *i;
    }

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

    Cost2 = graph.dijkstra(0);
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
        // if (i == 2) {
        //     for (auto elem : candidateResults)
        //         cout << elem << " ";
        //     cout << endl;
        // }
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