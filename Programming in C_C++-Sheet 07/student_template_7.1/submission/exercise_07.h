#pragma once
#include <cstdio>
#include <vector>
#include <functional>

// TODO 7.1.a: Implement the square function
template<class myType>
myType square(myType a) {
    return a*a;
}
// TODO 7.1.b: Implement the halve function
template<class myType>
double halve(myType a) {
    return static_cast<double>(a)/2;
}
// TODO 7.1.c: Implement the add function
template<class myType>
myType add(myType a, myType b) {
    return a+b;
}
// TODO 7.1.d: Implement the multiply function
template<class myType>
myType multiply(myType a, myType b) {
    return a*b;
}
// TODO 7.1.d: Implement the reduce function
template<class myType>
myType reduce(std::function<myType(myType,myType)> function, std::vector<myType> input, myType neutral) {

    myType returnSum = neutral;

    for(unsigned long i = 0; i < input.size(); i++) {
        returnSum = function(input[i], returnSum);
    }
    return returnSum;
}

// TODO 7.1.f: Implement the map function
template<class myType>
std::vector<myType> map(std::function<myType(myType)> function, std::vector<myType> input) {
    std::vector<myType> returnVector;

    for(unsigned long i = 0; i < input.size(); i++) {
        myType temp = function(input[i]);
        returnVector.push_back(temp);
    }
    return returnVector;
}