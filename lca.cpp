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
//In this program we are going to build a program for Least Common Ancestor in O(nlog(n)) time complexity.

#include<bits/stdc++.h>
using namespace std;

//All the required global variable are here...
int n, m, e, logn=22;
vector<bool> visit;
vector<vector<int>> parent, value;
vector<int> height, arr;
unordered_map<int, vector<int>> tree;

void dfs(int node, int p){	//use of this dfs function is to assign 1st parent.
	if(visit[node])
		return;

	visit[node] = true;
	parent[node][0] = p;	//Assigning the base value as 1st level parent of every node.
	value[node][0] = arr[node];	//Assigning 1st value as the given array.
	height[node] = height[p]+1;
	
	for(auto i:tree[node]) dfs(i, node);
}

void swap(int &a, int &b){
	a^=b; b^=a; a^=b;
}

pair<int, int> lca(int x, int y){	//this lca function is returning the pair 
	//where 1st value of the pair is the given lca node and 2nd value is the whatever value we want..
	//In this case its xor value of the given lca path.
	if(height[x]<height[y])	//For shortening the lenght of the code. So that we only need to make x node jump.
		swap(x, y);
	int diff = height[x]-height[y], i=0, ans=0;
	while(diff){
		if(diff&1){	//jump all the set bits. accordingly..
			ans^=value[x][i];
			x = parent[x][i];
		}
		i++;
		diff>>=1;
	}
	
	if(x==y) return {x, ans^arr[y]};

	for(int i=logn-1; i>=0; i--){	//We start with the highest bit jump 
		//for the value which differ in the sparse table then we jump that much bits.
		if(parent[x][i]!=parent[y][i]){
			x = parent[x][i];
			y = parent[x][i];
			ans^=(value[x][i]^value[y][i]);
		}
	}
	//It always stops 1 level below the actuyal answer.
	//that's why we need to jump one more value to get the actual answer.
	//and add the node to the value also. accordingly.
	ans^=(value[x][0]^value[y][0]);
	return {parent[x][0], ans^arr[parent[x][0]]};
}

//For printing the Sparse Table
void print(vector<vector<int>> sparse){
	for(int i=1; i<=n; i++){
		for(int j=0; j<=log2(n)+1; j++){
			cout<<sparse[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

int main(){

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	
	cin>>n>>m;

	arr = vector<int>(n+1);
	parent = vector<vector<int>>(1e5+1, vector<int>(logn));
	value = vector<vector<int>>(1e5+1, vector<int>(logn));
	height = vector<int>(n+1);
	visit = vector<bool>(n+1, false);

	for(int i=0; i<n-1; i++){
		int u, v;
		cin>>u>>v;
		tree[u].push_back(v); 
		tree[v].push_back(u);
	}

	dfs(1, 0);	//here this is working as building of the tables in O(nlog(n)) time.

	for(int i=1; i<logn; i++){	//this loop builds the whole sparse table after getting its base value.
		for(int j=1; j<=n; j++){
			parent[j][i] = parent[parent[j][i-1]][i-1];
			value[j][i] = value[j][i-1]^value[parent[j][i-1]][i-1];
		}
	}

	while(m--){
		int p, m;
		cin>>p>>m;
		pair<int, int> ans = lca(p, m);
		cout<<ans.second<<endl;
	}
}