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
//In this code file we are going to build a Segment Tree.
#include<bits/stdc++.h>
using namespace std;

vector<int> tree, lazy;

int power(int base, int p){
	int a = 1;
	while(p){
		if(p&1)
			a*=base;
		base*=base;
		p>>=1;
	}
	return a;
}

void print(vector<int> tree){
	cout<<"Tree - ";
	for(int i=0; i<tree.size(); i++)
		cout<<tree[i]<<" ";
	cout<<endl;
}

int givenRange(int index, int start, int end, int l, int r){
	  if(start>r || end<l)	//When range-[l, r] does not lie in the range of tree node.
	  	return 0;
	  if(l<=start && end<=r)	//When range completely lie between l&r inclusive.
	  	return tree[index];
	  int mid = (start+end)/2;	//If partially lie between range.
	  return (givenRange((index<<1), start, mid, l, r)+givenRange((index<<1)+1, mid+1, end, l, r));
}

void update(int i, int data){	//This is the function for updating the single value at i index in arr with data.

	if(i==0)
		return;

	tree[i] = data;
	if(i&1)
		return update((i>>1), tree[i]+tree[i-1]);
	return update((i>>1), tree[i]+tree[i+1]);
}

/* 
what if we have updates in a range [l,r] we have to add 10. If we follow the previous method of update then
we have to call that function (l-r+1) times which will be roughly O(n) in worst case.
But by using the method of lazy propogation we can reduce it to O(log(n)).

In Laxy Propogation we usually follow 2 cases :
	-> If [start, end] lies completely between [l, r] then we just update the current tree node and 
		update for its child (2*i, 2*(i+1)) we store in lazy array which we do further.
	-> While iterating if at that particular index lazy[i]!=0 then we update the current tree node
		 with that lazy array value and add the update to the child of lazy array also.
*/
int updateRange(int index, int start, int end, int l, int r, int data){
	
	if(lazy[index]!=0){
		tree[index] +=lazy[index];
		if(start!=end){
			lazy[index<<1]+=lazy[index];
			lazy[(index<<1)+1]+=lazy[index];
		}
		lazy[index]=0;
	}

	if(r<start || end<l)
		return tree[index];

	if(l<=start && end<=r){
		if(start!=end){
			lazy[index<<1]+=data;
			lazy[(index<<1)+1]+=data;
		}
		tree[index]+=((end-start+1)*data);
		return tree[index];
	}
	int mid = (start+end)/2;
	tree[index]=(updateRange(index<<1,start, mid, l, r, data)+updateRange((index<<1)+1, mid+1, end, l, r, data));
	return tree[index];
}

int main(){
	freopen("input.txt", "r", stdin);	//For reading a input file.
	freopen("output.txt", "w", stdout);	//For writing in output file.

	cin>>n;
	vector<int> arr(n);
	for(int i=0; i<n; i++) cin>>arr[i];

	int size = power(2, log2((n<<1)-1)+1), j=0;
	tree = vector<int>(size);
	lazy = vector<int>(size);

	//building segment tree here... O(n)
	for(int i=size>>1; i<(size>>1)+n; i++)
		tree[i] = arr[j++];		//Copy and pasting the values of arr in tree from size/2
	for(int i=(size>>1)-1; i>0; i--)
		tree[i] = tree[(i<<1)]+tree[(i<<1)+1];	//Building parent according to the leaf node using heap technique.
	print(tree);

	//Giving the sum accoring to the given range.... O(log(n))
	int rangeAns = givenRange(1, 0, (size>>1)-1, 1, 2);
	cout<<"Sum of a given range - "<<rangeAns<<endl;

	//Now if we have to update query... O(log(n)).
	int index = 3;				//Enter index you want to change in arr (arr[3] = 8).
	update((size>>1)+index, 3);	//It means tree[11(8+3)] = 8;
	cout<<"\nAfter updating at index - "<<index<<endl;
	print(tree);

	//In this we are going to updatae a particular range [l, r]
	int l = 2, r = 5, data = 10;
	cout<<"\nAfter updating range ["<<l<<", "<<r<<"] : "<<endl;
	updateRange(1, 0, (size>>1)-1, l, r, data);
	print(tree);
}
/*
	Here is the small Diagram I have made with example to help you clear the concept.

				30(1)
			/			\	
		  21(2)			  9(3)
		/	\			/	\
	  6(4)	  15(5)   9(6)	  0(7)
	/	\	/	\	/	\	/	\
	5	1	6	9	7	2	0	0	//leaf nodes which is in 2's power.
	8	9	10	11	12	13	14	15	- index in tree array.

	arr[6] = {5, 1, 6, 9, 7, 2}	- Suppose 'n' is the size of this array...
	Formula for calculating size of a tree array - 2^(log2(2*n-1)+1)
*/