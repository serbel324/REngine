#pragma once

#include <cmath>
#include <functional>
#include <vector>

#include <library/vec2.h>
#include <library/ext_math.h>

#include "vector_2d.h"
#include "functions.h"

struct PerlinNoise {
public:
    void GenerateRandom(Vec2ui32 size);
    double operator()(Vec2d point);

private:
    double DotProdWithGradient(uint32_t x, uint32_t y, Vec2d point);

private:
    Vector2D<Vec2d> _gradients;
    Vec2ui32 _size;
};

class CompositePerlinNoise {
public:
    using TransformerFunction = std::function<double(double)>;
    using AmplitudeGenerator = std::function<double(size_t)>;

public:
    struct Settings {
        uint32_t depth;
        Vec2ui32 first_layer_size;
        std::function<double(uint32_t)> amplitude_generator;
        std::function<double(double)> transformer_function;
    };

private:

public:
    CompositePerlinNoise() = default;

    void GenerateRandom(Settings settings);
    double operator()(Vec2<double> p);

private:
    Settings _settings;
    std::vector<PerlinNoise> _layers;
};
