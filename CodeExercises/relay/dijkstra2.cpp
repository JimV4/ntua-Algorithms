#include<iostream>
#include<list>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

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
        D = new int [nodes_number];
        prev = new int [nodes_number];
        //int D[nodes_number];       //D[u] = estimated cost of path s-u
        //int prev[nodes_number];    //prev[u] = previus of node u in s-u path;
        vector<int> S(nodes_number);
        list<int> help;

        for(int i = 0; i < nodes_number; i++) {
            D[i] = INT_MAX;
            prev[i] = s;
        }
        D[s] = 0;
        int w;

        for(int i = 0; i < nodes_number; i++) {
            w = select(V, D, nodes_number);
            S.push_back(w);
            V.remove(w);
            for(auto u = edges_of_node[w].begin(); u != edges_of_node[w].end(); u++) {
                if (D[*u] > D[w] + cost[w][*u]) {
                    prev[*u] = w;
                    D[*u] = D[w] + cost[w][*u];
                }
            }
        }

        cout << "Starting node: " << s << endl;
        int j;
        for (int i = 0; i < nodes_number; i++) {
            cout << "Path " << s << "-" << i << ": ";
            j = i;
            help.clear();
            help.push_back(i);
            while (j != s) {
                help.push_back(prev[j]);
                j = prev[j];
            }
            help.reverse();
            for (auto p = help.begin(); p != help.end(); p++) {
                cout << *p << " ";
            }
            cout << "--- Cost of path: " << D[i] << endl;
        }
        return D;
    }

private:
    int nodes_number;
    int *prev, *D;

    vector< list<int> > edges_of_node;  //vector with lists where each list contains the neighbors of a node
    vector<vector<int> > cost;   // 2d vector indicating the cost of a u-v edge
    list<int> V;

    int select(const list<int> & V, int D[], int size) {  //returns the node w from V-S (V) such thaw D[w] is minimum
        int minim = D[*V.begin()];
        auto j = V.begin();
        auto i = V.begin();
        for (j = V.begin(); j != V.end(); j++) {
            if (D[*j] < minim) {
                minim = D[*j];
                i = j;
            }
        }
        return *i;
    }

};

int main () {
    int *D = new int[5];
    /*Graph g(3);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 30);
    g.dijkstra(0);*/
    Graph g(5);
    g.addEdge(0, 1, 20);
    g.addEdge(1, 2, 12);
    g.addEdge(1, 3, 1);
    g.addEdge(3, 4, 3);
    D = g.dijkstra(0);
    for (int i = 0; i < 5; i++) {
        cout << D[i] << endl;
    }
}
