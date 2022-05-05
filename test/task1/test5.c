int main(){
    float a[10][2];
    int i;
    a[5,3] = 1.5; // HINT: this line has NO syntax error! It does have a semantic error because a[5,3] is a pointer but 1.5 is a double.
    a[5,3 = 1.5; // missing ']'
    if(a[1][2] = 0) i = 1 else i = 0;
}
