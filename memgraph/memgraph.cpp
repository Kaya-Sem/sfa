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

void MemGraph::createNode(string ID, NodeType type, int value) {
  this->Nodes[ID] = new Node(ID, type, value);
}

void MemGraph::removeNode(string ID) {
  Node *node = this->Nodes[ID];

  // Erase edges involving this node
  for (auto it = this->Edges.begin(); it != this->Edges.end();) {
    if (it->object == node || it->subject == node) {
      it = this->Edges.erase(it); // Erase and move to the next item
    } else {
      it++;
    }
  }

  delete node;           // Free the memory for the node
  this->Nodes.erase(ID); // Remove the node from the map
}
