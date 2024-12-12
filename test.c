int p(int x) {
    if(x < 0) return 0;

    return x + p(x - 1);
}

int main(void) {
    p(10);
    return 0;
}