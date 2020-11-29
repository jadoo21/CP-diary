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
//Storing Big size integer using array.
#include<iostream>
using namespace std;

int N = 1e5;	//array ka size h ye.. kch jyada bada le lia h lag rha...
int arr[100001]={0}, size=0;// size array ka size dhyan me rkhega kitna bada h...

int maximum(int a, int b){
	return (a>b)?a:b; // ye aise hi h.. array ka size badhta rhega carry k saath saath us par nazar rkhne k lie...
}

void print(int arr[]){
	int i=size-1;
	while(arr[i]==0){i--;}
	while(i>=0)
		cout<<arr[i--]<<" "; // ye array print karane k lie...
	cout<<endl;
}

void multiply(int n){
	int ones[N]={0}, tens[N]={0};
	/*
	For Example
		6 8 4 0	our previous arr
	  *     1 7 number we have to multiply... ten = 1, one = 7
	  ----------
	  6 1 8 8 0 this will going to store in ones 
	  6 8 4 0 X this will going to store in tens
	  ----------
	 1 1 6 2 8 0 and then in last we sum up and all this in arr again and this will become our new array...
	*/
	int one = n%10, ten = n/10, i=0, carry=0;
	while(i<size){	// this will multiply 6840 with 7-one
		int a = (arr[i]*one)+carry;
		ones[i] = a%10;
		carry = a/10;
		i++;
	}
	while(carry!=0){ // this is handling carry after multiplying like 6 in this example...
		ones[i++] = carry%10;
		carry/=10;
	}
	size = maximum(size, i); // if i is greater than size it means our array size got increased that's why we will replace it with.
	i=0; carry=0;
	while(i<size){ // this will multiply 6840 with 1-ten
		int a = (arr[i]*ten)+carry;
		tens[i] = a%10;
		carry = a/10;
		i++;
	}
	while(carry!=0){ //Similarly handling its carry also.. 
		tens[i++] = carry%10;
		carry/=10;
	}
	size = maximum(size, i); // similarly handling size...
	arr[0] = ones[0];
	i=1;carry=0;
	while(i<size){	//Now finally we will add ones and tens but remember tens will decrease by one... think about it why??
		if(ones[i]==-1)
			ones[i]=0;
		int a = ones[i]+tens[i-1]+carry;
		arr[i] = a%10;
		carry = a/10;
		i++;
	}
	while(carry!=0){	// remaining all the process is similar///
		arr[i++] = carry%10;
		carry/=10;
	}
	size = maximum(size, i);
	// Hope you have understand it all.... 
}

int main(){
	int n = 20, temp = n, i=0;
	while(temp!=0){	// In this we are inserting our n in arr.
		arr[i++] = temp%10;
		temp/=10;
		size++;
	}
	for(int i=n-1; i>1; i--){
		multiply(i);	// multiplying our arr everytime with number less than 1.
	}
	print(arr);// This will print our array....
}