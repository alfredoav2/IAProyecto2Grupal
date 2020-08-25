#pragma once
#pragma once
#include <iostream>
#include <vector>
using std::cout; using std::endl;
template <class T>
class GraphNode {
private:
    T data;
public:
    int val;
    bool visitado = false;
    std::vector<GraphNode<T>*> adyacentes;
    std::vector<int> costoAdyacentes;
    T getData() {
        return data;
    }
    GraphNode() {}
    GraphNode(T d) : data(d) {

    }
    ~GraphNode() {}
};