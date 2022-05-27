char course_name[101][7];
char course_need[100][7][7][7];
int courseNsize[100][7];
int course_com[100];
int main() {
    int i;
    i = 0;
    int com;
    com = 0;
    char se;
    int all;
    all = 0;
    int get;
    get = 0;
    int try;
    try = 0;
    int ptn;
    ptn = 0;
    scanf("%[^|,;\n]", course_name[i]);
    scanf("%c", se);
    while(se!=10) {
        int cre;
        scanf("%d", cre);
        scanf("%c", se);
        all = all + cre;
        int m, n;
        m = 0;
        n = 0;
        scanf("%[^,;|\n]", course_need[i][m][n]);
        scanf("%c", se);

        for (m=0; se!=124 ; scanf("%c", se)) {
            if (se==44) {
                n=n+1;
            }
            if (se==59) {
                courseNsize[i][m] = n+1;
                n = 0;
                m=m+1;
            }
            scanf("%[^,;|\n]", course_need[i][m][n]);
        }
        courseNsize[i][m] = n+1;
        scanf("%c", se);
        if (se == 10) {
            scanf("%[^,;|\n]", course_name[i+1]);
            scanf("%c", se);
        }
        else {
            if (se == 70) {
                try = try + cre;
            }
            if (se <= 68 && se >= 65) {
                try = try + cre;
                get = get + cre;
                course_com[i] = 1;
                ptn = ptn + cre * (69 - se);
            }
            scanf("%c", se);
            scanf("%[^,;|\n]", course_name[i+1]);
            scanf("%c", se);
        }
        i=i+1;
    }
    printf("GPA: %.1f\n", (ptn*1.0)/(try+0.0001));
    printf("Hours Attempted: %d\n", try);
    printf("Hours Completed: %d\n", get);
    printf("Credits Remaining: %d\n", all-get);
    printf("\nPossible Courses to Take Next\n");
    if(all-get==0) {
        printf("  None - Congratulations!\n");
    } else {
        for (com = 0; com < i; com = com + 1) {
            if (course_com[com]==0) {
                int j;
                int needCal;
                needCal = 1;
                for (j = 0; courseNsize[com][j]!=0&&j<7; j= j + 1) {
                    if(needCal!=0) {
                        int canTake;
                        canTake = 1;
                        int k;
                        for (k = 0; k < courseNsize[com][j]; k = k + 1) {
                            if (course_need[com][j][k][0] == 0) {
                                canTake = canTake * 1;
                            } else {
                                int flag;
                                flag = 0;
                                int ttt;
                                for (ttt = 0; ttt < i; ttt = ttt + 1) {
                                    if ((course_name[ttt]==course_need[com][j][k]) && (course_com[ttt] != 0)) {
                                        flag = 1;
                                    }
                                }
                                canTake = canTake * flag;
                            }
                        }
                        if(canTake) {
                            printf("  %s\n", course_name[com]);
                            needCal = 0;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

