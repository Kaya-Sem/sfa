#include "memgraph.hpp"


//  TODO: use member initialize list

Node::Node(string ID, NodeType type, int value) {
  this->ID = ID;
  this->type = type;
  this->value = value;
}

Edge::Edge(Node *subject, string predicate, Node *object) {
  this->subject = subject;
  this->predicate = predicate;
  this->object = object;
}

MemGraph::MemGraph() {}
