/*WAJIHA ABBASI- 24I-2059
HANAA SAJID- 24I-2029*/

#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<vector>
#include"fibheap.h"
#include"fibheap.cpp"
#include"binaryheap.h"
#include"binaryheap.cpp"
#include"hollowheap.h"
#include"hollowheap.cpp"


float binInsert, binExtMin, binDecKey, binHeight, binTrees;
float fibInsert, fibExtMin, fibDecKey, fibHeight, fibTrees, cascadeCuts;
float hollowInsert, hollowExtMin, hollowDecKey, hollowHeight, hollowTrees;

using namespace std;

void djikistra(int, int, int);
void djikistraFib(int, int, vector<vector<pair<int,float>>>);
void djikBinary(int,int, vector<vector<pair<int,float>>>);
void djikistraHollow(int, int, vector<vector<pair<int,float>>>);

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
    int v,e;
    switch(op) {
        case 1:
             v = 1185464;
             e=2428866;
            djikistra(1, v,e);
          //   djikBinary(1, v);
            //djikistraFib(1, v);
            //djikistra(1, v);
            //djikBinary(1, v);
            break;
        case 2:
             v = 43620;
             e=91542;
             djikistra(2, v,e);
            //djikistraFib(2, v);
            //djikBinary(2, v);
            //djikistra(2);
            break;
        case 3:
            v = 390171;
            e=855982;
            djikistra(3, v,e);
            //djikistra(3, v);
            //djikBinary(3, v);
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

void djikistra(int dataset, int v, int e) {
    clock_t tStart;
    clock_t tEnd;
    double tMs, binaryTime, fibTime, hollowTime;
    double memMB, binaryMem, fibMem, hollowMem; 

    cout<<"\nLoading data . . .";
    vector<vector<pair<int,float>>> adj(v+1);
    adj = loadData(dataset, v);

 cout<<"\n\n\t\t ᯓ݁˖ 𖥔.ᯓ  BINARY HEAP   ᯓ.𖥔 ݁ ˖ ᯓ݁";
    tStart = clock();
    djikBinary(dataset, v, adj);
    tEnd = clock();
    memMB = ((double)((v+1)* sizeof(BHNode))+(double)(v*sizeof(int)))/(1024.0 * 1024.0);
    tMs= (double)(tEnd- tStart)/ CLOCKS_PER_SEC*1000.0;

    cout<<"Binary Heap Memory usage: "<<memMB<< " MB"<<endl;
    cout<<"Total Djikistra-Binary Runtime: "<<tMs<<" ms"<<endl;
    
    binaryMem = memMB;
    binaryTime = tMs;
    
    
 cout<<"\n\n\t\t ᯓ݁˖ 𖥔.ᯓ  FIBONACCI HEAP   ᯓ.𖥔 ݁ ˖ ᯓ݁";
    tStart = clock();
    djikistraFib(dataset, v, adj);
    tEnd = clock();
    memMB = ((double)((v+1)* sizeof(node))+(double)(v*sizeof(int)))/(1024.0 * 1024.0);
    tMs= (double)(tEnd- tStart)/ CLOCKS_PER_SEC*1000.0;

    cout<<"Fibonacci Heap Memory usage: "<<memMB<< " MB"<<endl;
    cout<<"Total Djikistra-Fibonacci Runtime: "<<tMs<<" ms"<<endl;
    cout<<"Total Fibonacci cascading cuts: "<<cascadeCuts<<endl;

    fibMem = memMB;
    fibTime = tMs;
    

 cout<<"\n\n\t\t ᯓ݁˖ 𖥔.ᯓ  HOLLOW HEAP   ᯓ.𖥔 ݁ ˖ ᯓ݁";
    tStart = clock();
    djikistraHollow(dataset, v, adj);
    tEnd = clock();

    memMB = ((double)((v+1)* sizeof(Node))+(double)(v*sizeof(int)))/(1024.0 * 1024.0);
    tMs= (double)(tEnd- tStart)/ CLOCKS_PER_SEC*1000.0;

    cout<<"\n\nHollow Heap Memory usage: "<<memMB<< " MB"<< endl;
    cout<<"Total Djikistra-Hollow Runtime: "<<tMs<<" ms"<<endl;

    hollowMem = memMB;
    hollowTime = tMs;
    
    fstream outputFile;
    outputFile.open("../output.txt", ios::app); 
    outputFile<<"\nHeap Type"
            <<setw(15)<<"Nodes"
            <<setw(15)<<"Edges"
            <<setw(15)<<"Insert"
             <<setw(15)<<"Ext-Min"
              <<setw(15)<<"Dec-Key"
               <<setw(15)<<"Runtime"
               <<setw(15)<<"Height"
               <<setw(15)<<"#Trees"
               <<setw(15)<<"Mem"<<endl;

    outputFile<<"Binary"
            <<setw(18)<<v
            <<setw(15)<<e
            <<setw(15)<<binInsert
            <<setw(15)<<binExtMin
            <<setw(15)<<binDecKey
            <<setw(15)<<binaryTime
            <<setw(15)<<binHeight
            <<setw(15)<<binTrees
            <<setw(15)<<binaryMem<<endl;

    outputFile<<"Fibonacci"
            <<setw(15)<<v
            <<setw(15)<<e
            <<setw(15)<<fibInsert
            <<setw(15)<<fibExtMin
            <<setw(15)<<fibDecKey
            <<setw(15)<<fibTime
            <<setw(15)<<fibHeight
            <<setw(15)<<fibTrees
            <<setw(15)<<fibMem<<endl;

    outputFile<<"Hollow"
            <<setw(18)<<v
            <<setw(15)<<e
            <<setw(15)<<hollowInsert
            <<setw(15)<<hollowExtMin
            <<setw(15)<<hollowDecKey
            <<setw(15)<<hollowTime
            <<setw(15)<<hollowHeight
            <<setw(15)<<hollowTrees
            <<setw(15)<<hollowMem<<endl;
    outputFile.close();

            

    return;
}

// THIS IS WORKINGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGGG
void djikistraFib(int dataset, int v, vector<vector<pair<int,float>>> adj) {
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

    const float INF = 1000000000.0;
    vector<float> dist(v+1, INF); // INITIALLY ALL VERTICES ARE INFINITELY FAR AWAY
    // Distance from source to itself is 0
    dist[0] = 0;
    
    for (int i = 0; i <= v; i++) {
        node* nd = fibH.createNode(i, (i == 0) ? 0.0f : INF);
        fibH.insert(nd);
    }

    fibHeight = fibH.heapHeight();
    fibTrees = fibH.countTrees();

    //Process the queue until all reachable vertices are finalized
    while (fibH.H != nullptr) { //WHILE HEAP IS NOT EMPTY
        node* top = fibH.extract_min(); //EXTRACT MINIMUM DISTANCE ELEMENT
        if(top == nullptr) //IF THERE ARE NO ELEMENTS BREAK
            break;

        int srcIndex = top->n; //IDENTIFICATION OF THE MIN ELEMENT
        float weight = top->distance; //HOW FAR AWAY IS THE MIN ELEMENT??

        // DOES THE DISTANCE ARRAY ALREADY CONTAIN A SMALLER DISTANCE THAN THE MIN ELEMENT??
        //IF SO SKIP
        if (weight > dist[srcIndex])
            continue;

        // Explore all neighbors of the current vertex
        for (auto &p : adj[srcIndex]) { // this statement ITERATES THROUGH ALL THE NEIGHBORS OF adj[src]
            // it basically means
            //for(int i upto num(neighbors of src)) p = adj[src][i]
            int v = p.first;  //ID OF THE CURRENT VERTEX
            float w = p.second;  //DISTANCE OF THE CURRENT VERTEX

            // If we found a shorter path to v through u, update it
            if (dist[srcIndex] + w < dist[v]) {
                dist[v] = dist[srcIndex] + w;   
          //      cout<<"\nNEW DISTANCE FROM "<<srcIndex<<" to "<<v<<" is "<<dist[srcIndex]+w<<endl;
                fibH.decrease_key(v, dist[srcIndex]+w);
            }
         }
    }

    cascadeCuts = fibH.cascadingCuts;
    fibInsert = fibH.insertCount  ? (double)fibH.totalInsertTime  / fibH.insertCount  : 0;
    fibExtMin = fibH.extMinCount  ? (double)fibH.totalExtMinTime  / fibH.extMinCount  : 0;
    fibDecKey = fibH.decKeyCount  ? (double)fibH.totalDecKeyTime  / fibH.decKeyCount  : 0;

   cout << "\nFib Heap - shortest distances from vertex 0:" << endl;
    for (int i = 0; i <= 9 && i <= v; i++) {
        cout << "  dist[" << i << "] = ";
        if (dist[i] == INF) cout << "INF" << endl;
        else cout << dist[i] << endl;
    }
}

//THIS IS NAWTTTTTTT WORKINGGGGGGGGGGG RNNNNNNNNNNN
void djikistraGeneric(int dataset,int v, int heaptype){
    //heaptype
    //1 : binary
    // 2: fib
    //3: holloqw

//     int u,nb;
//     float w, newDist;

//     const float INF= 1000000000.0;
    
//     cout<<endl;
//     // cout<<"Loading data..."<< endl;
//     // vector<vector<pair<int,float>>> adj = loadData(dataset, v);
//     //cout<<"Data loaded.Running Dijkstra using Binary Hes..."<<endl;
    
//     vector<float> dist((v+1),INF);
//     dist[0] = 0;
    
    
//     //BinaryHeap binaryH; 
//         BinaryHeap bh(v);     //passign v so the pos[] array is sized correctly
//         FibonacciHeap fibH; 
//         //hollowheap
    
//    // for (int i = 0; i <= v; ++i){   //source gets 0 key and the rest get infinity
//         switch(heaptype) {
//             case 1: {
//                 BHNode* nd = bh.createNode(0);   
//                 nd->n =0;
//                 bh.insert(bh.H,nd);
//                 break; 
//             } 
//             case 2: {
//                 node* srcNode = fibH.createNode(0, 0);
//                 fibH.H = fibH.insert(srcNode);
//             } 
//             case 3: {
//                 //hollowheap
//             }
//         }
        
//    // }
    
//    int h;
//     switch(heaptype) {
//         case 1:
//             h=bh.height();
//             break;
//         case 2:
//             //h = fibH.getHeight();
//         case 3:
//             //hollow heap height
//             break;
//     }      //initial height


//     while(!bh.isEmpty()){
        
//         switch(heaptype) {
//             case 1: {
//                 BHNode* top = bh.extract_min(bh.H);
//                 if(top== nullptr){
//                     break;
//                 }
//                 u= top->degree;         //vertex no. 
//                 delete top;
//                 break;
//             } 
//             case 2: {
//                 node* top = fibH.extract_min();
//                 if(top== nullptr){
//                     break;
//                 }
//                 u= top->degree;         //vertex no. 
//                 delete top;
//                 break;
//             }
//             case 3: {
//                 //hollow heap
//             }
//         }   
 
//         if (dist[u] == INF){
//             break;          //all remaining vertices are unreachable
//         }
 
//         //relax all edges from u
//         for(int i = 0; i<(int)adj[u].size();i++){
//             nb = adj[u][i].first;
//             w = adj[u][i].second;
//             newDist = dist[u] +w;
 
//             if(newDist< dist[nb]){
//                 dist[nb] = newDist;
//                 switch(heaptype) {
//                     case 1:
//                         bh.decrease_key(bh.H, nb, newDist);
//                         break;
//                     case 2:
//                 //        fibH.decrease_key(fibH.H, nb, newDist);
//                         break;
//                     case 3:
//                         //hollow heap
//                         break;
//                 }
//             }
//         }
//     }

//     switch(heaptype) {
//         case 1:{    
//             cout<<"\nBinary Heap - shortest distances from vertex 0:" << endl;
//             for(int i = 0; i<= 9 && i <= v; i++){
//                 cout<<"  dist["<<i<<"] = ";
//                 if(dist[i]== INF)
//                     cout<<"INF"<< endl;
//                 else
//                     cout<<dist[i]<<endl;
//             }
//             break;
//         }
//     }
//     cout<<"Heap height: "<<h<< endl;

}

void djikistraHollow(int dataset, int v, vector<vector<pair<int,float>>> adj) {
    HollowHeap hH;
    vector<Item*> hollowNodes(v, nullptr);

	// cout<<"\nLoading data . . .";
    // vector<vector<pair<int,float>>> adj(v+1);
    // adj = loadData(dataset, v);

    cout<<"\nDjikistra using Hollow Heap running . . .";
	
	// Start the timer
	// milliseconds start = duration_cast<milliseconds>(system_clock::now().time_since_epoch());

	// Initialise the distance to each node

    const float INF = 1000000000.0;
   // vector<float> dist(v+1, INF); // INITIALLY ALL VERTICES ARE INFINITELY FAR AWAY
    // Distance from source to itself is 0
   // dist[0] = 0;
    
    hollowNodes[0] = hH.newitem();
	hollowNodes[0]->djikID = 0;
	hH.insert(hollowNodes[0], 0);
	
    for (int i = 1; i < v; i++){
		hollowNodes[i] = hH.newitem();
		hollowNodes[i]->djikID = i;
		hH.insert(hollowNodes[i], INF);
	}

    hollowHeight = hH.heapHeight();
    hollowTrees  = hH.countTrees();

	// Run dijkstra
	while (!hH.empty()){
		int a = hH.root->item->djikID;
		//float distance = hH.top();
		//hH.delete_min();
        float distance = hH.extract_min();
		for (auto b : adj[a]){
			if (distance + b.second < hollowNodes[b.first]->inheap->val) {
                hollowNodes[b.first]->inheap->val = distance + b.second;
				hH.decrease_key(hollowNodes[b.first], distance + b.second);
			}
		}
	}

    cout << "\nHollow Heap - shortest distances from vertex 0:" << endl;
    for (int i = 0; i <= 9 && i <= v; i++) {
        cout << "  dist[" << i << "] = ";
        if (hollowNodes[i]->inheap->val == INF) cout << "INF" << endl;
        else cout <<hollowNodes[i]->inheap->val << endl;
    }

    hollowInsert = hH.insertCount  ? (double)hH.totalInsertTime / hH.insertCount  : 0;
    hollowExtMin = hH.extMinCount  ? (double)hH.totalExtMinTime / hH.extMinCount  : 0;
    hollowDecKey = hH.decKeyCount  ? (double)hH.totalDecKeyTime / hH.decKeyCount  : 0;
    
}


///YAYYYYYYYYYYYYYY THIS IS WORKING
void djikBinary(int dataset,int v, vector<vector<pair<int,float>>> adj){
    int u,nb;
    float w, newDist;

    const float INF= 1000000000.0;
    
    cout<<endl;
    // cout<<"Loading data..."<< endl;
    // vector<vector<pair<int,float>>> adj = loadData(dataset, v);
    cout<<"Running Dijkstra using Binary heap..."<<endl;
    
    vector<float> dist((v+1),INF);
    dist[0] = 0;
    
 //   clock_t tStart = clock();

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
        
        if(dist[i]== INF){
            cout<<"INF"<< endl;
        }

        else{
            cout<<dist[i]<<endl;
        }
    }

    
    binInsert = bh.insertCount ? (double)bh.totalInsertTime / bh.insertCount : 0;
binExtMin = bh.extMinCount ? (double)bh.totalExtMinTime / bh.extMinCount : 0;
binDecKey = bh.decKeyCount ? (double)bh.totalDecKeyTime / bh.decKeyCount : 0;
    binHeight = h;
    binTrees = 1;
    
    //calculating memory usage
//    double memMB = ((double)((v+1)* sizeof(BHNode))+(double)(v*sizeof(int)))/(1024.0 * 1024.0);
//    cout<<"Memory usage: "<<memMB<< endl;

    //calculatinf time in ms
//    clock_t tEnd = clock();
//    double tMs = (double)(tEnd- tStart)/ CLOCKS_PER_SEC*1000.0;
 //   cout<<"Total Runtime: "<<tMs<<" ms"<<endl;

}

