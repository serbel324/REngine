#include <rengine/sfml_implementation/sfml_graphics.h>
#include <library/ext_math.h>

namespace REngine {

SFMLGraphics::SFMLGraphics(std::shared_ptr<sf::RenderWindow> win)
    : _render_window(win)
    , _screen_dimensions(_render_window->getSize().x, _render_window->getSize().y) {   
}

void SFMLGraphics::DrawPoint(Vec2<float> pos, Color color) {
    DrawPoint(pos.x, pos.y, color);
}

void SFMLGraphics::DrawPoint(float x, float y, Color color) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(1, 1));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    _render_window->draw(rectangle);
}

void SFMLGraphics::DrawCircle(float x, float y, float radius, Color fill_color) {
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setPosition(x - radius, y - radius);
    circle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    _render_window->draw(circle);
}

void SFMLGraphics::DrawCircle(Vec2<float> pos, float radius, Color fill_color) {
    DrawCircle(pos.x, pos.y, radius, fill_color);
}

void SFMLGraphics::DrawLine(float x1, float y1, float x2, float y2, Color color) {
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(x1, y1), sf::Color(color.r, color.g, color.b, color.a)),
        sf::Vertex(sf::Vector2f(x2, y2), sf::Color(color.r, color.g, color.b, color.a))
    };

    _render_window->draw(line, 2, sf::Lines);
}

void SFMLGraphics::DrawLine(Vec2<float> v1, Vec2<float> v2, Color color) {
    DrawLine(v1.x, v1.y, v2.x, v2.y, color);
}

void SFMLGraphics::DrawRect(float x, float y, float w, float h, Color fill_color) {
    sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w, h));
    rectangle.setPosition(x, y);
    rectangle.setFillColor(sf::Color(fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    _render_window->draw(rectangle);
}

void SFMLGraphics::DrawRect(Vec2<float> pos, Vec2<float> size, Color fill_color) {
    DrawRect(pos.x, pos.y, size.x, size.y, fill_color);
}

void SFMLGraphics::Fill(Color fill_color) {
    Camera::SPtr camera0 = _camera;
    ResetCamera();
    DrawRect(0, 0, _render_window->getSize().x, _render_window->getSize().y, fill_color);
    BindCamera(camera0);
}

void SFMLGraphics::Clear() {
    _render_window->clear();
}

void SFMLGraphics::BindCamera(Camera::SPtr camera) {
    _camera = camera;
    UpdateCameraView();
}

void SFMLGraphics::UpdateCameraView() {
    sf::View view;
    Vec2f camera_position = _camera ? _camera->GetPosition() : Vec2f{0, 0};
    Vec2f camera_scale = _camera ? _camera->GetScale() : Vec2f{1, 1};
    float camera_angle = _camera ? ExtMath::ToDegrees(_camera->GetAngleRad()) : 0;

    Vec2f s = _screen_dimensions * camera_scale;

    view.reset(sf::FloatRect(camera_position.x, camera_position.y, s.x, s.y));
    view.rotate(camera_angle);
    view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    _render_window->setView(view);
}

void SFMLGraphics::ResetCamera() {
    _camera.reset();
}

void SFMLGraphics::Present() {
    _render_window->display();
}

void SFMLGraphics::DrawTexture(const sf::Texture& texture, Vec2f position, Vec2f size) {
    DrawTexture(texture, position.x, position.y, size.x, size.y);
}

void SFMLGraphics::DrawTexture(const sf::Texture& texture, float x, float y, float w, float h) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(x - w / 2, y - h / 2);

    sf::Vector2u s = texture.getSize();
    sprite.setScale(w / s.x, h / s.y);
    _render_window->draw(sprite);
}

} // namespace REngine
