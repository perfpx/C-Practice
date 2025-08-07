#pragma once
#include <algorithm>
#include <iterator>
#include <utility>
#include <vector>

/**
 * @brief Comutes the Mean Squared Error.
 * You can assume that ground_truth.size() == prediction.size()
 * 
 * @param ground_truth Vector of ground truth values.
 * @param prediction Vector or predictions.
 * @return float The MSE value.
 */
float MSE(const std::vector<float> ground_truth,
          const std::vector<float> prediction);

/**
 * @brief Comutes the Mean Absolute Error.
 * You can assume that ground_truth.size() == prediction.size()
 * 
 * @param ground_truth Vector of ground truth values.
 * @param prediction Vector or predictions.
 * @return float The MAE value.
 */
float MAE(const std::vector<float> ground_truth,
          const std::vector<float> prediction);


// TODO 8.1.c: implement zip here!

template<class T, class U>
std::vector<std::pair<T, U>> zip(std::vector<T> vecT, std::vector<U> vecU) {
    
    std::vector<std::pair<T, U>> vec;

    std::transform(vecT.begin(), vecT.end(), vecU.begin(), std::back_inserter(vec), [](T elemT, U elemU)-> std::pair<T, U>{return std::pair(elemT, elemU);});

    return vec;
}
/**
 * @brief Generates a vector with integer values in the range [start, end[
 * Note: The list must be empty if start >= end
 * 
 * @param start The first value in the returned vector
 * @param end The upper limit of the range. This value is not included.
 * @return std::vector<int> The generated vector.
 */
std::vector<int> range(int start, int end);