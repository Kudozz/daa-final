#include <cmath>
#include <cstdlib>
#include <iostream>

/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/


using namespace std;

// Node creation
struct node {
    int n;
    pair<int, float> data;
    int degree;
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
        node *H;
        node *init();
        int createLink(node *, node *, node *);

        node *createNode(int);
        node *insert(node *, node *);
        node *unite(node *, node *);
        node *extract_min(node *);

        int decrease_key(node *, int, int);
        int delete_key(node *, int);

        int Consolidate(node *);
        int displayHeap(node *);

        node *Find(node *, int);
        int Cut(node *, node *, node *);
        int Cascase_cut(node *, node *);
    //constructor
        FibonacciHeap() { 
            H = init(); 
            nH=0;
        }
};

// Initialize heap
node *FibonacciHeap::init() {
    node *np;
    np = nullptr;
    return np;
}

// Create node
node *FibonacciHeap::createNode(int value) {
    node *x = new node;
    x->n = value;
    return x;
}

// Insert node
node *FibonacciHeap::insert(node *H, node *x) {
        x->degree = 0;
        x->parent = nullptr;
        x->child = nullptr;
        x->left = x;
        x->right = x;
        x->mark = 'F';
        x->C = 'N';

        if (H != nullptr) {
            (H->left)->right = x;
            x->right = H;
            x->left = H->left;
            H->left = x;
            
            if (x->n < H->n) // is new element min?
                H = x;
        } else { // empty heap - new element is root
            H = x;
        }
    nH = nH + 1;
    return H;
}

// Create linking
int FibonacciHeap::createLink(node *H1, node *y, node *z) {
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        if (z->right == z)
            H1 = z;
        y->left = y;
        y->right = y;
        y->parent = z;

        if (z->child == nullptr)
            z->child = y;

        y->right = z->child;
        y->left = (z->child)->left;
        ((z->child)->left)->right = y;
        (z->child)->left = y;

        if (y->n < (z->child)->n)
            z->child = y;
        z->degree++;
        return 0;
}

// Union Operation
node *FibonacciHeap::unite(node *H1, node *H2) {
    node *np;
    node *H = init();
    H = H1;
    (H->left)->right = H2;
    (H2->left)->right = H;
    np = H->left;
    H->left = H2->left;
    H2->left = np;
    return H;
}

// Display the heap
int FibonacciHeap::displayHeap(node *H) {
    node *p = H;
    if (p == nullptr) {
        cout << "Empty Heap" << endl;
        return 1;
    }
    cout << "Root Nodes: " << endl;

    do {
        cout << p->n;
        p = p->right;
        if (p != H) {
        cout << "-->";
        }
    } while (p != H && p->right != nullptr);
    cout << endl;
    return 0;
}

// Extract min
node *FibonacciHeap::extract_min(node *H1) {
        node *p;
        node *ptr;
        node *z = H1;

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
                (H1->left)->right = x;
                x->right = H1;
                x->left = H1->left;
                H1->left = x;

                if (x->n < H1->n)
                    H1 = x;

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
        H1 = z->right;

        if (z == z->right && z->child == nullptr)
            H = nullptr;

        else {
            H1 = z->right;
            Consolidate(H1);
        }
        nH = nH - 1;
        return p;
}

// Consolidation Function
int FibonacciHeap::Consolidate(node *H1) {
    int d, i;
    float f = (log(nH)) / (log(2));
    int D = f;
    node *A[D+1];
    //node *A[D];

    for (i = 0; i <= D; i++)
        A[i] = nullptr;

    node *x = H1;
    node *y;
    node *np;
    node *pt = x;

    do {
        pt = pt->right;

        d = x->degree;

        while (A[d] != nullptr) {
            y = A[d];

            if (x->n > y->n) {
                    np = x;
                    x = y;
                    y = np;
            }

            if (y == H1)
                H1 = x;
            
            createLink(H1, y, x);
            
            if (x->right == x)
                H1 = x;
            
            A[d] = nullptr;
            d = d + 1;
        }

        A[d] = x;
        x = x->right;
    } while (x != H1);

    H = nullptr;

    for (int j = 0; j <= D; j++) {
        if (A[j] != nullptr) {
            A[j]->left = A[j];
            A[j]->right = A[j];
            
            if (H != nullptr) {
                (H->left)->right = A[j];
                A[j]->right = H;
                A[j]->left = H->left;
                H->left = A[j];
                if (A[j]->n < H->n)
                H = A[j];
            } else {
                H = A[j];
            }

            if (H == nullptr)
                H = A[j];
            else if (A[j]->n < H->n)
                H = A[j];
        }
    }
    return 0;
}

// Decrease Key Operation
int FibonacciHeap::decrease_key(node *H1, int x, int k) {
    node *y;

    if (H1 == nullptr) {
        cout << "The Heap is Empty" << endl;
        return 0;
    }

    node *ptr = Find(H1, x);

    if (ptr == nullptr) {
        cout << "Node not found in the Heap" << endl;
        return 1;
    }

    if (ptr->n < k) {
        cout << "Entered key greater than current key" << endl;
        return 0;
    }

    ptr->n = k;
    y = ptr->parent;
    
    if (y != nullptr && ptr->n < y->n) {
        Cut(H1, ptr, y);
        Cascase_cut(H1, y);
    }

    if (ptr->n < H->n)
        H = ptr;

    return 0;
}

// Cutting Function
int FibonacciHeap::Cut(node *H1, node *x, node *y) {
    if (x == x->right)
            y->child = nullptr;

    (x->left)->right = x->right;
    (x->right)->left = x->left;

    if (x == y->child)
            y->child = x->right;

    y->degree = y->degree - 1;
    x->right = x;
    x->left = x;

    (H1->left)->right = x;
    x->right = H1;

    x->left = H1->left;
    H1->left = x;
    x->parent = nullptr;
    x->mark = 'F';
    return 0;
}

// Cascade cut
int FibonacciHeap::Cascase_cut(node *H1, node *y) {
    node *z = y->parent;
    if (z != nullptr) {
        if (y->mark == 'F') {
            y->mark = 'T';
        } else {
            Cut(H1, y, z);
            Cascase_cut(H1, z);
        }
    }
    return 0;
}

// Search function
node *FibonacciHeap::Find(node *H, int k) {
    node *x = H;
    x->C = 'Y';
    node *p = nullptr;

    if (x->n == k) {
        p = x;
        x->C = 'N';
        return p;
    }

    if (p == nullptr) {
        if (x->child != nullptr)
        p = Find(x->child, k);
        if ((x->right)->C != 'Y')
        p = Find(x->right, k);
    }

    x->C = 'N';
    return p;
}

// Deleting key
int FibonacciHeap::delete_key(node *H1, int k) {
    node *np = nullptr;
    int t;
    t = decrease_key(H1, k, -5000);
    
    if (!t)
        np = extract_min(H);

    if (np != nullptr)
        cout << "Key Deleted" << endl;
    else
        cout << "Key not Deleted" << endl;
    return 0;
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