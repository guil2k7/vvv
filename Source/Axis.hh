/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#pragma once

#include <Arduino.h>

namespace VVV {

enum AxisMode : uint8_t {
    AXIS_MODE_OFF,
    AXIS_MODE_A,
    AXIS_MODE_B,
};

class Axis {
public:
    constexpr Axis(uint8_t out1Pin, uint8_t out2Pin, uint8_t outLevelPin)
        : m_out1Pin{out1Pin}
        , m_out2Pin{out2Pin}
        , m_outLevelPin{outLevelPin}
        , m_outLevel{0}
        , m_mode{AXIS_MODE_OFF}
    {
    }

    inline void init() {
        pinMode(m_out1Pin, OUTPUT);
        pinMode(m_out2Pin, OUTPUT);
        pinMode(m_outLevelPin, OUTPUT);

        setModeToOff();
        setOutLevel(0);
    }

    inline void setModeToOff() {
        // if (m_mode == AXIS_MODE_OFF)
        //     return;

        digitalWrite(m_out1Pin, LOW);
        digitalWrite(m_out2Pin, LOW);

        m_mode = AXIS_MODE_OFF;
    }

    inline void setModeToA() {
        // if (m_mode == AXIS_MODE_A)
        //     return;

        digitalWrite(m_out1Pin, HIGH);
        digitalWrite(m_out2Pin, LOW);

        m_mode = AXIS_MODE_A;
    }

    inline void setModeToB() {
        // if (m_mode == AXIS_MODE_B)
        //     return;

        digitalWrite(m_out1Pin, LOW);
        digitalWrite(m_out2Pin, HIGH);

        m_mode = AXIS_MODE_B;
    }

    inline void setOutLevel(uint8_t level) {
        // if (m_outLevel == level)
        //     return;

        analogWrite(m_outLevelPin, level);

        m_outLevel = level;
    }

    inline AxisMode mode() const {
        return m_mode;
    }

    inline uint8_t outLevel() const {
        return m_outLevel;
    }

private:
    uint8_t m_out1Pin;
    uint8_t m_out2Pin;
    uint8_t m_outLevelPin;
    uint8_t m_outLevel;
    AxisMode m_mode;
};

} // namespace VVV
