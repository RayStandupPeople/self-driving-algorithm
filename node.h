// node.h file
#pragma once
#include <iostream>
#include <limits>
struct SlPoint {
  SlPoint(const double _s, const double _l) : s(_s), l(_l) {
  }
  double s;
  double l;
};

struct Node {
  Node(const SlPoint& _sl_point)
      : sl_point(_sl_point), pre_node(nullptr), cost(std::numeric_limits<double>::max()) {
  }
  SlPoint sl_point;
  Node* pre_node;
  double cost;
};
