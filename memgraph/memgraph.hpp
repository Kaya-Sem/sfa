#ifndef MEMGRAPH_HPP
#define MEMGRAPH_HPP

#include <map>
#include <set>
#include <string>

using namespace std;

//  TODO: use member initialize list

enum NodeType { Entity, Literal };

class Node {
public:
  string ID;
  NodeType type;
  int value;
  Node(string ID, NodeType type, int value);
};

class Edge {
public:
  Node *subject;
  string predicate;
  Node *object;
  Edge(Node *subject, string predicate, Node *object);
};

class MemGraph {
public:
  map<string, Node *> Nodes;
  set<Edge> Edges;

  MemGraph();
};

#endif
