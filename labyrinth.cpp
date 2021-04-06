// Largest simple path in labyrinth

#include<iostream>
#include<list>
#include <vector>
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
class Graph
{
  // adjacency lists
  list<int> *adj;

  void DFSUtil(int v, vector<bool> visited, vector<int> current_path);

  void saveLongestPath(vector<int> &current_path);
public:
  Graph(unsigned int V);

  unsigned int V; // No. of vertices

  vector<int> *largest_path;

  vector<unsigned long> *edge_coordinates;

  void addVertex(int v, int w);

  void addVertexEdgeAdjacency(vector<vector<unsigned long>> &input,
                              unsigned long i,
                              unsigned long j);

  void addEdgeCoordinates(int edge, unsigned long i, unsigned long j);

  void createGraph(vector<vector<unsigned long>> input);

  void DFS(int v);
};

Graph::Graph(unsigned int V)
{
  this->V = V;
  adj = new list<int>[V];

  largest_path = new vector<int>;
  largest_path->clear();

  edge_coordinates = new vector<unsigned long>[V];
}

void Graph::DFSUtil(int v, vector<bool> visited, vector<int> current_path)
// Transverse the graph to return paths up to edges with branching left.
{
  visited[v] = true;
  current_path.push_back(v);

  list<int>::iterator i;
  for(i = adj[v].begin(); i != adj[v].end(); ++i)
    if (!visited[*i])
      DFSUtil(*i, visited, current_path);

  this->saveLongestPath(current_path);

}

void Graph::saveLongestPath(vector<int> &current_path){
  // Saves the longest path when a DFS transversal branch has finished
  if(current_path.size() > this->largest_path->size())
    *largest_path = current_path;
}

void Graph::addVertex(int v, int w)
{
  adj[v].push_back(w);
}


void Graph::addVertexEdgeAdjacency(vector<vector<unsigned long>> &input, unsigned long i,
                            unsigned long j){
  // Add all the vertex for adjecent edges. Only vertical and horizontal\
  // adjacency is used.
  unsigned long adjecent_edge;
  if(i > 0){
    adjecent_edge = input[i - 1][j];
    if(adjecent_edge != '#')
      this->addVertex(input[i][j], adjecent_edge);
  }

  if(i + 1 < input.size()){
    adjecent_edge = input[i + 1][j];
    if(adjecent_edge != '#')
      this->addVertex(input[i][j], adjecent_edge);
  }

  if(j > 0){
    adjecent_edge = input[i][j - 1];
    if(adjecent_edge != '#')
      this->addVertex(input[i][j], adjecent_edge);
  }

  if(j + 1 < input[i].size()){
    adjecent_edge = input[i][j + 1];
    if(adjecent_edge != '#')
      this->addVertex(input[i][j], adjecent_edge);
  }

}

void Graph::addEdgeCoordinates(int edge, unsigned long i, unsigned long j){
  // Saves the edge coordinates in the labyrinth.
  this->edge_coordinates[edge] = {i, j};
}

void Graph::createGraph(vector<vector<unsigned long>> input){
  // Creates the graph from the labyrinth input.
  for(unsigned long i = 0; i < input.size(); i++){
    for(unsigned long j = 0; j < input[i].size(); j++){
      if(input[i][j] != '#'){
        this->addEdgeCoordinates(input[i][j], i, j);
        this->addVertexEdgeAdjacency(input, i, j);
      }
    }
  }
}

void Graph::DFS(int root)
{
  vector<bool> visited(V, false);

  vector<int> current_path;

  DFSUtil(root, visited, current_path);
}


void printResult(Graph &g, vector<string> input){
  cout << g.largest_path->size() << endl;

  // Asignate each visited hole the number in which order was visited
  unsigned long i, j, edge;
  for(unsigned long k = 0; k < g.largest_path->size(); k++){
    edge = (*g.largest_path)[k];
    i = g.edge_coordinates[edge][0];
    j = g.edge_coordinates[edge][1];
    input[i][j] = k;
  }

  // Print the final result
  for(auto const &line : input){
    for (auto const &c: line){
      if (c != '#' and c != '.')
        cout << to_string(c);
      else
        cout << c;
    }
    cout << endl;
  }
}


int main(int argc, char **argv)
{
  freopen(argv[1], "r", stdin);
  freopen(argv[2], "w", stdout);

  // Contains the edges
  vector<vector<unsigned long>> labyrinth;
  // Original input
  vector<string> input;

  string x;
  unsigned long edge_id = 0;
  while (cin >> x) {
    // Asignate an id to each hole
    vector<unsigned long> line;
    for(string::size_type i = 0; i < x.size(); i++){
      if(x[i] == '.'){
        line.push_back(edge_id);
        edge_id++;
      }
      else
        line.push_back(x[i]);
    }
    labyrinth.push_back(line);

    input.push_back(x);
  }

  // Run the algorithm for each hole
  Graph g(edge_id);
  g.createGraph(labyrinth);
  for(unsigned long i = 0; i < g.V; i++){
    g.DFS(i);
  }

  printResult(g, input);
  return 0;
}
