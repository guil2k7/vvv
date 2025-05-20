/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#include <Arduino.h>
#include "engine.hh"

using namespace vvv;

void Engine::setup_pins() {
    pinMode(left_wheel.dir_pin_a, OUTPUT);
    pinMode(left_wheel.dir_pin_b, OUTPUT);
    pinMode(left_wheel.speed_pin, OUTPUT);
    pinMode(left_wheel.led_pin, OUTPUT);

    pinMode(right_wheel.dir_pin_a, OUTPUT);
    pinMode(right_wheel.dir_pin_b, OUTPUT);
    pinMode(right_wheel.speed_pin, OUTPUT);
    pinMode(right_wheel.led_pin, OUTPUT);
}

void Engine::reset_wheels() {
    update_wheel(left_wheel, 0, false, true);
    update_wheel(right_wheel, 0, false, true);
}

void Engine::update_speed(int val) {
    update_wheel(left_wheel, static_cast<long>(left_wheel.speed) * val / m_speed, left_wheel.is_moving_backward, false);
    update_wheel(right_wheel, static_cast<long>(right_wheel.speed) * val / m_speed, right_wheel.is_moving_backward, false);

    m_speed = val;
}

void Engine::update_x_dir(int val) {
    if (val == m_last_x_val)
        return;

    if (val == 0) {
        update_wheel(left_wheel, m_speed, left_wheel.is_moving_backward, false);
        update_wheel(right_wheel, m_speed, right_wheel.is_moving_backward, false);

        if (!m_is_moving_backward) {
            digitalWrite(left_wheel.led_pin, LOW);
            digitalWrite(right_wheel.led_pin, LOW);
        }
    } else if (val > 0) {
        update_wheel(left_wheel, m_speed, left_wheel.is_moving_backward, false);

        if (val < 224)
            update_wheel(right_wheel, val * m_speed / 255, right_wheel.is_moving_backward, false);
        else
            update_wheel(right_wheel, 0, right_wheel.is_moving_backward, false);

        if (!m_is_moving_backward) {
            digitalWrite(left_wheel.led_pin, LOW);
            digitalWrite(right_wheel.led_pin, HIGH);
        }
    } else {
        update_wheel(right_wheel, m_speed, right_wheel.is_moving_backward, false);

        if (val > -224)
            update_wheel(left_wheel, val * m_speed / -255, left_wheel.is_moving_backward, false);
        else
            update_wheel(left_wheel, 0, left_wheel.is_moving_backward, false);

        if (!m_is_moving_backward) {
            digitalWrite(left_wheel.led_pin, HIGH);
            digitalWrite(right_wheel.led_pin, LOW);
        }
    }

    m_last_x_val = val;
}

void Engine::toggle_reverse_mode() {
    if (m_is_moving_backward) {
        m_is_moving_backward = false;

        update_wheel(left_wheel, left_wheel.speed, false, false);
        update_wheel(right_wheel, right_wheel.speed, false, false);

        digitalWrite(left_wheel.led_pin, LOW);
        digitalWrite(right_wheel.led_pin, LOW);
    } else {
        m_is_moving_backward = true;

        update_wheel(left_wheel, left_wheel.speed, true, false);
        update_wheel(right_wheel, right_wheel.speed, true, false);

        digitalWrite(left_wheel.led_pin, HIGH);
        digitalWrite(right_wheel.led_pin, HIGH);
    }
}

void Engine::update_wheel(Wheel& wheel, int speed, bool to_backward, bool force) {
    if (speed == 0) {
        if (wheel.speed != 0 || force) {
            digitalWrite(wheel.dir_pin_a, LOW);
            digitalWrite(wheel.dir_pin_b, LOW);
        }
    } else if (wheel.speed == 0 || wheel.is_moving_backward != to_backward || force) {
        if (to_backward) {
            digitalWrite(wheel.dir_pin_a, HIGH);
            digitalWrite(wheel.dir_pin_b, LOW);
        } else {
            digitalWrite(wheel.dir_pin_a, LOW);
            digitalWrite(wheel.dir_pin_b, HIGH);
        }

        wheel.is_moving_backward = to_backward;
    }

    analogWrite(wheel.speed_pin, speed);
    wheel.speed = speed;
}
