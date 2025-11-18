/*
 * author: Erick Martinez
 * assignment: ICA 13-graphs
 * date created: 11/18/2025
 *
 * In this exercise we’ll implement important methods for a Graph,
 * in two representations: an adjacency matrix and an adjacency list.
 *
 * As you write these methods, focus on the following things:
 *
 * 1. How the representations differ – what is easy to do in one representation
 * that might be more difficult (or slower) in the other.
 *
 * 2. The runtime efficiency of each method (in terms of the number of vertices
 * V and the number of edges E).
 *
 * 3. How you can use some of the methods to implement others.
 *
 */
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>

using namespace std;

class AdjacencyMatrixGraph {
   public:
    AdjacencyMatrixGraph(int num_vertices)
        // initialize adj_matrix
        : adj_matrix(num_vertices, vector<bool>(num_vertices, false)) {};

    void add_edge(int u, int v) {
        // add a directed edge from u to v
        adj_matrix[u][v] = true;
    }
    bool edge_exists(int u, int v) const {
        // return true if there is an edge from u to v
        return adj_matrix[u][v];
    }
    void print_edges(int u) const {
        // from vertex u
        for (int v = 0; v < adj_matrix.size(); ++v) {
            if (edge_exists(u, v)) {
                cout << u << " ->" << v << endl;
            }
        }
    }
    void print_edges() const {
        // from all vertices
        for (int u = 0; u < adj_matrix.size(); u++) {
            print_edges(u);
        }
    }
    int count_all_edges() const {
        // in the entire graph
        int count = 0;

        for (int u = 0; u < adj_matrix.size(); u++) {
            for (int v = 0; v < adj_matrix.size(); v++) {
                if (edge_exists(u, v)) {
                    count++;
                }
            }
        }
        return count;
    }

   private:
    vector<vector<bool> > adj_matrix; // a VxV matrix
    // adj_matrix[u][v] is true if there is an edge u -> v
};

class AdjacencyListGraph {
   public:
    AdjacencyListGraph(int num_vertices) : adj_list(num_vertices) {};
    // init adj_list

    void add_edge(int u, int v) {
        // dont want to re add!
        if (!edge_exists(u, v)) {
            // add a directed edge from u to v
            adj_list[u].push_back(v);
        }
    }
    bool edge_exists(int u, int v) const {
        // return true if there is an edge from u to v
        auto iterator = find(adj_list[u].begin(), adj_list[u].end(), v);
        return iterator != adj_list[u].end();
    }
    void print_edges(int u) const {
        // from vertex u
    }
    void print_edges() const {
        // from all vertices
    }
    int count_all_edges() const {
        // in the entire graph
    }

   private:
    // a vector of V lists
    vector<list<int> > adj_list;
    // adj_list[u] is a list with the destinations of all edges leaving
    // vertex u
};

int main() {
    // Just a sample of how the above classes might be used
    const int NUM_VERTICES = 8;
    AdjacencyMatrixGraph matrixGraph(NUM_VERTICES);
    AdjacencyListGraph listGraph(NUM_VERTICES);
    for (int i = 0; i < NUM_VERTICES; ++i) {
        for (int j = i + 1; j < NUM_VERTICES; ++j) {
            matrixGraph.add_edge(i, j);
            listGraph.add_edge(i, j);
        }
    }

    cout << "matrixGraph has " << matrixGraph.count_all_edges() << " edges:\n";
    matrixGraph.print_edges();

    cout << "listGraph has " << listGraph.count_all_edges() << " edges:\n";
    listGraph.print_edges();

    return 0;
}
