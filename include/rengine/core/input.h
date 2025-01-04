#pragma once

#include <cstdint>
#include <unordered_map>

#include <library/vec2.h>

namespace REngine {

enum KeyCode : uint8_t {
    kA = 0,
    kB,
    kC,
    kD,
    kE,
    kF,
    kG,
    kH,
    kI,
    kJ,
    kK,
    kL,
    kM,
    kN,
    kO,
    kP,
    kQ,
    kR,
    kS,
    kT,
    kU,
    kV,
    kW,
    kX,
    kY,
    kZ,
    k0,
    k1,
    k2,
    k3,
    k4,
    k5,
    k6,
    k7,
    k8,
    k9,
    kLeftShift,
    kRightShift,
    kLeftControl,
    kRightControl,
    kLeftAlt,
    kRightAlt,
    kSpace,
    __KEY_CODE_ITEMS_COUNT__,
};

enum MouseButtonCode : uint8_t {
    kLeftMouseButton = 0,
    kRightMouseButton,
    kMiddleMouseButton,
    kMouseButton4,
    kMouseButton5,
    __MOUSE_BUTTON_ITEMS_COUNT__,
};

class InputController {
public:
    void Init();
    bool IsKeyDown(KeyCode key_code) const;
    bool IsMouseButtonDown(MouseButtonCode mouse_button_code) const;
    Vec2f GetMousePosition() const;

    void SetKeyPosition(KeyCode key_code, bool is_down);
    void SetMouseButtonPosition(MouseButtonCode mouse_button_code, bool is_down);
    void SetMousePosition(float x, float y);
    void SetMousePosition(Vec2f position);

private:
    std::unordered_map<KeyCode, bool> _key_position;
    std::unordered_map<MouseButtonCode, bool> _mouse_button_position;
    Vec2f _mouse_position;
};

} // namespace REngine
