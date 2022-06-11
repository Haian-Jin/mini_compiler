int main() {
    int a;
    a = 0;
    printf("%d\n", a);
    a++;
    printf("%d\n", a);
    --a;
    printf("%d\n", a);
    int b;
    b = a < 0 ? 2:3;
    printf("%d\n", b);
    return 0;
}