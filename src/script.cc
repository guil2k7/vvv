/*----------------------------------------------------------------*
 * Copyright 2025 Maicol Castro <maicolcastro.abc@gmail.com>.
 * Distributed under the MIT License.
 * See LICENSE.txt in the root directory of this project or at
 * https://opensource.org/license/mit.
 *----------------------------------------------------------------*/

#include <Arduino.h>
#include "script.hh"

using namespace vvv;
using namespace vvv::engine_script;

void ScriptRunner::process() {
    if (millis() < m_pause_end_ts)
        return;

    Instruction instr;

    for (;;) {
        if (m_ip >= m_code_len)
            break;

        instr = m_code[m_ip++];

        switch (instr.opcode) {
            case OPCODE_WAIT:
                m_pause_end_ts = millis() + instr.imm_u;
                break;

            case OPCODE_UPDATE_X_DIR:
                m_engine->update_x_dir(instr.imm_s);
                continue;

            case OPCODE_UPDATE_SPEED:
                m_engine->update_speed(instr.imm_u);
                continue;

            case OPCODE_TOGGLE_REVERSE_MODE:
                m_engine->toggle_reverse_mode();
                continue;
        }

        break;
    }
}
