#include "common.h"

struct Point {
    double x;
    double y;
    Point(double x, double y):x(x), y(y) {}
    Point() = default;
};

double dot(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}

double len(Point& a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

int main() {
    // a = [x1, y1]
    // b = [x2, y2]
    // a*b = |a|*|b|*cos(a*b)
    Point a(sqrt(3), 0), b(sqrt(3), 1);
    cout << dot(a, b) / len(a) / len(b) << endl;
    return 0;
}
