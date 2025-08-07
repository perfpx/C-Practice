#include "histogram.h"

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

Histogram::Histogram(const std::vector<std::string> &words) {
  // TODO 5.1.a) make sure the histogram is normalized when the constructor is done
    

    size_t size = words.size();
    double key = 1;
    double normalizedKey = (key/static_cast<double>(size));

    for(unsigned long i = 0; i < size; i++) {

      if(histogram.contains(words[i])) {
        key = histogram.find(words[i])->second;
        key += 1/static_cast<double>(size);

        histogram.insert_or_assign(words[i], key);

      } else {

        key = 1;
        normalizedKey = (key/static_cast<double>(size));
        histogram.insert({words[i], normalizedKey});
       
      }
    }
}

size_t Histogram::size() const {
  // TODO 5.1.a)
  return histogram.size();
}

bool Histogram::contains(const std::string &word) const {
  // TODO 5.1.a)
  if (histogram.find(word) != histogram.end()) {
    return true;
  }
  return false;
}

double Histogram::probability(const std::string &word) const {
  // TODO 5.1.a)
  double probs = 0.0;
  if (Histogram::contains(word)) {
      probs = histogram.at(word);
  } else {
    probs = 0.0;
  }
  return probs;
}

// TODO 5.1.b

std::vector<std::pair<double, std::string>> Histogram::most_common_words(unsigned int n_words) const {

  unsigned int counter = 0;

  std::multimap<double, std::string> multi;
  
  std::vector<std::pair<double, std::string>> returnVector;

  for(auto& entries : histogram ) {
      multi.insert(std::pair(Histogram::probability(entries.first), entries.first));
  }
  for(auto i = multi.rbegin(); i != multi.rend(); i++) {

    counter++;

    if(counter == n_words + 1) {
      break;
    }
    std::pair<double, std::string> safe;
    safe.first = i->first;
    safe.second = i->second;
    returnVector.push_back(safe);
  }
  
  
  
  return returnVector;
}
// TODO 5.1.c

double Histogram::dissimilarity(const Histogram &other) const {

  size_t sizeOfA = Histogram::size();
  size_t sizeOfOther = other.size();
  std::vector<std::string> sharedWords;
  double disSimilarity = 0.0;
  double sumProb = 0.0;

  unsigned long numberOfSharedWords = 0;

  for(auto& entriesA : histogram) {
    if(other.contains(entriesA.first)) {
      sharedWords.push_back(entriesA.first);
      numberOfSharedWords++;
    }
  }
  for(unsigned long i = 0; i < numberOfSharedWords; i++) {
    sumProb += std::abs(Histogram::probability(sharedWords[i]) - other.probability(sharedWords[i]));
  }

  disSimilarity = (1 - (static_cast<double>(numberOfSharedWords) / sizeOfA)) + (1 - (static_cast<double>(numberOfSharedWords) / sizeOfOther)) +sumProb;

  return disSimilarity;
}
// TODO 5.1.d

size_t Histogram::closest(const std::vector<Histogram> &candidates) const {

  std::map<size_t, double> newMap;
  std::pair<size_t, double> index;
  for(unsigned long i = 0; i < candidates.size(); i++) {
    
    newMap.insert(std::pair(i, Histogram::dissimilarity(candidates[i])));
  }

  while (newMap.size() > 1) {

    for(unsigned long i = 0; i < 1; i++) {

      if(newMap[i] > newMap[i+1]) {
        newMap.erase(i);
      } else {
        newMap.erase(i+1);
      }
    }
  }
  for(auto& e : newMap) {
    index.first = e.first;
    index.second = e.second;
  }

  return index.first;
}