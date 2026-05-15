#pragma once

/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/
//daa project

#include<iostream>
#include<vector>
#include<chrono>

using namespace std;


struct BHNode{      //struct for binary heap nodes
    int degree;     //vertex id
    int index;      //position in heap array
    float n;        //distance

};

class BinaryHeap{
private:
    vector<BHNode*> heap;   //heap[0] is null
    int* pos;              //pos[vertexId] wil give the idx in heap[] and return -1 if it's not present
    int capacity;         //length of pos[] = num of vertices+ 1
 
    int parent(int i) const{
        return (i/2); 
    }
    
    int left(int i) const{ 
        return (2*i); 
    }
    
    int right(int i) const{ 
        return ((2*i)+1); 
    }
 
    void swapNodes(int i,int j);
    void siftUp(int i);
    void siftDown(int i);
 
public:
    long long totalInsertTime = 0, insertCount = 0;
    long long totalExtMinTime = 0, extMinCount = 0;
    long long totalDecKeyTime = 0, decKeyCount = 0;

    BHNode* H;      // points to heap[1] (the minimum)..it is NULL when empty
    BinaryHeap(int numVertices);
    ~BinaryHeap();
    BHNode* createNode(int vertexId);
    BHNode* insert(BHNode* unused,BHNode* x);
    BHNode* extract_min(BHNode* unused);
    int decrease_key(BHNode* unused, int vertexId, float newKey);
    BHNode* find_min() const;
    int height() const;
    void displayHeap() const;

    bool isEmpty() const{ 
        return ((int)heap.size()<= 1); 
    }
    int size() const{ 
        return ((int)heap.size()-1); 
    }



};