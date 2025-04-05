#pragma once

#include <memory>
#include <string>

#include <rengine/core/graphics.h>
#include <rengine/core/input.h>
#include <library/utils.h>
#include <library/vec2.h>

namespace REngine {

class Frame : public SmartPointerAliases<Frame> {
public:
    struct Settings {
        Vec2ui32 screen_size = Vec2ui32{1600, 900};
        std::string window_name = "Frame";
    };

public:
    Frame(Settings settings);

    virtual void Initialize();
    virtual bool Update(float elapsed_sec);
    virtual void Render();
    virtual void PollEvents();

    virtual ~Frame() = default;

protected:
    Graphics* Gr();
    InputController* Ic();

    bool IsRunning() const;

protected:
    const Settings _settings;

protected:
    std::shared_ptr<Graphics> _graphics;
    std::shared_ptr<InputController> _input_controller;

    bool _is_running;
};

} // namespace REngine
