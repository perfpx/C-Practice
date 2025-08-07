#include "shortest_paths.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <iostream>
#include <cmath>
#include <vector>

size_t ShortestPaths::getNodeIdByName(const std::string& name) const {
    // NOTE: if you like, you can make this more efficient by caching the mapping in a mutable hash map that gets reset when calling non-const functions
    const auto it = std::find_if(adjacency_matrix.begin(), adjacency_matrix.end(), [=](const Location& row) -> bool { return row.name == name; });
    if (it == adjacency_matrix.end())
        throw std::runtime_error("Location "+name+" not found");
    return static_cast<size_t>(std::distance(adjacency_matrix.begin(), it));
}

float ShortestPaths::Location::distanceFromTo(const ShortestPaths::Location &other) const {
    return std::sqrt( (other.pos_x - pos_x) * (other.pos_x - pos_x) + (other.pos_y - pos_y) * (other.pos_y - pos_y));
}

size_t ShortestPaths::shortestPoint(const std::vector<size_t> &vector, const std::vector<float> &distanceVec) const {
    return static_cast<size_t>(std::distance(vector.begin(), 
                 std::min_element(vector.begin(), vector.end(),
                 [&distanceVec] (const auto& x, const auto& y) {
            
                 return distanceVec[x] < distanceVec[y];
        })));
}

std::vector<size_t> ShortestPaths::compute_shortest_path(size_t from, size_t to) const
{
    /// your result path
    std::vector<size_t> result;
    /// increment this for every node that you pop from the queue
    size_t num_visited = 0;

    // Vector which stores all Points that need to be processed
    std::vector<size_t> queue;

    std::vector<float> distance(size(), INFINITY);
    std::vector<size_t> previous(size());
    std::vector<size_t> zeroVec{};

    // Location that we want to find
    Location goalDest = this->at(to);

    // Fills queue with numbers from 0 to size()
    for(size_t i = 0; i < size(); i++) {
        queue.push_back(i);
    }

    // Initialize distance and previous
    distance[from] = this->at(from).distanceFromTo(goalDest);
    previous[from] = from;

    while(!queue.empty()) {

        // Searches and fetches the point with the shortest distance from 
        // the start point and returns corresponding distance
        size_t minimalDist = shortestPoint(queue, distance);

        // Set valueDist as queue at point of the minimal distance
        size_t valueDist = queue[minimalDist];

        // Checks if the distance at the point valueDist equals 
        // infinity or the point is already equals to then the while-loop breaks
        if(distance[valueDist] == INFINITY || valueDist == to) {
            break;
        }

        // Increases the number of visited points by 1
        num_visited++;
        
        // Erasing point from queue
        queue.erase(std::remove(queue.begin(), queue.end(), valueDist), queue.end());

        unsigned long counter = 0;

        while(counter < size()){

            // Stores result from std::find
            auto point = std::find(queue.begin(), queue.end(), counter);

            // Checks if point is in queue and location has a value
            if(point != queue.end() && this->at(valueDist).at(counter).has_value()) {
                
                Location nextNodes = this->at(counter);

                // Adds distance at the point valueDist and the edges of the graph
                float alt = distance[valueDist] + this->at(valueDist).at(counter).value() + this->at(valueDist).distanceFromTo(goalDest);

                if(alt < distance[counter]) {
                    distance[counter] = alt;
                    previous[counter] = valueDist;
                }
            }
            counter++;

        }

    }
    // Empty vector is returned if point equals infinity
    if(distance[to] == INFINITY) {
            return zeroVec;
    }
    size_t currentNode = to;
    
    // While current node doesn't equal from it is pushed into the result vector
    // current node is changed to the previous node 
    while(currentNode != from) {
        result.push_back(currentNode);
        currentNode = previous[currentNode];
    }
    result.push_back(from);

    // Reverse result vector
    std::reverse(result.begin(), result.end());

    std::cout << "Nodes visited: " << num_visited << std::endl;

    
    return result;
}
