#include "memgraph.hpp"

//  TODO: use member initialize list

//  FIX: why using int value?
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

void MemGraph::removeNode(string ID) {
  Node *node = this->Nodes[ID];

  // Erase edges involving this node
  for (auto it = this->Edges.begin(); it != this->Edges.end();) {
    Edge *edge = *it; // Dereference iterator: Edge*
    if (edge->object == node || edge->subject == node) {
      it = this->Edges.erase(it); // Erase and move to the next item
    } else {
      ++it;
    }
  }

  delete node;           // Free the memory for the node
  this->Nodes.erase(ID); // Remove the node from the map
}

/* Will update the graph from a Triple object. If the subject does not already
 * exist, it will be created. The object node will also be created if it does
 * not yet exist
 */
//  TODO:
void MemGraph::updateFromTriple(Triple triple) {
  Node *node;

  if (this->Nodes.count(triple.subject) == 1) {
    node = this->Nodes[triple.subject];
  } else {
    node = new Node(triple.subject, Entity, 1);
    this->Nodes[node->ID] = node;
  }

  Node *object = new Node("temp", (triple.object.isLiteral) ? Literal : Entity,
                          object->value);

  Edge *edge = new Edge(node, triple.predicate, object);

  this->Edges.push_back(edge);
}
