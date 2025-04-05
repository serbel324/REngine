#include <rengine/core/driver.h>

#include <cassert>
#include <chrono>
#include <ctime>
#include <thread>
#include <utility>

namespace REngine {

Driver::Driver(Frame::UPtr&& frame, Settings settings)
    : _frame(std::forward<Frame::UPtr>(frame))
    , _settings(settings) {
}

void Driver::RunFrame() {
    using SystemClock = std::chrono::system_clock;
    using Timestamp = std::chrono::time_point<SystemClock>;
    Timestamp start_time = SystemClock::now();

    _frame->Initialize();

    while (true) {
        Timestamp current_time = SystemClock::now();
        int64_t elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(current_time - start_time).count();
        float elapsed_sec = 0.001 * 0.001 * elapsed_us;
        if (_settings.minimum_update_delay_sec > elapsed_sec) {
            int64_t us_to_sleep = std::max((int64_t)0, (int64_t)std::round(_settings.minimum_update_delay_sec) * 1'000'000 - elapsed_us);
            std::this_thread::sleep_for(std::chrono::microseconds(us_to_sleep));
            elapsed_sec = _settings.minimum_update_delay_sec;
        }
        start_time = SystemClock::now();

        if (!_frame->Update(elapsed_sec)) {
            break;
        }
        _frame->Render();
    }
}

} // namespace REngine