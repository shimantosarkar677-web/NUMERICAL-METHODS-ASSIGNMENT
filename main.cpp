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
