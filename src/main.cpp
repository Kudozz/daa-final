/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"fibheap.h"
#include"fibheap.cpp"
#include"binaryheap.h"
#include"binaryheap.cpp"


using namespace std;

void djikistra(int, int);
void djikistraFib(int, int);
void djikBinary(int,int);
vector<vector<pair<int,float>>> loadData(int, int);

int main() {
    cout<< "\n\nᯓ.𖥔 ݁ ˖ ᯓ★⊹˖ᯓ.𖥔ᯓ݁ ᯓ.𖥔 ݁ ˖ ᯓ★⊹˖ᯓ.𖥔ᯓ݁ ˖ ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ★"
            "\n\n⊹\t\t  /\\_/\\                                type     ★"
            "\n\n★\t\t (  .ω.)   ____    type                         ⊹"
            "\n\nᯓ\t\t  |  つ__/     /             type               ★" 
        <<" \n\n𖥔\t\t                                                𖥔"
        <<" \n\n⊹\t\tWELCOME TO MY HEAP COMPLEXITY ANALYSER          ★"
        <<" \n\n★\t\t                                                ⊹"
        <<" \n\nᯓ.𖥔 ݁ ˖ ᯓ★⊹˖ᯓ.𖥔ᯓ݁ ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ࣪ ˖ᯓ.𖥔 ݁ ˖ ᯓ★⊹ ";
    
    cout<<"\n\n ᯓ݁˖ 𖥔.ᯓ  DATASET SELECTION   ᯓ.𖥔 ݁ ˖ ᯓ݁"
        <<"\n(1) Chongqing Road Data"
        <<"\n(2) Hong Kong Road Data"
        <<"\n(3) Shanghai Road Data"
        <<"\n(0) Exit"
        <<"\nEnter choice: ";
    int op;
    cin>>op;

    fstream dataFile; 
    string line; 
    int v;
    switch(op) {
        case 1:
             v = 1185464;
          //   djikBinary(1, v);
             djikistraFib(1, v);
            //djikistra(1, v);
            break;
        case 2:
             v = 43620;
            djikistraFib(2, v);
            djikBinary(2, v);
            //djikistra(2);
            break;
        case 3:
            v = 390171;
            //djikistra(3, v);
            //djikistra(3);
            break;
        case 0:
            cout<<"\n\nGoodbye! ᯓ.𖥔 ݁ ˖ ᯓ"<<endl<<endl;
            break;
        default:
            cout<<"\nInvalid option! Exiting ... "<<endl<<endl;
            break;
    }

    dataFile.close();
    return 0;
}

vector<vector<pair<int,float>>> loadData(int dataset, int v) {
    fstream dataFile;
    if(dataset==1) {
        dataFile.open("../data/Chongqing.road-d", ios::in);
    }
    else if(dataset==2) {
        dataFile.open("../data/Hongkong.road-d", ios::in);
    }
    else if(dataset==3) {
        dataFile.open("../data/Shanghai.road-d", ios::in);
    }

    vector<vector<pair<int,float>>> adj(v+1); //using a dynamically allocated vector
    //because otherwise there is stack overflow
    string line;
    int src, dest;
    float w;

    while(getline(dataFile, line)) {
        if(line[0] == '#')//ignore comments
            continue; 

        stringstream ss(line);
        ss>>src;        
        ss>>dest;
        ss>>w;
        pair destWeightPair= make_pair(dest, w);
        adj[src].push_back(destWeightPair);//add to adjacency list
            // although this is a directed graph, both directions
            //are already listed in the datasets
            //so we dont add to list of both src and dest
    }

    dataFile.close();  

    // for(int i = 0; i < 10; i++) {
    // cout << i << " -> ";
    // for(auto& p : adj[i]) {
    //     cout << "(" << p.first << ", " << p.second << ") ";
    // }
    cout << endl;
    return adj;
}


void djikistraFib(int dataset, int v) {
    cout<<"\nLoading data . . .";
    vector<vector<pair<int,float>>> adj(v+1);
    adj = loadData(dataset, v);

    cout<<"\nDjikistra using Fibonacci Heap running . . .";
    int src = 0;
    // for(int i = 0; i < 10; i++) {
    // cout << i << " -> ";
    // for(auto& p : adj[i]) {
    //     cout << "(" << p.first << ", " << p.second << ") ";
    // }
    // cout<<endl;
    // }

    FibonacciHeap fibH;
     //HollowHeap hollowH;

    const float INF = 1000000000.0;
    vector<float> dist(v+1, INF);
    // Distance from source to itself is 0
    dist[0] = 0;
    
    for (int i = 0; i <= v; i++) {
        node* nd = fibH.createNode(i, (i == 0) ? 0.0f : INF);
        fibH.insert(nd);
    }

    //Process the queue until all reachable vertices are finalized
    while (fibH.H != nullptr) {
        node* top = fibH.extract_min();
        if(top == nullptr)
            break;

        int srcIndex = top->n;
        float weight = top->distance;

        // if(dist[srcIndex] == INF) 
        //     break;

        // If this distance not the latest shortest one, skip it
        if (weight > dist[srcIndex])
            continue;

        // Explore all neighbors of the current vertex
        for (auto &p : adj[srcIndex]) { // this statement ITERATES THROUGH ALL THE NEIGHBORS OF adj[src]
            // it basically means
            //for(int i upto num(neighbors of src)) p = adj[src][i]
            int v = p.first; 
            float w = p.second; 

            // If we found a shorter path to v through u, update it
            if (dist[srcIndex] + w < dist[v]) {
                dist[v] = dist[srcIndex] + w;   
          //      cout<<"\nNEW DISTANCE FROM "<<srcIndex<<" to "<<v<<" is "<<dist[srcIndex]+w<<endl;
                fibH.decrease_key(v, dist[srcIndex]+w);
            }
         }
    }

   cout << "\nFib Heap - shortest distances from vertex 0:" << endl;
    for (int i = 0; i <= 9 && i <= v; i++) {
        cout << "  dist[" << i << "] = ";
        if (dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}

void djikistraGeneric(int dataset,int v, int heaptype){
    //heaptype
    //1 : binary
    // 2: fib
    //3: holloqw

    int u,nb;
    float w, newDist;

    const float INF= 1000000000.0;
    
    cout<<endl;
    cout<<"Loading data..."<< endl;
    vector<vector<pair<int,float>>> adj = loadData(dataset, v);
    cout<<"Data loaded.Running Dijkstra..."<<endl;
    
    vector<float> dist((v+1),INF);
    dist[0] = 0;
    
    
    //BinaryHeap binaryH; 
        BinaryHeap bh(v);     //passign v so the pos[] array is sized correctly
        FibonacciHeap fibH; 
        //hollowheap
    
   // for (int i = 0; i <= v; ++i){   //source gets 0 key and the rest get infinity
        switch(heaptype) {
            case 1: {
                BHNode* nd = bh.createNode(0);   
                nd->n =0;
                bh.insert(bh.H,nd);
                break; 
            } 
            case 2: {
                node* srcNode = fibH.createNode(0, 0);
                fibH.H = fibH.insert(srcNode);
            } 
            case 3: {
                //hollowheap
            }
        }
        
   // }
    
   int h;
    switch(heaptype) {
        case 1:
            h=bh.height();
            break;
        case 2:
            //h = fibH.getHeight();
        case 3:
            //hollow heap height
            break;
    }      //initial height


    while(!bh.isEmpty()){
        
        switch(heaptype) {
            case 1: {
                BHNode* top = bh.extract_min(bh.H);
                if(top== nullptr){
                    break;
                }
                u= top->degree;         //vertex no. 
                delete top;
                break;
            } 
            case 2: {
                node* top = fibH.extract_min();
                if(top== nullptr){
                    break;
                }
                u= top->degree;         //vertex no. 
                delete top;
                break;
            }
            case 3: {
                //hollow heap
            }
        }   
 
        if (dist[u] == INF){
            break;          //all remaining vertices are unreachable
        }
 
        //relax all edges from u
        for(int i = 0; i<(int)adj[u].size();i++){
            nb = adj[u][i].first;
            w = adj[u][i].second;
            newDist = dist[u] +w;
 
            if(newDist< dist[nb]){
                dist[nb] = newDist;
                switch(heaptype) {
                    case 1:
                        bh.decrease_key(bh.H, nb, newDist);
                        break;
                    case 2:
                //        fibH.decrease_key(fibH.H, nb, newDist);
                        break;
                    case 3:
                        //hollow heap
                        break;
                }
            }
        }
    }

    switch(heaptype) {
        case 1:{    
            cout<<"\nBinary Heap - shortest distances from vertex 0:" << endl;
            for(int i = 0; i<= 9 && i <= v; i++){
                cout<<"  dist["<<i<<"] = ";
                if(dist[i]== INF)
                    cout<<"INF"<< endl;
                else
                    cout<<dist[i]<<endl;
            }
            break;
        }
    }
    cout<<"Heap height: "<<h<< endl;

}

void djikBinary(int dataset,int v){
    int u,nb;
    float w, newDist;

    const float INF= 1000000000.0;
    
    cout<<endl;
    cout<<"Loading data..."<< endl;
    vector<vector<pair<int,float>>> adj = loadData(dataset, v);
    cout<<"Data loaded.Running Dijkstra..."<<endl;
    
    vector<float> dist((v+1),INF);
    dist[0] = 0;
    
    
    //BinaryHeap binaryH; 
    BinaryHeap bh(v);     //passign v so the pos[] array is sized correctly
    for (int i = 0; i <= v; ++i){   //source gets 0 key and the rest get infinity
        BHNode* nd = bh.createNode(i);   
        nd->n =((i==0)? 0 : INF);
        bh.insert(bh.H,nd);
    }
    
    int h=bh.height();      //initial height
    while(!bh.isEmpty()){
        BHNode* top = bh.extract_min(bh.H);
        if(top== nullptr){
            break;
        }
 
        u= top->degree;         //vertex no. 
        delete top;
 
        if (dist[u] == INF){
            break;          //all remaining vertices are unreachable
        }
 
        //relax all edges from u
        for(int i = 0; i<(int)adj[u].size();i++){
            nb = adj[u][i].first;
            w = adj[u][i].second;
            newDist = dist[u] +w;
 
            if(newDist< dist[nb]){
                dist[nb] = newDist;
                bh.decrease_key(bh.H, nb, newDist);
            }
        }
    }

    cout<<"\nBinary Heap - shortest distances from vertex 0:" << endl;
    for(int i = 0; i<= 9 && i <= v; i++){
        cout<<"  dist["<<i<<"] = ";
        if(dist[i]== INF)
            cout<<"INF"<< endl;
        else
            cout<<dist[i]<<endl;
    }
    cout<<"Heap height: "<<h<< endl;

}