int main() {
    char a[3][10];
    int i;
    for (i = 0; i < 3; i = i + 1) {
        scanf("%s", a[i]);
    }
    for (i = 0; i < 3; i = i + 1) {
        printf("%s\n", a[2-i]);
    }
    return 0;
}