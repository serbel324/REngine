#include <rengine/sfml_implementation/sfml_frame.h>
#include <rengine/sfml_implementation/sfml_graphics.h>
#include <rengine/core/color.h>
#include <library/vec2.h>

#include "vector_2d.h"
#include "perlin_noise.h"

#include <iostream>

Vec2ui32 g_screen_size = Vec2ui32{3600, 1800};

class ExampleFrame : public REngine::SFMLFrame {
public:
    ExampleFrame()
        : SFMLFrame(
            Frame::Settings{
                .screen_size = g_screen_size,
                .window_name = "MainFrame",
            })
    {}

    virtual void Initialize() override {
        std::cout << "Initialize Frame" << std::endl;
        _height.Assign(_screen_size);
        _noise_size = _screen_size / _cell_size;

        Vec2ui32 noise_first_layer_size(10, 10);
        uint32_t depth = 5;
        CompositePerlinNoise noise;
        noise.GenerateRandom(
            CompositePerlinNoise::Settings{
                .depth = depth,
                .first_layer_size = noise_first_layer_size,
                .amplitude_generator = Fold(Exponential{}, Linear(depth, -1)),
                .transformer_function = Fold(Sigmoid{}, Linear(0, 3)),
            }
        );

        sf::Image noise_image;
        noise_image.create(_noise_size.x, _noise_size.y);

        for (uint32_t y = 0; y < _noise_size.y; ++y) {
            for (uint32_t x = 0; x < _noise_size.x; ++x) {
                Vec2d point(x, y);
                point = point / _noise_size * noise_first_layer_size;
                _height[x, y] = noise(point);
                double c = _height[x, y] * 256;
                noise_image.setPixel(x, y, sf::Color(c, c, c, 255));
            }
        }
        _prerendered_noise.loadFromImage(noise_image, sf::IntRect(0, 0, _noise_size.x, _noise_size.y));
    }

    bool Update(float elapsed_sec) override {
        sf::Image noise_image;
        noise_image.create(_noise_size.x, _noise_size.y);
        for (uint32_t y = 0; y < _noise_size.y; ++y) {
            for (uint32_t x = 0; x < _noise_size.x; ++x) {
                double c = _height[x, y] * 256;
                noise_image.setPixel(x, y, sf::Color(c, c, c, 255));
            }
        }
        _prerendered_noise.loadFromImage(noise_image, sf::IntRect(0, 0, _noise_size.x, _noise_size.y));
        return Frame::Update(elapsed_sec);
    }

    void Render() override {
        REngine::SFMLGraphics* gr = dynamic_cast<REngine::SFMLGraphics*>(Gr());
        gr->Clear();
        // TODO: better texture drawing

        gr->DrawTexture(_prerendered_noise, Vec2f(0, 0), _screen_size);
        gr->DrawCircle(Ic()->GetMousePosition(), 10, REngine::Color::BLACK);
        Frame::Render();
    }

private:
    Vec2ui32 _noise_first_layer_size;
    Vec2ui32 _screen_size = g_screen_size;
    Vec2ui32 _noise_size;
    uint32_t _cell_size = 4;
    Vector2D<double> _height;
    sf::Texture _prerendered_noise;
};
