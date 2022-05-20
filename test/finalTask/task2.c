int a[100][100];
int b[100][100];
int c[100][100];
int an;
int am;
int bn;
int bm;
int cn;
int cm;
int t;

int main(){
    //cin>>an;cin>>am;
    int i; i=0;
    int j; j=0;
    int x;
    int y;
    while(i<an){
        j=0;
        while(j<am){
            //cin>>a[i][j];
            j=j+1;
        }
        i=i+1;
    }

    //cin>>bn;cin>>bm;
    i=0;
    j=0;
    while(i<bn){
        j=0;
        while(j<bm){
            //cin>>b[i][j];
            j=j+1;
        }
        i=i+1;
    }

    cn = an;
    cm = bm;
    i=0;
    while(i<cn){
        j=0;
        while(j<cm){
            t=0;
            x=0;
            while(x<am){
                t = t + a[i][x]*b[x][j];
            x=x+1;}
            c[i][j]=t;
        j=j+1;}
    i=i+1;}

    i=0;
    while(i<cn){
        j=0;
        while(j<cm){
            //cout<<c[i][j]<<' ';
        j=j+1;}
        //cout<<'\n';
    i=i+1;}
}
