#include "adjacency_list_graph.h"

//#include <_types/_uint32_t.h>
#include <cstddef>
#include <iterator>
#include <optional>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

void detail::AdjacencyListGraphBase::add_edge(uint32_t from, uint32_t to, float weight)
{
    // TODO: task 10.1 a)
    
    // Checking if we have to resize Vector -> that is the case when from bigger is than the size
    if(edges.size() < from) {
        edges.resize(from + 1);
    }
    // Checking if Edge already exists in Vector
    for(const auto& v: edges[from]) {
        if(v.first == to) {
            throw std::runtime_error("Provided Edge already exists in Vector");
        }
    }
    // Pushing Edge into Vector
    edges[from].push_back(std::make_pair(to, weight));
}


void detail::AdjacencyListGraphBase::remove_edge(uint32_t from, uint32_t to)
{

    // TODO: task 10.1 b)

    // Checking if Edge is big enough and erasing Edge if lambda function returns true
    // erase_if returns 1 if edge was deleted
    // negating if clause so it returns runtime error if no edge was deleted 
    if(!(edges.size() > from && (std::erase_if(edges.at(from), [&to](const std::pair<uint32_t, float> &x) {return x.first == to;}) > 0))) {
        
        throw std::runtime_error("Provided Edge does not exist!");
    }


}

std::optional<float> detail::AdjacencyListGraphBase::get_edge(uint32_t from, uint32_t to) const
{
    // TODO: task 10.1 c)

    // Checking if edges is big enough
    if(edges.size() > from) {
        for(const auto& v : edges[from]) {
            // checking if edge is in Vector
            if(v.first == to) {
                return std::optional<float>(v.second);
            }
        }
    }
    // returning empty optional if edge is not in vector
    return std::optional<float>{};

}

const std::vector<std::pair<uint32_t, float>>& detail::AdjacencyListGraphBase::get_edges_starting_at(uint32_t node) const
{
    // TODO: task 10.1 d)
    
    // Checking if edges is big enough and node is smaller that total number of nodes
    if(edges.size() > node && node < get_num_nodes()) {
        return edges.at(node);
    }

    return zeroVec;

}
