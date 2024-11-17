#ifndef MEMGRAPH_HPP
#define MEMGRAPH_HPP

#include "../transducer/Transducer.hpp"
#include <string>
#include <unordered_map>
#include <vector>

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
  unordered_map<string, Node *> Nodes;
  vector<Edge *> Edges;

  MemGraph();
  void removeNode(string ID);
  void updateFromTriple(Triple triple);
};

#endif
