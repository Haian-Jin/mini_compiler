struct a{
    int b;
    double k;
};
int main(){
    struct a ss;
    ss.k = 3.2;
    ss.b = 1;
    printf("%d %lf\n", ss.b, ss.k);
    return 0;
}

