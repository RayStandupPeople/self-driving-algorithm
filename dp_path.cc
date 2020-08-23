#include "dp_path.h"
#include "box2d.h"
#include "quintic_polynomial_curve1d.h"
#include <iostream>
#include <algorithm>
DpPath::DpPath(const std::vector<std::vector<SlPoint>>& sample_points,
               const std::vector<Box2d>& obstacles)
    : obstacles_(obstacles) {
  Init(sample_points);
}

bool DpPath::Search(std::vector<SlPoint>* const path) {
  
  CalculateCostTable();
  auto& last_level = cost_table_.back();
  Node* min_cost_node = nullptr;
  double min_cost = std::numeric_limits<double>::max();
  for (auto& p : last_level) {
    if (p.cost < min_cost) {
      min_cost = p.cost;
      min_cost_node = &p;
    }
  }
  if (min_cost_node == nullptr || min_cost == std::numeric_limits<double>::max()) {
    return false;
  }

  while (min_cost_node != nullptr) {
    path->emplace_back(min_cost_node->sl_point);
    min_cost_node = min_cost_node->pre_node;
  }
  std::reverse(path->begin(), path->end());
  return true;
}

void DpPath::Init(const std::vector<std::vector<SlPoint>>& sample_points) {
  for (const auto& level : sample_points) {
    std::vector<Node> level_points;
    for (const auto& p : level) {
      level_points.emplace_back(p);
    }
    cost_table_.emplace_back(level_points);
  }
}

void DpPath::CalculateCostTable() {
  cost_table_[0][0].cost = 0.0;
  for (uint32_t s = 1; s < cost_table_.size(); ++s) {
    for (uint32_t l = 0; l < cost_table_[s].size(); ++l) {
      CalculateCostAt(s, l);
    }
  }
}

void DpPath::CalculateCostAt(const int32_t s, const int32_t l) {
  auto& pre_level = cost_table_[s - 1];
  double min_cost = std::numeric_limits<double>::max();
  for (auto& pre_point : pre_level) {
    double cost = CalculateAllObstacleCost(pre_point.sl_point, cost_table_[s][l].sl_point) +
                  CalculateReferenceLineCost(pre_point.sl_point, cost_table_[s][l].sl_point);
    cost += pre_point.cost;
    if (cost < min_cost) {
      min_cost = cost;
      cost_table_[s][l].pre_node = &pre_point;
      cost_table_[s][l].cost = min_cost;
    }
  }
}

double DpPath::CalculateAllObstacleCost(const SlPoint& pre_point, const SlPoint& cur_point) const {
  const double curve_length = cur_point.s - pre_point.s;
  QuinticPolynomialCurve1d curve(pre_point.l, 0.0, 0.0, cur_point.l, 0.0, 0.0, curve_length);
  double cost = 0.0;
  constexpr double kStep = 0.1;
  for (double s = 0.0; s < curve_length; s += kStep) {
    double vehicle_l = curve.Evaluate(0, s);
    double vehicle_s = pre_point.s + s;
    double vehicle_heading = std::atan(curve.Evaluate(1, s));
    Box2d veh({vehicle_s, vehicle_l}, vehicle_heading, vehicle_length_, vehicle_width_);
    for (const auto& obs : obstacles_) {
      cost += CalculateObstacleCost(obs, veh);
    }
  }
  return cost;
}

double DpPath::CalculateObstacleCost(const Box2d& obs, const Box2d& veh) const {
  if (obs.HasOverlap(veh)) {
    return std::numeric_limits<double>::max();
  }
  const double dis = obs.DistanceTo(veh);
  if (dis > 2 * vehicle_width_) {
    return 0.0;
  }
  return 1.0 / (dis + std::numeric_limits<double>::epsilon());
}

double DpPath::CalculateReferenceLineCost(const SlPoint& pre_point,
                                          const SlPoint& cur_point) const {
  const double curve_length = cur_point.s - pre_point.s;
  QuinticPolynomialCurve1d curve(pre_point.l, 0.0, 0.0, cur_point.l, 0.0, 0.0, curve_length);
  double cost = 0.0;
  constexpr double kStep = 0.1;
  for (double s = 0.0; s < curve_length; s += kStep) {
    double l = curve.Evaluate(0, s);
    cost += std::fabs(l * l);
  }
  return cost;
}