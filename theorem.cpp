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
//In this module we are going to discuss some number theory theorems.

#include<bits/stdc++.h>

#define int long long

using namespace std;

int prime[50]={};
vector<int> p;
void primeCalculate(){
	int n = 50;
	prime[0]=1; prime[1]=1;
	for(int i=2; i*i<n; i++){
		if(!prime[i])
			for(int j=i*i; j<n; j+=i)
				prime[j]=1;
	}
	for(int i=0; i<n; i++) if(!prime[i]) p.push_back(i);
}

int combination(int n, int r , int m){
	vector<int> dp(r+1);	
	dp[0] = 1;
	for(int i=1; i<=n; i++)
		for(int j=min(i, r); j>0; j--)
			dp[j] = (dp[j]+dp[j-1])%m;
	return dp[r];
}

/*
What lucas theorem says is... we have to convert n & r in terms of p.
n = (nk)*p^k+...+n1*p^1+n0
similarly with r;
Then compute nkCrk * nk-1Crk-1 *--- so on..
And this nk and rk all are less than prime p so we have limit the use of memory by doing so...
*/
int lucasTheorem(int n, int r, int m){
	if(r==0)
		return 1;
	int a = n%m, b = r%m;
	if(a<b)
		return 0;
	b = (b>(a-b))?(a-b):b; 
	int ans = combination(a, b, m)*lucasTheorem(n/m, r/m, m);
	return ans%m;
}

void print(vector<int> arr){
	for(int i=0; i<arr.size(); i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}

void extendedGcd(int a, int b, int &x, int &y){
	if(a==0){
		x = 0;
		y = 1;
		return;
	}
	int x1, y1;
	extendedGcd(b%a, a, x1, y1);
	x = y1-((b/a)*x1);
	y = x1;
	return;
}

int32_t main(){

	freopen("output.txt", "w", stdout);
	freopen("input.txt", "r", stdin);

	primeCalculate();

	int t;
	cin>>t;
	while(t--){
		int n, r, m, sum=0;
		cin>>n>>r>>m;
		vector<int> factor, arr;
		int j=0, temp = m;
		while(temp!=1){
			while(temp%p[j]!=0){j++;}
			factor.push_back(p[j]);
			temp/=p[j];
		}
		for(int i=0; i<factor.size(); i++){
			arr.push_back(lucasTheorem(n, r, factor[i]));
			int x, y, inv;
			extendedGcd(m/factor[i], factor[i], x, y);
			inv = (x+factor[i])%factor[i];
			sum+=(arr[i]*inv*(m/factor[i]));
			sum%=m;
		}
		cout<<sum<<endl;
	}

}