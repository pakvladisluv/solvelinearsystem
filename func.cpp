
#include "func.h"

double func(int k, int n, int i, int j)
{
    double a;
    if (k == 1) {
        a = n - max(i, j);
    } else if (k == 2) {
        a = max(i, j) + 1;
    } else if (k == 3) {
        a = abs(i - j);
    } else {
        a = 1 / (double)(i + j + 1);
    }
    return a;
}

bool read(char *name, double *a, int n)
{
    ifstream f;
    f.open(name);
    if (!f.is_open()) {
        return false;
    }
    if (f.peek() == EOF) {
        f.close();
        return false;
    }
    ifstream c;
    c.open(name);
    char check;
    c >> check;
    while (!c.eof()) {
        if ((check < '0' || check > '9') && check != '-') {
            c.close();
            return false;
        }
        c >> check;
    }
    c.close();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (f.eof()) {
                return false;
            }
            f >> a[i * n + j];
        }
    }
    f.close();
    return true;
}

void right(double const *a, double *b, int n)
{
    for (int i = 0; i < n; i++) {
        b[i] = 0;
        for (int k = 0; k < (n + 1) / 2; k++) {
            b[i] += a[i * n + 2 * k];
        }
    }
}

void print(int n, int m, double *a, double *b)
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i * n + j] < 0) {
                cout << " " << scientific << setprecision(3) << a[i * n + j];
            } else {
                cout << "  " << scientific << setprecision(3) << a[i * n + j];
            }
        }
        if (b[i] < 0) {
            cout << " " << b[i] << endl;
        } else {
            cout << "  " << b[i] << endl;
        }
    }
}

bool Rmatrix(int n, double *a, double *R, double *D)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            R[i * n + j] = 0;
        }
    }
    R[0] = sqrt(fabs(a[0]));
    if (R[0] < MIN) {
        return false;
    }
    D[0] = a[0] / fabs(a[0]);
    for (int i = 1; i < n; i++) {
        R[i] = a[i] / (R[0] * D[0]);
    }
    for (int i = 1; i < n; i++) {
        R[i * n + i] = a[i * n + i];
        for (int k = 0; k < i; k++) {
            R[i * n + i] -= R[k * n + i] * D[k] * R[k * n + i];
        }
        if (fabs(R[i * n + i]) < MIN) {
            return false;
        }
        D[i] = R[i * n + i] / fabs(R[i * n + i]);
        R[i * n + i] = sqrt(fabs(R[i * n + i]));
        for (int j = i + 1; j < n; j++) {
            R[i * n + j] = a[i * n + j];
            for (int k = 0; k < i; k++) {
                R[i * n + j] -= R[k * n + i] * D[k] * R[k * n + j];
            }
            R[i * n + j] /= R[i * n + i] * D[i];
        }
    }
    return true;
}

bool determinant(int n, double *R)
{
    for (int i = 0; i < n; i++) {
        if (fabs(R[i * n + i]) < MIN) {
            return false;
        }
    }
    return true;
}

void solving(int n, double const *R, double const *b, double *D)
{
    double *X = new double[n];
    X[0] = b[0] / R[0];
    for (int i = 1; i < n; i++) {
        X[i] = b[i];
        for (int j = 0; j < i; j++) {
            X[i] = X[i] - X[j] * R[j * n + i];
        }
        X[i] = X[i] / R[i * n + i];
    }
    for (int i = 0; i < n; i++) {
        if (D[i] < 0) {
            X[i] = -X[i];
        }
    }
    D[n - 1] = X[n - 1] / R[n * n - 1];
    for (int i = n - 2; i >= 0; i--) {
        D[i] = X[i];
        for (int j = i + 1; j < n; j++) {
            D[i] = D[i] - D[j] * R[i * n + j];
        }
        D[i] = D[i] / R[i * n + i];
    }
    delete[] X;
}

void residual(int n, double const *a, double const *b, double const *D)
{
    double *S = new double[n];
    double x = 0;
    for (int i = 0; i < n; i++) {
        S[i] = 0;
        x = x + b[i];
        for (int j = 0; j < n; j++) {
            S[i] = S[i] + a[i * n + j] * D[j];
        }
        S[i] = S[i] - b[i];
        if (i != 0) {
            S[0] = S[0] + S[i];
        }
    }
    x = fabs(S[0] / x);
    delete[] S;
    cout << "Residual: " << x << endl;
}

void error(int n, double *D)
{
    for (int i = 1; i < n; i++) {
        D[0] += D[i];
    }
    n = n / 2;
    cout << "Error: " << fabs(D[0] - n) << endl;
}

unsigned long long currentTimeNano()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long long)(t.tv_sec * GIGA_MODIFIER + t.tv_nsec);
}

unsigned long long currentTimeMillis()
{
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (long long)(t.tv_sec * KILO_MODIFIER + t.tv_nsec * MICRO_MODIFIER);
}
