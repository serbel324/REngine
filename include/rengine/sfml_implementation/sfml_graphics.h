#pragma once

#include <rengine/core/graphics.h>
#include <SFML/Graphics.hpp>

namespace REngine {

class SFMLGraphics : public Graphics {
public:
    /* requires RenderWindow pointer, Window's dimensions and Camera object pointer (optionally) */
    SFMLGraphics(std::shared_ptr<sf::RenderWindow> win);

    void DrawPoint(Vec2<float> pos, Color color) override;
    void DrawPoint(float x, float y, Color color) override;

    void DrawCircle(float x, float y, float radius, Color fill_color) override;
    void DrawCircle(Vec2<float> pos, float radius, Color fill_color) override;

    void DrawLine(Vec2<float> v1, Vec2<float> v2, Color color) override;
    void DrawLine(float x1, float y1, float x2, float y2, Color color) override;

    void DrawRect(Vec2<float> pos, Vec2<float> size, Color fill_color) override;
    void DrawRect(float x, float y, float w, float h, Color fill_color) override;

    void Fill(Color fill_color) override;
    void Clear() override;

    void BindCamera(Camera::SPtr camera) override;
    void ResetCamera() override;
    void UpdateCameraView() override;

    void Present() override;

    void DrawTexture(const sf::Texture& texture, Vec2f position, Vec2f size);
    void DrawTexture(const sf::Texture& texture, float x, float y, float w, float h);

private:
    void ApplyViewport();

    std::shared_ptr<sf::RenderWindow> _render_window;
    Vec2ui32 _screen_dimensions;
    Camera::SPtr _camera;
};

} // namespace REngine
