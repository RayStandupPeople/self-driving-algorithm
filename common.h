  #pragma once
  #include "vec2d.h"

  namespace common{
  /**
 * @brief Cross product between two 2-D vectors from the common start point,
 *        and end at two other points.
 * @param start_point The common start point of two vectors in 2-D.
 * @param end_point_1 The end point of the first vector.
 * @param end_point_2 The end point of the second vector.
 *
 * @return The cross product result.
 */
double CrossProd(const Vec2d &start_point, const Vec2d &end_point_1,
                 const Vec2d &end_point_2);

/**
 * @brief Cross product between two vectors.
 *        One vector is formed by 1st and 2nd parameters of the function.
 *        The other vector is formed by 3rd and 4th parameters of the function.
 * @param x0 The x coordinate of the first vector.
 * @param y0 The y coordinate of the first vector.
 * @param x1 The x coordinate of the second vector.
 * @param y1 The y coordinate of the second vector.
 *
 * @return The cross product result.
 */
double CrossProd(const double x0, const double y0, const double x1,
                 const double y1);

 /**
   * @brief Compute squared value.
   * @param value The target value to get its squared value.
   * @return Squared value of the input value.
   */
double Square(const double &value); 

  /**
 * @brief Wrap angle to [0, 2 * PI).
 * @param angle the original value of the angle.
 * @return The wrapped value of the angle.
 */
double WrapAngle(const double angle);

/**
 * @brief Normalize angle to [-PI, PI).
 * @param angle the original value of the angle.
 * @return The normalized value of the angle.
 */
double NormalizeAngle(const double angle);
}
