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
#include<bits/stdc++.h>
using namespace std;

#define w(t)    int t; cin>>t; while(t--)
#define in(n)   int n; cin>>n

unordered_map<int, unordered_map<int, int>> dict;

int count(int egg, int floor){

    if(dict[egg][floor])
        return dict[egg][floor];

    //These are some base cases...
    if(egg==0 || floor==0)
        return 0;
    if(floor==1)
        return 1;
    if(egg==1)
        return floor;

    int ans =INT_MAX;
    for(int k=1; k<=floor; k++){
        ans = min(ans, max(count(egg, floor-k), count(egg-1, k-1)));
    }

    dict[egg][floor] = ans+1;
    return dict[egg][floor];
}

int32_t main() {

	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

    w(t){
        in(n); in(k);
        cout<<count(n, k)<<endl;
    }
}
