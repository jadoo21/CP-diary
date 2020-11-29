#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> graph;
vector<pair<int, int>> ans; //all pair of nodes have critical edges.
vector<bool> visit;

vector<int> visitedTime, lowTime;
int discoveredTime =0; //for updating visitedTime & lowTime according to their discovery

void dfs(int current_node, int prev){

    visitedTime[current_node] = lowTime[current_node] = discoveredTime++;

    visit[current_node] = true;
    
    for(auto adjacent_node:graph[current_node]){
        if(adjacent_node==prev) //need not to traverse parent again
            continue;

        if(!visit[adjacent_node]){ //if visiting for first time
            
            dfs(adjacent_node, current_node); //traverse further nodes

            //updating lowTime of current_node
            lowTime[current_node] = min(lowTime[current_node], lowTime[adjacent_node]);

            //condition for a edge to be critical
            if(visitedTime[current_node]<lowTime[adjacent_node])
                ans.push_back(make_pair(current_node, adjacent_node));
        }
        else{ //if node is already visited then just need to update lowTime
            lowTime[current_node] = min(lowTime[current_node], visitedTime[adjacent_node]);
        }
    }
}

int main(){

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n, m; //number of nodes and number of edges
    cin>>n>>m;
    
    graph.resize(n+1); //2D dynamic array -> adjacency list
    visit = vector<bool>(n+1, false); //keep track of visited nodes

    visitedTime.resize(n+1);
    lowTime.resize(n+1);

    for(int i=0; i<m; i++){
        int u, v; //u<->v two nodes with an edge
        cin>>u>>v;
        //That's how we are going to add adjacent node
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
        
    dfs(1, 0); //traversing all the nodes

    //After completing the loop we have our ans with all pair of edges.
    cout<<"All the critical edges are - "<<endl;
    for(auto it: ans){
        cout<<it.first<<" <-> "<<it.second<<endl;
    }
}