/*		 _________
		/|______/ \
		||  _|_|\  |
		|| |_|   | /
		||    _ / |
		||  _| \\  \	
		||_|_|\ || |
		|/_|/ | /|_/
		      /__/  	Written by: Rishabh Roshan
*/
//In this we are going to learn sparse table which can only work when there is no update query only range query.
//Time complexity of building table is O(nlog(n)) but giving result of the query in O(1) time.
#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> sparse;

//For printing our Sparse Table.
void print(vector<vector<int>> arr){
	for(int i=0; i<arr.size(); i++){
		for(int j=0; j<arr[i].size(); j++){
			cout<<arr[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
}

//Building our sparse table.
void build(){
    int n = sparse[0].size();
    for(int i=1; (1<<i)<=n; i++){
        for(int j=0; (j+(1<<i)-1)<n; j++){
            sparse[i][j] = sparse[i-1][j]+sparse[i-1][(j+(1<<(i-1)))];
        }
    }
}

//Query to get the value of any particular range from Sparse Table.
int query(int l, int r){
    int size = r-l+1, ans=0 , j=l, i=0;
    while(size!=0){
        if(size&1){
            ans+=sparse[i][j];
            j+=(1<<i);
        }
        i++;
        size>>=1;
    }
    return ans;
}

int main(){
	//Write your code here...
}