#include "exercise_82.h"
#include "point.h"
#include <algorithm>
#include <vector>

std::vector<Point> sort_x(const std::vector<Point> &points) {
  // TODO 8.2.a)
  std::vector<Point> vec = points;
  auto sortByX = [](const auto& a, const auto& b) { return a.x < b.x;};
  std::sort(vec.begin(), vec.end(), sortByX);  
  return vec;
}

std::vector<Point> sort_y(const std::vector<Point> &points) {
  // TODO 8.2.b)
  std::vector<Point> vec = points;
  auto sortByY = [](const auto& a, const auto& b) { return a.y < b.y;};
  std::sort(vec.begin(), vec.end(), sortByY);  
  return vec;
}

Point median(const std::vector<Point> &points) {
  // TODO 8.2.c)
  float medX;
  float medY;
  std::vector<Point> sortedByX = sort_x(points);
  std::vector<Point> sortedByY = sort_y(points);
  unsigned long size = points.size();

  if(size % 2 == 0) {
    medX = (sortedByX[size / 2  - 1].x + sortedByX[size / 2].x) / 2;
    medY = (sortedByY[size / 2  - 1].y + sortedByY[size / 2].y) / 2;
  }
  else {
    medX = sortedByX[(size + 1) / 2 - 1].x;
    medY = sortedByY[(size + 1) / 2 - 1].y;
  }
  return Point(medX, medY);
}