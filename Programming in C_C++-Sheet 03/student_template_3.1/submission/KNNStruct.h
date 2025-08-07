#include <cstdlib>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <map>

struct DYNPoint {

	std::vector<float> data;

	// We use a static function to return a DYNPoint object (this pattern is sometimes called a "factory method")
	// We can mark functions as nodiscard to indicate that we must use the return value in some way (e.g, it doesn't get discarded as ).
	[[nodiscard]] static DYNPoint createRandomPoint(unsigned int size, int minimum=-5000, int maximum=5000) {
		DYNPoint p;
		if (size > 0 && minimum <= maximum) {			
			// STUDENT TODO: add your code	DONE	
			for(unsigned int i = 0; i < size; i++) {
				int value = std::rand() % (std::abs(minimum - maximum)) + minimum;
				p.data.push_back(value);
			}
				
		}
		return p;
	}
};
bool compare(const std::pair<std::pair<DYNPoint, unsigned int>, float> &A,
			 const std::pair<std::pair<DYNPoint, unsigned int>, float> &B) {
				return (A.second < B.second);
			 }
struct KNN {
	KNN(float(*_function_ptr_Distance)(const DYNPoint &, const DYNPoint &))
		: function_ptr_Distance(_function_ptr_Distance)
	{
	}

	std::vector<std::pair<DYNPoint, unsigned int>> trainingData{}; // default initialize on creation

	float(*function_ptr_Distance)(const DYNPoint &, const DYNPoint &) = 0;

	// just sets the training data (no actual training required)
	void TrainKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset) {
		trainingData.clear();
		trainingData = dataset;
	}
	


	int classify(const unsigned int k, const DYNPoint &A) const {

		int class_label = -1;
		std::vector<std::pair<std::pair<DYNPoint, unsigned int>, float>> knn{};
		std::map<unsigned int, int> counter;
		std::pair<unsigned int, int> max{};
		if (k && function_ptr_Distance && trainingData.size()) {

			// STUDENT TODO: your code
			for(auto const &pair : trainingData) {
				float dist = function_ptr_Distance(pair.first, A);
				knn.push_back(std::pair(pair, dist));
			}
			
			std::sort(knn.begin(), knn.end(), compare);
		}


		for(int i = 0; i < k; i++) {
			unsigned int val = knn.at(i).first.second;

			if(counter.contains(val)) {
				counter[val]++;
			} else {
				counter.insert(std::pair(val, 1));
			}
		}
		for(auto const &pair : counter) {
			if(pair.second > max.second) {
				max = pair;
			}
		}

		return max.first;
	}
};

float DistanceManhattan(const DYNPoint &A, const DYNPoint &B) {

	// STUDENT TODO: your code DONE

	float distance = 0;

	for(int i = 0; i < A.data.size(); i++) {

		distance += std::abs(A.data[i] - B.data[i]);
		
	}
	return static_cast<float>(distance) / A.data.size();

}
float DistanceEuclid(const DYNPoint &A, const DYNPoint &B) {

	// STUDENT TODO: your code
	float distance = 0;

	for(int i = 0; i < A.data.size(); i++) {
		distance += std::pow((A.data[i] - B.data[i]), 2);
	}

	distance = std::sqrt(distance / A.data.size());

	return static_cast<float>(distance);

}

void createDataset(std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const unsigned int amount, const unsigned int class_label,
				const unsigned int point_size, const int minimum, const int maximum) {

	if (amount > 0 && point_size>0 && minimum <= maximum) {

	// STUDENT TODO: your code DONE

		for(int i = 0; i < amount; i++) {
			std::pair<DYNPoint, unsigned int> pair = std::pair(DYNPoint::createRandomPoint(point_size, minimum, maximum), class_label);
			dataset.push_back((pair));
		}

	}
}

void evaluateKNN(const std::vector<std::pair<DYNPoint, unsigned int>> &dataset, const KNN &Classifier, const unsigned int k) {
	if (!dataset.empty()) {
		float acc = 0;
		for (size_t i = 0; i < dataset.size(); i++) {
			if (static_cast<unsigned int>(Classifier.classify(k, dataset[i].first)) == dataset[i].second)
				acc++;
		}
		std::cout << "Accuracy: " << acc / float(dataset.size()) << std::endl;
	}
}









