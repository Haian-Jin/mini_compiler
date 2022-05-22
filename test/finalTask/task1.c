int a[10001];

int QuickSort(int left, int right) {
	if(left >= right) {
        return 0;
    }
    
	int i, j, temp, standard;
	i = left; j = right;
	standard = i;
	while(i != j){
		while((a[j] >= a[standard]) && (j > i))
		j = j -1;
		while((a[i] <= a[standard]) && (i < j))
		i = i + 1;
		if(i != j){
			temp = a[j];
			a[j] = a[i];
			a[i] = temp;
		}
	} 
	if(i == j){
		    temp = a[standard];
			a[standard] = a[j] ;
			a[j] = temp;
	}
	QuickSort(left, i-1);
	QuickSort(i+1, right);
    return 0;
} 


int main(){
    int n;
    scanf("%d", n);
    int i;
    i = 0;
    while(i < n) {
        scanf("%d", a[i]);
        i = i + 1;
    }

    QuickSort(0, n-1);
    i = 0;
    while(i < n){
        printf("%d\n", a[i]);
        i = i + 1;
    }

    return 0;

}
