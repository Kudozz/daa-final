/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/

#include"binaryheap.h"

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
 
void BinaryHeap::siftUp(int i){
    while((i>1) && (heap[parent(i)]->n >heap[i]->n)){
        swapNodes(i,parent(i));
        i= parent(i);
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
    int i= (int)heap.size();
    heap.push_back(x);
    x->index = i;
    pos[x->degree] = i;
 
    siftUp(i);
    H = heap[1];
    
    return H;
}
 
//finding minimum....O(1) as it the top element
BHNode* BinaryHeap::find_min() const{
    if (isEmpty()){
        return NULL;
    }

    return heap[1];
}
 
//extracting minimum....t.c= O(log n)
BHNode* BinaryHeap::extract_min(BHNode* unused){
    BHNode* minNode;
    int last;
 
    if(isEmpty()){
        return NULL;
    }
 
    minNode = heap[1];
    last = size();
 
    pos[minNode->degree]= -1;
 
    if(last == 1){
        heap.pop_back();
        H = NULL;
        
        return minNode;
    }
 
    heap[1] = heap[last];
    heap[1]->index = 1;
    pos[heap[1]->degree]= 1;
    heap.pop_back();
    siftDown(1);
    H = heap[1];
    
    return minNode;

}
 
//  decrease_key///t,c =O(log n)
int BinaryHeap::decrease_key(BHNode* unused, int vertexId, float newKey){
    int i;
 
    if((vertexId< 0) || (vertexId >= capacity)){
        return 1;
    }
 
    i = pos[vertexId];
    
    if(i== -1){
        return 1;       //vertex is nawtt in the heap
    }
 
    if(newKey> heap[i]->n){             //new key is larger than the current key
        cout<<"Ignored!!! New key is larger than current key!!!"<<endl;
        
        return 0;               //new key is ignored
    }
 
    heap[i]->n = newKey;
    siftUp(i);
    H = heap[1];
    
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
 