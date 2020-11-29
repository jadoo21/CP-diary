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
//In this file we are going to build Bit Index Tree (Fenwick Tree)

#include<bits/stdc++.h>
using namespace std;

vector<int> tree;
int size;

void print(vector<int> arr){
	for(int i=0; i<arr.size(); i++) cout<<arr[i]<<" ";
	cout<<endl;
}

void insert(int index, int data){
	index++;
	while(index<=size){
		tree[index]+=data;
		index+=(index&(-index));
	}
}

int getSum(int index){
	int ans=0;
	index++;
	while(index>0){
		ans+=tree[index];
		index-=(index&(-index));
	}
	return ans;
}

int main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int n;
	cin>>n;
	vector<int> arr(n);
	tree = vector<int>(n+1); size = n+1;
	for(int i=0; i<arr.size(); i++){
		cin>>arr[i];
		insert(i, arr[i]);
	}
	print(tree);
	cout<<(getSum(5)-getSum(1));
}