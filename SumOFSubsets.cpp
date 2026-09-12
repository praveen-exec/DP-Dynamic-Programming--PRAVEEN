//Recursion
#include<iostream>
using namespace std;

bool isSOS(int set[],int sum,int n){

    if(sum==0) 
     return true;

    if(n==0)
     return false;

    //Majboori --> Exclude
    if(set[n-1] > sum)
     return isSOS(set,sum,n-1);

    return isSOS(set,sum,n-1) || isSOS(set,sum-set[n-1],n-1);
}

int main(){
    int sum;
    cout<<"Enter the value of Sum : ";
    cin>>sum;
    int set[]={1,2,3,4};
    
    //size of set = n
    int n=sizeof(set)/sizeof(set[0]);


    cout<<"Sum of Subsets Possible or Not ? "<<endl;
    if(isSOS(set,sum,n))
     cout<<"Yes!";
    else
     cout<<"No";
    
    return 0;
}


//DP --> Memorization
#include<iostream>
using namespace std;
vector<vector<int>> dp;
bool isSOS(int set[],int sum,int n,vector<vector<int>>& dp){

    if(sum==0) 
     return true;

    if(n==0)
     return false;


    //check in dp
    if(dp[n][sum] != -1) 
      return dp[n][sum];


    //Majboori --> Exclude
    if(set[n-1] > sum)
     return dp[n][sum] = isSOS(set,sum,n-1,dp);

    //Not Take or Take
    dp[n][sum] = isSOS(set,sum,n-1,dp) || isSOS(set,sum-set[n-1],n-1,dp);

    return dp[n][sum];
}

int main(){
    int sum;
    cout<<"Enter the value of Sum : ";
    cin>>sum;
    int set[]={1,2,3,4};
    
    //size of set = n
    int n=sizeof(set)/sizeof(set[0]);

    dp.resize(n + 1,vector<int>(sum + 1,-1));


    cout<<"Sum of Subsets Possible or Not ? "<<endl;
    if(isSOS(set,sum,n,dp))
     cout<<"Yes!";
    else
     cout<<"No";
    
    return 0;
}


//DP --> Bottom Up
#include<iostream>
using namespace std;
vector<vector<int>> dp;
bool isSOS(int set[],int sum,int n,vector<vector<int>>& dp)
{

     //if sum = 0 && n != 0 --> true
    for(int i=0;i<=n;i++)
     dp[i][0] = true;
    
    //if n = 0  && sum != 0 --> false
    for(int j=1;j<=sum;j++)
     dp[0][j] = false;


    for(int i=1 ; i<=n ;i++)
    {
        for(int j=1; j<=sum ;j++)
        {
          //Majboori
          if(set[i-1] > j)
           dp[i][j] = dp[i-1][j];
           else
           dp[i][j] = dp[i-1][j] || dp[i-1][j-set[i-1]];
        }
    }
    return dp[n][sum];

}


int main(){
    int sum;
    cout<<"Enter the value of Sum : ";
    cin>>sum;
    int set[]={1,2,3,4};
    
    //size of set = n
    int n=sizeof(set)/sizeof(set[0]);

    dp.resize(n + 1,vector<int>(sum + 1));


    cout<<"Sum of Subsets Possible or Not ? "<<endl;
    if(isSOS(set,sum,n,dp))
     cout<<"Yes!";
    else
     cout<<"No";
    
    return 0;
}