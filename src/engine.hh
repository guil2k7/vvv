/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#pragma once

namespace vvv {

struct Wheel {
    int dir_pin_a = 0;
    int dir_pin_b = 0;
    int speed_pin = 0;
    int speed = 0;
    int led_pin = 0;
    bool is_moving_backward = false;
};

class Engine {
public:
    constexpr Engine()
        : left_wheel{}, right_wheel{}
        , m_last_x_val{0x7FFF}
        , m_speed{127}, m_is_moving_backward{false} {}

    Wheel left_wheel;
    Wheel right_wheel;

    void setup_pins();
    void reset_wheels();
    void update_speed(int value);
    void update_x_dir(int value);
    void toggle_reverse_mode();

private:
    int m_last_x_val;
    int m_speed;
    bool m_is_moving_backward;

    void update_wheel(Wheel& wheel, int speed, bool to_backward, bool force);
};

} // namespace vvv
