#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include"fibheap.h"
#include"fibheap.cpp"
using namespace std;

void djikistra(int, int);
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
        <<"\n(0) Exit";
    int op;
    cin>>op;

    fstream dataFile; 
    string line; 
    int v;
    switch(op) {
        case 1:
             v = 1185464;
            djikistra(1, v);
            break; 
        case 2:
             v = 43620;
            djikistra(2, v);
            //djikistra(2);
            break;
        case 3:
            v = 390171;
            djikistra(3, v);
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


void djikistra(int dataset, int v) {
    vector<vector<pair<int,float>>> adj(v+1);
    adj = loadData(dataset, v);

    // for(int i = 0; i < 10; i++) {
    // cout << i << " -> ";
    // for(auto& p : adj[i]) {
    //     cout << "(" << p.first << ", " << p.second << ") ";
    // }
    // cout<<endl;
    // }
    
    int src = 0;
    //BinaryHeap binaryH; 
    FibonacciHeap fibH;
     //HollowHeap hollowH;

    vector<int> dist(v);

    // Distance from source to itself is 0
    dist[src] = 0;
    node* srcNode = fibH.createNode(src);
    fibH.H = fibH.insert(fibH.H, srcNode);

    // Process the queue until all reachable vertices are finalized
    while (fibH.H != nullptr) {
        node* top = fibH.extract_min(fibH.H);

        int src = top->degree;
        int dest = top->data.first;  
        int weight = top->data.second; 

        // If this distance not the latest shortest one, skip it
        if (weight > dist[src])
            continue;

        // Explore all neighbors of the current vertex
        for (auto &p : adj[src]) { // this statement ITERATES THROUGH ALL THE NEIGHBORS OF adj[src]
            // it basically means
            //for(int i upto num(neighbors of src)) p = adj[src][i]
            int v = p.first; 
            int w = p.second; 

            // If we found a shorter path to v through u, update it
            if (dist[src] + w < dist[v]) {
                dist[v] = dist[src] + w;   
                fibH.decrease_key(fibH.H, dest, w);
            }
        }
    }

}

