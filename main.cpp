#include "func.h"

int main(int argc, char *argv[])
{
    if (argc < 4 || argc > FIVE) {
        cout << "incorrect arguments" << endl;
        return -1;
    }
    unsigned long long time = 0;
    time = currentTimeNano();
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    int k = atoi(argv[3]);
    char *name = argv[4];
    if (k == 0 && argc <= 4) {
        return -1;
    }
    if (n < 1 || m < 1 || k < 0 || k > 4 || n < m) {
        return -1;
    }
    if (n > MAX) {
        return -2;
    }
    double *a = new double[n * n];
    double *R = new double[n * n];
    if (k == 0) {
        if (!read(name, a, n)) {
            delete[] a;
            delete[] R;
            return -3;
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i * n + j] = func(k, n, i, j);
                R[i * n + j] = 0;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(a[i * n + j] - a[j * n + i]) > MIN) {
                delete[] a;
                delete[] R;
                return -4;
            }
        }
    }
    double *b = new double[n];
    right(a, b, n);
    print(n, m, a, b);
    cout << endl;
    ;
    if (k == 3) {
        delete[] a;
        delete[] R;
        delete[] b;
        return 0;
    }
    double *D = new double[n];
    for (int i = 0; i < n; i++) {
        D[i] = 0;
    }
    if (!Rmatrix(n, a, R, D)) {
        delete[] a;
        delete[] b;
        delete[] R;
        delete[] D;
        return -4;
    }
    if (!determinant(n, R)) {
        delete[] a;
        delete[] b;
        delete[] R;
        delete[] D;
        return -4;
    }
    print(n, m, R, b);
    cout << endl;
    solving(n, R, b, D);
    cout << "Solution:";
    for (int i = 0; i < m; i++) {
        cout << ' ' << D[i];
    }
    cout << endl;
    time = currentTimeNano() - time;
    cout << "Time: " << time << endl;
    residual(n, a, b, D);
    error(n, D);
    delete[] a;
    delete[] b;
    delete[] R;
    delete[] D;
    return 0;
}
