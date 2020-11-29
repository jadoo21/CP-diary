/*       _________
        /|______/ \
        ||  _|_|\  |
        || |_|   | /
        ||    _ / |
        ||  _| \\  \    
        ||_|_|\ || |
        |/_|/ | /|_/
              /__/      Written by: Rishabh Roshan
*/
//In this code we are going to cover how to find SCC using Kosaraju's Algorithm in a directed Graph.

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define int            	long long
#define integer        	int32_t
#define mod         	1000000007
#define vint        	vector<int>
#define pint        	pair<int, int>
#define umint        	unordered_map<int, int>
#define mint        	map<integer, integer>
#define in(x)        	int x; cin>>x
#define setbits(x)    	__builtin_popcountll(x)
#define zerobits(x)    	__builtin_ctzll(x)
#define w(x)        	int x; cin>>x; while(x--)
#define sp(x, y)    	fixed<<setprecision(y)<<x
#define poll(x)        	x.front(); x.pop()
#define f(x)        	for(int i=0; i<x; i++)
#define fj(x)			for(int j=0; j<x; j++)
#define fn(n, x)		for(int i=n; i<x; i++)
#define endl         	'\n'
#define inf         	1e9 

using namespace std;
using namespace __gnu_pbds;

typedef tree< int ,  null_type ,  less<int> ,  rb_tree_tag ,  tree_order_statistics_node_update> order_set;

void om_shree_ganeshaya_namah(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}

vector<bool> visit;
unordered_map<int, vint> dict, rdict;
vint scc;
stack<int> s;

void dfs(int node){ //DFS for pushing all nodes to the stack.

    visit[node] = true;

    for(auto i:dict[node]){
        if(visit[i])
            continue;
        dfs(i);
    }
    s.push(node);
}

void rdfs(int node, int value){

//This DFS help us to cover nodes belong to the SCC in a graph.

    visit[node] = true;
    scc[node] = value;

    for(auto i:rdict[node]){
         if(visit[i])
            continue;
        rdfs(i, value);
    }
}

int32_t main() {

    om_shree_ganeshaya_namah();

    in(n); in(m);
    scc.resize(n+1);
    visit = vector<bool>(n+1, false);

    f(m){
        in(u); in(v);
        dict[u].push_back(v); //original directed graph
        rdict[v].push_back(u); // transpose graph after reversing the graph
    }

    for(int i=1; i<=n; i++){
        if(visit[i])
            continue;
        dfs(i); //traverse node and push it in stack
    }

    visit = vector<bool>(n+1, false);
    while(!s.empty()){
        int temp = s.top();
        s.pop();
        if(visit[temp])
            continue;
        rdfs(temp, temp); 
        /*then traverse each node in transpose graph and whatever we can cover will belong to the 
        Strong Connected Components of the graph.*/
    }

    w(q){
        in(x); in(y);
        string ans = "no";
        if(scc[x]==scc[y])
            ans = "yes";
        cout<<ans<<endl;
    }

}
