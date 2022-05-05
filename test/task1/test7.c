int a,b,c[100];
double d,e,f[100];
int fun(int a1,double a2){
    return c;// return type error
}
int a;// re-definition
struct S{
    int sa,sb;
};
struct T{
    int b;
    int b;// re-definition
    int a;
};
struct S S;// re-definition
struct S s,y;
struct UT o;// undefined struct type name
double fun(int a){// re-definition
    return;// return type mismatch
}
void funStruct(struct S a, struct T b){
    return a;// return type mismatch
}
double returnmismatchfunction(){
    a+b;
    return s;// return type mismatch
}
int main(){
    a=b+ut;// undefined variable
    ufun();// undefined variable
    a=s;// type mismatch
    a+c;// type mismatch
    c+f;// type mismatch(unsupported operation)
    s-y;// type mismatch
    fun(a);// argument number mismatch
    fun(a,a,a);// argument number mismatch
    fun(s,y);// argument type mismatch
    a[10];
    a[1][1][1];// too many []'s
    b();// not a function
    b(a);// not a function
    c[1.5];// type mismatch (for operator[])
    c[1];
    c[1][1];// top many []'s
    a.sa;// not a struct
    s.sc;// undefined member
    funStruct(s,y);// argument type mismatch 
    return a+b;
}
