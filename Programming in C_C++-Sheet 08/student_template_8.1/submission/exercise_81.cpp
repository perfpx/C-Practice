#include "exercise_81.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>
#include <numeric>


float MSE(const std::vector<float> ground_truth,
          const std::vector<float> prediction) {
  // TODO: 8.1.a)

  unsigned long N = ground_truth.size();
  std::vector<float> vec;
  std::transform(ground_truth.begin(),ground_truth.end(), prediction.begin(), std::back_inserter(vec), [](float gt, float pred)-> float {return static_cast<float>(std::pow( (gt - pred), 2));} );
  float mse = std::accumulate(vec.begin(), vec.end(), 0.f);

  return (1.f / static_cast<float>(N)) * mse;
}

float MAE(const std::vector<float> ground_truth,
          const std::vector<float> prediction) {
  // TODO: 8.1.b)
  unsigned long N = ground_truth.size();
  std::vector<float> vec;
  std::transform(ground_truth.begin(), ground_truth.end(), prediction.begin(), std::back_inserter(vec), [](float gt, float pred) -> float { return std::abs(gt-pred);});
  float mae = std::accumulate(vec.begin(), vec.end(), 0.f);
  
  return (1.f / static_cast<float>(N)) * mae;

}

std::vector<int> range(int start, int end) {
  // TODO: 8.1.d)
  int size = 0;
  if(start < 0 && end > 0 && end > start) {
    size = std::abs(start) + end;
  }
  else if(start > 0 && end > 0 && end > start) {
    size = end - start;
  }
  else if(start < 0 && end < 0 && end > start) {
    size = std::abs(start) - std::abs(end);
  }
  else if(start == 0 && end > start) {
    size = end;
  }
  else if(end == 0 && end > start) {
    size = std::abs(start);
  }
  if(start >= end) {
    return std::vector<int>();
  }
  std::vector<int> vec(static_cast<unsigned long>(size));
  std::generate(vec.begin(), vec.end(), [=]() mutable {return start++;});
  return vec;
}

