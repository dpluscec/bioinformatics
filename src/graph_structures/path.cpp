// Copyright 2018 Dunja Vesinger, Domagoj Pluščec

#include "graph_structures/path.h"

#include <vector>
#include <string>

#include "graph_structures/edge.h"
#include "graph_structures/sequence_node.h"

Path::Path(SequenceNode* start_node) {
  this->path_.push_back(start_node);
  this->finalized_ = false;
}

void Path::Add(SequenceNode* node, Edge* edge) {
  this->path_.push_back(node);
  this->edges_.push_back(edge);
}

void Path::Finalize() {
  end_node_id_ = path_.back()->GetId();

  Edge* first_edge = edges_[0];
  long length =
      first_edge->GetExtensonLenOrigin() + first_edge->GetOverlapLength();

  Edge* previus_edge = first_edge;
  for (int i = 1, end = edges_.size(); i < end; i++) {
    Edge* curr_edge = edges_[i];
    long begining_index =
        previus_edge->GetOverhangTarget() + previus_edge->GetOverlapLenTarget();
    long end_index =
        curr_edge->GetExtensonLenOrigin() + curr_edge->GetOverlapLenOrigin();
    length += end_index - begining_index;
    previus_edge = curr_edge;
  }
  Edge* last_edge = edges_.back();
  length += last_edge->GetExtensonLenTarget();

  length_ = length;
  finalized_ = true;
}

long Path::GetLength() {
  if (!finalized_) {
    throw "Path is not finalized";
  }

  return length_;
}

bool Path::operator<(const Path &other) const {
  return length_ < other.length_;
}
std::string Path::GetEndId() {
  if (!finalized_) {
    throw "Path is not finalized";
  }
  return end_node_id_;
}
Path::~Path() {
  path_.clear();
  path_.shrink_to_fit();
}

std::vector<Edge *> Path::GetEdges() {
  return edges_;
}

std::vector<SequenceNode*> Path::GetNodes() {
  return path_;
}

