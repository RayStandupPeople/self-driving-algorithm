// class DpPath file
#pragma once
#include "node.h"
#include <iostream>
#include <vector>

#include "box2d.h"

class DpPath final {
 public:
  explicit DpPath(const std::vector<std::vector<SlPoint>>& sample_points,
                  const std::vector<Box2d>& obstacles);

  bool Search(std::vector<SlPoint>* const path);

 private:
  void Init(const std::vector<std::vector<SlPoint>>& sample_points);

  void CalculateCostTable();

  void CalculateCostAt(const int32_t l, const int32_t s);

  double CalculateAllObstacleCost(const SlPoint& pre_point, const SlPoint& cur_point) const;

  double CalculateObstacleCost(const Box2d& obs, const Box2d& veh) const;

  double CalculateReferenceLineCost(const SlPoint& pre_point, const SlPoint& cur_point) const;

 private:
  std::vector<std::vector<Node>> cost_table_;
  std::vector<Box2d> obstacles_;
  const double vehicle_length_ = 2.0;
  const double vehicle_width_ = 1.0;

};