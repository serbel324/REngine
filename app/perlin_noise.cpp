#include "perlin_noise.h"

void PerlinNoise::GenerateRandom(Vec2ui32 size) {
    _size = size + Vec2ui32(1, 1);
    _gradients.Assign(_size);
    for (uint32_t y = 0; y < _size.y; ++y) {
        for (uint32_t x = 0; x < _size.x; ++x) {
            double a = ExtMath::RandomDouble(0, 2 * ExtMath::PI);
            _gradients[x, y] = Vec2d(std::cos(a), std::sin(a));
        }
    }
}

double PerlinNoise::DotProdWithGradient(uint32_t x, uint32_t y, Vec2d point) {
    double x1 = point.x - static_cast<double>(x);
    double y1 = point.y - static_cast<double>(y);
    Vec2d dp = Vec2d(x1, y1);
    Vec2d gradient = _gradients.GetClosest(x, y);
    return dot_prod(dp, gradient);
}

double PerlinNoise::operator()(Vec2d p) {
    uint32_t ix = std::floor(p.x);
    uint32_t iy = std::floor(p.y);
    double p00 = DotProdWithGradient(ix, iy, p);
    double p10 = DotProdWithGradient(ix + 1, iy, p);
    double p01 = DotProdWithGradient(ix, iy + 1, p);
    double p11 = DotProdWithGradient(ix + 1, iy + 1, p);
    return ExtMath::SmootherstepSquare(p00, p10, p01, p11,
            Vec2d(p.x - ix, p.y - iy));
}

void CompositePerlinNoise::GenerateRandom(Settings settings) {
    _settings = settings;

    _layers.resize(_settings.depth);
    for (uint32_t i = 0; i < _settings.depth; ++i) {
        _layers[i].GenerateRandom(_settings.first_layer_size * (1 << i));
    }
}

double CompositePerlinNoise::operator()(Vec2<double> p) {
    double v = 0;
    double ampl_sum = 0;
    for (uint32_t i = 0; i < _settings.depth; ++i) {
        double a = _settings.amplitude_generator ? _settings.amplitude_generator(i) : 1;
        v += _layers[i](p * (1 << i)) * a;
        ampl_sum += a;
    }
    double v_normalized = v / ampl_sum;
    return _settings.transformer_function ? _settings.transformer_function(v_normalized) : v_normalized;
}

