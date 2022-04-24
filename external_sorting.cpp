#include <bits/stdc++.h>
using namespace std;
#define inf 10000

int n_buffer;
int size;
int* records;

void k_merge(int* arr, int s, int* mid, int e, int k){
    int n=e+1-s;
    if(n<=0)return;
    int tmp[n];
    int ptr[k];
    ptr[0]=s;
    for(int j=1;j<k;j++){
        ptr[j]=mid[j-1]+1;
    }
    int i=0;
    while(i<n){
        int min=inf;
        int x=-1;
        for(int j=0;j<k-1;j++){
            if(ptr[j]<=mid[j]){
                if(arr[ptr[j]]<min){
                    x=j;
                    min=arr[ptr[j]];
                }
            }
        }
        if(ptr[k-1]<=e){
            if(arr[ptr[k-1]]<min){
                x=k-1;
                min=arr[ptr[k-1]];
            }
        }
        ptr[x]++;
        tmp[i]=min;
        i++;
    }
    int j=0;
    for(int p=s;p<=e;p++){
        arr[p]=tmp[j];
        j++;
    }
}

void k_merge_sort(int* arr, int start, int end, int k){
    
    int n=end-start+1;
    int n_pg=n/size+(n%size==0?0:1);
    if(n_pg<=k){
        int k2=n_pg;
        int m[k2-1];
        for(int i=1;i<k2;i++){
            m[i-1]=start+i*size-1;
        }
        k_merge(arr,start, m, end, k2);
        return;
    }
    int x=n_pg/k+(n_pg%k==0?0:1);
    int m[k-1];
    int y=start;
    for(int i=1;i<k;i++){
        if(n_pg%k!=0 && i-1==n_pg%k){
            x--;
        }
        y+=x*size;
        m[i-1]=y-1;
    }
    k_merge_sort(arr, start, m[0], k);

    for (int i = 0; i < k-2; i++){
        k_merge_sort(arr, m[i]+1, m[i+1], k );
    }

    k_merge_sort(arr, m[k-2]+1, end, k);
    k_merge(arr, start, m, end, k);

}


int main(){

    cin>>n_buffer>>size;

    int n;cin>>n;

    int n_pg=n/size+(n%size==0?0:1);

    records=new int[n];
    
   for (int i = 0; i < n; i++){
        cin>>records[i];
    }

    
    int j=0;
    
    for(;j<n-size;j+=size){
        sort(records+j,records+j+size);
    }
    sort(records+j,records+n);


    int k=n_buffer-1;

    k_merge_sort(records,0,n-1,k);

    for (int i = 0; i < n; i++){
        cout<<records[i]<<endl;
    }

    return 0; 
}
