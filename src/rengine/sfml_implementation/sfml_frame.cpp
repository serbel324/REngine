#include <rengine/sfml_implementation/sfml_frame.h>
#include <rengine/sfml_implementation/sfml_graphics.h>
#include <rengine/sfml_implementation/sfml_input.h>

namespace REngine {

inline std::shared_ptr<sf::RenderWindow> MakeGenericWindow(Vec2ui32 dimensions,
                                                           std::string name = "App") {
    return std::make_shared<sf::RenderWindow>(sf::VideoMode(dimensions.x, dimensions.y), 
                                              name, sf::Style::Close);
}

SFMLFrame::SFMLFrame(Frame::Settings settings)
    : Frame(settings)
    , _render_window(MakeGenericWindow(settings.screen_size, settings.window_name))
{
    _graphics.reset(new SFMLGraphics(_render_window));
}

void SFMLFrame::PollEvents() {
    sf::Event e;

    while (_render_window->pollEvent(e)) {
        switch (e.type) {
        case sf::Event::Closed:
            _render_window->close();
            _is_running = false;
            break;

        default:
            HandleSFMLEvent(Ic(), e);
            break;
        }
    }
}

} // namespace REngine
