#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <random>
#include <cassert>
#include <algorithm>

using namespace std;

// This class represents a directed graph, with edges represented with an
// adjacency matrix.
class Graph {
   public:
    // Construct a graph with num_vertices nodes, with no edges.
    Graph(int num_vertices)
        : adjacencyMatrix(num_vertices, vector<bool>(num_vertices, false)) {}

    // Check and fail if the given vertex is out of range for this graph.
    // Parameters:
    //  - vtx: the vertex number to check
    void check_vertex_range(size_t vtx) const {
        assert(0 <= vtx and vtx < size());
    }

    // Get the number of nodes in this graph
    // Return value: the number of graph nodes
    size_t size() const { return adjacencyMatrix.size(); }

    // Add a directed edge from "from" to "to".
    // Parameters:
    //  - from: the source node of the edge
    //  - to: the destination node of the edge
    void add_edge(int from, int to) {
        check_vertex_range(from);
        check_vertex_range(to);
        adjacencyMatrix[from][to] = true;
    }

    // Check if there is a directed edge from "from" to "to".
    // Parameters:
    //  - from: the source node of the edge
    //  - to: the destination node of the edge
    bool has_edge(int from, int to) const {
        check_vertex_range(from);
        check_vertex_range(to);
        return adjacencyMatrix[from][to];
    }

    // Print the entire adjacency matrix to the given stream. Note that to
    // make the formatting layout nicely, only the last digit of the row and
    // column headers are printed (so instead of "12", print only "2").
    // Parameters:
    //  - out: the stream to send the output to
    void printMatrix(ostream &out = cout) const {
        out << " ";
        for (size_t j = 0; j < size(); ++j) {
            out << " " << (j % 10); // only print out the last digit
        }
        out << endl;
        for (size_t i = 0; i < size(); ++i) {
            out << (i % 10); // only print out the last digit
            for (size_t j = 0; j < size(); ++j) {
                out << " " << (adjacencyMatrix[i][j] ? 1 : 0);
            }
            out << endl;
        }
    }

    // Print only the actual edges to the given stream, in a format that can
    // be rendered by GraphViz. If you put the output of this into GraphViz,
    // it will show you the graph visually.
    // See https://dreampuf.github.io/GraphvizOnline/
    // Parameters:
    //  - out: the stream to send the output to
    void printGraphviz(ostream &out = cout) const {
        out << "digraph G {\n"; // for "directed graph"
        for (size_t i = 0; i < size(); ++i) {
            for (size_t j = 0; j < size(); ++j) {
                if (has_edge(i, j)) {
                    out << "  " << i << " -> " << j << ";\n";
                }
            }
        }
        out << "}\n";
    }

   private:
    vector<vector<bool> > adjacencyMatrix;
};

// Define a new type for keeping track of the status of a vertex during DFS/BFS
// search.
typedef enum { UNVISITED, BEING_VISITED, VISITED } VisitStatus;

// dfs is a recursive algorithm for searching the graph "g" from the vertex
// "current".
//
// Start by setting the status of current to BEING_VISITED.
// Then explore the UNVISITED neighbors of the current vertex (recursively).
// Then set the status of current to VISITED, and add it to the finish_order.
//
// Write this using recursion. If you finish early and want an extra challenge,
// then try rewriting it iteratively (using a stack to simulate the recursion).
// If you rewrite it iteratively, be careful in what order you visit nodes so
// you get the same behavior as the recursive method.
//
// Parameters:
//  - g: the graph to search
//  - current: the vertex where the search is currently at
//  - status: a vector with one entry for each vertex, containing UNVISITED,
//            BEING_VISITED, or VISITED
//  - finish_order: an initially empty vector which you should append current to
//                  once current becomes VISITED
void dfs(Graph const &g, int current, vector<VisitStatus> *status,
         vector<int> *finish_order) {
    // FILL IN HERE -- my code is 8 lines long
}

// bfs is a non-recursive algorithm for searching the graph "g" from the vertex
// "current".
//
// Start by:
//  - setting the status of current to BEING_VISITED
//  - put current on the queue
// Then, while the queue is not empty:
//  - pull vertex x off the front
//  - for each neighbor y of x that is UNVISITED
//      - mark y as BEING_VISITED and put y on the queue
//  - mark x as VISITED
//
// Parameters:
//  - g: the graph to search
//  - current: the vertex where the search is currently at
//  - status: a vector with one entry for each vertex, containing UNVISITED,
//            BEING_VISITED, or VISITED
//  - discovery_order: an initially empty vector which you should append current
//                     to once current becomes BEING_VISITED
void bfs(Graph const &g, int current, vector<VisitStatus> *status,
         vector<int> *discovery_order) {
    // FILL IN HERE -- my code is 16 lines long
}

// main constructs a graph of a specified size, adds a set of randomly chosen
// edges (at the specified density), and then runs DFS and BFS on the graph
// (starting from vertex 0), and reports the finish order of the reachable
// vertices.
//
// Parameters:
//  - argc: the number of command-line arguments
//  - argv: the command-line argument values
//
// You can specify two command line arguments:
//  - the number of nodes (default: 10)
//  - the graph density (default: 20%)
int main(int argc, char **argv) {
    // Set up parameters for creating the graph -- number of nodes and edges.
    const int NUM_NODES = (argc > 1) ? stoi(argv[1]) : 10;
    assert(0 < NUM_NODES and NUM_NODES <= 1000);

    // "Density" means "percent of possible edges". The value can be between 0
    // and 100.
    const int GRAPH_DENSITY = (argc > 2) ? stoi(argv[2]) : 20;
    assert(0 <= GRAPH_DENSITY and GRAPH_DENSITY <= 100);
    const int NUM_EDGES = NUM_NODES * (NUM_NODES - 1) * GRAPH_DENSITY / 100;

    cout << "Creating a graph with " << NUM_NODES << " nodes and " << NUM_EDGES
         << " edges\n";
    Graph g(NUM_NODES);

    // set up random numbers, with a seed (for reproducible results)
    mt19937 random_number_generator(1776);

    // add NUM_EDGES random edges
    for (int num_edges_added = 0; num_edges_added < NUM_EDGES;) {
        int u = random_number_generator() % NUM_NODES;
        int v = random_number_generator() % NUM_NODES;
        if (u != v and not g.has_edge(u, v)) {
            g.add_edge(u, v);
            num_edges_added++;
        }
    }

    // "status" keeps track of UNVISITED/BEING_VISITED/VISITED for each vertex
    vector<VisitStatus> status(g.size(), UNVISITED);
    // "finish_order" records when each vertex gets marked VISITED (for DFS)
    // "discovery_order" records when each vertex gets marked BEING_VISITED (for
    // BFS)
    vector<int> finish_order, discovery_order;

    // do a DFS starting from vertex 0, then print the finish_order
    dfs(g, 0, &status, &finish_order);
    cout << "DFS finish order:   ";
    for (auto x : finish_order) {
        cout << " " << x;
    }
    cout << endl;

    // reset the status vector
    fill(status.begin(), status.end(), UNVISITED);

    // do a BFS starting from vertex 0, then print the discovery_order
    bfs(g, 0, &status, &discovery_order);
    cout << "BFS discovery order:";
    for (auto x : discovery_order) {
        cout << " " << x;
    }
    cout << endl;

    // uncomment this to get output you can use to
    // visualize the graph at https://dreampuf.github.io/GraphvizOnline/
    // g.printGraphviz();

    return 0;
}
