#pragma once

#include <cmath>
#include <concepts>
#include <functional>

using TransformerFunction = std::function<double(double)>;

// f(x) = f1(f2(x))
class Fold {
public:
    Fold(TransformerFunction f1, TransformerFunction f2)
        : _f1(f1)
        , _f2(f2)
    {}

    double operator()(double x) const {
        return _f1(_f2(x));
    }

private:
    TransformerFunction _f1;
    TransformerFunction _f2;
};

// f(x) = exp(x)
class Exponential {
public:
    double operator()(double x) const {
        return std::exp(x);
    }
};

// f(x) = 1 / (1 + exp(-x))
class Sigmoid {
public:
    double operator()(double x) const {
        return 1. / (1 + std::exp(-x));
    }
};

// f(x) = a + b * x
class Linear {
public:
    Linear(double a, double b)
        : _a(a)
        , _b(b)
    {}

    double operator()(double x) const {
        return _a + _b * x;
    }

private:
    double _a;
    double _b;
};
