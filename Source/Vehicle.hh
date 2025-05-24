/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#pragma once

#include "Axis.hh"

namespace VVV {

class Vehicle {
public:
    constexpr Vehicle(Axis const& frontAxis, Axis const& backAxis)
        : m_frontAxis{frontAxis}, m_backAxis{backAxis}
        , m_isReversing{false}
    {
    }

    inline void init() {
        m_frontAxis.init();
        m_backAxis.init();
    }

    inline void setSpeed(int newSpeed) {
        m_backAxis.setOutLevel(newSpeed);
    }

    inline void setDirection(int value) {
        if (value == 0)
            m_frontAxis.setModeToOff();
        else if (value < 0)
            m_frontAxis.setModeToA();
        else
            m_frontAxis.setModeToB();
    }

    inline void toggleReverseMode() {
        m_isReversing = !m_isReversing;

        if (m_isReversing)
            m_backAxis.setModeToB();
        else
            m_backAxis.setModeToA();
    }

    inline bool isReversing() const {
        return m_isReversing;
    }

private:
    Axis m_frontAxis;
    Axis m_backAxis;
    bool m_isReversing;
};

} // namespace VVV
