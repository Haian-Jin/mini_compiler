int a[1000];


int qsort(int st, int arrN){
    if(arrN<=1) return 0;
    int pivot;
    pivot = a[st];
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
    return 0;
}

int main(){
    // // cin>>arrN;
    int n;
    n = 20;
    int i;
    i = 1;
    while(i<=n){
        // cin>>a[i];
        a[n-i] = i;
        i = i + 1;
    }
    qsort(0,n);
    i = 0;
    while(i<n){
        // cout<<a[i];
        printf("%d ", a[i]);
        i = i + 1;
    }
    return 0;
    // cout<<'\arrN';
}
