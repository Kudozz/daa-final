/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/

#include"binaryheap.h"
//daa project


static const float BH_INF = 1000000000.0;   //infinity


BinaryHeap::BinaryHeap(int numVertices){    //constructor
    int i;
    capacity= numVertices+1;
    pos = new int[capacity];
    
    for(i=0; i<capacity; i++){
        pos[i]= -1;
    }

    heap.push_back(NULL);   //heap[0] is never used
    H= NULL;
}
 
BinaryHeap::~BinaryHeap(){      //destructor
    int i;
    
    for(i=1; i< (int)heap.size(); i++){
        delete heap[i];
    }

    delete[] pos;
}


//helper functions
void BinaryHeap::swapNodes(int i,int j){
    BHNode* tmp;
    pos[heap[i]->degree]= j;
    pos[heap[j]->degree]= i;
 
    tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;

    heap[i]->index =i;
    heap[j]->index =j;

}
 
//siftUp  t.c = O(1)+O(1)+O(log n)= O(log n)
void BinaryHeap::siftUp(int i){
    while((i>1) && (heap[parent(i)]->n >heap[i]->n)){
    //(i>1) =node is not root
    //(heap[parent(i)]->n >heap[i]->n)= parent value is greater tgen curr node value
    //heap property is violated
    //O(log n)
        swapNodes(i,parent(i));         //O(1)
        //swap curr node with its parent 
        
        i= parent(i);                   //O(1)
        //move the index upward to continue checking if heap property is violated or not
    }

}
 
void BinaryHeap::siftDown(int i){
    int n = size();
    int smallest = i;
    int l = left(i);
    int r = right(i); 
 
    if((l<= n) && (heap[l]->n< heap[smallest]->n)){
        smallest = l;
    }

    if((r<= n) && (heap[r]->n< heap[smallest]->n)){
        smallest = r;
    }
 
    if(smallest != i){
        swapNodes(i, smallest);
        siftDown(smallest);
    }
}
 
//createNode...time complexity= O(1)
BHNode* BinaryHeap::createNode(int vertexId){
    BHNode* x = new BHNode;
    x->n = BH_INF;
    x->degree= vertexId;    //vertexId stored in degree
    x->index  = 0;
    
    return x;
}

//insertion ..t.c =O(logn)
BHNode* BinaryHeap::insert(BHNode* unused,BHNode* x){
    int i= (int)heap.size();       //O(1)
    //gets curr size of the heap ..this is the idx where the new node will be inserted
    
    heap.push_back(x);             //O(1)
    //adds a new node at the end of he array(heap)

    x->index = i;                   //O(1)
    //stores the idx of the node in the heap to track its position

    pos[x->degree] = i;             //O(1)
    //stores the position ofhte vertex in the pos[] array
 
    siftUp(i);                      //O(log n)
    //fixes the heap property by moving node upward if needed

    H = heap[1];                    //O(1)
    //updates the pointer to point at the root of the heap...root is at index 1 in binary heap
    
    return H;
}
 
//finding minimum....O(1) as it is the top element
BHNode* BinaryHeap::find_min() const{
    if(isEmpty()){                  //O(1)
    //if heap has no elements, there is nothing to return so return null
        return NULL;                //O(1)
    }

    return heap[1];
}
 

//extracting minimum....t.c= O(log n)
//removes and returns the minimum element from heap
BHNode* BinaryHeap::extract_min(BHNode* unused){
    BHNode* minNode;                //O(1) 
    //pointer to store min node=root

    int last;                       //O(1)
    //stores the idx of the last element in heap
 
    if(isEmpty()){                  //O(1)
        return NULL;    //if heap is empty, return null
    }
 
    minNode = heap[1];              //O(1)
    //stores the root node

    last = size();                  //O(1)
    //last index in heap
 
    pos[minNode->degree]= -1;       //O(1)
    //removes the mapping of root vertex from the pos array...which means that the root is no longer in the heap
    
    if(last == 1){                  //O(1)
    //if there is only one element in heap
        heap.pop_back();            //O(1)
        //remove only one element from the heap
        
        H = NULL;                   //O(1)
        //heap is empty now 
        
        return minNode;         //return the reoved node
    }
 
    heap[1] = heap[last];           //O(1)
    //move the last eleemnt to root pos

    heap[1]->index = 1;             //O(1)
    //update the index of the node to 1....root is always at 1 in binary heap

    pos[heap[1]->degree]= 1;       //O(1)
    //update the pos of the node in the pos array

    heap.pop_back();                //O(1)
    //remove the last element...we have it at root now so we cam remov it from the end
    
    siftDown(1);                    //O(log n)
    //restores the heap property by pushing the node downwards..as we put the largest node as the root..heap property is violated
    
    H = heap[1];                    //O(1)
    //upadting the root pointer to point at the correct root after restoring heap property
    
    return minNode;

}
 
//reduces the key value of a vertex in the heap
//t,c =O(log n)
int BinaryHeap::decrease_key(BHNode* unused, int vertexId, float newKey){
    int i;              //O(1)
    //index of vertex in the heap
 
    if((vertexId< 0) || (vertexId >= capacity)){    //O(1)
    //checks if teh vertex id is valid
        return 1;       //invalid input returns 1
    }
 
    i = pos[vertexId];                  //O(1)
    //getting the pos of vertex in the heap from the pos array
    
    if(i== -1){                         //O(1)
        return 1;       //vertex is nawtt in the heap
    }
 
    if(newKey> heap[i]->n){             //O(1)
    //new key is larger than the current key..heap property voilated  
        return 0;               //new key is ignored
    }
 
    heap[i]->n = newKey;            //O(1)
    //updates the key value of the node

    siftUp(i);                      //O(log n)
    //restores heap property

    H = heap[1];                    //O(1)
    //updating the root pointer
    
    return 0;

}
 
//height
int BinaryHeap::height() const{
    int n = size();
    int h = 0;
    int tmp = n;
 
    if(n== 0){
        return 0;
    }
 
    while(tmp >1){
        tmp >>= 1;
        h++;
    }

    return h;
}
 

//level by level print
void BinaryHeap::displayHeap() const{
    int i, n,levelSize,count;
 
    n = size();
    levelSize = 1;
    count = 0;
 
    if(n == 0){
        cout<<"Empty Heap"<<endl;
        
        return;
    }
 
    cout<<"Binary Heap(key | vertex):"<<endl;
 
    for(i=1; i<= n; i++){
        cout<<"["<<heap[i]->n <<"|v"<<heap[i]->degree<<"] ";
        count++;
        if(count == levelSize){
            cout<< endl;
            levelSize *= 2;
            count = 0;
        }

    }

    cout << endl;

}
 