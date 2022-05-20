int a[1000];
int n;

int qsort(int st, int arrN){
    if(arrN<=1)return 0;
    int pivot; pivot = a[st];
    int i; i = 0;
    int j; j = arrN-1;
    int t;
    while(i<j){
        t = a[st+j];
        while(i<j && t>pivot){
            j = j - 1;
        }
        t = a[st+i];
        a[st+i] = a[st+j];
        a[st+j] = t;
        t = a[st+i];
        while(i<j && t<=pivot){
            i = i + 1;
        }
        t = a[st+i];
        a[st+i] = a[st+j];
        a[st+j] = t;
    }
    qsort(st, i);
    qsort(st+i+1, arrN-i-1);
}

int main(){
    // // cin>>arrN;
    int i; i = 0;
    while(i<n){
        // cin>>a[i];
         i = i + 1;
    }
    qsort(0,n);
    i = 0;
    while(i<n){
        // cout<<a[i];
        i = i + 1;
    }
    // cout<<'\arrN';
}
