extern int array[];

int *ptr = &array[0];
int sum(int *a, int n) {
    int i, s = 0;

    for (i = 0; i < n; i++) {
        s += a[i];
    }
    return s;
}