#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <time.h>

#define GIGA_MODIFIER 1e9
#define KILO_MODIFIER 1e3
#define MICRO_MODIFIER 1e-6
#define MAX 10000
#define MIN 1e-18
#define FIVE 5

using namespace std;

double func(int k, int n, int i, int j);
bool read(char *name, double *a, int n);
void right(double const *a, double *b, int n);
void print(int n, int m, double *a, double *b);
bool Rmatrix(int n, double *a, double *R, double *D);
bool determinant(int n, double *R);
void solving(int n, double const *R, double const *b, double *D);
void residual(int n, double const *a, double const *b, double const *D);
void error(int n, double *D);
unsigned long long currentTimeNano();
unsigned long long currentTimeMillis();
