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
