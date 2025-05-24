/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#include <Arduino.h>
#include "Script.hh"

using namespace VVV;

void ScriptRunner::process() {
    if (millis() < m_pauseEndTs)
        return;

    Instruction inst;

    while (m_ip < m_codeLength) {
        inst = m_code[m_ip++];

        switch (inst.opcode) {
            case OPCODE_WAIT:
                m_pauseEndTs = millis() + inst.immU;
                break;

            case OPCODE_SET_DIRECTION:
                vehicle->setDirection(inst.immS);
                continue;

            case OPCODE_SET_SPEED:
                vehicle->setSpeed(inst.immU);
                continue;

            case OPCODE_TOGGLE_REVERSE_MODE:
                vehicle->toggleReverseMode();
                continue;
        }

        break;
    }
}
