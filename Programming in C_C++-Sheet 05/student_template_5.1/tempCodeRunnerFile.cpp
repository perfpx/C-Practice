#include <cstddef>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>



int main() {
    std::map<const std::string, double> word;

    word.insert(std::pair(std::string("cookie"), 2));

    std::printf(word["cookie"]);
    return 0;
}