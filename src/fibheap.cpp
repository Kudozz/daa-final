#include"fibheap.h"
// Initialize heap
node *FibonacciHeap::init() {
    node *np;
    np = nullptr;
    return np;
}

// Create node
node *FibonacciHeap::createNode(int id, float distance) {
    node *x = new node;
    x->n = id;
    x->distance = distance;

     x->degree = 0;
        x->parent = nullptr;
        x->child = nullptr;
        x->left = x;
        x->right = x;
        x->mark = 'F';
        x->C = 'N';
    return x;
}

// Insert node
node *FibonacciHeap::insert(node *x) {

        if (H != nullptr) {
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;
            
            if (x->distance < H->distance) // is new element min?
                H = x;
        } else { // empty heap - new element is root
            H = x;
        }
    nH = nH + 1;
    return H;
}

// Create linking
int FibonacciHeap::createLink(node *y, node *z) {
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        if (z->right == z)
            H = z;
        y->left = y;
        y->right = y;
        y->parent = z;

        if (z->child == nullptr)
            z->child = y;

        y->right = z->child;
        y->left = (z->child)->left;
        ((z->child)->left)->right = y;
        (z->child)->left = y;

        if (y->distance < (z->child)->distance)
            z->child = y;
        z->degree++;
        return 0;
}

// Union Operation
node *FibonacciHeap::unite(node *H2) {
    node *np;
    node *HNew = init();
    HNew = H;
    (HNew->left)->right = H2;
    (H2->left)->right = HNew;
    np = HNew->left;
    HNew->left = H2->left;
    H2->left = np;
    return HNew;
}

// Display the heap
int FibonacciHeap::displayHeap() {
    node *p = H;
    if (p == nullptr) {
        cout << "Empty Heap" << endl;
        return 1;
    }
    cout << "Root Nodes: " << endl;

    do {
        cout << p->distance;
        p = p->right;
        if (p != H) {
        cout << "-->";
        }
    } while (p != H && p->right != nullptr);
    cout << endl;
    return 0;
}

// Extract min
node *FibonacciHeap::extract_min() {
        node *p;
        node *ptr;
        node *z = H;

        p = z;
        ptr = z;

        if (z == nullptr) //empty heap
            return z;

        node *x;
        node *np;

        x = nullptr;

        if (z->child != nullptr) 
            x = z->child;

        if (x != nullptr) {
            node *first = x;
            do {
                np = x->right;
                (H->left)->right = x;
                x->right = H;
                x->left = H->left;
                H->left = x;

                if (x->distance < H->distance)
                    H = x;

                x->parent = nullptr;
                x = np;
            } while (x != first);      // ← correct: stop when we've wrapped around
            // ptr = x;
            // do {
            //     np = x->right;
            //     (H1->left)->right = x;
            //     x->right = H1;
            //     x->left = H1->left;
            //     H1->left = x;

            //     if (x->n < H1->n)
            //         H1 = x;

            //     x->parent = nullptr;
            //     x = np;
            // } while (np != ptr);
        }

        (z->left)->right = z->right;
        (z->right)->left = z->left;
        H = z->right;

        if (z == z->right && z->child == nullptr)
            H = nullptr;

        else {
            H = z->right;
            Consolidate();
        }
        nH = nH - 1;
        return p;
}

// Consolidation Function
int FibonacciHeap::Consolidate() {
    if (nH <= 1) return 0;
    
    int D = (int)(log((float)nH) / log(2.0f)) + 2;
    vector<node*> A(D + 2, nullptr);

    // Snapshot the root list FIRST before any linking
    vector<node*> roots;
    node *x = H;
    do {
        roots.push_back(x);
        x = x->right;
    } while (x != H);

    // Now iterate over the snapshot
    for (node* x : roots) {
        int d = x->degree;
        while (A[d] != nullptr) {
            node *y = A[d];
            if (x->distance > y->distance) {
                swap(x, y);
            }
            if (y == H) H = x;
            createLink(y, x);
            if (x->right == x) H = x;
            A[d] = nullptr;
            d++;
        }
        A[d] = x;
    }

    // Rebuild root list
    H = nullptr;
    for (int j = 0; j < D + 2; j++) {
        if (A[j] != nullptr) {
            A[j]->left = A[j];
            A[j]->right = A[j];
            if (H != nullptr) {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->distance < H->distance)
                    H = A[j];
            } else {
                H = A[j];
            }
        }
    }
    return 0;
}
// int FibonacciHeap::Consolidate() {
//     cout << "Consolidate called, nH = " << nH << endl;
//     int d, i;
//     float f = (log(nH)) / (log(2));
//     int D = f;

    
// node *A[D+1];
//     //node *A[D];

//     for (i = 0; i <= D; i++)
//         A[i] = nullptr;

//     node *x = H;
//     node *y;
//     node *np;
//     node *pt = x;

//     do {
//         pt = pt->right;

//         d = x->degree;

//         while (A[d] != nullptr) {
//             y = A[d];

//             if (x->distance > y->distance) {
//                     np = x;
//                     x = y;
//                     y = np;
//             }

//             if (y == H)
//                 H = x;
            
//             createLink(y, x);
            
//             if (x->right == x)
//                 H = x;
            
//             A[d] = nullptr;
//             d = d + 1;
//         }

//         A[d] = x;
//         x = x->right;
//     } while (x != H);

//     H = nullptr;

//     for (int j = 0; j <= D; j++) {
//         if (A[j] != nullptr) {
//             A[j]->left = A[j];
//             A[j]->right = A[j];
            
//             if (H != nullptr) {
//                 (H->left)->right = A[j];
//                 A[j]->right = H;
//                 A[j]->left = H->left;
//                 H->left = A[j];
//                 if (A[j]->distance < H->distance)
//                 H = A[j];
//             } else {
//                 H = A[j];
//             }

//             if (H == nullptr)
//                 H = A[j];
//             else if (A[j]->distance< H->distance)
//                 H = A[j];
//         }
//     }
//     return 0;
// }

// Decrease Key Operation
int FibonacciHeap::decrease_key(int nodeID, float distance) {
    node *y;

    if (H == nullptr) {
        cout << "The Heap is Empty" << endl;
        return 0;
    }

    node *ptr = Find(H, nodeID);

    if (ptr == nullptr) {
        cout << "Node " << nodeID<<" not found in the Heap" << endl;
        return 1;
    }

    if (ptr->distance < distance) {
        cout << "Entered key greater than current key" << endl;
        return 0;
    }

    ptr->distance = distance;
    y = ptr->parent;
    
    if (y != nullptr && ptr->distance < y->distance) {
        Cut(ptr, y);
        Cascase_cut(y);
    }

    if (ptr->distance < H->distance)
        H = ptr;

    return 0;
}

// Cutting Function
int FibonacciHeap::Cut(node *x, node *y) {
    if (x == x->right)
            y->child = nullptr;

    (x->left)->right = x->right;
    (x->right)->left = x->left;

    if (x == y->child)
            y->child = x->right;

    y->degree = y->degree - 1;
    x->right = x;
    x->left = x;

    (H->left)->right = x;
    x->right = H;

    x->left = H->left;
    H->left = x;
    x->parent = nullptr;
    x->mark = 'F';
    return 0;
}

// Cascade cut
int FibonacciHeap::Cascase_cut( node *y) {
    cascadingCuts++;
    node *z = y->parent;
    if (z != nullptr) {
        if (y->mark == 'F') {
            y->mark = 'T';
        } else {
            Cut(y, z);
            Cascase_cut(z);
        }
    }
    return 0;
}

// Search function
node *FibonacciHeap::Find(node* H, int nodeID) {
    node *x = H;
    x->C = 'Y';
    node *p = nullptr;

    if (x->n == nodeID) {
        p = x;
        x->C = 'N';
        return p;
    }

    if (p == nullptr) {
        if (x->child != nullptr)
        p = Find(x->child, nodeID);
        if (p == nullptr &&(x->right)->C != 'Y')
        p = Find(x->right, nodeID);
    }

    x->C = 'N';
    return p;
}

// Deleting key
int FibonacciHeap::delete_key(int k) {
    node *np = nullptr;
    int t;
    t = decrease_key(k, -5000);
    
    if (!t)
        np = extract_min();

    if (np != nullptr)
        cout << "Key Deleted" << endl;
    else
        cout << "Key not Deleted" << endl;
    return 0;
}

int FibonacciHeap::countTrees() {
    if (H == nullptr) return 0;
    int count = 1;
    node *p = H->right;
    while (p != H) { count++; p = p->right; }
    return count;
}

int FibonacciHeap::treeHeight(node *n) {
    if (n == nullptr) return 0;
    int maxChildHeight = 0;
    if (n->child != nullptr) {
        node *c = n->child;
        do {
            maxChildHeight = max(maxChildHeight, treeHeight(c));
            c = c->right;
        } while (c != n->child);
    }
    return 1 + maxChildHeight;
}

int FibonacciHeap::heapHeight() {
    if (H == nullptr) return 0;
    int maxH = 0;
    node *p = H;
    do {
        maxH = max(maxH, treeHeight(p));
        p = p->right;
    } while (p != H);
    return maxH;
}

/*
int main() {
    int n, m, l;
    FibonacciHeap fh;
    node *p;
    node *H;
    fh.H = fh.init();

    p = fh.createNode(7);
    fh.H = fh.insert(fh.H, p);
    p = fh.createNode(3);
    fh.H = fh.insert(fh.H, p);
    p = fh.createNode(17);
    fh.H = fh.insert(fh.H, p);
    p = fh.createNode(24);
    fh.H = fh.insert(fh.H, p);

    fh.displayHeap(fh.H);

   p = fh.extract_min(fh.H);
   if (p != nullptr)
       cout << "The node with minimum key: " << p->n << endl;
   else
        cout << "Heap is empty" << endl;

    m = 24;
    l = 16;
    fh.decrease_key(fh.H, m, l);

    m = 16;
    fh.delete_key(fh.H, m);
}
    */