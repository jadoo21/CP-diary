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
//In this we are going to calculate Combination using Binomial Coefficient technique...
//C(n, k) is similar to the coefficient of x^k in the expansion fo (1+x)^n
//C(n, k) = C(n-1, k-1)+C(n-1, k);

#include<bits/stdc++.h>

using namespace std;

vector<int> C(101);

int minimum(int a, int b){
	return (a<b)?a:b;
}

int combination(int n, int r){
	C[0]=1;
	for(int i=1; i<=n; i++){
		for(int j=minimum(i, r); j>0; j--)
			C[j] = (C[j]+C[j-1]);
	}
	return C[r];
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cout<<combination(5,1);
}