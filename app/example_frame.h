#include <rengine/sfml_implementation/sfml_frame.h>
#include <rengine/core/color.h>

#include <iostream>

Vec2ui32 g_screen_size = Vec2ui32{800, 800};

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
    }

    void Render() override {
        REngine::Graphics* gr = Gr();
        // gr->Clear();
        gr->Fill(REngine::Color::WHITE);
        gr->DrawCircle(Ic()->GetMousePosition(), 10, REngine::Color::RED);
        Frame::Render();
    }
};
