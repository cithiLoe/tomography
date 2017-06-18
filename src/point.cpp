#include <iostream>
#include <cmath>

#include "point.h"

point::point(const double x, const double y, const double z) {
    R[0] = x;
    R[1] = y;
    R[2] = z;
}

double point::length() const {
    return sqrt(R[0] * R[0] + R[1] * R[1] + R[2] * R[2]);
}

double point::length_squared() const {
    return R[0] * R[0] + R[1] * R[1] + R[2] * R[2];
}

double point::radius_squared() const {
    return R[0] * R[0] + R[1] * R[1];
}

point operator + (const point& a, const point& b) {
    point c;
    for (int i = 0; i < 3; ++i) {
        c.R[i] = a.R[i] + b.R[i];
    }
    return c;
}

point operator - (const point& a, const point& b) {
    point c;
    for (int i = 0; i < 3; ++i) {
        c.R[i] = a.R[i] - b.R[i];
    }
    return c;
}

double operator * (const point& a, const point& b) {
    return a.R[0] * b.R[0] + a.R[1] * b.R[1] + a.R[2] * b.R[2];
}

point operator * (const point& a, const double& b) {
    point c;
    for (int i = 0; i < 3; ++i) {
        c.R[i] = a.R[i] * b;
    }
    return c;
}

point operator * (const double& a, const point& b) {
    point c;
    for (int i = 0; i < 3; ++i) {
        c.R[i] = a * b.R[i];
    }
    return c;
}

point operator / (const point& a, const double& b) {
    point c;
    for (int i = 0; i < 3; ++i) {
        c.R[i] = a.R[i] / b;
    }
    return c;
}

std::ostream& operator << (std::ostream& out, point& a) {
    out << a.R[0] << " " << a.R[1] << " " << a.R[2];
    return out;
}

std::istream& operator >> (std::istream& in, point& a) {
    in >> a.R[0] >> a.R[1] >> a.R[2];
    return in;
}