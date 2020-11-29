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
//In this we are going to calculate Fibonacci series using matrix exponentiation in O(log(n)) time complexity.

#include<bits/stdc++.h>

#define int long long
#define mod 1000000007

using namespace std;

void multiply(int arr[2][2], int mat[2][2]){
	int m = mat[0][0], n = mat[0][1], o = mat[1][0], p = mat[1][1];
	int w = arr[0][0], x = arr[0][1], y = arr[1][0], z = arr[1][1];
	int a = ((m*w)%mod + (n*y)%mod)%mod;
	int b = ((m*x)%mod + (n*z)%mod)%mod; 
	int c = ((o*w)%mod + (p*y)%mod)%mod;
	int d = ((o*x)%mod + (p*z)%mod)%mod;

	arr[0][0] = a; arr[0][1] = b;
	arr[1][0] = c; arr[1][1] = d;
}

int fib(int n){
	int id[2][2] = {{1, 0}, {0, 1}}, base[2][2] = {{1, 1}, {1, 0}};
	while(n!=0){
		if(n&1)
			multiply(id, base);
		multiply(base, base);
		n>>=1;
	}
	return id[0][0];
}

int32_t main(){

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int t;
	cin>>t;
	while(t--){
		int n, k, ans;
		cin>>n>>k;
		if(n>k){
			int q = (n/k), r = (n%k);
			ans = (((fib(k)-1)*q)%mod + (fib(r)-1))%mod;
		}
		else
			ans = (fib(n)-1);
		cout<<ans<<endl;
	}
}