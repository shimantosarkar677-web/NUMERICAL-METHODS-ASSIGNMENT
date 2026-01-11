#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double MU = 100.0;

struct Vector2 {
    double y1, y2;
};

Vector2 f(Vector2 y) {
    return {
        y.y2,
        MU * (1.0 - y.y1 * y.y1) * y.y2 - y.y1
    };
}
struct Matrix2x2 {
    double a11, a12, a21, a22;
};

Matrix2x2 getJacobian(Vector2 y) {
    return {
        0.0, 1.0,
        -2.0 * MU * y.y1 * y.y2 - 1.0,
        MU * (1.0 - y.y1 * y.y1)

    };
}

Vector2 solveImplicitStep(Vector2 y_n, double h) {
    Vector2 y_next = y_n;
    const int max_iters = 50;
    const double tol = 1e-8;

    for (int i = 0; i < max_iters; ++i) {
        Vector2 func = f(y_next);

        double G1 = y_next.y1 - y_n.y1 - h * func.y1;
        double G2 = y_next.y2 - y_n.y2 - h * func.y2;

        Matrix2x2 Jf = getJacobian(y_next);

        double M11 = 1.0 - h * Jf.a11;

