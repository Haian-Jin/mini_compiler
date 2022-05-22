int a[100][100];
int b[100][100];
int c[100][100];

int main() {

    int an, am;
    int bn, bm;
    int cn, cm;
    int t;

    int i, j;
    int x;
    int y;

    scanf("%d %d", an, am);
    i = 0;
    j = 0;
    while (i < an) {
        j = 0;
        while (j < am) {
            scanf("%d", a[i][j]);
            j = j + 1;
        }
        i = i + 1;
    }

    scanf("%d %d", bn, bm);
    if (am != bn) {
        printf("Incompatible Dimensions\n");
        return 0;
    }

    i = 0;
    j = 0;
    while (i < bn) {
        j = 0;
        while (j < bm) {
            scanf("%d", b[i][j]);
            j = j + 1;
        }
        i = i + 1;
    }

    cn = an;
    cm = bm;
    i = 0;
    while (i < cn) {
        j = 0;
        while (j < cm) {
            t = 0;
            x = 0;
            while (x < am) {
                t = t + a[i][x] * b[x][j];
                x = x + 1;
            }
            c[i][j] = t;
            j = j + 1;
        }
        i = i + 1;
    }

    i = 0;
    while (i < cn) {
        j = 0;
        while (j < cm) {
            printf("%10d", c[i][j]);
            j = j + 1;
        }
        printf("\n");
        i = i + 1;
    }
    return 0;
}
