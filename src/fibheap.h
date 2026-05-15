
#ifndef FIBHEAP_H
#define FIBHEAP_H
/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/
#include <cmath>
#include <cstdlib>
#include <iostream>
#include<vector>
/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/


using namespace std;


// Node creation
struct node {
    int n; //index
    float distance; //distance
    int degree; // degree
    node *parent;
    node *child;
    node *left;
    node *right;
    char mark;

    char C;
};

// Implementation of Fibonacci heap
class FibonacciHeap {
   private:
    int nH;

   public:
        int cascadingCuts;
        node *H;

        node *init();
        int createLink(node *, node *);

        node *createNode(int, float);
        node *insert(node *);
        node *unite(node *);
        node *extract_min();

        int decrease_key(int, float);
        int delete_key(int);

        int Consolidate();
        int displayHeap();

        node *Find(node*, int);
        int Cut(node *, node *);
        int Cascase_cut( node *);

        int countTrees();
        int treeHeight(node*);
        int heapHeight();
    //constructor
        FibonacciHeap() { 
            H = init(); 
            cascadingCuts = 0;
            nH=0;
        }
};

#endif